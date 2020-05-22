# So far I do it differently, but here's one way
# of generating random convex polygons
#     http://cglab.ca/~sander/misc/ConvexGeneration/convex.html

N_TESTS   = 3000

import os
import random
import cv2 as cv
import numpy as np
from numpy.random import rand

MIN_SIDES = 3
MAX_SIDES = 20

MIN_DIM = 1024
MAX_DIM = 2048

MIN_SIDE_LEN = 150
MAX_SIDE_LEN = 500

MIN_WIDTH = 1
MAX_WIDTH = 25

MIN_ANGLE = 45.0 / 180.0 * np.pi
MAX_ANGLE = 170.0 / 180.0 * np.pi
ANGLE_STD_FACTOR = 3.0

MIN_GAP = 10
MAX_GAP = 100

random.seed(0)
np.random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
tests_dir   = os.path.join(dir_path, 'tests')
images_dir    = os.path.join(dir_path, 'images')
images_ans_dir = os.path.join(dir_path, 'images-ans')

if not os.path.exists(tests_dir):
    os.mkdir(tests_dir)

if not os.path.exists(images_dir):
    os.mkdir(images_dir)

if not os.path.exists(images_ans_dir):
    os.mkdir(images_ans_dir)

open(os.path.join(tests_dir, '001'), 'w').close()

all_in_one = open(os.path.join(tests_dir, '001.a'), 'w')
all_in_one.write('%d\n' % N_TESTS)

curr_test = 1
def print_test(sides, img):
    global curr_test

    assert(curr_test <= N_TESTS)
    assert(MIN_SIDES <= sides <= MAX_SIDES)
    assert(MIN_DIM <= img.shape[0] <= MAX_DIM)
    assert(MIN_DIM <= img.shape[1] <= MAX_DIM)

    print('printing test %d' % curr_test)
    print(sides, img.shape)

    fname = os.path.join(images_dir, '%03d.png' % curr_test)
    out_fname = os.path.join(images_ans_dir, '%03d.a' % curr_test)

    cv.imwrite(fname, img)
    with open(out_fname, 'w') as f:
        f.write('%d\n' % sides)

    all_in_one.write('%d ' % sides)

    curr_test += 1

def dist2(a, b):
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

# vecprod of vectors a->u and u->v
def vecprod(u, a, v):
    return (u[0] - a[0]) * (v[1] - a[1]) - (u[1] - a[1]) * (v[0] - a[0])

# the angle when going from a->u to a->v
def get_angle(u, a, v):
    dotprod = (u[0] - a[0]) * (v[0] - a[0]) + (u[1] - a[1]) * (v[1] - a[1])
    return np.arccos(dotprod / np.sqrt(dist2(u, a) * dist2(v, a)))

def rand_polygon(mean_n_sides):
    mean_alpha = 2 * np.pi / mean_n_sides

    direction = rand() * 2 * np.pi

    points = [ (0.0, 0.0) ]
    while True:
        delta = np.random.normal(
            mean_alpha, mean_alpha / ANGLE_STD_FACTOR)
        delta = max(delta, np.pi - MAX_ANGLE)
        delta = min(delta, np.pi - MIN_ANGLE)
        # print(delta)

        direction -= delta

        length = random.randint(MIN_SIDE_LEN, MAX_SIDE_LEN)

        curr = points[-1]
        nxt = (curr[0] + np.cos(direction) * length,
               curr[1] + np.sin(direction) * length)

        first = points[0]
        if dist2(first, nxt) < MIN_SIDE_LEN ** 2:
            break

        if len(points) > 2:
            second = points[1]
            if (vecprod(curr, first, nxt) >= 0 or
                vecprod(second, first, nxt) >= 0): # non-convex
                break

        points.append(nxt)

    if len(points) <= 2:
        # this should only happen when the third vertex somehow ends
        # up really close to the first one, which is very unlikely.
        return None # fail

    a1 = get_angle(points[-2], points[-1], points[0])
    a2 = get_angle(points[-1], points[0], points[1])
    if (not (MIN_ANGLE <= a1 <= MAX_ANGLE) or
        not (MIN_ANGLE <= a2 <= MAX_ANGLE)):
        # print(a1, a2)
        return None

    return points

def rand_test(mean_n_sides):
    while True:
        points = rand_polygon(mean_n_sides)
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

    diff_x = int(maxx - minx)
    diff_y = int(maxy - miny)

    dimx = random.randint(max(diff_x + 2 * MIN_GAP, MIN_DIM), MAX_DIM)
    dimy = random.randint(max(diff_y + 2 * MIN_GAP, MIN_DIM), MAX_DIM)

    x_to_add = random.randint(2 * MIN_GAP, 2 * MAX_GAP) + max(MIN_DIM - diff_x, 0)
    y_to_add = random.randint(2 * MIN_GAP, 2 * MAX_GAP) + max(MIN_DIM - diff_y, 0)

    gap_xl = random.randint(MIN_GAP, dimx - diff_x - MIN_GAP)
    gap_yl = random.randint(MIN_GAP, dimy - diff_y - MIN_GAP)

    maxx = 0
    maxy = 0
    coords = [ ]
    for p in points:
        x = int(np.round(p[0] - minx)) + gap_xl
        y = int(np.round(p[1] - miny)) + gap_yl
        maxx = max(x, maxx)
        maxy = max(y, maxy)
        coords.append((x, y))

    img = np.ones((dimy, dimx), np.uint8) * 255

    sides = len(coords)
    for i in range(sides):
        p = coords[i]
        p = (p[0], dimy - p[1] - 1)
        coords[i] = p

    width = random.randint(MIN_WIDTH, MAX_WIDTH)
    coords.append(coords[0])
    for i in range(sides):
        cv.line(img, coords[i], coords[i + 1], 0, thickness=width)

    return sides, img

if __name__ == '__main__':
    for i in range(N_TESTS):
        mean_sides = random.randint(3, 10)

        print_test(*rand_test(mean_sides))
