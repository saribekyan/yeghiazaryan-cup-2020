N_TESTS   = 20
MAX_N   = 10 ** 6
MAX_Q   = 100

import os
import random

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = 1
def print_test(n, h):
    global curr_test

    assert(curr_test <= N_TESTS)
    assert(1 <= n <= MAX_N)
    assert(1 <= h <= n)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%d %d\n' % (n, h))

    # create empty out files since they are required by the interactor
    with open(fname + ".a", 'w'):
        pass

    curr_test += 1

# sample tests
print_test(5, 4)
print_test(10, 6)
print_test(2, 2)
print_test(1, 1)

print_test(MAX_N, 1)
print_test(MAX_N, MAX_N)
print_test(MAX_N, 2 * MAX_Q)
print_test(MAX_N, MAX_N - 2 * MAX_Q)

while curr_test <= N_TESTS:
    n = random.randint(1, MAX_N)
    h = random.randint(1, n)
    print_test(n, h)
