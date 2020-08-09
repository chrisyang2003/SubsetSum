from math import sqrt
n = 10
s = 4
k = 5
alist = [i + 1 for i in range(n)]
N = int(sqrt(n)) + 1

blist = [[] for j in range(n + 1)]
for i in range(len(blist)):
    if i < len(blist) - 1:
        blist[i] = [1 if i == j else 0 for j in range(n)]
        blist[i] += [N * alist[i], N]
    else:
        blist[i] = [0 for i in range(n)]
        blist[i] += [N * s, k * N]

