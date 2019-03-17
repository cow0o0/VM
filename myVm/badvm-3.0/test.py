data = open("log.txt","r").read()
a = data.find('''[*]---- Start vmCode ----''')
src_code = data[:a]

print(src_code)
print(data[a:])