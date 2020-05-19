# So far I do it differently, but here's one way
# of generating random convex polygons
#     http://cglab.ca/~sander/misc/ConvexGeneration/convex.html

N_TESTS   = 100

import os
import random
import cv2 as cv
import numpy as np
from numpy.random import rand


MIN_SIDES = 3
MAX_SIDES = 20

MIN_DIM = 64
MAX_DIM = 2048

MIN_SIDE_X_WIDTH = 100
MAX_SIDE_LEN = 300

MIN_ANGLE = 10 / 180.0 * np.pi
MAX_ANGLE = 170 / 180.0 * np.pi
ANGLE_STD_FACTOR = 3.0

MIN_GAP = 10
MAX_GAP = 100

random.seed(0)
np.random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

all_in_one = open(os.path.join(test_dir, 'correct.a'), 'w')

curr_test = 1
def print_test(sides, img):
    global curr_test
    print(sides, img.shape)

    assert(curr_test <= N_TESTS)
    assert(MIN_SIDES <= sides <= MAX_SIDES)
    assert(MIN_DIM <= img.shape[0] <= MAX_DIM)
    assert(MIN_DIM <= img.shape[1] <= MAX_DIM)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d.png' % curr_test)
    out_fname = os.path.join(test_dir, '%03d.a' % curr_test)

    cv.imwrite(fname, img)
    with open(out_fname, 'w') as f:
        f.write('%d\n' % sides)

    all_in_one.fwrite('%d\n' % sides)

    curr_test += 1

def dist2(a, b):
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

def vecprod(u, a, v):
    return (u[0] - a[0]) * (v[1] - a[1]) - (u[1] - a[1]) * (v[0] - a[0])

def get_angle(u, a, v):
    dotprod = (u[0] - a[0]) * (v[0] - a[0]) + (u[1] - a[1]) * (v[1] - a[1])
    return np.arccos(dotprod / np.sqrt(dist2(u, a) * dist2(v, a)))

def rand_polygon(mean_n_sides, min_side_len):
    assert(min_side_len <= MAX_SIDE_LEN)

    mean_alpha = 2 * np.pi / mean_n_sides
    direction = rand() * 2 * np.pi

    points = [ (0.0, 0.0) ]
    while True:
        delta = np.random.normal(mean_alpha, mean_alpha / ANGLE_STD_FACTOR)
        delta = max(delta, np.pi - MAX_ANGLE)
        delta = min(delta, np.pi - MIN_ANGLE)

        direction -= delta

        length = rand() * (MAX_SIDE_LEN - min_side_len) + min_side_len + 1

        curr = points[-1]
        nxt = (curr[0] + np.cos(direction) * length,
               curr[1] + np.sin(direction) * length)

        first = points[0]
        if dist2(first, nxt) < min_side_len ** 2:
            break

        if len(points) > 2:
            second = points[1]
            if (vecprod(curr, first, nxt) >= 0 or
                vecprod(second, first, nxt) >= 0): # non-convex
                break
            a1 = get_angle(curr, nxt, first)
            a2 = get_angle(nxt, first, second)
            if (not (MIN_ANGLE <= a1 <= MAX_ANGLE) or
                not (MIN_ANGLE <= a2 <= MAX_ANGLE)):
                break

        points.append(nxt)

    if len(points) == 2:
        # this should only happen when the third vertex somehow ends
        # up really close to the first one, which is very unlikely.
        return None # fail
    return points

def rand_test(mean_n_sides, width):
    while True:
        points = rand_polygon(mean_n_sides, width * MIN_SIDE_X_WIDTH)
        if points is not None:
            break

    minx = points[0][0]
    maxx = minx
    miny = points[0][1]
    maxy = miny

    for p in points:
        minx = min(minx, p[0])
        maxx = max(maxx, p[0])
        miny = min(miny, p[1])
        maxy = max(maxy, p[1])

    minx -= 1
    miny -= 1

    gap_xl = random.randint(MIN_GAP, MAX_GAP)
    gap_xr = random.randint(MIN_GAP, MAX_GAP)
    gap_yl = random.randint(MIN_GAP, MAX_GAP)
    gap_yr = random.randint(MIN_GAP, MAX_GAP)

    maxx = 0
    maxy = 0
    coords = [ ]
    for p in points:
        x = int(np.round(p[0] - minx)) + gap_xl
        y = int(np.round(p[1] - miny)) + gap_yl
        maxx = max(x, maxx)
        maxy = max(y, maxy)
        coords.append((x, y))

    dimx = maxx + gap_xr
    dimy = maxy + gap_yr

    img = np.ones((dimy, dimx), np.uint8) * 255

    sides = len(coords)
    for i in range(sides):
        p = coords[i]
        p = (p[0], dimy - p[1] - 1)
        coords[i] = p

    coords.append(coords[0])
    for i in range(sides):
        cv.line(img, coords[i], coords[i + 1], 0, thickness=width)

    return sides, img

if __name__ == '__main__':
    for i in range(N_TESTS):
        mean_sides = random.randint(3, 10)

        width = random.randint(1, 30)
        width = min(width, MAX_SIDE_LEN // MIN_SIDE_X_WIDTH)

        print_test(*rand_test(mean_sides, width))
