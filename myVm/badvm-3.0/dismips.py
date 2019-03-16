# from __future__ import print_function
from capstone import *
from capstone.mips import *
from xprint import to_hex, to_x
from libnum import n2s,s2n
import random

def print_mips(md):
    print ("[*]---- Start disassemble ----")
    for i in md.disasm(CODE, BASE_ADDR + START):
        print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
    print ("[*]---- Finish disassemble ----")

def getOffset(md):
    offset = 0
    offset_table = []
    for insn in md.disasm(CODE, BASE_ADDR + START):
        if insn.mnemonic == "sb":
            offset_table.append(offset)
            offset += 6
        if insn.mnemonic == "lbu":
            offset_table.append(offset)
            offset += 6
        if insn.mnemonic == "lb":
            offset_table.append(offset)
            offset += 6
        if insn.mnemonic == "addiu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "addi":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "addu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "add":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "subiu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "subi":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "subu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sub":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "muliu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "muli":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "mulu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "mul":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "andi":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "andiu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "andu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "and":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sll":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sllv":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sra":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "srl":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "srav":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "srlv":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "xor":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "xori":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "nor":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "nori":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sltiu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "slti":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "slt":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sltu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "bnez":
            offset_table.append(offset)
            offset += 3
        if insn.mnemonic == "bne":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "beqz":
            offset_table.append(offset)
            offset += 3
        if insn.mnemonic == "beq":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "b":
            offset_table.append(offset)
            offset += 2
        if insn.mnemonic == "nop":
            offset_table.append(offset)
            offset += 1
    return offset_table

