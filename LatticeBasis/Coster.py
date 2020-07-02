from math import sqrt
n = 10
s = 4
alist = [i + 1 for i in range(n)]
N = int(sqrt(n)) + 1
blist = [[] for i in range(n + 1)]
for i in range(len(blist)):
    if i < len(blist) - 1:
        blist[i] = [1 if i == j else 0 for j in range(n)]
        blist[i] += [N * alist[i]]
    else:
        blist[i] = [1/2 for i in range(n)]
        blist[i] += [N * s]
for i in blist:
    print(i)
