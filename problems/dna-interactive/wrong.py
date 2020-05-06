# error = "wa-bad-algo"
# error = "wa-rand-reply"
# error = "wa-too-many-queries"
# error = "wa-too-many-chars"
# error = "pe"
# error = "tle"
# error = "client-quit"

MAX_Q = 100
MAX_CHARS = 1000000

import sys
import random
import time

random.seed(0)

f = sys.stdin

E = f.readline().rstrip()
n = len(E)

if error == "wa-bad-algo":
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

    print("Randovirus")
    sys.stdout.flush()

elif error == "wa-rand-reply":
    print(random.choice(["Earthovirus", "Randovirus"]))
    sys.stdout.flush()

elif error == "wa-too-many-queries":
    for i in range(MAX_Q + 1):
        print("A")
        sys.stdout.flush()
        f.readline()

elif error == "wa-too-many-chars":
    print("A" * (MAX_CHARS + 1))
    sys.stdout.flush()

elif error == "pe":
    print("Should get a presentation error")
    sys.stdout.flush()

elif error == "tle":
    print("A")
    sys.stdout.flush()
    time.sleep(3)

elif error == "client-quit":
    exit(0)

else:
    exit(1)
