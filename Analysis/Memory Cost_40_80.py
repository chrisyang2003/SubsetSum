import matplotlib.pyplot as plt
import numpy as np

x = [i for i in range(40, 100, 20)]
y = [42.31, 49.9, 328.7]
y2 = [43, 54, 531]

xy = (x[0], y[0])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-10, 10),
                textcoords='offset points')
xy = (x[1], y[1])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-20, -13),
             textcoords='offset points')
xy = (x[2], y[2])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-58, -4),
             textcoords='offset points')

xy = (x[0], y2[0])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-10, 25),
             textcoords='offset points')
xy = (x[1], y2[1])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-28, 15),
             textcoords='offset points')
xy = (x[2], y2[2])
plt.annotate("(%s,%s)" % xy, xy=xy, xytext=(-50, -5),
             textcoords='offset points')


plt.plot(x, y, color="r", linestyle="--", marker="o", linewidth=1.0)
plt.plot(x, y2, color="b", linestyle="--", marker="*", linewidth=1.0)

plt.title('Memory Cost')

plt.xlabel('Dimension')
plt.ylabel('memory used (in MiB)')
plt.show()

