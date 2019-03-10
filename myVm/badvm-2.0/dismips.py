from capstone import *


fp = open("login","rb").read()

CODE = fp[0xE34:0xEA4]

md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32+CS_MODE_LITTLE_ENDIAN)
md.detail = True
for i in md.disasm(CODE, 0x400E34):
    print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))


# md = Cs(CS_ARCH_X86, CS_MODE_64)
# for (address, size, mnemonic, op_str) in md.disasm_lite(CODE, 0x1000):
# 	print("0x%x:\t%s\t%s" %(address, mnemonic, op_str))