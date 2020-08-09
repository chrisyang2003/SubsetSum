import numpy as np
import random

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


x = [21862 * 4, 21862 * 2, 21862, 10803, 5493, 2798, 1437, 765, 428, 256, 172, 131,
     109, 97, 93, 87, 87, 87, 87.44, 87.7, 87.3, 88.3, 88.1, 88, 88]
y = [i for i in range(6, 31)]

z = [39202, 38540,36540, 33660, 20278, 20266, 21392, 21239, 23290, 29126, 39714, 72124, 124357, 230845, 413062,
     842506, 1581233, 3434788, 7233676, 12642463, 29444269, 48168904, 98429352, 220704368, 388887618]

x = np.array(x)
y = np.array(y)
z = np.array(z)

ax = plt.subplot(111, projection='3d')

ax.scatter(x[13:], y[13:], z[13:], c='r', marker='^')
ax.scatter(x[4:13], y[4:13], z[4:13], c='g', marker='1')
ax.scatter(x[:4], y[:4], z[:4], c='r', marker='^')

ax.invert_xaxis()


ax.set_title('Dimension n = 100')
ax.set_xlabel('Memory (in MiB)')  # 坐标轴
ax.set_ylabel('M')
ax.set_zlabel('Time (in seconds)')
plt.show()
