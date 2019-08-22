import fmm
import numpy as np
import matplotlib.pyplot as plt

def direct_compute(shot, weight):
    potentials = []
    for i in np.arange(shot.shape[0]):
        current_point = shot[i]
        pot = 0
        for j in np.arange(shot.shape[0]):
            if i==j:
                continue
            else:
                R = np.linalg.norm(current_point - shot[j])
                pot += weight[j] / R
        potentials.append(pot)
    return np.asarray(potentials)


num_points = 163300
num_iter = 1
num_terms = 10
bin_size = 200
theta = 0.001
dodebug = False
for i in np.arange(num_iter):
    print("Run " + str(i+1))
    A = np.random.uniform(0, 1, 3 * num_points)
    B = np.random.uniform(0, 1, num_points)
    C = fmm.bonsai(num_points, A, B, 0.75, dodebug)
    C_act = direct_compute(np.reshape(A,(num_points,3),order='F'),B)
    C = -C

plt.plot(C)
plt.plot(C_act)
plt.show()
print(str(C))