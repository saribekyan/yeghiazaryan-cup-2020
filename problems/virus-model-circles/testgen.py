N_TESTS   = 40
MANUAL_TESTS = 0

MAX_VALS = 10 ** 5

import os
import random

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = MANUAL_TESTS + 1
def print_test(T, *vals):
    global curr_test

    assert(MANUAL_TESTS < curr_test <= N_TESTS)

    assert(1 <= T <= MAX_VALS)
    assert(type(T) == int)

    vals = list(vals)
    assert(len(vals) == 8)
    for x in vals:
        assert(type(x) == int)
        assert(-MAX_VALS <= x <= MAX_VALS)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%d\n' % T)
        for i in range(8):
            f.write('%d' % vals[i])
            if i % 4 == 3:
                f.write('\n')
            else:
                f.write(' ')

    curr_test += 1

def rand_shift(test, max_shuffle=MAX_VALS // 2):
    test = list(test)
    for i in range(0, 4):
        x = random.randint(-max_shuffle, max_shuffle)
        test[i + 1] += x
        test[i + 5] += x
    return test

def rand_line_closeby():
    test = [ None ] * 9
    x0 = random.randint(-2, 2)
    y0 = random.randint(-2, 2)

    f = random.randint(1, MAX_VALS // 2)
    f2 = 3 * f
    vx = random.randint(-MAX_VALS // f2, MAX_VALS // f2)
    vy = random.randint(-MAX_VALS // f2, MAX_VALS // f2)

    x1 = x0 - f * vx
    y1 = y0 - f * vy
    
    t = random.randint(1, 2 * f)
    return [t, 0, 0, 0, 0, x1, y1, vx, vy]

# test types
# no segment-circle intersection:
#  x 0.1. T is small, but the line intersects
#  x 0.2. T is large and the line does not intersect
#  x 0.3. If they moved the oppposite direction, they would intersect.
# one common segment-circle point:
#  x 1.1. Line is tangential
#  x 1.2. They meet at time T exactly
#  x 1.3. They meet at time 0 exactly
# infinite common points:
#  x 2.1. Time 0 is inside the circle, but not at time T
#  x 2.2. Time T is inside the circle, but not at the 0
#  x 2.3. Inside both at time T and 0 and moving
#  x 2.4. (standard) Starts outside, meets infinitely many points, leaves
# no segment exists
#  x 3.1. Stuck far away
#  x 3.2. Stuck on edge
#  x 3.3. Stuck inside

manuals = [ ]

# type 1.1
manuals.append([5,
           2, 0, 0, 1,
           0, 7, 0, -1])

# type 0.1
manuals.append([2,
           0, 0, 1, 1,
           8, 8, -1, -1])

# type 2.4
manuals.append([5,
           -3, -1, 2, 3,
           4, 2, -1, 2])

######## end of sample tests ########## TODO - are they good?

# type 0.2
manuals.append([100,
                0, 0, 0, 0,
                10, 10, 0, -40])

# type 0.3
manuals.append([100,
                1, 2, 1, 2,
                -1, -1, -1, -1])

# type 1.2
manuals.append([4,
                0, 0, 1, 0,
                10, 0, -1, 0])

# type 1.3
manuals.append([100,
                0, 0, 0, 0,
                2, 0, 1, 0])

# type 2.1
manuals.append([50,
                0, 0, 0, 0,
                1, 0, 10, 10])

# type 2.2
manuals.append([200,
                0, 0, 0, 0,
                200, 0, -1, 0])

# type 2.3
manuals.append([2,
                0, 0, 0, 0,
                -1, -1, 1, 1])

# type 3.1
manuals.append([10,
                1, 2, 3, 4,
                5, 6, 3, 4])

# type 3.2
manuals.append([50,
                0, 0, 0, 0,
                -2, 0, 0, 0])

# type 3.3
manuals.append([1,
                5, 6, 7, 8,
                6, 7, 7, 8])

######### large manuals ##########

manuals.append([MAX_VALS,
                0, 0, 0, 0,
                MAX_VALS // 2, 3, -1, 0])

manuals.append([MAX_VALS,
                0, 0, 0, 0,
                MAX_VALS // 2, 1, -1, 0])

# sample tests
for i in range(len(manuals)):
    if i < 3: # sample tests
        print_test(*manuals[i])
    else:
        print_test(*rand_shift(manuals[i]))

while curr_test <= N_TESTS:
    print_test(*rand_shift(rand_line_closeby()))
