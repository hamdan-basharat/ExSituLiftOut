import serial
import tkinter as tk

root = tk.Tk()
root.title("ExSitu Lift-out")
root.configure(background="#D4D0C8")
root.minsize(600, 400)
root.maxsize(1200, 800)
root.geometry("300x300+50+50")

# B = tk.Button(root, text="Hello")
# B.pack()
# tk.Label(text="Position 1", width=10).grid(row=0, column=0)
# tk.Label(text="Position 2", width=10).grid(row=0, column=1)
# tk.Label(text="Position 3", width=10).grid(row=1, column=0)
# tk.Label(text="Position 4", width=10).grid(row=1, column=1)

frm_entry = tk.Frame(master=root)
ent_temperature = tk.Entry(master=frm_entry, width=10)
lbl_temp = tk.Label(master=frm_entry, text="\N{DEGREE FAHRENHEIT}")

ent_temperature.grid(row=0, column=0, sticky="e")
lbl_temp.grid(row=0, column=1, sticky="w")

btn_convert = tk.Button(
    master=root,
    text="\N{RIGHTWARDS BLACK ARROW}",
    #command=fahrenheit_to_celsius
)
lbl_result = tk.Label(master=root, text="\N{DEGREE CELSIUS}")

frm_entry.grid(row=0, column=0, padx=10)
btn_convert.grid(row=0, column=1, pady=10)
lbl_result.grid(row=0, column=2, padx=10)

root.mainloop()

#
# # Create the Fahrenheit entry frame with an Entry
# # widget and label in it
# frm_entry = tk.Frame(master=window)
# ent_temperature = tk.Entry(master=frm_entry, width=10)
# lbl_temp = tk.Label(master=frm_entry, text="\N{DEGREE FAHRENHEIT}")
#
# # Layout the temperature Entry and Label in frm_entry
# # using the .grid() geometry manager
# ent_temperature.grid(row=0, column=0, sticky="e")
# lbl_temp.grid(row=0, column=1, sticky="w")
#
# # Create the conversion Button and result display Label
# btn_convert = tk.Button(
#     master=window,
#     text="\N{RIGHTWARDS BLACK ARROW}",
#     command=fahrenheit_to_celsius
# )
# lbl_result = tk.Label(master=window, text="\N{DEGREE CELSIUS}")
#
# # Set up the layout using the .grid() geometry manager
# frm_entry.grid(row=0, column=0, padx=10)
# btn_convert.grid(row=0, column=1, pady=10)
# lbl_result.grid(row=0, column=2, padx=10)
#
# # Run the application
# window.mainloop()
#
