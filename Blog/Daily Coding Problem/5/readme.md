# Daily Coding Problem: Problem #5 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Jane Street.

`cons(a, b)` constructs a pair, and `car(pair)` and `cdr(pair)` returns the first and last element of that pair. For example, `car(cons(3, 4))` returns `3`, and `cdr(cons(3, 4))` returns `4`.

Given this implementation of cons:

```python
def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair
```

Implement `car` and `cdr`.

## My solution (is this cheating?)

This is a python solution. I don't know whether a C++ implementation is possible or not. Is nested function allowed in C++? Can a function be a parameter in C++?

```python
def car(pair):
    return pair(lambda a, b: a)
    
def cdr(pair):
    return pair(lambda a, b: b)
```

----

## Googled solution (if I actually googled it)

[https://github.com/cwetanow/DailyCodingProblem/blob/master/DailyCodingProblem.Solutions/01-99/01-19/Problem05/solution.js](https://github.com/cwetanow/DailyCodingProblem/blob/master/DailyCodingProblem.Solutions/01-99/01-19/Problem05/solution.js)

Looks it uses the same idea..
