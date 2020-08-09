import matplotlib.pyplot as plt
import numpy as np

x = [i for i in range(100, 200, 20)]
y = [73, 1701, 3139.1, 175 * 1024, 313 * 1024]
y2 = [3966 * 4, 534207, 4276206.02360, 136645298.65001154, 4916381697.440333]


xy = (x[0], y[0])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-13, 7),
             textcoords='offset points')
xy = (x[1], y[1])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-20, 5),
             textcoords='offset points')
xy = (x[2], y[2])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-15, -15),
             textcoords='offset points')
xy = (x[3], y[3])
plt.annotate("175GB ≈ (%s,%s) " % xy, xy=xy, xytext=(-123, -5),
             textcoords='offset points')
xy = (x[4], y[4])
plt.annotate("313GB ≈ (%s,%s)" % xy, xy=xy, xytext=(-105, 6),
             textcoords='offset points')

# for xy in zip(x, y2):
#     plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(3, -5),
#                  textcoords='offset points')

plt.yscale('log')
plt.plot(x, y, color="r", linestyle="--", marker="o", linewidth=1.0)
plt.plot(x, y2, color="b", linestyle="--", marker="*", linewidth=1.0)

plt.title('Memory Cost')
plt.xlabel('Dimension')
plt.ylabel('memory used (in MiB)')
plt.show()
