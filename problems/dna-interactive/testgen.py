N_TESTS  = 40
MAX_N    = 10 ** 5
LEN_LOST = 100

DNA = 'AGCT'

import os
import random

random.seed(0)

script_path = os.path.realpath(__file__)
dir_path    = os.path.dirname(script_path)
test_dir    = os.path.join(dir_path, 'tests')

if not os.path.exists(test_dir):
    os.mkdir(test_dir)

curr_test = 1
def print_test(E, X, same):
    global curr_test

    if curr_test > N_TESTS:
        print("Done!")
        return

    n = len(E)
    # assert(1 <= curr_test <= N_TESTS)
    assert(1 <= len(E) <= MAX_N)
    assert(n / 2 <= sum(map(len, X)))
    for x in X:
        assert(len(x) >= LEN_LOST)
    assert(same == 0 or same == 1)

    print('printing test %d' % curr_test)
    print('%f percent of DNA remains' % (100.0 * sum(map(len, X)) / n))

    fname = os.path.join(test_dir, '%03d' % curr_test)
    with open(fname, 'w') as f:
        f.write('%s\n' % E)
        f.write('%d\n' % same)
        f.write('%d\n' % len(X))
        for x in X:
            f.write('%s\n' % x)

    # create empty out files since they are required by the interactor
    with open(fname + ".a", 'w'):
        pass

    curr_test += 1
    print()

def rand_dna(n):
    return ''.join(random.choices(DNA, k=n))

def break_dna(D, cuts):
    n = len(D)
    cuts = sorted(cuts) + [ n ]
    X = [ ]
    l = 0
    for r in cuts:
        if r - l >= LEN_LOST:
            X.append(D[l:r])
        l = r
    return X

def rand_save(save, n_saved):
    n = len(save)
    saved_chars = save.count(True)
    while saved_chars < n_saved:
        i = random.randint(0, n - LEN_LOST)
        j = i + LEN_LOST
        if save[i:j].count(False) > 0:
            continue
        for p in range(i, j):
            if save[p] is None:
                saved_chars += 1
            save[p] = True
    return save

def cut_everywhere(save):
    return [ i for i, x in enumerate(save) if not x ] # can be None too

def cut_false(save):
    return [ i for i, x in enumerate(save) if x is False ]

def cut_rand(save):
    n = len(save)
    cuts = cut_false(save)
    new_cuts = [ i for i, x in enumerate(save) if x is None ]
    ncuts = random.randint(len(new_cuts) // 40, len(new_cuts) // 20)
    cuts += random.choices(new_cuts, k = ncuts)
    return cuts

def cut_every_so_often(save):
    n = len(save)
    cuts = cut_false(save)
    for i in range(0, n, LEN_LOST // 2):
        if not save[i]:
            cuts.append(i)
    return cuts

def make_test(n, cut_f, same):
    E = rand_dna(n)
    if same == 1:
        D = E
    else:
        D = rand_dna(n)

    # which character we keep
    # None - means have not decided yet
    save = [ None ] * n

    save = rand_save(save, n / 2)
    cuts = cut_f(save)
    X = break_dna(D, cuts)
    return E, X, same

print_test( *make_test( LEN_LOST, cut_rand, 1 ) )
print_test( *make_test( LEN_LOST, cut_rand, 0 ) )

print_test( *make_test( 5 * LEN_LOST, cut_rand, 1 ) )
print_test( *make_test( 5 * LEN_LOST, cut_rand, 0 ) )

while curr_test <= N_TESTS:
    n = random.randint(LEN_LOST, MAX_N)
    cut_f = random.choice([cut_rand , cut_every_so_often, cut_everywhere ])
    same = random.randint(0, 1)

    print_test(*make_test( n, cut_f , same ))
