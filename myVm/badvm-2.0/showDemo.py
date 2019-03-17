import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext

src_code=''' 
uint_8 v1 = 0;

for(uint8_t i = 0 ; i < 6 ; i++)
{
    v1 += passwd[i] ^ (49 + i);
}'''

mipsel_code='''
****************
Platform: MIPS-32 (Little-endian)
Code: 0x19 0x00 0xc0 0xa3 0x1a 0x00 0xc0 0xa3 0x1a 0x00 0xc0 0xa3 0x14 0x00 0x00 0x10 0x00 0x00 0x00 0x00 0x1a 0x00 0xc2 0x93 0x30 0x00 0xc3 0x27 0x21 0x10 0x62 0x00 0xf4 0xff 0x43 0x80 0x1a 0x00 0xc2 0x93 0x31 0x00 0x42 0x24 0xff 0x00 0x42 0x30 0x00 0x16 0x02 0x00 0x03 0x16 0x02 0x00 0x26 0x10 0x62 0x00 0x00 0x16 0x02 0x00 0x03 0x16 0x02 0x00 0xff 0x00 0x43 0x30 0x19 0x00 0xc2 0x93 0x21 0x10 0x62 0x00 0x19 0x00 0xc2 0xa3 0x1a 0x00 0xc2 0x93 0x01 0x00 0x42 0x24 0x1a 0x00 0xc2 0xa3 0x1a 0x00 0xc2 0x93 0x06 0x00 0x42 0x2c 0xea 0xff 0x40 0x14 0x00 0x00 0x00 0x00
Disasm:
[*]---- Start disassemble ----
0x400ea0:	sb	$zero, 0x19($fp)
0x400ea4:	sb	$zero, 0x1a($fp)
0x400ea8:	sb	$zero, 0x1a($fp)
0x400eac:	b	0x400f00
0x400eb0:	nop	
0x400eb4:	lbu	$v0, 0x1a($fp)
0x400eb8:	addiu	$v1, $fp, 0x30
0x400ebc:	addu	$v0, $v1, $v0
0x400ec0:	lb	$v1, -0xc($v0)
0x400ec4:	lbu	$v0, 0x1a($fp)
0x400ec8:	addiu	$v0, $v0, 0x31
0x400ecc:	andi	$v0, $v0, 0xff
0x400ed0:	sll	$v0, $v0, 0x18
0x400ed4:	sra	$v0, $v0, 0x18
0x400ed8:	xor	$v0, $v1, $v0
0x400edc:	sll	$v0, $v0, 0x18
0x400ee0:	sra	$v0, $v0, 0x18
0x400ee4:	andi	$v1, $v0, 0xff
0x400ee8:	lbu	$v0, 0x19($fp)
0x400eec:	addu	$v0, $v1, $v0
0x400ef0:	sb	$v0, 0x19($fp)
0x400ef4:	lbu	$v0, 0x1a($fp)
0x400ef8:	addiu	$v0, $v0, 1
0x400efc:	sb	$v0, 0x1a($fp)
0x400f00:	lbu	$v0, 0x1a($fp)
0x400f04:	sltiu	$v0, $v0, 6
0x400f08:	bnez	$v0, 0x400eb4
0x400f0c:	nop	
'''

