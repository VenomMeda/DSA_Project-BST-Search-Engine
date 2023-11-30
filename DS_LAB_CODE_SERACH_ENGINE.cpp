#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> // For transform function
using namespace std;

// ----- BSTNode class for further use in BST class -----
class BSTNode
{
public:
    // data members
    BSTNode *left;
    int SerialNumber;
    string Url;
    string Description;
    BSTNode *right;

    // default constructor
    BSTNode();
};
// functions for class BSTNode
BSTNode::BSTNode()
{
    left = right = NULL;
}
// ----- class BSTNode ends -----

// ----- class BST for further use -----
class BST
{
public:
    // data member
    BSTNode *root;

    // default constructor
    BST();

    // functions
    void Insert(int, string, string);

    void Display(BSTNode *); // for checking BST validity
    void Searchtemp(char[]); // for checking BST validity

    void Destroy(BSTNode *);
    ~BST();
};
// functions for class BST
// default constructor
BST::BST()
{
    root = NULL;
}
// functions
// function to insert nodes (according to the serial numbers)
void BST::Insert(int sno, string url, string desc)
{
    // declaring and initializing (according to accessed data from the file) a dynamically allocated BSTNode
    BSTNode *bstnode = new BSTNode;
    bstnode->SerialNumber = sno;
    bstnode->Url = url;
    bstnode->Description = desc;

    // condition when the tree is empty
    if (root == NULL)
    {
        root = bstnode;
    }
    // condition when the tree is not empty
    else
    {
        // temp pointer to root
        BSTNode *temp = root;
        // prev pointer to trace the previous node
        BSTNode *prev;

        // iterating through nodes
        while (temp != NULL)
        {
            // tracing nodes and placing temp on the place where the node is to be inserted
            prev = temp;
            if (bstnode->SerialNumber < temp->SerialNumber)
            {
                temp = temp->left;
            }
            else if (bstnode->SerialNumber > temp->SerialNumber)
            {
                temp = temp->right;
            }
            // for duplicate number
            else
            {
                return;
            }
        }

        // inserting node
        if (bstnode->SerialNumber > prev->SerialNumber)
        {
            prev->right = bstnode;
        }
        else if (bstnode->SerialNumber < prev->SerialNumber)
        {
            prev->left = bstnode;
        }
    }
}
// function for destroying dynamically allocated nodes in the tree
void BST::Destroy(BSTNode *node)
{
    if (node)
    {
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }
}
// destructor (calling destroy function)
BST::~BST()
{
    Destroy(root);
}
// for checking validity (in-order traversal)
void BST::Display(BSTNode *nodeptr)
{
    if (nodeptr == NULL)
    {
        return;
    }

    Display(nodeptr->left);
    cout << nodeptr->SerialNumber << endl;
    cout << nodeptr->Url << endl;
    Display(nodeptr->right);
}
// ----- class BST ends -----

// Helper function (for further use) to find a word in the given description/string
bool findword(string str, const char word[])
{
    // Converting string to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    // Converting word to lowercase
    string lowercaseWord = word;
    transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);

    // Searching for the lowercase word in the lowercase string
    return str.find(lowercaseWord) != string::npos;
}

// Search function (using findword()) for searching and printing the URLs recursively (in-order traversal)
void Search(BSTNode *nodeptr, char word[])
{
    if (nodeptr == NULL)
    {
        return;
    }
    else
    {
        Search(nodeptr->left, word);

        // printing URL if the word is found
        if (findword(nodeptr->Description, word))
        {
            cout << nodeptr->Url << endl;
        }

        Search(nodeptr->right, word);
    }
}
// function for ease of implementation, giving root to recursive function by argument
void BST::Searchtemp(char word[])
{
    Search(root, word);
}

// this is the implementation for the overall menu (instead of using main())
void Implementation()
{
    // asking for the filename
    cout << "\n---------------------------" << endl;
    cout << "Please Enter the filename: ";
    string filename;
    cin >> filename;

    // opening the file
    fstream myfile;
    myfile.open(filename, ios::in);

    // making a Binary Search Tree (BST) object
    BST bst;

    // if the file exists
    if (myfile.is_open())
    {
        cout << "\nFile loaded successfully!" << endl;
        cout << "---------------------------" << endl;

        // variable for getting lines in the file
        string data;

        // getting serial numbers of URLs
        // for iteration purpose
        // skipping 2nd and 3rd line
        int i = 0;

        // making a dynamic BSTNode
        BSTNode *bstnode = new BSTNode;

        // variables to store data
        int sno;
        string Url;
        string Description;

        // iterating through the file
        while (getline(myfile, data))
        {
            // condition for getting desired data (URL and Serial Numbers)
            if (i == 0)
            {
                // getting URL
                Url = data;

                // getting serial numbers
                // converting character data into numbers (by operating on their ASCII value)
                int num;
                if (data[1] == ' ')
                {
                    num = data[0] - 48;
                }
                else if (data[1] != ' ' && data[0] == '1')
                {
                    num = (data[0] + data[1]) - 87;
                }
                else if (data[1] != ' ' && data[0] == '2')
                {
                    num = (data[0] + data[1]) - 78;
                }
                else if (data[1] != ' ' && data[0] == '3')
                {
                    num = (data[0] + data[1]) - 69;
                }
                else if (data[1] != ' ' && data[0] == '4')
                {
                    num = (data[0] + data[1]) - 60;
                }
                else if (data[1] != ' ' && data[0] == '5')
                {
                    num = (data[0] + data[1]) - 51;
                }

                // getting Serial Numbers
                sno = num;

                // moving forward
                i++;
                continue;
            }

            // getting 2nd line (Description)
            else if (i == 1)
            {
                // getting description
                Description = data;

                // moving forward
                i++;
                continue;
            }

            // skipping the third line ('\n')
            else if (i == 2)
            {
                i = 0;
            }

            // inserting the node in the BST by giving data in arguments
            bst.Insert(sno, Url, Description);
        }
        // closing the file
        myfile.close();
    }
    // if the file is not found
    else
    {
        cout << "File not found!" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    // searching the word
    while (true)
    {
        // taking input repeatedly (while the user does not terminate)
        cout << "\nPress: " << endl;
        cout << "1: To Search" << endl;
        cout << "2: To Terminate" << endl;
        cout << "Enter: ";
        int chk;
        cin >> chk;

        // if you want to search
        if (chk == 1)
        {
            // taking input from the user for searching
            char word[100];
            cout << "\n-----------------------" << endl;
            cout << "Enter Word: ";
            cin >> word;
            cout << "-----------------------" << endl;
            cout << "\n";
            // searching and printing the URLs
            bst.Searchtemp(word);
            cout << "_______________________" << endl;
        }
        // if you want to terminate
        else if (chk == 2)
        {
            cout << "\nTerminated!" << endl;
            cout << "_____________\n"
                 << endl;
            break;
        }
    }
}

int main()
{
    Implementation();

    return 0;
}
