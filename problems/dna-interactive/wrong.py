import sys
import random

random.seed(0)

f = sys.stdin

E = f.readline().rstrip()
n = len(E)

iters = 100

s = 0
while s + 10 < n:
    qlen = random.randint(10, 1000)
    print(E[s : s + qlen])
    sys.stdout.flush()
    ans = f.readline().rstrip()
    if ans == "Yes":
        print("Earthovirus")
        sys.stdout.flush()
        exit(0)
    s += 1

print("Marsovirus")
sys.stdout.flush()
