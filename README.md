# FastLine

**FastLine** is a Python module for performing geometric line operations. Implemented in C++ and bound to Python, it is optimized for speed, making it suitable for projects that require numerous line calculations.

## Installation

You can install FastLine using `pip`:

```bash
pip install FastLine
```

Alternatively, install it directly from the source repository:

```bash
git clone https://github.com/MrGolden1/FastLine.git
cd FastLine
pip install .
```

## Usage

Import the `Line` class from the FastLine module and create line instances using either two points or slope-intercept form.

```python
from FastLine import Line

# Define a line by two points
line1 = Line(p1=(0, 0), p2=(10, 10))

# Define a line by its slope and intercept
line2 = Line(m=4, b=-1)
```

### Methods

#### `solve`

Calculates the corresponding y for a given x or x for a given y.

```python
>>> line1.solve(x=20)
20.0

>>> line2.solve(y=20)
5.25
```

#### `distance_to`

Computes the shortest distance from a given point to the line.

```python
>>> line1.distance_to((20, 50))
21.213203435596427

>>> line2.distance_to((-15, 17))
18.91777875283397
```

#### `crossed_by`

Determines the side of the line on which a point lies. Returns `-1`, `0`, or `1` indicating the opposite side, on the line, or a specific side, respectively. You will need to define the orientation of each side based on your application's context.

```python
>>> line1.crossed_by((20, 50))  # Specific side
1

>>> line1.crossed_by((50, 50))  # On the line
0

>>> line1.crossed_by((-20, -50))  # Opposite side
-1
```

#### `intersection`

Finds the intersection point with another line. Returns `None` if the lines are parallel.

```python
>>> line1.intersection(line2)
(0.3333333333333333, 0.3333333333333333)
```

## Acknowledgements

- [Intersection of Two Lines](https://stackoverflow.com/a/3838398/10220190)
- [Distance from a Point to a Line](https://stackoverflow.com/a/39840218/10220190)
- [Line Side Determination](https://stackoverflow.com/a/20679579/10220190)

## Author

**M. Ali Zarrinzadeh**

- Email: [ali.zarrinzadeh@gmail.com](mailto:ali.zarrinzadeh@gmail.com)

## Speed Benchmarks

FastLine has been benchmarked against pure Python, NumPy, and Numba implementations to evaluate its performance in checking intersections between M and N line segments.

### Running the Benchmarks

1. **Install Dependencies:**

    Ensure you have the necessary dependencies installed:

    ```bash
    pip install numpy numba
    ```

2. **Execute the Benchmark Script:**

    Run the benchmark script to compare performance:

    ```bash
    python benchmark.py
    ```

### Benchmark Results

The following table summarizes the benchmark results comparing FastLine with pure Python, NumPy, and Numba implementations:

| Implementation                     | Time (seconds) |
|------------------------------------|----------------|
| **FastLine**                       | 0.1523         |
| Pure Python                        | 0.4266         |
| NumPy (Non-Vectorized)              | 2.8718         |
| Numba                              | 0.6909         |

---

For any questions or contributions, feel free to contact the author or submit an issue on the [GitHub repository](https://github.com/MrGolden1/FastLine).