import time
import numpy as np
import numba
from FastLine import Line

def benchmark_fastline():
    start_time = time.time()
    l1 = Line(p1=(0, 0), p2=(10, 10))
    l2 = Line(m=4, b=-1)
    for _ in range(1000000):
        l1.intersection(l2)
    end_time = time.time()
    return end_time - start_time

def benchmark_pure_python():
    def intersection(l1, l2):
        x1, y1, x2, y2 = l1
        x3, y3, x4, y4 = l2
        denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
        if denom == 0:
            return None
        px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom
        py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom
        return px, py

    start_time = time.time()
    l1 = (0, 0, 10, 10)
    l2 = (0, -1, 10, 39)
    for _ in range(1000000):
        intersection(l1, l2)
    end_time = time.time()
    return end_time - start_time

def benchmark_numpy():
    def intersection(l1, l2):
        x1, y1, x2, y2 = l1
        x3, y3, x4, y4 = l2
        denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
        if denom == 0:
            return None
        px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom
        py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom
        return px, py

    start_time = time.time()
    l1 = np.array([0, 0, 10, 10])
    l2 = np.array([0, -1, 10, 39])
    for _ in range(1000000):
        intersection(l1, l2)
    end_time = time.time()
    return end_time - start_time

@numba.jit(nopython=True)
def numba_intersection(l1, l2):
    x1, y1, x2, y2 = l1
    x3, y3, x4, y4 = l2
    denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if denom == 0:
        return None
    px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom
    py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom
    return px, py

def benchmark_numba():
    start_time = time.time()
    l1 = np.array([0, 0, 10, 10])
    l2 = np.array([0, -1, 10, 39])
    for _ in range(1000000):
        numba_intersection(l1, l2)
    end_time = time.time()
    return end_time - start_time

def main():
    print("Benchmarking FastLine...")
    fastline_time = benchmark_fastline()
    print(f"FastLine: {fastline_time:.4f} seconds")

    print("Benchmarking Pure Python...")
    pure_python_time = benchmark_pure_python()
    print(f"Pure Python: {pure_python_time:.4f} seconds")

    print("Benchmarking NumPy...")
    numpy_time = benchmark_numpy()
    print(f"NumPy: {numpy_time:.4f} seconds")

    print("Benchmarking Numba...")
    numba_time = benchmark_numba()
    print(f"Numba: {numba_time:.4f} seconds")

if __name__ == "__main__":
    main()
