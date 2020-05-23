import os
import sys

for i in range(1, 27):
    os.system('cp bugs/data/bugs_%02d.in tests/%03d' % (i, i + 2))
    os.system('cp bugs/data/bugs_%02d.ans tests/%03d.a' % (i, i + 2))