secCode='''
[*]---- Start SecCode ----
#0x400ea0:	sb	$zero, 0x19($fp)
	#MovImm2Reg,0x19,RFPO,
		PushImm,0x19,
		PopReg,RFPO,
	#MovReg2Mem,ZERO,RFP,
#0x400ea4:	sb	$zero, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
		PushImm,0x1a,
		PopReg,RFPO,
	#MovReg2Mem,ZERO,RFP,
#0x400ea8:	sb	$zero, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
		PushImm,0x1a,
		PopReg,RFPO,
	#MovReg2Mem,ZERO,RFP,
#0x400eac:	b	0x400f00
	Jmp,139,
#0x400eb0:	nop	
	Nop,
#0x400eb4:	lbu	$v0, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
	#MovMem2Reg,RFP,RAX,
#0x400eb8:	addiu	$v1, $fp, 0x30
	#AddReg4Imm2Reg,RFP,0xc0,RBX,
#0x400ebc:	addu	$v0, $v1, $v0
	#AddReg4Reg2Reg,RBX,RAX,RAX,
		PushReg,RBX,
		PushReg,RAX,
		AtomAdd,
		PopReg,RAX,
#0x400ec0:	lb	$v1, -0xc($v0)
	#MovImm2Reg,0xfffffff4,RFPO,
	#MovMem2Reg,RAX,RBX,
		PushMem,RAX,
		PopReg,RBX,
#0x400ec4:	lbu	$v0, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
	#MovMem2Reg,RFP,RAX,
		PushMem,RFP,
		PopReg,RAX,
#0x400ec8:	addiu	$v0, $v0, 0x31
	#AddReg4Imm2Reg,RAX,0x31,RAX,
#0x400ecc:	andi	$v0, $v0, 0xff
	#AndReg4Imm2Reg,RAX,0xff,RAX,
		PushReg,RAX,
		PushImm,0xff,
		AtomAnd,
		PopReg,RAX,
#0x400ed0:	sll	$v0, $v0, 0x18
	#SllReg4Imm2Reg,RAX,0x18,RAX,
#0x400ed4:	sra	$v0, $v0, 0x18
	#SraReg4Imm2Reg,RAX,0x18,RAX,
#0x400ed8:	xor	$v0, $v1, $v0
	#XorReg4Reg2Reg,RBX,RAX,RAX,
#0x400edc:	sll	$v0, $v0, 0x18
	#SllReg4Imm2Reg,RAX,0x18,RAX,
		PushReg,RAX,
		PushImm,0x18,
		AtomSll,
		PopReg,RAX,
#0x400ee0:	sra	$v0, $v0, 0x18
	#SraReg4Imm2Reg,RAX,0x18,RAX,
		PushReg,RAX,
		PushImm,0x18,
		AtomSra,
		PopReg,RAX,
#0x400ee4:	andi	$v1, $v0, 0xff
	#AndReg4Imm2Reg,RAX,0xff,RBX,
		PushReg,RAX,
		PushImm,0xff,
		AtomAnd,
		PopReg,RBX,
#0x400ee8:	lbu	$v0, 0x19($fp)
	#MovImm2Reg,0x19,RFPO,
		PushImm,0x19,
		PopReg,RFPO,
	#MovMem2Reg,RFP,RAX,
#0x400eec:	addu	$v0, $v1, $v0
	#AddReg4Reg2Reg,RBX,RAX,RAX,
#0x400ef0:	sb	$v0, 0x19($fp)
	#MovImm2Reg,0x19,RFPO,
	#MovReg2Mem,RAX,RFP,
		PushReg,RAX,
		PopMem,RFP,
#0x400ef4:	lbu	$v0, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
		PushImm,0x1a,
		PopReg,RFPO,
	#MovMem2Reg,RFP,RAX,
		PushMem,RFP,
		PopReg,RAX,
#0x400ef8:	addiu	$v0, $v0, 1
	#AddReg4Imm2Reg,RAX,0x1,RAX,
		PushReg,RAX,
		PushImm,0x1,
		AtomAdd,
		PopReg,RAX,
#0x400efc:	sb	$v0, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
	#MovReg2Mem,RAX,RFP,
		PushReg,RAX,
		PopMem,RFP,
#0x400f00:	lbu	$v0, 0x1a($fp)
	#MovImm2Reg,0x1a,RFPO,
	#MovMem2Reg,RFP,RAX,
		PushMem,RFP,
		PopReg,RAX,
#0x400f04:	sltiu	$v0, $v0, 6
	SetLessThanImm,RAX,0x6,RAX,
#0x400f08:	bnez	$v0, 0x400eb4
	BranchNotEquelZero,RAX,24,
#0x400f0c:	nop	
	Nop,
	Ret,
[*]---- Finish vmCode ----
'''
win = tk.Tk()
win.resizable(False,False)#大小固定
win.title("虚拟机保护演示")    # 添加标题

# 创建一个容器,
monty = ttk.LabelFrame(win,text="Demo")     # 创建一个容器，其父容器为win
monty.grid(column=0, row=0, padx=10, pady=10)       # padx  pady   该容器外围需要留出的空余空间
ttk.Label(monty, text="===>").grid(column=1, row=1)    # 添加一个标签，并将其列设置为1，行设置为0

# 静态文本框
TextFrame = ttk.LabelFrame(monty,text="C语言")
TextFrame.grid(column=0,row=1,padx=10, pady=10)
scrolW = 50 # 设置文本框的长度
scrolH = 10 # 设置文本框的高度
scr = tk.Text(TextFrame, width=scrolW, height=scrolH, wrap=tk.WORD)     # wrap=tk.WORD   这个值表示在行的末尾如果有一个单词跨行，会将该单词放到下一行显示,比如输入hello，he在第一行的行尾,llo在第二行的行首, 这时如果wrap=tk.WORD，则表示会将 hello 这个单词挪到下一行行首显示, wrap默认的值为tk.CHAR
scr.insert(1.0,src_code)
scr.grid() 

# frame two
second = ttk.LabelFrame(monty,text="MIPS指令")
second.grid(column=2, row=1, padx=10, pady=10)
change_one = scrolledtext.ScrolledText(second, width=70, height=20, wrap=tk.WORD)
change_one.grid(row = 0)

#frame three
third = ttk.LabelFrame(second,text="虚拟机指令")
third.grid(row=1, padx=10, pady=10)
change_two = scrolledtext.ScrolledText(third, width=70, height=20, wrap=tk.WORD) 
change_two.grid(row = 0)

# button被点击之后会被执行
def clickMe():   # 当acction被点击时,该函数则生效
    change_one.insert(1.0,mipsel_code)
    change_two.insert(1.0,secCode)

# 按钮
action = ttk.Button(monty, text="转换", command=clickMe,style="C.TButton",compound = "text")     # 创建一个按钮, text：显示按钮上面显示的文字, command：当这个按钮被点击之后会调用command函数
action.grid(column=1, row=3)    # 设置其在界面中出现的位置  column代表列   row 代表行
action.focus()

win.mainloop()