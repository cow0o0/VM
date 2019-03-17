from xprint import to_hex, to_x,to_x_32
from libnum import s2n,n2s
from struct import pack

a = -12
b = to_x_32(a)
c = "0"*(8-len(b))+b
re = []
for i in range(4):
    re.append(c[i*2:i*2+2])
a = ''.join(re)
d = int(a,16)
print d