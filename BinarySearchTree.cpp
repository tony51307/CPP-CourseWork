// Suppose that each node containing a keyvalue (int) and link in a binary search tree also has the field LeftSize as described in the text. Please write a class BinaryTree to implement the following functions:
//(1)  insertNode() to insert a node into a binary search tree.
//(2)  deleteNode() to delete a node(delete by value)from the binary search tree.(If there are two child, replace the delete node with the smallest key in the right sub tree.)
//(3)  searchByValue() to search a node by value, if it exists, show the LeftSize and Depth of the node.
//(4)  searchByRank() to search a node by rank K(the Kth smallest).
//(5)  showInorder() to print out the inorder traversal of the nodes’ values.
//(6)  showPreorder() to print out the preorder traversal of the nodes’ values.
//(7)  showPostorder() to print out the postorder traversal of the nodes’ values.
//and interact with the user by the corresponding command: function# keyvalue, where function# is valid from 1 to 7, and keyvalue is the value of nodes in the binary tree.
//Note : If you insert duplicate data, output : ”Duplicate data.” 
//       If there’s no such value to delete, output : “No such value to delete.”
//       If there’s no such value to search, output : “No such value.”

#include <iostream>
#include <algorithm>
#include <string>
 
using namespace std;
 
class Node {
public:
    Node(int x) {
        value = x;
    }
public:
    int value;
    Node* left = 0;
    Node* right = 0;
    int LeftSize = 1;
};
 
class Tree {
public:
 
    bool isExist(int x) {
        if (head == 0) {
            return false;
        }
        Node* last = head;
        while (true) {
            if (last->value > x&&last->left!=0) {
                last = last->left;
            }
            else if (last->value < x&&last->right != 0) {
                last = last->right;
            }
            else if(last->value==x){
                return true;
            }else if (last->value < x&&last->right == 0) {
                return false;
            }
            else if (last->value >x&&last->left == 0) {
                return false;
            }
        }
    }
 
    void insert(int x) {
        if (isExist(x)) {
            cout << "Duplicate data." << endl;
            return;
        }
        if (head == 0) {
            head = new Node(x);
            cout << "[INSERT SUCCESS]" << endl;
            return;
        }
 
        Node* last = head;
        while (true) {
             
            if (last->value > x&&last->left != 0) {
                last->LeftSize++;
                last = last->left;
            }
            else if (last->value < x&&last->right != 0) {
                last = last->right;
            }
            else if (last->value > x&&last->left == 0) {
                last->LeftSize++;
                last->left = new Node(x);
                cout << "[INSERT SUCCESS]" << endl;
                break;
            }
            else if (last->value < x&&last->right == 0) {
                last->right = new Node(x);
                cout << "[INSERT SUCCESS]" << endl;
                break;
            }
        }
    }
 
    void Delete(int x) {
        if (!isExist(x)) {
            cout << "No such value to delete." << endl;
            return;
        }
 
        Node* last = head;
        Node* parent = 0;
        int direction = 0;
        while (true) {
            if (last->value > x) {
                last->LeftSize--;
                parent = last;
                last = last->left;
                direction = 1;
            }
            else if (last->value < x) {
                parent = last;
                last = last->right;
                direction = 2;
            }
            else {
                if (last->left == 0 && last->right == 0) {
                    if (direction == 0) {
                        head = 0;
                    }
                    else if (direction == 1) {
                        parent->left = 0;
                    }
                    else if (direction == 2) {
                        parent->right = 0;
                    }
                }else if (last->left != 0 && last->right == 0) {
                    if (direction == 0) {
                        head = last->left;
                    }
                    else if (direction == 1) {
                        parent->left = last->left;
                    }
                    else if (direction == 2) {
                        parent->right = last->left;
                    }
                }
                else if (last->left == 0 && last->right != 0) {
                    if (direction == 0) {
                        head = last->right;
                    }
                    else if (direction == 1) {
                        parent->left = last->right;
                    }
                    else if (direction == 2) {
                        parent->right = last->right;
                    }
                }
                else if (last->left != 0 && last->right != 0) {
                    Node* last1 = last->right;
                    Node* parent1 = last;
                    int direction1 = 0;
                    while (last1->left != 0) {
                        last1->LeftSize--;
                        parent1 = last1;
                        last1 = last1->left;
                        direction1 = 1;
                    }
                    if (direction1 == 0) {
                        last->value = last1->value;
                        last->right = last1->right;
                    }
                    else if(direction1==1){
                        last->value = last1->value;
                        parent1->left = 0;
                    }
                }
                cout << "[DELETE SUCCESS]" << endl;
                break;
            }
        }
    }
 
    void searchByValue(int x) {
        if (!isExist(x)) {
            cout << "No such value." << endl;
        }
        else {
            int depth = 1;
            Node* last = head;
            while (true) {
                if (last->value > x) {
                    last = last->left;
                    depth++;
                }
                else if (last->value < x) {
                    last = last->right;
                    depth++;
                }
                else {
                    cout << "LeftSize = " << last->LeftSize << ", Depth = " << depth << endl;
                    break;
                }
            }
         
        }
     
    }
 
 
    void searchByRank(int x) {
        int rank = x;
        Node* last = head;
        while (true) {
            if (rank < last->LeftSize) {
                last = last->left;
            }else if(rank > last->LeftSize&&last->right!=0) {
                rank -= last->LeftSize;
                last = last->right;
            }
            else if (rank > last->LeftSize&&last->right == 0) {
                cout << "No such value." << endl;
                break;
            }
            else if (rank == last->LeftSize) {
                cout << "The "<<x<<"th smallest is "<<last->value << endl;
                break;
            }
        }
    }
 
    void Inorder(Node* n) {
        if (n != 0) {
            Inorder(n->left);
            cout << n->value << " ";
            Inorder(n->right);
        }
    }
 
    void Preorder(Node* n) {
        if (n != 0) {
            cout << n->value << " ";
            Preorder(n->left);
            Preorder(n->right);
        }
    }
 
    void Postorder(Node* n) {
        if (n != 0) {
            Postorder(n->left);
            Postorder(n->right);
            cout << n->value << " ";
        }
    }
public:
    Node* head = 0;
};
 
int main()
{
    int cmd;
    Tree t;
    while (cin >> cmd) {
        if (cmd == 1) {
            int num;
            cin >> num;
            t.insert(num);
        }else if (cmd == 2) {
            int num;
            cin >> num;
            t.Delete(num);
        }
        else if (cmd == 3) {
            int num;
            cin >> num;
            t.searchByValue(num);
        }
        else if (cmd == 4) {
            int num;
            cin >> num;
            t.searchByRank(num);
        }
        else if (cmd == 5) {
            t.Inorder(t.head);
            cout << endl;
        }
        else if (cmd == 6) {
            t.Preorder(t.head);
            cout << endl;
        }
        else if (cmd == 7) {
            t.Postorder(t.head);
            cout << endl;
        }
    }
}
 
