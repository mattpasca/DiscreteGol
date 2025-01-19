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
grid = np.zeros((GRID_SIZE,GRID_SIZE), dtype=np.int32)

glider = [
    [0, 1, 0],
    [0, 0, 1],
    [1, 1, 1]
]

grid[0:3,0:3] = glider

grid_ptr = grid.ctypes.data_as(ct.POINTER(ct.c_int))

fig, ax = plt.subplots()
cax = ax.imshow(grid, cmap='gray')
plt.ion() 
plt.show()
i = 0
for i in range(100):
	cax.set_data(grid)
	plt.draw()
	plt.pause(0.1)
	
	new_grid_ptr = shared_library.state_transition(grid_ptr, GRID_SIZE)
	
	grid_ptr = new_grid_ptr
	grid = np.ctypeslib.as_array(grid_ptr, shape=(GRID_SIZE, GRID_SIZE))
	
shared_library.free_matrix(grid_ptr)

