import random
import time

array1 = [10, 15, 3, 7]
k1 = 17


def solve(array: list[int], k: int) -> (bool, int, int):
    targets = set()
    for item in array:
        if item in targets:
            return True, item, k - item
        targets.add(k - item)
    return False, None, None

if __name__ == '__main__':
    s = time.perf_counter()
    print("Result:", solve(array1, k1))
    e = time.perf_counter()
    print(f"time consumed: {e-s:.6f} seconds")

    array2 = [random.randint(1, 200) for _ in range(100)]
    k2 = random.randint(1, 200)
    print('Random generated data:', k2, array2)
    s = time.perf_counter()
    print("Result:", solve(array2, k2))
    e = time.perf_counter()
    print(f"time consumed: {e-s:.6f} seconds")
