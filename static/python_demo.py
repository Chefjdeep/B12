def add(a, b):
    return a + b


def subtract(a, b):
    return a - b


def multiply(a, b):
    result = 0
    for i in range(b):
        result = result + a
    return result


def factorial(n):
    result = 1
    i = 1
    while i <= n:
        result = result * i
        i = i + 1
    return result


class Calculator:
    def compute(self, x, y):
        if x > y:
            return add(x, y)
        elif x == y:
            return multiply(x, y)
        else:
            return subtract(y, x)


def main():
    calc = Calculator()

    a = 3
    b = 5

    sum_val = add(a, b)
    diff_val = subtract(a, b)
    prod_val = multiply(a, b)
    fact_val = factorial(a)

    print(sum_val)
    print(diff_val)
    print(prod_val)
    print(fact_val)

    result = calc.compute(a, b)
    print(result)


if __name__ == "__main__":
    main()

