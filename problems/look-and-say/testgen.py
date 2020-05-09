N_TESTS   = 16

MAX_N = 16

import os
import random

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = 1
def print_test(n):
    global curr_test

    assert(1 <= curr_test <= N_TESTS)
    assert(1 <= n <= MAX_N)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%d\n' % n)

    curr_test += 1

for n in range(1, MAX_N + 1):
    print_test(n)
