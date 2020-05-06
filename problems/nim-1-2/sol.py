import sys

f = sys.stdin

n = int(f.readline())

while True:
    if n % 3 == 2:
        d = 1
    else:
        d = 2

    print(d)
    sys.stdout.flush()
    n -= d

    if n == 1:
        break
    
    d = int(f.readline())
    n -= d
