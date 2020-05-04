import sys
import random

random.seed(0)

f = sys.stdin

E = f.readline().rstrip()
n = len(E)

iters = 100
qlen  = 50

for i in range(100):
    s = random.randint(0, n - qlen)
    print(E[s : s + qlen])
    sys.stdout.flush()
    ans = f.readline().rstrip()
    if ans == "Yes":
        print("Earthovirus")
        sys.stdout.flush()
        exit(0)

print("Marsovirus")
sys.stdout.flush()
