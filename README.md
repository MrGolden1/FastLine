# FastLine
Python module for geometric Line operations implmented in C++, and it is optimized for speed. I created this module to use in a project where I needed to do many of such calculations.
# installation

```bash
$ pip install FastLine
```

or 

```bash
git clone https://github.com/MrGolden1/FastLine.git
cd FastLine
pip install .
```

# usage

```python
from FastLine import Line
# define a line by two points
l1 = Line(p1=(0,0), p2=(10,10))
# define a line by its slope and intercept
l2 = Line(m=4, b=-1)
```

## methods:

`solve:` takes x or y as argument and return the corresponding value
```python
>>> l1.solve(x=20)
20.0
>>> l2.solve(y=20)
5.25
```

`distance_to:` takes a point as argument and return the nearest distance to the line.
```python
>>> l1.distance_to((20,50))
21.213203435596427
>>> l2.distance_to((-15,17))
18.91777875283397
```

`crossed_by:` takes a point as argument and return a value in __[-1,0,1]__ (upon a specific side, upon the line, uopn opposite side). You'd need to calibrate what each side is.
```python
>>> l1.crossed_by((20,50)) # specific side
1
>>> l1.crossed_by((50,50)) # on the line
0
>>> l1.crossed_by((-20,-50)) # opposite side
-1
```
`intersection:` takes a line as argument and return the intersection point. If two lines are parallel, it returns __None__.
```python
>>> l1.intersection(l2)
(0.3333333333333333, 0.3333333333333333)
```

### Thanks to:
https://stackoverflow.com/a/3838398/10220190
https://stackoverflow.com/a/39840218/10220190
https://stackoverflow.com/a/20679579/10220190



`Author:`M.Ali Zarrinzadeh

`Email:`ali.zarrinzadeh@gmail.com


