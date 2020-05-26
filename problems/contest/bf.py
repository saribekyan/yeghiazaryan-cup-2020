# some brute force simulation that
# doesn't always work

import sys

fin = sys.stdin

x = fin.readline().split()
n, T, f = int(x[0]), int(x[1]), float(x[2])

p = [ ]
s = [ ]
for i in range(n):
    x = fin.readline().split()
    p.append(float(x[0]))
    s.append(int(x[1]))

E = 0.0

for mask in [ list of masks ]: # not all masks are valid, need to calibrate per test case.
    mask_p = 1.0
    score = 0.0

    taken = [ False ] * n
    curr_p = list(p)
    for t in range(T):
        j = -1
        for i in range(0, n):
            if (not taken[i]) and (j == -1 or s[i] * curr_p[i] > s[j] * curr_p[j]):
                j = i

        if j != -1:
            if ((mask >> t)&1) == 1:
                mask_p *= curr_p[j]
                score += s[j]
                taken[j] = True
            else:
                mask_p *= (1 - curr_p[j])
                curr_p[j] *= f
        else:
            break

    E += score * mask_p

print(E)
