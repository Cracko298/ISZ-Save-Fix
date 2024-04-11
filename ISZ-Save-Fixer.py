import tkinter as tk
from tkinter import ttk, filedialog
from datetime import datetime
import os

# Get the list of files in the current directory
file_names = [f for f in os.listdir('.') if os.path.isfile(f) and f.startswith('Data')]
# Create the Tkinter window
window = tk.Tk()
window.title("File Dropdown Menu")
window.geometry('720x360')

# Create a label
label = tk.Label(window, text="Select a file:")
label.pack(pady=10)
selected_file = tk.StringVar()
dropdown = ttk.Combobox(window, textvariable=selected_file, state='readonly')
dropdown['values'] = file_names
dropdown.pack()

def backupSaveGame():
    time = datetime.now()
    selected_file_name = selected_file.get()
    if 'Data' not in selected_file_name:
        print(f"Selected File: {selected_file_name}, isn't a SaveGame File.")
    else:
        folder = f'.\\ISZSF_Backups\\{selected_file_name}\\{time.month}{time.day}{time.year}_{time.hour}{time.minute}{time.second}'
        print(f"Backing-Up Selected SaveGame: {selected_file_name}")
        os.makedirs(folder,exist_ok=True)
        with open(f".\\{selected_file_name}",'rb+') as f:
            save_data = f.read()
            f.close()
        with open(f"{folder}\\Data0", 'wb+') as copy:
            copy.write(save_data)
    


# Function to load files with specific extensions
def load_file(extensions):
    extensions_list = extensions.split(', ')
    file_types = [("Plugin files", f"*.{ext}") for ext in extensions_list]
    file_path = filedialog.askopenfilename(filetypes=file_types)
    if file_path == '':
        print('Exiting Plugin Loader')
    else:
        print(f"Plugin Selected: {file_path}")

# Create a menubar
menubar = tk.Menu(window)

# Create a File menu
file_menu = tk.Menu(menubar, tearoff=0)
file_menu.add_command(label="Load Plugin", command=lambda: load_file("Zplg, GBplg, ISplg"))
file_menu.add_command(label="Backup SaveGame", command=backupSaveGame)
file_menu.add_command(label="JSON SaveGame Parse", command=backupSaveGame)
menubar.add_cascade(label="File", menu=file_menu)

# Display the menubar
window.config(menu=menubar)

window.mainloop()
