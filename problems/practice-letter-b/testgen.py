N_TESTS   = 10
MAX_LEN   = 1000

import os
import random

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = 1
def print_test(s):
    global curr_test

    assert(curr_test <= N_TESTS)
    assert(1 <= len(s) <= MAX_LEN)

    print('printing test %d' % curr_test)
    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%s\n' % s)

    curr_test += 1

import string

letters = string.ascii_lowercase

# sample tests
print_test("abracadabra")
print_test("abbazabba")

print_test("b" * MAX_LEN)
print_test("a" * MAX_LEN)

while curr_test <= N_TESTS:
    n = random.randint(1, MAX_LEN)
    s = ''.join(random.choice(letters) for i in range(n))
    print_test(s)