def print_vmCode(md):
    print ("[*]---- Start vmCode ----")
    offset_table = getOffset(md)
    for insn in md.disasm(CODE, BASE_ADDR + START):
        if insn.id == 0:
            return
        reg_name = []
        if len(insn.operands) > 0:
            for i in insn.operands:
                if i.type == MIPS_OP_REG:
                    reg_name.append(insn.reg_name(i.reg))
                if i.type == MIPS_OP_IMM:
                    imm = to_x(i.imm)
                if i.type == MIPS_OP_MEM:
                    if i.mem.base != 0:
                        mem_base = insn.reg_name(i.mem.base)
                    if i.mem.disp != 0:
                        mem_disp =  to_x(i.mem.disp & 0xffffffff)
        if(DEBUG):
            print("#0x%x:\t%s\t%s" %(insn.address, insn.mnemonic, insn.op_str))
        
        #sb 
        if insn.mnemonic == "sb":
            print("\tMovImm2Reg,0x%s,RFPO," % (mem_disp))
            print("\tMovReg2Mem,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[mem_base]))

        #lbu lb
        if insn.mnemonic == "lbu":
            print("\tMovImm2Reg,0x%s,RFPO," % (mem_disp))
            print("\tMovMem2Reg,%s,%s," % (REG_TABLE[mem_base],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "lb":
            print("\tMovImm2Reg,0x%s,RFPO," % (mem_disp))
            print("\tMovMem2Reg,%s,%s," % (REG_TABLE[mem_base],REG_TABLE[reg_name[0]]))
        #addiu addi addu add
        if insn.mnemonic == "addiu":
            if REG_TABLE[reg_name[1]] == "RFP":
                imm = hex((int(imm,16) * 4))[2:]
            print("\tAddReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "addi":
            if REG_TABLE[reg_name[1]] == "RFP":
                imm = hex((int(imm,16) * 4))[2:]
            print("\tAddReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "addu":
            print("\tAddReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "add":
            print("\tAddReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        
        #subiu subi subu sub
        if insn.mnemonic == "subiu":
            print("\tSubReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "subi":
            print("\tSubReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "subu":
            print("\tSubReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "sub":
            print("\tSubReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #muliu muli mulu mul
        if insn.mnemonic == "muliu":
            print("\tMulReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "muli":
            print("\tMulReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "mulu":
            print("\tMulReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "mul":
            print("\tMulReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #andi andiu andu and
        if insn.mnemonic == "andi":
            print("\tAndReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "andiu":
            print("\tAndReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "andu":
            print("\tAndReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "and":
            print("\tAndReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #sll sllv
        if insn.mnemonic == "sll":
            print("\tSllReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "sllv":
            print("\tSllReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #sra srl srav srlv
        if insn.mnemonic == "sra":
            print("\tSraReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))   
        if insn.mnemonic == "srl":
            print("\tSraReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "srav":
            print("\tSraReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "srlv":
            print("\tSraReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #xor xori
        if insn.mnemonic == "xor":
            print("\tXorReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]])) 
        if insn.mnemonic == "xori":
            print("\tXorReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 

        #nor nori
        if insn.mnemonic == "nor":
            print("\tNorReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]])) 
        if insn.mnemonic == "nori":
            print("\tNorReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 

        #sltiu slti slt sltu
        if insn.mnemonic == "sltiu":
            print("\tSetLessThanImm,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
        if insn.mnemonic == "slti":
            print("\tSetLessThanImm,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
        if insn.mnemonic == "slt":
            print("\tSetLessThanReg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "sltu":
            print("\tSetLessThanReg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #benz bne bqez beq b
        if insn.mnemonic == "bnez":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchNotEquelZero,%s,%s," % (REG_TABLE[reg_name[0]],b_offset))
        if insn.mnemonic == "bne":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchNotEquelReg,%s,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[reg_name[1]],b_offset))
        if insn.mnemonic == "beqz":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchIfEquelZero,%s,%s," % (REG_TABLE[reg_name[0]],b_offset))
        if insn.mnemonic == "beq":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchIfEquelReg,%s,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[reg_name[1]],b_offset))
        if insn.mnemonic == "b":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tJmp,%s," % (b_offset))

        #nop
        if insn.mnemonic == "nop":
            print("\tNop,")

        reg_name = []

    print("\tRet,")
    print ("[*]---- Finish vmCode ----")

def Get_SecCode_OffsetTable(md):
    offset_table = []
    offset = 0
    j = 0
    for insn in md.disasm(CODE, BASE_ADDR + START):
        if insn.mnemonic == "sb":
            offset_table.append(offset)
            if(rand_list[j]):
                offset += 4
                j += 1
            else:
                offset += 3
                j += 1
            if(rand_list[j]):
                offset += 4
                j += 1
            else:
                offset += 3
                j += 1
        if insn.mnemonic == "lbu":
            offset_table.append(offset)
            if(rand_list[j]):
                offset += 4
                j += 1
            else:
                offset += 3
                j += 1
            if(rand_list[j]):
                offset += 4
                j += 1
            else:
                offset += 3
                j += 1
        if insn.mnemonic == "lb":
            offset_table.append(offset)
            if(rand_list[j]):
                offset += 4
                j += 1
            else:
                offset += 3
                j += 1
            if(rand_list):
                offset += 4
                j += 1
            else:
                offset += 3
                j += 1
        if insn.mnemonic == "addiu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "addi":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "addu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "add":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "subiu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "subi":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "subu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "sub":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "muliu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "muli":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "mulu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "mul":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "andi":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "andiu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "andu":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "and":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "sll":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "sllv":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "sra":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "srl":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "srav":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "srlv":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "xor":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "xori":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "nor":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "nori":
            if(rand_list[j]):
                offset_table.append(offset)
                offset += 7
                j += 1
            else:
                offset_table.append(offset)
                offset += 4
                j += 1
        if insn.mnemonic == "sltiu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "slti":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "slt":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "sltu":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "bnez":
            offset_table.append(offset)
            offset += 3
        if insn.mnemonic == "bne":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "beqz":
            offset_table.append(offset)
            offset += 3
        if insn.mnemonic == "beq":
            offset_table.append(offset)
            offset += 4
        if insn.mnemonic == "b":
            offset_table.append(offset)
            offset += 2
        if insn.mnemonic == "nop":
            offset_table.append(offset)
            offset += 1
    return offset_table


def print_SecCode(md):
    print ("[*]---- Start SecCode ----")
    offset_table = Get_SecCode_OffsetTable(md)
    j = 0
    for insn in md.disasm(CODE, BASE_ADDR + START):
        if insn.id == 0:
            return
        reg_name = []
        if len(insn.operands) > 0:
            for i in insn.operands:
                if i.type == MIPS_OP_REG:
                    reg_name.append(insn.reg_name(i.reg))
                if i.type == MIPS_OP_IMM:
                    imm = to_x(i.imm)
                if i.type == MIPS_OP_MEM:
                    if i.mem.base != 0:
                        mem_base = insn.reg_name(i.mem.base)
                    if i.mem.disp != 0:
                        mem_disp =  to_x(i.mem.disp & 0xffffffff)
        if(DEBUG):
            print("#0x%x:\t%s\t%s" %(insn.address, insn.mnemonic, insn.op_str))

        #sb 
        if insn.mnemonic == "sb":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MovImm2Reg,0x%s,RFPO," % (mem_disp))
                print("\t\tPushImm,0x%s," % (mem_disp))
                print("\t\tPopReg,RFPO,")
                j += 1
            else:
                print("\t#MovImm2Reg,0x%s,RFPO," % (mem_disp))
                j += 1
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MovReg2Mem,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[mem_base]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[0]]))
                print("\t\tPopMem,%s," % (REG_TABLE[mem_base]))
                j += 1
            else:
                print("\t#MovReg2Mem,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[mem_base]))
                j += 1

        #lbu lb
        if insn.mnemonic == "lbu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MovImm2Reg,0x%s,RFPO," % (mem_disp))
                print("\t\tPushImm,0x%s," % (mem_disp))
                print("\t\tPopReg,RFPO,")
                j += 1
            else:
                print("\t#MovImm2Reg,0x%s,RFPO," % (mem_disp))
                j += 1
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MovMem2Reg,%s,%s," % (REG_TABLE[mem_base],REG_TABLE[reg_name[0]]))
                print("\t\tPushMem,%s," % (REG_TABLE[mem_base]))
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#MovMem2Reg,%s,%s," % (REG_TABLE[mem_base],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "lb":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MovImm2Reg,0x%s,RFPO," % (mem_disp))
                print("\t\tPushImm,0x%s," % (mem_disp))
                print("\t\tPopReg,RFPO,")
                j += 1
            else:
                print("\t#MovImm2Reg,0x%s,RFPO," % (mem_disp))
                j += 1
            if(rand_list):
                if(DEBUG):
                    print("\t#MovMem2Reg,%s,%s," % (REG_TABLE[mem_base],REG_TABLE[reg_name[0]]))
                print("\t\tPushMem,%s," % (REG_TABLE[mem_base]))
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#MovMem2Reg,%s,%s," % (REG_TABLE[mem_base],REG_TABLE[reg_name[0]]))
                j += 1
        #addiu addi addu add
        if insn.mnemonic == "addiu":
            if REG_TABLE[reg_name[1]] == "RFP":
                imm = hex((int(imm,16) * 4))[2:]
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AddReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomAdd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AddReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "addi":
            if REG_TABLE[reg_name[1]] == "RFP":
                imm = hex((int(imm,16) * 4))[2:]
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AddReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomAdd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AddReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "addu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AddReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomAdd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AddReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "add":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AddReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomAdd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AddReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        #subiu subi subu sub
        if insn.mnemonic == "subiu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SubReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomSub,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SubReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "subi":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SubReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomSub,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SubReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "subu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SubReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomSub,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SubReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "sub":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SubReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomSub,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SubReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        #muliu muli mulu mul
        if insn.mnemonic == "muliu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MulReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomMul,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#MulReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "muli":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MulReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomMul,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#MulReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "mulu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MulReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomMul,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#MulReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "mul":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#MulReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomMul,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#MulReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1

        #andi andiu andu and
        if insn.mnemonic == "andi":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AndReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomAnd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AndReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "andiu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AndReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomAnd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AndReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "andu":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AndReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomAnd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AndReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "and":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#AndReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomAnd,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#AndReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1

        #sll sllv
        if insn.mnemonic == "sll":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SllReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomSll,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SllReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "sllv":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SllReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomSll,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SllReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1

        #sra srl srav srlv
        if insn.mnemonic == "sra":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SraReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))   
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomSra,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SraReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
                j += 1
        if insn.mnemonic == "srl":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SraReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomSra,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SraReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "srav":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SraReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomSra,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SraReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "srlv":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#SraReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomSra,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#SraReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1

        #xor xori
        if insn.mnemonic == "xor":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#XorReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]])) 
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomXor,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#XorReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]])) 
                j += 1
        if insn.mnemonic == "xori":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#XorReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomXor,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#XorReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]]))
                j += 1

        #nor nori
        if insn.mnemonic == "nor":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#NorReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]])) 
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[2]]))
                print("\t\tAtomNor,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#NorReg4Reg2Reg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
                j += 1
        if insn.mnemonic == "nori":
            if(rand_list[j]):
                if(DEBUG):
                    print("\t#NorReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
                print("\t\tPushReg,%s," % (REG_TABLE[reg_name[1]]))
                print("\t\tPushImm,0x%s," % (imm))
                print("\t\tAtomNor,")
                print("\t\tPopReg,%s," % (REG_TABLE[reg_name[0]]))
                j += 1
            else:
                print("\t#NorReg4Imm2Reg,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
                j += 1

        #sltiu slti slt sltu
        if insn.mnemonic == "sltiu":
            print("\tSetLessThanImm,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
        if insn.mnemonic == "slti":
            print("\tSetLessThanImm,%s,0x%s,%s," % (REG_TABLE[reg_name[1]],imm,REG_TABLE[reg_name[0]])) 
        if insn.mnemonic == "slt":
            print("\tSetLessThanReg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))
        if insn.mnemonic == "sltu":
            print("\tSetLessThanReg,%s,%s,%s," % (REG_TABLE[reg_name[1]],REG_TABLE[reg_name[2]],REG_TABLE[reg_name[0]]))

        #benz bne bqez beq b
        if insn.mnemonic == "bnez":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchNotEquelZero,%s,%s," % (REG_TABLE[reg_name[0]],b_offset))
        if insn.mnemonic == "bne":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchNotEquelReg,%s,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[reg_name[1]],b_offset))
        if insn.mnemonic == "beqz":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchIfEquelZero,%s,%s," % (REG_TABLE[reg_name[0]],b_offset))
        if insn.mnemonic == "beq":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tBranchIfEquelReg,%s,%s,%s," % (REG_TABLE[reg_name[0]],REG_TABLE[reg_name[1]],b_offset))
        if insn.mnemonic == "b":
            offset_index = (int(imm,16)-(BASE_ADDR+START))/4
            b_offset = offset_table[offset_index]
            print("\tJmp,%s," % (b_offset))

        #nop
        if insn.mnemonic == "nop":
            print("\tNop,")

        reg_name = []

    print("\tRet,")
    print ("[*]---- Finish vmCode ----")

def generate_randlist():
    vlen = (END - START)/4/2
    rand = random.randint(10**(vlen-1),10**vlen)
    rand_list = list(bin(rand)[2:])
    a = []
    for i in rand_list:
        a.append(int(i))
    return a

def main():
    for (arch, mode, code, comment) in all_tests:
        print("*" * 16)
        print("Platform: %s" % comment)
        print("Code: %s" % to_hex(code))
        print("Disasm:")
        try:
            md = Cs(arch, mode)
            md.detail = True
            # print_mips(md)
            print_vmCode(md)
            # print_SecCode(md)
        except CsError as e:
            print("ERROR: %s" % e)

if __name__ == '__main__':
    START = 0xEA0
    END   = 0xF10
    BASE_ADDR = 0x400000
    DEBUG = 1
    REG_TABLE = {"v0":"RAX","v1":"RBX","v2":"RCX","v3":"RDX","fp":"RFP","zero":"ZERO"}
    fp = open("login","rb").read()
    CODE = fp[START:END]
    all_tests = (
            (CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN, CODE, "MIPS-32 (Little-endian)"),
    )
    rand_list = generate_randlist()
    main()
