// Description:
// Try to transform an infix expression into its prefix and postfix equivalent with C++. 
// Assume that the operators in the expression only include (, ), *, /, +, and -. Design a class called Stack and implement the necessary member functions, such as push() and pop() to accomplish the infix transformation.

// Input: An infix expression such as A*B/C.

#include <iostream>
using namespace std;

// implement stack
class Stack{
public:
    int capacity;
    int top=-1;
    char *array;
     
    void setStack(int n){
        capacity=n;
        array=new char[n];
    }
     
    bool isEmpty(){
        if(top<0){
            return true;
        }else{
            return false;
        }
    }
     
    void push(char token){
        if(top>=capacity-1){
            throw "The stack is full.";
        }else{
            top++;
            array[top]=token;
        }
    }
     
    void pop(){
        if(isEmpty()){
            throw "The stack is empty.";
        }else{
            top--;
        }
    }
     
    char Top(){
        return array[top];
    }
 
};


int isp(char token){
    if(token=='+'||token=='-'){
        return 2;
    }else if(token=='#'||token=='('||token==')'){
        return 3;
    }else{
        return 1;
    }
}

// find the incoming priority
int icp(char token){
    if(token=='+'||token=='-'){
        return 2;
    }else if(token=='#'){
        return 0;
    }else if(token=='('||token==')'){
        return -1;
    }else{
        return 1;
    }
}
 
// check if it is an operand
bool isOperand(char token){
    if(token == '-'||token=='+'||token =='*'||token=='/'||token==')'||token=='('){
        return false;
    }else{
        return true;
    }
}
 
// convert to postfix
void Postfix(string e){
    Stack stack;
    stack.setStack((int)e.length());
    stack.push('#');
    cout<<"Postfix: ";
    for(int i=0; i<(int)e.length();i++){
        if(isOperand(e[i])){
            cout<<e[i];
        }else if(e[i]==')'){
            for(;stack.Top()!='(';stack.pop())
                cout<<stack.Top();
            stack.pop();
        }else if(e[i]=='('){
            stack.push(e[i]);
        }else{
            for(;isp(stack.Top())<=icp(e[i]);stack.pop())
                cout<<stack.Top();
            stack.push(e[i]);
        }
    }
     
    for(;!stack.isEmpty();stack.pop()){
        if(stack.Top()=='#')
            break;
        cout<<stack.Top();
    }
    cout<<"\n";
}
 
// convert to postfix
void Prefix(string e){
    char p[(int)e.length()];
    for(int i =0; i<(int)e.length();i++){
        p[i]=e[(int)e.length()-1-i];
    }
    Stack stack;
    stack.setStack((int)e.length());
    stack.push('#');
    char d [(int)e.length()];
    int num=0;
    for(int i=0; i<stack.capacity;i++){
        if(isOperand(p[i])){
            d[num++]=p[i];
        }else if(p[i]=='('){
            for(;stack.Top()!=')';stack.pop())
                d[num++]=stack.Top();
            stack.pop();
        }else if(p[i]==')'){
            stack.push(p[i]);
        }
        else{
            for(;isp(stack.Top())<icp(p[i]);stack.pop())
                d[num++]=stack.Top();
            stack.push(p[i]);
        }
    }
     
    for(;!stack.isEmpty();stack.pop()){
        if(stack.Top()=='#')
            break;
        d[num++]=stack.Top();
    }
    cout<<"Prefix: ";
    for(int i =num-1; i>=0;i--){
        cout<<d[i];
    }
    cout<<"\n"<<endl;
}
 
int main() {
    string infixexpression;
    while(cin>>infixexpression){
        Postfix(infixexpression);
        Prefix(infixexpression);
        }
    cout<<"\n";
}
