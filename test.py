import fmm
import numpy as np

num_points = 1633000
num_iter = 1
num_terms = 10
bin_size = 200
theta = 0.001
dodebug = False
for i in np.arange(num_iter):
    print("Run " + str(i+1))
    A = np.random.uniform(0, 1, 3 * num_points)
    B = np.random.uniform(0, 1, num_points)
    fmm.bonsai(num_points, A, B, dodebug)
