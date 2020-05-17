N_TESTS   = 10
MAX_A   = 10 ** 9

import os
import random

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = 1
def print_test(a, b):
    global curr_test

    assert(curr_test <= N_TESTS)
    assert(-MAX_A <= a <= MAX_A)
    assert(-MAX_A <= b <= MAX_A)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%d %d\n' % (a, b))

    curr_test += 1

# sample tests
print_test(2, 2)
print_test(1, 4)

while curr_test <= N_TESTS:
    a = random.randint(-MAX_A, MAX_A)
    b = random.randint(-MAX_A, MAX_A)
    print_test(a, b)
