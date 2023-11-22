import csv

d = [0]
dd = [0]
for row in csv.reader(open('my_results.csv')):
    n = int(row[1])
    d.append(n)
    dd.append(dd[-1] + n)

assert(sum(d) == dd[-1])

for n in range(1, len(d)):
    assert(sum(d[:n+1]) == dd[n])
    print(n, dd[n] * 100 / dd[-1])
