N_TESTS   = 20
MAX_N   = 10000

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

    assert(curr_test <= N_TESTS)
    assert(1 <= n <= MAX_N)
    assert(n % 3 != 1)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%d\n' % n)

    # create empty out files since they are required by the interactor
    with open(fname + ".a", 'w'):
        pass

    curr_test += 1

# sample tests
print_test(3)
print_test(5)

while curr_test <= N_TESTS:
    n = random.randint(4, MAX_N)
    if n % 3 == 1:
        n -= random.randint(1, 2)
    print_test(n)
