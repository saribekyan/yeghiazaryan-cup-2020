# remove the lines where hayk-sol made a mistake

mistakes = open('hayk-orig-sol-mistakes.txt', 'r').readlines()

mistakes = [int(x.split()[0]) - 1 for x in mistakes]
print(len(mistakes))
print(mistakes)
print()

fin = open('tests-orig/001', 'r')

Q = [ ]
for s in fin.readlines():
    x = s.split()
    Q.append((int(x[10]), int(x[8]), int(x[5])))

print(len(Q))

fout = open('tests-orig/001.a', 'r')
ans = [x.strip() for x in fout.readlines()]

print(len(ans))

new_in = open('tests/001', 'w')
new_out = open('tests/001.a', 'w')

for i in range(len(Q)):
    y, r, p = Q[i]
    if not (i in mistakes):
        new_in.write("Which company was at position %d in race %d of %d F1 Grands Prix?\n"
                        % (p, r, y))
        new_out.write("%s\n" % ans[i])
