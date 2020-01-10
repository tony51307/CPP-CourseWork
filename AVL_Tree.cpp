// Write a program to implement print, insert, and remove operations for AVL tree. After doing some insert and remove operations, you have to make sure tree is still an AVL tree.
// You need to design you own class and add any function to implement AVL tree.
// Command requirement:
// INSERT <int> - insert integer data into tree. If insert duplicate data, ignore.
// REMOVE <int> - remove integer data from tree. If the removed node has two children nodes, choose the largest node from left child tree to replace. If node not exists, ignore.
// After removing a node, if your AVL tree can do both LL and LR rotation to fix the balance of tree, choose LL rotation fisrt, and if AVL tree can do both RR and RL rotation to fix the balance of tree, choose RR rotation fisrt.
// PRINT – print out data of tree with pre-order traversal.
   
#include <iostream>
#include <cmath>
#include <vector>
   
using namespace std;
   
class Node{
public:
    Node(int v){
        value=v;
        BF=0;
    }
public:
    Node *rlink=0;
    Node *llink=0;
    int value;
    int BF;
};
   
class AVL{
public:
    void insert(int v){
        if(!root){
            root=new Node(v);
            count++;
            return;
        }
           
        Node *a=0;
        Node *pa=0;
        Node *p=root;
        Node *pp=0;
        setBF(root);
        while(p){
            if(p->BF){
                a=p;
                pa=pp;
            }
            if(v<p->value){
                pp=p;
                p=p->llink;
            }else if(v>p->value){
                pp=p;
                p=p->rlink;
            }else{
                p->value=v;
                return;
            }
        }
           
        Node *y=new Node(v);
        if(v<pp->value){
            pp->llink=y;
            count++;
   
        }else{
            pp->rlink=y;
            count++;
   
        }
           
   
        int d;
        Node *b;
        Node *c;
        if(a==0){
            return;
        }else if(v>a->value){
            p=a->rlink;
            b=a->rlink;
        }else if(v<a->value){
            p=a->llink;
            b=a->llink;
        }
        while(p!=y){
            if(v>p->value){
                p=p->rlink;
            }else{
                p=p->llink;
            }
        }
        setBF(root);
        if(abs(a->BF)<=1){
            return;
        }
   
        if(a->BF>1){
            if(b->BF>=1){
                a->llink=b->rlink;
                b->rlink=a;
            }else{
                c=b->rlink;
                b->rlink=c->llink;
                a->llink=c->rlink;
                c->llink=b;
                c->rlink=a;
                b=c;
            }
        }else{
            if(b->BF>=1){
                c=b->llink;
                b->llink=c->rlink;
                a->rlink=c->llink;
                c->rlink=b;
                c->llink=a;
                b=c;
                  
            }else{
                a->rlink=b->llink;
                b->llink=a;
   
            }
               
        }
        if(pa==0){
            root=b;
        }else if(a==pa->llink){
            pa->llink=b;
        }else{
            pa->rlink=b;
        }
        return;
    }
       
