// Design a dynamic hash table that uses a directory.
// To be specific, your design should include these commands.
// put key: Insert a key into the hash table and print the index of directory of the hash table. If the bucket is full, you must resize the hash table and new directory size is twice the old directory size.
// get index: Print a set of the bucket. If the bucket is empty, you must print “The bucket is empty.” If the index is out of range, you must print “Out of range”.
// exit: Exit the program.

// Note :
// The size of directory depends on the number of bits of h(k, p) used to index into the directory. For example, when h(k, 2) is used, the directory size is .
// Default p is 2.
// Every bucket size is 2.
// Every key is composed of two characters. First character is only from A to D. Second character is only from 0 to 7.
// The hash function h(k) will transform keys into the 6-bit non-negative integer and we use h(k, p) to denote the integer formed by the p least significant bits of h(k). For example, h(A0, 1) = 0, h(A1, 3) = 1, h(B1, 4) = 1001 = 9, and h(C1, 6) = 110001 = 49.

#include <iostream>
#include <string>
 
using namespace std;
 
class Node {
public:
    Node(string x) {
        value = x;
    }
public:
    string value;
    Node* next = 0;
};
 
class bucket {
public:
    bool isFull() {
        if (num >= 2) {
            return true;
        }
        return false;
    }
 
    void add(string x) {
        Node* last = head;
        while (last->next != 0) {
            last = last->next;
        }
        last->next = new Node(x);
        num++;
    }
public:
    Node* head = 0;
    int num = 0;
};
 
class Hash {
public:
    string toBit(int x, int l) {
        int num = x;
        string result;
        while (num != 0) {
            result.append(to_string(num % 2));
            num /= 2;
        }
        while ((int)result.length() < l) {
            result += '0';
        }
        string newresult;
        for (int i = (int)result.length() - 1; i >= 0; i--) {
            newresult += result[i];
        }
        return newresult;
    }
 
    string toBit_string(string x) {
        string x1 = toBit(x[0] - 'A', 3);
        string x2 = toBit(x[1] - '0', 3);
        x1[0] = '1';
        return x1 + x2;
    }
 
    int toindex(string x, int l) {
        return stoi(toBit_string(x).substr((int)toBit_string(x).length() - l, l), nullptr, 2);
    }
 
    int toindexNum(string x, int l) {
        return stoi(x.substr((int)x.length() - l, l), nullptr, 2);
    }
 
    Hash() {
        for (int i = 0; i < length; i++) {
            array[i].head = new Node(toBit(i, p));
        }
    }
 
    void rearrange(bucket *a) {
        for (int i = 4; i < length; i++) {
            if (a[i].num <= 0) {
                int plength = (int)a[i].head->value.length() - 1;
                while (a[toindexNum(a[i].head->value, plength)].num <= 0 && plength - 1 >= 2) {
                    plength--;
                }
                 
                if (a[toindexNum(a[i].head->value, plength)].num > 0) {
                    a[i].head->next = a[toindexNum(a[i].head->value, plength)].head->next;
                }
            }
        }
    }
 
    void insert(string x) {
        for (int i = 2; i <= p; i++) {
            if (!array[toindex(x,i)].isFull()) {
                array[toindex(x, i)].add(x);
                rearrange(array);
                cout << toindex(x, p) << endl;
                return;
            }
        }
 
        int originpos = toindex(x, p);
        int power = 1;
        while (toindex(x, p) == toindex(array[originpos].head->next->value, p) && toindex(x, p) == toindex(array[originpos].head->next->next->value, p)) {
            p++;
            power *= 2;
        }
        length *= power;
        bucket* newarray = new bucket[length];
        for (int i = 0; i < length; i++) {
            newarray[i].head = new Node(toBit(i, p));
        }
 
        for (int i = 0; i < length / power; i++) {
            if (array[i].num > 0) {
                Node* last = array[i].head;
                while (last->next != 0) {
                    last = last->next;
                    newarray[toindex(last->value, p)].add(last->value);
                }
            }
        }
 
        newarray[toindex(x, p)].add(x);
        cout << toindex(x, p) << endl;
        rearrange(newarray);
        array = new bucket[length];
        copy(newarray, newarray + length, array);
    }
 
    void get(int x) {
        if (x >= length) {
            cout << "Out of range." << endl;
        }
        else if (array[x].num <= 0 && array[x].head->next == 0) {
            cout << "The bucket is empty." << endl;
        }
        else {
            cout << array[x].head->next->value;
            if (array[x].head->next->next!= 0) {
                cout <<" " <<array[x].head->next->next->value;
            }
            cout << endl;
        }
    }
public:
    bucket* array = new bucket[4];
    int p = 2;
    int length = 4;
};
 
int main()
{
    Hash h;
    string cmd;
    while (cin >> cmd) {
        // insert new value
        if (cmd == "put") {
            string x;
            cin >> x;
            h.insert(x);
         // get value from certain index
        }else if (cmd == "get") {
            int x;
            cin >> x;
            h.get(x);
        }
        else if (cmd == "exit") {
            break;
        }
    }
}
