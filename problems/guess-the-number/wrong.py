import sys

f = sys.stdin

n = int(f.readline())

for i in range(1, n + 1):
    print(i)
    sys.stdout.flush()
    res = int(f.readline())
    if res == 0:
        break
