import tkinter

tk = tkinter.Tk()
tk.title("VMP Demo")
label = tkinter.Label(master=tk,text="Please input username!")
label.pack()
entry = tkinter.Entry(master=tk)
entry.pack()
button = tkinter.Button(master=tk,text="submit")
button.pack()

tk.mainloop()