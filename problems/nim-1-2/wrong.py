import sys

f = sys.stdin

n = int(f.readline())

while True:
    d = 1

    print(d)
    sys.stdout.flush()

    n -= d

    if n == 1:
        break
    
    d = int(f.readline())
    n -= d
