import numpy as np

w = np.array([3, 2])
v = np.array([4, 1])
v = v.transpose()
x = w*v

print(sum(x))