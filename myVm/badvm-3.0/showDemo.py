import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext

src_code=''' 
uint_8 v1 = 0;

for(uint8_t i = 0 ; i < 6 ; i++)
{
    v1 += passwd[i] ^ (49 + i);
}'''
data = open("log.txt","r").read()
index = data.find('''[*]---- Start vmCode ----''')
mipsel_code = data[:index]
secCode = data[index:]

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