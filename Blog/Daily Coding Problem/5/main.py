import random
import time
from typing import Any


def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair

def car(pair):
    return pair(lambda a, b: a)
    
def cdr(pair):
    return pair(lambda a, b: b)

if __name__ == '__main__':
    s = time.perf_counter()
    print(f"Result: {car(cons(3, 4))=}, {cdr(cons(3, 4))=}")
    e = time.perf_counter()
    print(f"time consumed: {e-s:.6f} seconds")
