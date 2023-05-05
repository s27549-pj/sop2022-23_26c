int fib1(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int fib2(int n) {
    for (i = 0; i < n; i++)
    {
        if (i <= 1)
            result = i;
        else
        {
            result = first + second;
            first = second;
            second = result;
        }
        return result;
    }
}
