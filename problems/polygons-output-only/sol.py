start_t = 1
end_t = 3000

DEBUG = False

resf = open('result.txt', 'w')

import cv2 as cv
import numpy as np
import os
import sys

sys.setrecursionlimit(50000)

B = 5
S = 20
THRESHOLD = 2 / 180.0 * np.pi

def bfs(a, x, y, cleanup):
    res = [ ]
    q = [(x, y, 0)]
    a[x, y] = False
    while len(q) > 0:
        (x, y, d) = q.pop(0)
        if (not cleanup) and d % S == 0:
            if len(res) == 0 or d > res[-1][2]:
                res.append((x, y, d))
        if cleanup and d >= B:
            continue
        for i in [-1, 0, 1]:
            for j in [-1, 0, 1]:
                if (i != 0 or j != 0) and a[x + i, y + j]:
                    q.append((x + i, y + j, d + 1))
                    a[x + i, y + j] = False
    return res

def dist2(a, b):
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

def get_angle(u, a, v):
    dotprod = (u[0] - a[0]) * (v[0] - a[0]) + (u[1] - a[1]) * (v[1] - a[1])
    return np.arccos(dotprod / np.sqrt(dist2(u, a) * dist2(v, a)))

for test in range(start_t, end_t + 1):
    fname = 'tests/%03d.png' % test
    img = cv.imread(fname, cv.IMREAD_GRAYSCALE)

    print("Read test %d" % test)

    cv.floodFill(img, None, (0, 0), 128)

    n, m = img.shape
    edges = np.zeros((n - 2, m - 2), dtype=bool)
    for i in [-1, 0, 1]:
        for j in [-1, 0, 1]:
            if i != 0 or j != 0:
                e = (img[1:-1, 1:-1] == 0) & (img[1+i:n-1+i, 1+j:m-1+j] == 255)
                edges = edges | e

    if DEBUG:
        cv.imwrite('debug1.png', np.array(edges, dtype='uint8') * 255)
    
    found = False
    for si in range(n - 2):
        for sj in range(m - 2):
            if edges[si, sj]:
                found = True
                break
        if found:
            break
    # find some si, sj

    # clean up around it
    bfs(edges, si, sj, True)

    if DEBUG:
        cv.imwrite('debug2.png', np.array(edges, dtype='uint8') * 255)

    # find a new starting point
    found = False
    for i in range(-2 * B, 2 * B):
        for j in range(-2 * B, 2 * B):
            if edges[si + i, sj + j]:
                si += i
                sj += j
                found = True
                break
        if found:
            break

    # print(si, sj)

    res = bfs(edges, si, sj, False)

    if DEBUG:

        a = np.zeros(edges.shape, dtype='uint8')
        for p in res:
            a[p[0], p[1]] = 255
        a[res[0][0], res[0][1]] = 100
        a[res[1][0], res[1][1]] = 170
        cv.imwrite('debug3.png', a)

    res = res[1:]

    res.append(res[0])
    res.append(res[1])
    n_seg = len(res)

    aligned = [ ]
    for i in range(n_seg - 2):
        angle = get_angle(res[i + 1], res[i], res[i + 2])
        if DEBUG:
            print(i, angle / np.pi * 180.0)
        aligned.append(angle <= THRESHOLD)

    shift = 0
    while aligned[0]:
        aligned.append(aligned.pop(0))
        shift += 1
    while not aligned[0]:
        aligned.append(aligned.pop(0))
        shift += 1

    if DEBUG:
        print(shift)
        print(aligned)


    assert(aligned[0]) # it should start aligned
    c = 0
    for i in range(1, len(aligned)):
        if (not aligned[i]) and aligned[i - 1]:
            c += 1
    
    resf.write('%d ' % c)
    if DEBUG:
        print(c)
        print()
