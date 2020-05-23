import urllib
import time

f = open('tests/001', 'r')

Q = [ ]
for s in f.readlines():
    x = s.split()
    Q.append((int(x[10]), int(x[8]), int(x[5])))

for y, r, p in Q:
    try:
        year_str = str(urllib.request.urlopen("https://www.statsf1.com/en/%d.aspx" % y).read())

        gp_row = year_str[year_str.find("%d. " % r): ]
        gp_href = gp_row[gp_row.find("%d/" % y):]
        gp_name = gp_href[5:gp_href.find(".")]
        # gp_ind = year_str.find("%d. " % r)
        # gp_len = year_str[gp_ind:].find("\\")
        # gp_name = year_str[gp_ind + 2 + len(str(r)) : gp_ind + gp_len]
        # gp_name = gp_name.lower()

        # print(y, gp_name)

        res_str = str(urllib.request.urlopen("https://www.statsf1.com/en/%d/%s/classement.aspx" % (y, gp_name)).read())

        table = res_str[res_str.find("Pos"):]
        row = table[table.find('\\t<td align="right">%d</td>' % p):]

        item = row
        for i in range(4):
            item = item[item.find("<td")+1:]

        ans_cut = None
        for i in range(len(item) - 1):
            if item[i] == '>' and item[i+1].isupper():
                ans_cut = item[i+1:]
                break

        if ans_cut is None:
            print("1 - Couldn't find for %d %d %d" % (y, r, p))
        else:
            ans = ans_cut[:ans_cut.find("<")]
            print(ans)
    except e:
        print("2 - Couldn't find for %d %d %d" % (y, r, p))

        print("sleeping")
        time.sleep(5)