    void deleteNode(int x){
          
            Node *last=root;
            Node *parent=0;
            int direction=0;
            while(true){
                if(x>last->value&&last->rlink!=0){
                    parent=last;
                    last=last->rlink;
                    direction=1;
                }else if(x<last->value&&last->llink!=0){
                    parent=last;
                    last=last->llink;
                    direction=2;
                }else if((x<last->value&&last->llink==0)||(x>last->value&&last->rlink==0)){
                    return;
                }else if(x==last->value){
                    if(last->llink!=0&&last->rlink==0){
                        if(direction==1){
                            parent->rlink=last->llink;
                        }else if(direction==2){
                            parent->llink=last->llink;
                        }else if(direction==0){
                            root=last->llink;
                        }
                    }else if(last->llink==0&&last->rlink!=0){
                        if(direction==1){
                            parent->rlink=last->rlink;
                        }else if(direction==2){
                            parent->llink=last->rlink;
                        }else if(direction==0){
                            root=last->rlink;
                        }
                    }else if(last->llink==0&&last->rlink==0){
                        if(direction==1){
                            parent->rlink=0;
                        }else if(direction==2){
                            parent->llink=0;
                        }else if(direction==0){
                            root=0;
                        }
                    }else if(last->llink!=0&&last->rlink!=0){
                        Node *last1=last->llink;
                        Node *parent1=last;
                        int direction1=0;
                        while(last1->rlink!=0){
                            parent1=last1;
                            last1=last1->rlink;
                            direction1=1;
                        }
                        if(direction1==0){
                            last->value=last1->value;
                            last->llink=last1->llink;
                        }else if(direction1==1){
                            last->value=last1->value;
                            parent1->rlink=0;
                        }
                    }
                    count--;
                    break;
                }
        }
           
           
        setBF(root);
           
        Node *last3=root;
        Node *last3p=0;
           
        Node *y=0;
        Node *yp;
        while(true){
            if(abs(last3->BF)>1){
                y=last3;
                yp=last3p;
            }
            if(x>last3->value&&last3->rlink!=0){
                last3p=last3;
                last3=last3->rlink;
            }else if(x<last3->value&&last3->llink!=0){
                last3p=last3;
                last3=last3->llink;
            }else if(x>last3->value&&last3->rlink==0){
                break;
            }else if(x<last3->value&&last3->llink==0){
                break;
            }
        }
           
        if(y==0){
            return;
        }
           
        Node *b;
        Node *c;
        if(y->BF>1){
            b=y->llink;
            if(y->llink->llink!=0){
                y->llink=b->rlink;
                b->rlink=y;
            }else if(y->llink->rlink!=0){
                c=b->rlink;
                b->rlink=c->llink;
                y->llink=c->rlink;
                c->llink=b;
                c->rlink=y;
                b=c;
            }
        }else{
            b=y->rlink;
            if(y->rlink->rlink!=0){
                y->rlink=b->llink;
                b->llink=y;
            }else if(y->rlink->llink!=0){
                c=b->rlink;
                c=b->llink;
                b->llink=c->rlink;
                y->rlink=c->llink;
                c->rlink=b;
                c->llink=y;
                b=c;
            }
        }
        if(yp==0){
            root=b;
        }else if(y==yp->llink){
            yp->llink=b;
        }else{
            yp->rlink=b;
        }
        return;
    }
       
    void bf_count(Node *trees)
    {
        if(trees != 0) {
            bf_count(trees->llink);
            bf_count(trees->rlink);
            trees->BF = height_count(trees->llink) - height_count(trees->rlink);
        }
    }
       
    int height_count(Node *trees)
    {
        if(trees == 0)
            return 0;
        else     if(trees->llink == NULL && trees->rlink == NULL)
            return 1;
        else
            return 1 + (height_count(trees->llink) > height_count(trees->rlink)?
                        height_count(trees->llink) : height_count(trees->rlink));
    }
       
    void setBF(Node *a){
        if(a!=0){
            bf_count(a);
            setBF(a->llink);
            setBF(a->rlink);
        }
    }
       
    vector<int> showPreorder(Node *x, vector<int> stack){
        if(x!=0){
        stack.push_back(x->value);
        stack=showPreorder(x->llink,stack);
        stack=showPreorder(x->rlink,stack);
        }
        return stack;
    }
public:
    Node *root=0;
    int count=0;
};
   
   
int main(int argc, const char * argv[]) {
    // insert code here...
       
    string cmd;
    AVL a;
    while(cin>>cmd){
        if(cmd=="INSERT"){
            int num;
            cin>>num;
            a.insert(num);
        }else  if(cmd=="REMOVE"){
            int num;
            cin>>num;
            a.deleteNode(num);
        }else  if(cmd=="PRINT"){
            vector<int> stack;
            stack=a.showPreorder(a.root,stack);
            for(int i=0;i<stack.size()-1;i++){
                cout<<stack[i]<<",";
            }
            cout<<stack[stack.size()-1]<<endl;
        }
    }
    return 0;
}
