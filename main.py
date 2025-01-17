import numpy as np
import ctypes as ct
import matplotlib.pyplot as plt

# Access to the library with the C function
shared_library = ct.CDLL('./state_transition.so')

shared_library.state_transition.argtypes = [
    ct.POINTER(ct.c_int),
    ct.c_int
    ]
shared_library.state_transition.restype = ct.POINTER(ct.c_int)

shared_library.free_matrix.argtypes = [ct.POINTER(ct.c_int)]
shared_library.free_matrix.restype = None

GRID_SIZE = 20
grid = np.zeros((GRID_SIZE,GRID_SIZE))

glider = [
    [0, 1, 0],
    [0, 0, 1],
    [1, 1, 1]
]

grid[0:3,0:3] = glider



plt.imshow(grid, cmap='gray')
plt.show()
