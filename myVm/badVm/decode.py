
enc = [118 ,48 ,51, 68, 45, 64, 47, 101, 43 ,123, 105 ,84 ,113, 61, 115  ,68]

dec = []
for i in range(len(enc)):
    j = (0x30+15-i)^enc[i]
    dec.append(j)

print (dec)

# [73, 14, 14, 120, 22, 122, 22, 93, 28, 77, 92, 96, 66, 15, 66, 116]