import ast
import sys
from pathlib import Path


class CEmitter(ast.NodeVisitor):
    def __init__(self):
        self.out = []
        self.indent = 0
        self.locals = set()
        self.args = set()
        self.array_args = set()  # Track arguments that are arrays

    def emit(self, line=""):
        self.out.append("    " * self.indent + line)

    # ---------- Top-level ----------

    def visit_Module(self, node):
        for stmt in node.body:
            self.visit(stmt)

    def visit_FunctionDef(self, node):
        self._emit_function(node)

    def _emit_function(self, node, parent_scope_locals=None):
        self.locals = set()
        self.array_args = set()
        if parent_scope_locals is None:
            parent_scope_locals = set()
        self.args = {arg.arg for arg in node.args.args}

        # If arg name ends with "_arr", treat as array
        args_list = []
        for a in self.args:
            if a.endswith("_arr"):
                args_list.append(f"int {a}[]")
                self.array_args.add(a)
            else:
                args_list.append(f"int {a}")
        args = ", ".join(args_list)
        self.emit(f"int {node.name}({args}) {{")
        self.indent += 1

        # Capture body output
        body_out = []
        old_out = self.out
        self.out = body_out

        for stmt in node.body:
            self.visit(stmt)

        # Restore output
        self.out = old_out

        # Emit local variable declarations
        for var in sorted(self.locals - self.args - parent_scope_locals):
            self.emit(f"int {var};")

        if self.locals:
            self.emit()

        # Emit function body
        for line in body_out:
            self.emit(line)

        self.indent -= 1
        self.emit("}")
        self.emit()

        # Nested functions: add locals to parent scope
        parent_scope_locals.update(self.locals)

    # ---------- Statements ----------

    def visit_Return(self, node):
        if node.value:
            self.emit(f"return {self.expr(node.value)};")
        else:
            self.emit("return;")

    def visit_Assign(self, node):
        value = self.expr(node.value)
        for target in node.targets:
            tname = self.expr(target)
            self.locals.add(tname)
            self.emit(f"{tname} = {value};")

    def visit_AugAssign(self, node):
        target = self.expr(node.target)
        self.locals.add(target)
        op = self.augop(node.op)
        value = self.expr(node.value)
        self.emit(f"{target} {op}= {value};")

    def visit_Expr(self, node):
        self.emit(f"{self.expr(node.value)};")

    def visit_If(self, node):
        self.emit(f"if ({self.expr(node.test)}) {{")
        self.indent += 1
        for stmt in node.body:
            self.visit(stmt)
        self.indent -= 1
        if node.orelse:
            self.emit("} else {")
            self.indent += 1
            for stmt in node.orelse:
                self.visit(stmt)
            self.indent -= 1
        self.emit("}")

    def visit_For(self, node):
        if not isinstance(node.iter, ast.Call) or getattr(node.iter.func, "id", None) != "range":
            raise NotImplementedError("Only for-loops over range() supported")
        args = node.iter.args
        if len(args) == 1:
            start, end = "0", self.expr(args[0])
        else:
            start, end = self.expr(args[0]), self.expr(args[1])
        var = self.expr(node.target)
        self.locals.add(var)
        self.emit(f"for (int {var} = {start}; {var} < {end}; {var}++) {{")
        self.indent += 1
        for stmt in node.body:
            self.visit(stmt)
        self.indent -= 1
        self.emit("}")

    def visit_While(self, node):
        self.emit(f"while ({self.expr(node.test)}) {{")
        self.indent += 1
        for stmt in node.body:
            self.visit(stmt)
        self.indent -= 1
        self.emit("}")

    # ---------- Expressions ----------

    def expr(self, node):
        if isinstance(node, ast.Name):
            return node.id

        if isinstance(node, ast.Constant):
            if isinstance(node.value, str):
                return f"\"{node.value}\""
            return repr(node.value)

        if isinstance(node, ast.JoinedStr):
            # f-string: concatenate parts
            parts = []
            for value in node.values:
                if isinstance(value, ast.Constant):
                    parts.append(f"\"{value.value}\"")
                elif isinstance(value, ast.FormattedValue):
                    parts.append(self.expr(value.value))
                else:
                    raise NotImplementedError("Unsupported f-string part")
            return " + ".join(parts)

        if isinstance(node, ast.BinOp):
            return f"{self.expr(node.left)} {self.op(node.op)} {self.expr(node.right)}"

        if isinstance(node, ast.Call):
            fn = self.expr(node.func)
            args = ", ".join(self.expr(a) for a in node.args)
            return f"{fn}({args})"

        if isinstance(node, ast.Compare):
            left = self.expr(node.left)
            right = self.expr(node.comparators[0])
            op = self.cmp(node.ops[0])
            return f"{left} {op} {right}"

        if isinstance(node, ast.Subscript):
            val = self.expr(node.value)
            idx = self.expr(
                node.slice.value if isinstance(node.slice, ast.Index) else node.slice
            )
            return f"{val}[{idx}]"

        if isinstance(node, ast.Attribute):
            # obj.attr → "obj.attr" in C code
            value = self.expr(node.value)
            return f"{value}.{node.attr}"


        raise NotImplementedError(f"Unsupported expression: {type(node).__name__}")


    def op(self, node):
        return {
            ast.Add: "+",
            ast.Sub: "-",
            ast.Mult: "*",
            ast.Div: "/",
            ast.Mod: "%",
        }[type(node)]

    def augop(self, node):
        return {
            ast.Add: "+",
            ast.Sub: "-",
            ast.Mult: "*",
            ast.Div: "/",
            ast.Mod: "%",
        }[type(node)]

    def cmp(self, node):
        return {
            ast.Eq: "==",
            ast.NotEq: "!=",
            ast.Lt: "<",
            ast.LtE: "<=",
            ast.Gt: ">",
            ast.GtE: ">=",
        }[type(node)]


# ---------- Driver functions ----------

def python_to_c(source: str) -> str:
    tree = ast.parse(source)
    emitter = CEmitter()
    emitter.visit(tree)
    return "\n".join(emitter.out)


def convert_directory(input_dir: str, output_dir: str):
    input_dir = Path(input_dir)
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    for py_file in input_dir.glob("*.py"):
        with open(py_file, "r", encoding="utf-8") as f:
            src = f.read()

        c_code = python_to_c(src)
        out_file = output_dir / (py_file.stem + ".c")
        with open(out_file, "w", encoding="utf-8") as f:
            f.write(c_code)

        print(f"Converted {py_file.name} → {out_file.name}")


# ---------- Main ----------

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python batch_py_to_c_arrays.py <input_dir> <output_dir>")
        sys.exit(1)

    convert_directory(sys.argv[1], sys.argv[2])