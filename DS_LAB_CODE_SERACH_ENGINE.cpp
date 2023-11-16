
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
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
BSTNode ::BSTNode()
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
BST ::BST()
{
    root = NULL;
}
// functions
// funtion to insert nodes (according to the serial numbers)
void BST ::Insert(int sno, string url, string desc)
{
    // declaring and initializing (acc to accessed data from file) a dynamically allocated BSTNode
    BSTNode *bstnode = new BSTNode;
    bstnode->SerialNumber = sno;
    bstnode->Url = url;
    bstnode->Description = desc;

    // condition when tree is empty
    if (root == NULL)
    {
        root = bstnode;
    }
    // condition when tree is not empty
    else
    {
        // temp pointer to root
        BSTNode *temp = root;
        // prev pointer to trace previous node
        BSTNode *prev;

        // iterating through nodes
        while (temp != NULL)
        {
            // tracing nodes and placing temp on the place where node is to be inserted
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
// for checking calidity (inorder traversal)
void BST ::Display(BSTNode *nodeptr)
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

// helper functiopn (for further use) to find a word in given description/string
bool findword(string str, char word[])
{
    // converting string into character array
    char arr[200];
    int q = 0;
    while (q != str.length())
    {
        arr[q] = str[q];
        q++;
    }
    arr[q] = '\0';

    // itrerating on word and string for searching word
    int i = 0;
    int count = 0;
    int chk = false;
    while (arr[i] != '\0')
    {
        int j = 0;
        // if first alphabet matches
        if (arr[i] == word[j])
        {
            // chcking for further alphabets one by one
            while (true)
            {
                if (arr[i] == word[j])
                {
                    i++;
                    j++;
                    count++;
                }
                else
                {
                    break;
                }
            }
            // checking if it is completly matched
            if (count == strlen(word))
            {
                // making check true if matched
                chk = true;
            }
            else
            {
                count = 0;
            }
        }
        // breaking loop if found
        if (chk == true)
        {
            break;
        }
        // else
        i++;
    }

    // returning answer
    if (chk == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Search function (using findword()) for searching and printing the URLs recursively (inorder traversal)
void Search(BSTNode *nodeptr, char word[])
{
    if (nodeptr == NULL)
    {
        return;
    }
    else
    {
        Search(nodeptr->left, word);

        // printing URL if word found
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

// this is the implementation for overall menu (intead of using main())
void Implementation()
{
    // asking for filename
    cout << "\n---------------------------" << endl;
    cout << "Please Enter the filename: ";
    string filename;
    cin >> filename;

    // opening file
    fstream myfile;
    myfile.open(filename, ios::in);

    // making a Binary Search Tree (BST) object
    BST bst;

    // if file exist
    if (myfile.is_open())
    {
        cout << "\nFile loaded successfully!" << endl;
        cout << "---------------------------" << endl;

        // variable for getting lines in file
        string data;

        // getting serial number of urls
        // for iteration purpose
        // skipping 2nd and 3rd line
        int i = 0;

        // making a dynamic BSTnode
        BSTNode *bstnode = new BSTNode;

        // variables to store data
        int sno;
        string Url;
        string Description;

        // iterating through file
        while (getline(myfile, data))
        {
            // condition for getting desired data (URL and Serial Numbers)
            if (i == 0)
            {
                // getting URL
                Url = data;

                // getting serial numbers
                // converting character data into numbers (by opearting on their ASCII value)
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

                // getting Serail Numbers
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

            // skipping third line ('\n')
            else if (i == 2)
            {
                i = 0;
            }

            // iserting the node in bst by giving data in arguments
            bst.Insert(sno, Url, Description);
        }
        // closing file
        myfile.close();
    }
    // if file not found
    else
    {
        cout << "File not found!" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    // searching the word
    while (true)
    {
        // taking input repeateadly (while user do not terminates)
        cout << "\nPress: " << endl;
        cout << "1: To Search" << endl;
        cout << "2: To Terminate" << endl;
        cout << "Enter: ";
        int chk;
        cin >> chk;

        // if want to search
        if (chk == 1)
        {
            // taking input from user for searching
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
        // if wants to terminate
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