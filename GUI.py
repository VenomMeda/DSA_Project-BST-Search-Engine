import tkinter as tk
from tkinter import scrolledtext, messagebox

def set_custom_icon(window):
    # Replace 'path_to_icon.ico' with the path to your ICO file
    icon_path = r'C:\Users\ACER\Downloads\qt_94938.ico'
    
    try:
        window.iconbitmap(icon_path)
    except tk.TclError:
        print(f"Icon file not found at {icon_path}")

class BSTNode:
    def __init__(self, sno, url, desc):
        self.left = None
        self.SerialNumber = sno
        self.Url = url
        self.Description = desc
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, sno, url, desc):
        self.root = self._insert(self.root, sno, url, desc)

    def _insert(self, root, sno, url, desc):
        if root is None:
            return BSTNode(sno, url, desc)
        
        if sno < root.SerialNumber:
            root.left = self._insert(root.left, sno, url, desc)
        elif sno > root.SerialNumber:
            root.right = self._insert(root.right, sno, url, desc)

        return root

    def destroy(self):
        self.root = self._destroy(self.root)

    def _destroy(self, root):
        if root:
            root.left = self._destroy(root.left)
            root.right = self._destroy(root.right)
            return None
        return None

    def display(self):
        result = []
        self._display(self.root, result)
        return result

    def _display(self, root, result):
        if root:
            self._display(root.left, result)
            result.append(root.SerialNumber)
            result.append(root.Url)
            result.append("\n")  # Adding newline for better readability
            self._display(root.right, result)

    def searchtemp(self, word):
        result = []
        self._searchtemp(self.root, word, result)
        return ''.join(result)

    def _searchtemp(self, node, word, result):
        if node:
            self._searchtemp(node.left, word, result)

            if self._find_word(node.Description, word):
                result.append(node.Url + '\n')

            self._searchtemp(node.right, word, result)

    def _find_word(self, text, word):
        return word.lower() in text.lower()

# Function to create and initialize the BST
def create_bst():
    bst = BST()

    # Sample data for testing
    bst.insert(1, "https://www.google.com", "Search engine website, also provides email, maps, news, etc.")
    bst.insert(2, "https://www.wikipedia.org", "Online encyclopedia, also provides news, etc.")
    bst.insert(3, "https://www.github.com", "Development platform for version control and collaboration, also provides project management tools, etc.")
    bst.insert(4, "https://www.cnn.com", "News and media website, also provides email, etc.")
    bst.insert(5, "https://www.amazon.com", "E-commerce platform, also provides cloud computing, etc.")
    bst.insert(6, "https://www.nytimes.com", "News and media website.")
    bst.insert(7, "https://www.linkedin.com", "Social media platform for professionals")

    return bst

# Function to perform search and display results
def search_button_clicked():
    keyword = search_entry.get()
    result_text.delete(1.0, tk.END)  # Clear previous results

    # Perform search and get results
    results = bst.searchtemp(keyword)

    # Check if results are found or not
    if results:
        result_text.insert(tk.END, results)
    else:
        # Display error message if no results found
        messagebox.showerror("Search Error", "Keyword not found in the BST.")


# Main program
bst = create_bst()

# Create the main window
window = tk.Tk()
window.title("BST Search Engine")

# Create and place widgets
search_label = tk.Label(window, text="Enter Keyword:")
search_label.pack(pady=10)

search_entry = tk.Entry(window)
search_entry.pack(pady=10)

search_button = tk.Button(window, text="Search", command=search_button_clicked)
search_button.pack(pady=10)

result_text = scrolledtext.ScrolledText(window, width=40, height=10, wrap=tk.WORD)
result_text.pack(pady=10)

set_custom_icon(window)
# Start the Tkinter event loop
window.mainloop()
