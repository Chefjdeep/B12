import ast

# ============================================================
# Python → C-like IR lifter (malware-analysis oriented)
# FIX: restores if/else, for, while emission
# ============================================================

def _indent(n):
    return "    " * n


def _safe(fn):
    def wrapper(*args, **kwargs):
        try:
            return fn(*args, **kwargs)
        except Exception:
            return "/* error */"
    return wrapper


def infer_type(node):
    if isinstance(node, ast.Constant):
        if isinstance(node.value, int):
            return "int"
        if isinstance(node.value, float):
            return "double"
        if isinstance(node.value, str):
            return "char *"
    return "void *"


class _PyToC(ast.NodeVisitor):
    def __init__(self):
        self.structs = []
        self.functions = []
        self.main_body = []
        self.classes = {}
        self.locals = set()
        self.current_class = None

    # ---------------- Expressions ----------------

    @_safe
    def expr(self, node):
        if node is None:
            return ""

        # ---------------- Names & constants ----------------

        if isinstance(node, ast.Name):
            return node.id

        if isinstance(node, ast.Constant):
            if node.value is None:
                return "NULL"
            if isinstance(node.value, str):
                return f'"{node.value}"'
            return str(node.value)

        # ---------------- Attribute chains ----------------
        # os.path.exists → os->path->exists

        if isinstance(node, ast.Attribute):
            parts = []
            cur = node
            while isinstance(cur, ast.Attribute):
                parts.append(cur.attr)
                cur = cur.value
            if isinstance(cur, ast.Name):
                parts.append(cur.id)
            return "->".join(reversed(parts))

        # ---------------- Calls ----------------

        if isinstance(node, ast.Call):
            return self.call(node)

        # ---------------- Unary ops ----------------
        # not x → !(x)

        if isinstance(node, ast.UnaryOp):
            if isinstance(node.op, ast.Not):
                return f"!({self.expr(node.operand)})"
            if isinstance(node.op, ast.USub):
                return f"-({self.expr(node.operand)})"
            return self.expr(node.operand)

        # ---------------- Binary ops ----------------

        if isinstance(node, ast.BinOp):
            return f"({self.expr(node.left)} {self.op(node.op)} {self.expr(node.right)})"

        # ---------------- Boolean ops ----------------
        # a and b → a && b

        if isinstance(node, ast.BoolOp):
            op = "&&" if isinstance(node.op, ast.And) else "||"
            return "(" + f" {op} ".join(self.expr(v) for v in node.values) + ")"

        # ---------------- Comparisons ----------------
        # x is None → x == NULL

        if isinstance(node, ast.Compare):
            parts = []
            left = self.expr(node.left)
            for op, right in zip(node.ops, node.comparators):
                parts.append(f"{left} {self.op(op)} {self.expr(right)}")
                left = self.expr(right)
            return "(" + " && ".join(parts) + ")"

        # ---------------- Subscripts ----------------
        # a[b] → a[b]

        if isinstance(node, ast.Subscript):
            return f"{self.expr(node.value)}[{self.expr(node.slice)}]"

        # ---------------- f-strings ----------------
        # f"x {y}" → "x %s"

        if isinstance(node, ast.JoinedStr):
            out = []
            for v in node.values:
                if isinstance(v, ast.Constant):
                    out.append(str(v.value))
                elif isinstance(v, ast.FormattedValue):
                    out.append("%s")
            return f'"{"".join(out)}"'

        # ---------------- Ternary ----------------
        # a if b else c → (b ? a : c)

        if isinstance(node, ast.IfExp):
            return f"({self.expr(node.test)} ? {self.expr(node.body)} : {self.expr(node.orelse)})"

        # ---------------- Fallback ----------------

        return "/* expr */"


    def op(self, op):
        return {
            ast.Add: "+", ast.Sub: "-", ast.Mult: "*", ast.Div: "/",
            ast.Mod: "%", ast.Eq: "==", ast.NotEq: "!=",
            ast.Lt: "<", ast.LtE: "<=", ast.Gt: ">", ast.GtE: ">=", ast.Is: "==", ast.IsNot: "!=",

        }.get(type(op), "?")

    @_safe
    def call(self, node):
        if isinstance(node.func, ast.Attribute):
            obj = self.expr(node.func.value)
            method = node.func.attr
            args = ", ".join(self.expr(a) for a in node.args)
            return f"{obj}->vptr->{method}({obj}{', ' if args else ''}{args})"

        name = self.expr(node.func)

        if name == "print":
            args = [self.expr(a) for a in node.args]
            if args:
                return f'printf("%s\\n", {args[0]})'
            return 'printf("\\n")'

        args = ", ".join(self.expr(a) for a in node.args)
        return f"{name}({args})"

    # ---------------- Statements ----------------

    @_safe
    def visit_Assign(self, node):
        target = self.expr(node.targets[0])

        if isinstance(node.value, ast.Call) and isinstance(node.value.func, ast.Name):
            cname = node.value.func.id
            if cname in self.classes:
                return f"{cname} *{target} = {cname}_new();"

        value = self.expr(node.value)

        if target not in self.locals:
            self.locals.add(target)
            return f"{infer_type(node.value)} {target} = {value};"

        return f"{target} = {value};"

    @_safe
    def visit_Expr(self, node):
        return self.expr(node.value) + ";"

    @_safe
    def visit_Return(self, node):
        return f"return {self.expr(node.value)};"

    @_safe
    def visit_If(self, node):
        lines = [f"if ({self.expr(node.test)}) {{"]

        for s in node.body:
            lines.append(_indent(1) + self.dispatch(s))
        lines.append("}")

        if node.orelse:
            lines.append("else {")
            for s in node.orelse:
                lines.append(_indent(1) + self.dispatch(s))
            lines.append("}")

        return "\n".join(lines)

    @_safe
    def visit_For(self, node):
        if isinstance(node.iter, ast.Call) and self.expr(node.iter.func) == "range":
            args = node.iter.args
            var = self.expr(node.target)

            start = "0"
            stop = self.expr(args[0])
            step = "1"

            if len(args) >= 2:
                start = self.expr(args[0])
                stop = self.expr(args[1])
            if len(args) == 3:
                step = self.expr(args[2])

            self.locals.add(var)
            lines = [
                f"for (int {var} = {start}; {var} < {stop}; {var} += {step}) {{"
            ]
        else:
            lines = [f"/* for ({self.expr(node.target)} in {self.expr(node.iter)}) */ {{"]

        for s in node.body:
            lines.append(_indent(1) + self.dispatch(s))
        lines.append("}")

        return "\n".join(lines)

    @_safe
    def visit_While(self, node):
        lines = [f"while ({self.expr(node.test)}) {{"]
        for s in node.body:
            lines.append(_indent(1) + self.dispatch(s))
        lines.append("}")
        return "\n".join(lines)

    # ---------------- Functions & Classes ----------------

    @_safe
    def visit_FunctionDef(self, node):
        self.locals = set()

        if self.current_class:
            cname = self.current_class
            fname = f"{cname}_{node.name}"
            args = [f"{cname} *self"] + [f"void *{a.arg}" for a in node.args.args[1:]]
        else:
            fname = node.name
            args = [f"void *{a.arg}" for a in node.args.args]

        lines = [f"void {fname}({', '.join(args)}) {{"]

        for s in node.body:
            lines.append(_indent(1) + self.dispatch(s))

        lines.append("}")
        self.functions.append("\n".join(lines))
        return None

    @_safe
    def visit_ClassDef(self, node):
        cname = node.name
        methods = {}

        for base in node.bases:
            if isinstance(base, ast.Name) and base.id in self.classes:
                methods.update(self.classes[base.id]["methods"])

        self.current_class = cname
        for item in node.body:
            if isinstance(item, ast.FunctionDef):
                methods[item.name] = item
                self.visit(item)
        self.current_class = None

        self.classes[cname] = {"methods": methods}

        vt = [f"typedef struct {cname}_vtable {{"]

        for m in methods:
            vt.append(_indent(1) + f"void (*{m})(struct {cname} *self);")

        vt.append(f"}} {cname}_vtable;")

        st = [
            f"typedef struct {cname} {{",
            _indent(1) + f"{cname}_vtable *vptr;",
            f"}} {cname};"
        ]

        self.structs.append("\n".join(vt))
        self.structs.append("\n".join(st))

        ctor = [
            f"{cname} *{cname}_new() {{",
            _indent(1) + f"{cname} *obj = malloc(sizeof({cname}));",
            _indent(1) + f"obj->vptr = malloc(sizeof({cname}_vtable));"
        ]

        for m in methods:
            ctor.append(_indent(1) + f"obj->vptr->{m} = {cname}_{m};")

        ctor.append(_indent(1) + "return obj;")
        ctor.append("}")

        self.functions.append("\n".join(ctor))
        return None

    # ---------------- Dispatcher ----------------

    def dispatch(self, node):
        m = "visit_" + node.__class__.__name__
        if hasattr(self, m):
            return getattr(self, m)(node)
        return "/* stmt */"

    def process(self, tree):
        for n in tree.body:
            if isinstance(n, ast.ClassDef):
                self.visit(n)
            elif isinstance(n, ast.FunctionDef):
                self.visit(n)
            else:
                self.main_body.append(self.dispatch(n))

    def emit(self):
        out = [
            "#include <stdio.h>",
            "#include <stdlib.h>\n"
        ]

        for s in self.structs:
            out.append(s + "\n")

        for f in self.functions:
            out.append(f + "\n")

        out.append("int main() {")
        for s in self.main_body:
            out.append(_indent(1) + s)
        out.append("    return 0;")
        out.append("}")

        return "\n".join(out)


# ============================================================
# Public API
# ============================================================

def python_to_c(source: str) -> str:
    try:
        tree = ast.parse(source)
    except Exception:
        return "int main() { return 0; }"

    try:
        t = _PyToC()
        t.process(tree)
        return t.emit()
    except Exception:
        return "int main() { return 0; }"
