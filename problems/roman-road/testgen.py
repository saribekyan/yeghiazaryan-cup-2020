N_TESTS   = 40
FIRST_TEST = 6

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

def all_pairs_intersecting(N, stuck):
    W = random.randint(2, MAX_W)
    L = MAX_L
    if stuck:
        wi = np.ones(N, dtype='int') * W
    else:
        wi = np.ones(N, dtype='int') * (W // 2)
    ti = np.arange(N, dtype='int') * 100
    si = (np.arange(N, dtype='int') + 1) * 100

    return (L, W, ti, si, wi)

def mixed(N, stuck):
    W = random.randint(3, MAX_W)
    L = random.randint(MAX_L // 2, MAX_L)

    wi1 = np.random.randint(1, W // 3, N // 2)
    wi2 = np.random.randint(W - 2 * (W // 3), W - (W // 3), N - N // 2)
    wi = np.concatenate([wi1, wi2])

    if stuck:
        ti = np.arange(N, dtype='int') * 100
        si = (np.arange(N, dtype='int') + 1) * 100
    else:
        ti = np.random.randint(0, MAX_ti, N)
        si = np.random.randint(0, MAX_si, N)

    return (L, W, ti, si, wi)

def no_conflict(N):
    W = random.randint(1, MAX_W)
    L = MAX_L
    ti = np.random.randint(0, MAX_ti // 1000, N)
    si = MAX_si // (ti + 1)
    wi = np.random.randint(1, W, N)

    return (L, W, ti, si, wi)


print_test(*rand_test(10))
print_test(*all_pairs_intersecting(10, True))
print_test(*all_pairs_intersecting(10, False))
print_test(*mixed(10, True))
print_test(*mixed(10, False))
print_test(*no_conflict(10))

while curr_test <= N_TESTS:
    if curr_test <= N_TESTS - 10:
        N = random.randint(1, MAX_N)
    else:
        N = MAX_N

    if curr_test % 5 == 0:
        test = rand_test(N)
    elif curr_test % 5 == 1:
        test = all_pairs_intersecting(N, True)
    elif curr_test % 5 == 2:
        test = all_pairs_intersecting(N, False)
    elif curr_test % 5 == 3:
        test = mixed(N, random.choice([True, False]))
    elif curr_test % 5 == 4:
        test = no_conflict(N)

    print_test(*test)
