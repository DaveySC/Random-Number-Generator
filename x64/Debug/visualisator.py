import matplotlib.pyplot as plt
from sys import argv
from matplotlib.ticker import NullFormatter

file_name = 'rnd.dat'
if (len(argv) == 2):
    file_name = argv[1]

l = []
with open(file_name) as f:
    for line in f:
        for x in line.split():
            l.append(int(x))


fig, ax = plt.subplots()

ax.scatter(range(len(l)), l, c='#F08080', s=10)
#ax.scatter(l, range(len(l)), c='#F08080', s=10)

#ax.yaxis.set_major_formatter(NullFormatter())
ax.set_facecolor('#FFFACD')

plt.show()
