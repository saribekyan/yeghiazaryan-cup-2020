import sys

f = sys.stdin

n = int(f.readline())

s = '1'
for i in range(2, n + 1):
    c = 1
    new_s = ''
    s += '#'
    for j in range(1, len(s)):
        if s[j] != s[j - 1]:
            new_s += str(c) + s[j - 1]
            c = 1
        else:
            c += 1
    s = new_s

print(s)
