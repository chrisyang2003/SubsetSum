from math import sqrt
n = 10
s = 4
alist = [i + 1 for i in range(n)]

blist = [[] for i in range(n + 1)]
for i in range(len(blist)):
    if i < len(blist) - 1:
        blist[i] = [2 if i == j else 0 for j in range(n)]
        blist[i] += [n * alist[i], 0]
    else:
        blist[i] = [1 for i in range(n)]
        blist[i] += [n * s, 1]
# for i in blist:
#     print(i)
