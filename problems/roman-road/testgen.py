N_TESTS   = 20
FIRST_TEST = 5

MAX_N = 10 ** 5
MAX_L = 10 ** 9
MAX_W = 10 ** 7

MAX_ti = 10 ** 9
MAX_si = 10 ** 9


import os
import random
import numpy as np

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = FIRST_TEST

def print_test(L, W, t, s, w):
    global curr_test

    assert(curr_test <= N_TESTS)

    N = len(t)

    assert(len(s) == N and len(w) == N)
    assert(1 <= N <= MAX_N)
    assert(1 <= L <= MAX_L)
    assert(1 <= W <= MAX_W)

    assert((0 <= t).all() and (t <= MAX_ti).all())
    assert((1 <= s).all() and (s <= MAX_si).all())
    assert((1 <= w).all() and (w <= W).all())

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%d %d %d\n' % (N, L, W))
        data = np.array([t, s, w]).transpose()
        np.savetxt(f, data, fmt='%d')

    curr_test += 1

def rand_test(N):
    W = random.randint(1, MAX_W)
    L = random.randint(1, MAX_L)
    wi = np.random.randint(1, W, N)
    ti = np.random.randint(0, MAX_ti, N)
    si = np.random.randint(0, MAX_si, N)

    return (L, W, ti, si, wi)

while curr_test <= N_TESTS:
    if curr_test <= N_TESTS - 5:
        N = random.randint(1, MAX_N)
    else:
        N = MAX_N
    print_test(*rand_test(N))
