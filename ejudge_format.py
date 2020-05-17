import sys
import argparse
import os
from os import path
import string
import shutil

src_in = ""
src_out = ".a"

dst_in = ".in"
dst_out = ".out"

def parse_args():
    parser = argparse.ArgumentParser(description='Convert contest to the ejudge default format.')

    parser.add_argument('ejudge', type=str,
                        help='path to the ejudge contest root')

    parser.add_argument('--tex', type=str,
                        dest='texfile',
                        help='path to the main statements.tex; converts all problems')

    parser.add_argument('--prob_path', dest='problem_path',
                        help='path to a problem to be converted')

    parser.add_argument('--letter', dest='letter',
                        help='letter to convert a problem to')

    args = parser.parse_args()

    if not path.isdir(args.ejudge):
        print("No ejudge dir found... qutting...")
        exit(1)

    if not ( (args.texfile is None) ^ ( args.problem_path is None) ):
        print("Either give a problem or a tex file... not both and not none... quitting...")
        exit(1)

    if (args.problem_path is not None):
        args.problem_path = path.abspath(args.problem_path)
        if (args.letter is None):
            print("You gave me a problem, but not a letter... quitting...")
            exit(1)
        
        if (args.letter not in string.ascii_uppercase):
            print("The letter is not an ascii uppercase... quitting...")
            exit(1)

        if not path.isdir(args.problem_path):
            print("No such problem %s... quitting..." % args.problem_path)
            exit(1)

        args.problems_base = path.dirname(args.problem_path)
        args.problem_name = path.basename(args.problem_path)

    else:
        args.texfile = path.abspath(args.texfile)
        if not path.isfile(args.texfile):
            print("No such file %s... quitting..." % args.texfile)
            exit(1)

        args.contest_base = path.dirname(path.dirname(args.texfile))
        args.problems_base = path.join(args.contest_base, 'problems')

    if not path.isdir(args.problems_base):
        print("No problem base found at %s... quitting..." % args.problems_base)
        exit(1)
    
    print("Parsed successfully")
    print()
    return args

def get_problems_from_tex(texfile):
    problem_list = [ ]
    letter_id = 0
    with open(texfile, 'r') as f:
        for line in f.readlines():
            if line.startswith('\\includeproblem{'):
                st = line.find('{')
                en = line.find('}')
                problem_list.append(
                    (line[st + 1:en], string.ascii_uppercase[letter_id]))
                letter_id += 1
    return problem_list

def convert_problem(problems_base, problem, ejudge, letter):
    print("Creating problem %s -> %s" % (problem, letter))
    problem_path = path.join(problems_base, problem)

    dest_dir = path.join(ejudge, 'problems', letter)

    if path.isdir(dest_dir):
        print("Destination directory exists for problem %s. Overwrite? y/n" % letter)
        ans = sys.stdin.readline()
        if ans[0] != 'y':
            print('Ok, skipping problem %s -> %s' % (problem, letter))
            print()
            return
        else:
            shutil.rmtree(dest_dir)

    dest_tests_dir = path.join(dest_dir, "tests")
    os.makedirs(dest_tests_dir)

    src_tests_dir = path.join(problem_path, "tests")

    tests_list = os.listdir(src_tests_dir)
    print(tests_list)

    n_moved = 0
    for f in tests_list:
        try:
            test = f.split('.')[0]
            if 0 < int(test) <= 999:
                if f == test + src_in:
                    shutil.copy(path.join(src_tests_dir, f),
                                path.join(dest_tests_dir, test + dst_in))
                    n_moved += 1
                elif f == test + src_out:
                    shutil.copy(path.join(src_tests_dir, f),
                                path.join(dest_tests_dir, test + dst_out))
                    n_moved += 1
                    
        except:
            pass
    
    n_warnings = 0

    print("  %d test files moved" % n_moved)
    if n_moved % 2 != 0:
        print("  WARNING - odd number of test files")
        n_warnings += 1
    if n_moved < 10:
        print("  WARNING - only %d tests?" % (n_moved))
        n_warnings += 1
    print()

    checkers_dir = path.join(ejudge, 'checkers')
    if not path.isdir(checkers_dir):
        os.mkdir(checkers_dir)

    small_letter = letter.lower()

    for prog in ['interactor', 'checker', 'check']:
        src_file = path.join(problem_path, prog + '.cpp')
        if path.isfile(src_file):
            print("Looks like %s has %s.cpp . Copying to ejudge" % (problem, prog))
            if prog == 'interactor':
                dest_fname = 'interactor'
            else:
                dest_fname = 'check'
            dest_fname += '_' + small_letter + '.cpp'

            dst_file = path.join(dest_dir, dest_fname)
            shutil.copy(src_file, dst_file)

            dst_file = path.join(checkers_dir, dest_fname)
            shutil.copy(src_file, dst_file)

            print("Do you want me to build %s ? y/n" % (dest_fname))
            if sys.stdin.readline()[0] == 'y':
                out_fname = dest_fname.split('.')[0]
                out_path = path.join(dest_dir, out_fname)
                cmd = "g++ %s -O3 -o %s" % (src_file, out_path)

                print("  Running cmd: %s" % cmd)
                res = os.system(cmd)
                if res != 0:
                    print("    The result was non zero: %d, go figure it out.. contiuing..." % res)
                    n_warnings += 1
                print()

    print("Done problem %s -> %s" % (problem, letter))
    print()

    return n_warnings

if __name__ == '__main__':
    args = parse_args()

    if args.texfile is not None:
        problems_to_convert = get_problems_from_tex(args.texfile)
    else:
        problems_to_convert = [ (args.problem_name, args.letter) ]
    
    print("I will convert:")
    for (problem, letter) in problems_to_convert:
        print("  %s -> %s" % (problem, letter))
    print()
    print("Destination contest: %s" % (args.ejudge))
    print()
    print("  expecting extension \"%s\" for input  -> \"%s\"" % (src_in, dst_in))
    print("  expecting extension \"%s\" for output -> \"%s\"" % (src_out, dst_out))

    print("OK? y/n")
    if sys.stdin.readline()[0] != 'y':
        print("quitting...")
        exit(1)

    n_warnings = 0
    for problem, letter in problems_to_convert:
        n_warnings += convert_problem(
            args.problems_base, problem,
            args.ejudge,
            letter)

    if n_warnings > 0:
        print("There were %d WARNINGS above" % n_warnings)
