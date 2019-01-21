#-*-coding:utf-8-*-
code=[0x09,0x03,0x0D,0x00,0x09,0x00,0x0D,0x01,0x09,0x00,0x0D,0x02,0x0B,0x01,0x0B,0x00,0x04,0x08,0x23,0x0B,0x01,0x09,0x01,0x01,0x0D,0x01,0x0B,0x02,0x0B,0x01,0x01,0x0D,0x02,0x06,0x0C,0x0B,0x02,0x0E,0x10]

def interpreter():
    inst = {
    0: "noop",
    1: "iadd",
    2: "isub",
    3: "imul",
    4: "ilt",
    5: "ieq",
    6: "br",
    7: "brt",
    8: "brf",
    9: "iconst",
    10: "load",
    11: "gload",
    12: "store",
    13: "gstore",
    14: "print",
    15: "pop",
    16: "halt",
    }

    index = 0
    while 1:
        op = code[index]
        if inst[op] == "halt" :
            print "%s: exit" % (inst[op])
            break
        if inst[op] == "iadd" :
            print "%s: r0 = r0 + r1" % (inst[op])
            index = index + 1
            continue
        if inst[op] == "print" :
            print "%s: " % (inst[op])
            index = index + 1
            continue
        if inst[op] == "gstore" :
            d_index = code[index+1]
            print "%s: d%d = r0" % (inst[op],d_index)
            index = index + 2
            continue
        if inst[op] == "ilt" :
            print "%s: JL" % (inst[op])
            index = index + 1
            continue
        if inst[op] == "brf" :
            d_index = code[index+1]
            print "%s: jmp %d" % (inst[op],d_index)
            index = index + 2
            continue
        if inst[op] == "br" :
            d_index = code[index+1]
            print "%s: jmp %d" % (inst[op],d_index)
            index = index + 2
            continue
        if inst[op] == "gload" :
            d_index = code[index+1]
            print "%s: r0 = d%d " % (inst[op],d_index)
            index = index + 2
            continue
        if inst[op] == "iconst" :
            d_index = code[index+1]
            print "%s: r0 = %d " % (inst[op],d_index)
            index = index + 2
            continue
        index = index + 1

interpreter()