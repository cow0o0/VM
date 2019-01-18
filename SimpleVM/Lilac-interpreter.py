with open("code") as f:
    code = map(ord, f.read())
print code
inst = {
    0: ("exit", 0),
    1: ("push", 4),
    2: ("pop", 0),
    3: ("add", 2),
    4: ("sub", 2),
    5: ("mul", 2, ''),
    6: ("rshift", 2, ''),
    7: ("mov", 2),
    8: ("movs", 2),
    9: ("xor", 2),
    10: ("or", 2)
}

ip = 0
disasm = ''
while True:
    if ip >= len(code):
        break
    opcode = code[ip]
    if not inst.has_key(opcode):
        disasm += "invalid\n"
        continue
    mnem = inst[opcode][0]
    addition = inst[opcode][1]
    if addition == 0:
        oprand = ''
    elif addition == 4:
        num = code[ip+1] + (code[ip+2] << 8) + (code[ip+3] << 16) + (code[ip+4] << 24)
        oprand = hex(num)
    elif addition == 2 and len(inst[opcode]) != 3:
        oprand = "[%d], [%d]" % (code[ip+1], code[ip+2])
    elif addition == 2:
        oprand = "[%d], %d" % (code[ip+1], code[ip+2])

    disasm += "0x%02x: %s %s\n" % (ip, mnem, oprand)
    ip += addition+1
print disasm