#include <iostream>
#include <algorithm>
using namespace std;
 
struct Triple {
    int row;
    int col;
    int value;
};
 
class Matrix;
 
class MatrixNode {
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);
private:
    MatrixNode* down = 0, *right = 0;
    bool head;
    union {
        MatrixNode* next = 0;
        Triple triple;
    };
    MatrixNode(bool, Triple*);
};
 
MatrixNode::MatrixNode(bool b, Triple* t) {
    head = b;
    if (b) {
        right = down = this;
    }
    else {
        triple = *t;
    }
}
 
 
 
class Matrix {
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);
public:
    Matrix() {
        this->headnode = 0;
        this->av = 0;
    }
    Matrix(const Matrix& a);
    ~Matrix();
    Matrix operator + (const Matrix& b);
    Matrix operator-(const Matrix& b);
    Matrix operator*(Matrix& b);
    const Matrix& operator=(const Matrix& a);
    const Matrix Transpose();
private:
    MatrixNode* headnode;
    MatrixNode* av;
};
 
Matrix::Matrix(const Matrix& a) {
    this->headnode = a.headnode;
    this->av = a.av;
}
 
 
Matrix::~Matrix() {
    if (!headnode)
        return;
    headnode->right = av;
    av = headnode;
}
 
istream& operator>>(istream& is, Matrix& matrix) {
    Triple s;
    is >> s.row >> s.col >> s.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0) {
        matrix.headnode->right = matrix.headnode;
        return is;
    }
 
    MatrixNode** head = new MatrixNode * [p];
    for (int i = 0; i < p; i++) {
        head[i] = new MatrixNode(true, 0);
    }
    int currentRow = 0;
    MatrixNode* last = head[0];
 
    for (int i = 0; i < s.value; i++) {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last = last->right = new MatrixNode(false, &t);
        head[t.col]->next = last;
        head[t.col]->next->down = last;
    }
 
    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++) {
        if (head[i]->next != 0) {
            head[i]->next->down = head[i];
        }
    }
    for (int i = 0; i < p - 1; i++) {
        head[i]->next = head[i + 1];
    }
    head[p - 1]->next = matrix.headnode;
    matrix.headnode->right = head[0];
    delete[]head;
    return is;
}
 
ostream& operator<<(ostream& os, Matrix& matrix) {
    MatrixNode* x = matrix.headnode->right;
    while (x != matrix.headnode) {
        if (x->right->head == true) {
            x = x->right->next;
        }
        else {
            Triple s;
            s.row = x->right->triple.row;
            s.col = x->right->triple.col;
            s.value = x->right->triple.value;
            os << s.row << " " << s.col << " " << s.value << endl;
            x = x->right;
        }
    }
    return os;
}
 
Matrix Matrix:: operator+(const Matrix& b) {
    if (this->headnode->triple.col == b.headnode->triple.col && b.headnode->triple.row == this->headnode->triple.row) {
        Triple s;
        s.row = b.headnode->triple.row;
        s.col = b.headnode->triple.col;
        s.value = b.headnode->triple.value;
        Matrix a;
        a.headnode = new MatrixNode(false, &s);
        int p = max(b.headnode->triple.row, b.headnode->triple.col);
        MatrixNode** head = new MatrixNode * [p];
        for (int i = 0; i < p; i++) {
            head[i] = new MatrixNode(true, 0);
        }
 
        int xcurrentrow = 0;
        int ycurrentrow = 0;
        a.headnode->right = head[0];
        MatrixNode* last = head[0];
        MatrixNode* x = headnode->right;
        MatrixNode* y = b.headnode->right;
        MatrixNode* x1 = headnode->right;
        MatrixNode* y1 = b.headnode->right;
 
        while (x != this->headnode && y != b.headnode) {
            if (x->right == 0 && y->right == 0) {
                x = x->next;
                y = y->next;
                y1 = y;
                x1 = x;
                ycurrentrow++;
                xcurrentrow++;
            }
            else if (x->right != 0 && y->right == 0) {
                while (x->right != x1) {
                    Triple t;
                    t.row = x->right->triple.row;
                    t.col = x->right->triple.col;
                    t.value = x->right->triple.value;
                    last = last->right = new MatrixNode(false, &t);
                    a.headnode->triple.value += 1;
                    x = x->right;
                    head[t.col]->next = last;
                }
                x = x->right->next;
                x1 = x;
                last->right = head[xcurrentrow++];
 
                last = head[xcurrentrow];
            }
            else if (x->right == 0 && y->right != 0) {
                while (y->right != y1) {
                    Triple t;
                    t.row = y->right->triple.row;
                    t.col = y->right->triple.col;
                    t.value = y->right->triple.value;
                    last = last->right = new MatrixNode(false, &t);
                    a.headnode->triple.value += 1;
                    y = y->right;
                    head[t.col]->next = last;
                }
                y = y->right->next;
                y1 = y;
                last->right = head[ycurrentrow++];
 
                last = head[ycurrentrow];
            }
            else if (x->right != 0 && y->right != 0) {
                while (y->right != y1 && x->right != x1) {
                    if (x->right->triple.col < y->right->triple.col) {
                        Triple t;
                        t.col = x->right->triple.col;
                        t.row = x->right->triple.row;
                        t.value = x->right->triple.value;
                        last = last->right = new MatrixNode(false, &t);
                        a.headnode->triple.value += 1;
                        x = x->right;
                        head[t.col]->next = last;
                    }
                    else if (x->right->triple.col > y->right->triple.col) {
                        Triple t;
                        t.col = y->right->triple.col;
                        t.row = y->right->triple.row;
                        t.value = y->right->triple.value;
                        last = last->right = new MatrixNode(false, &t);
                        a.headnode->triple.value += 1;
 
                        y = y->right;
                        head[t.col]->next = last;
                    }
                    else if (x->right->triple.col == y->right->triple.col) {
                        Triple t;
                        t.col = x->right->triple.col;
                        t.row = x->right->triple.row;
                        t.value = (x->right->triple.value) + (y->right->triple.value);
                        last = last->right = new MatrixNode(false, &t);
                        a.headnode->triple.value += 1;
                        x = x->right;
                        y = y->right;
                        head[t.col]->next = last;
                    }
                }
                if (y->right != y1) {
                    while (y->right != y1) {
                        Triple t;
                        t.col = y->right->triple.col;
                        t.row = y->right->triple.row;
                        t.value = y->right->triple.value;
                        last = last->right = new MatrixNode(false, &t);
                        y = y->right;
                        head[t.col]->next = last;
                        a.headnode->triple.value += 1;
                    }
                }
                else if (x->right != x1) {
                    while (x->right != x1) {
                        Triple t;
                        t.col = x->right->triple.col;
                        t.row = x->right->triple.row;
                        t.value = x->right->triple.value;
                        last = last->right = new MatrixNode(false, &t);
                        x = x->right;
                        head[t.col]->next = last;
                        a.headnode->triple.value += 1;
                    }
                }
                x = x->right->next;
                y = y->right->next;
                y1 = y;
                x1 = x;
                last->right = head[ycurrentrow];
                ycurrentrow++;
                xcurrentrow++;
                last = head[ycurrentrow];
            }
        }
 
        for (int i = 0; i < b.headnode->triple.col; i++) {
            if (head[i]->next != 0) {
                head[i]->next->down = head[i];
            }
        }
 
        for (int i = 0; i < p - 1; i++) {
            head[i]->next = head[i + 1];
        }
        head[p - 1]->next = a.headnode;
        a.headnode->right = head[0];
        delete[]head;
 
        cout << a;
        return a;
 
    }
    else {
        cout << "Error dimensions!" << endl;
        return b;
    }
}
 
Matrix Matrix:: operator-(const Matrix& b) {
    if (this->headnode->triple.col == b.headnode->triple.col && b.headnode->triple.row == this->headnode->triple.row) {
        Matrix a;
        Triple s;
        s.row = b.headnode->triple.row;
        s.col = b.headnode->triple.col;
        s.value = 0;
        a.headnode = new MatrixNode(false, &s);
        s.value = 0;
        int p = max(b.headnode->triple.row, b.headnode->triple.col);
        MatrixNode** head = new MatrixNode * [p];
        for (int i = 0; i < p; i++) {
            head[i] = new MatrixNode(true, 0);
        }
 
        int xcurrentrow = 0;
        int ycurrentrow = 0;
        a.headnode->right = head[0];
        MatrixNode* last = head[0];
        MatrixNode* x = headnode->right;
        MatrixNode* y = b.headnode->right;
        MatrixNode* x1 = headnode->right;
        MatrixNode* y1 = b.headnode->right;
 
        while (x != this->headnode && y != b.headnode) {
            if (x->right == 0 && y->right == 0) {
                x = x->next;
                y = y->next;
                y1 = y;
                x1 = x;
                ycurrentrow++;
                xcurrentrow++;
            }
            else if (x->right != 0 && y->right == 0) {
                while (x->right != x1) {
                    Triple t;
                    t.row = x->right->triple.row;
                    t.col = x->right->triple.col;
                    t.value = x->right->triple.value;
                    last = last->right = new MatrixNode(false, &t);
                    s.value += 1;
                    x = x->right;
                    head[t.col]->next = last;
                }
                x = x->right->next;
                x1 = x;
                last->right = head[xcurrentrow++];
 
                last = head[xcurrentrow];
            }
            else if (x->right == 0 && y->right != 0) {
                while (y->right != y1) {
                    Triple t;
                    t.row = y->right->triple.row;
                    t.col = y->right->triple.col;
                    t.value = -1 * (y->right->triple.value);
                    last = last->right = new MatrixNode(false, &t);
                    s.value += 1;
                    y = y->right;
                    head[t.col]->next = last;
                }
                y = y->right->next;
                y1 = y;
                last->right = head[ycurrentrow++];
 
                last = head[ycurrentrow];
            }
            else if (x->right != 0 && y->right != 0) {
                while (y->right != y1 && x->right != x1) {
                    if (x->right->triple.col < y->right->triple.col) {
                        Triple t;
                        t.col = x->right->triple.col;
                        t.row = x->right->triple.row;
                        t.value = x->right->triple.value;
                        last = last->right = new MatrixNode(false, &t);
                        s.value += 1;
                        x = x->right;
                        head[t.col]->next = last;
                    }
                    else if (x->right->triple.col > y->right->triple.col) {
                        Triple t;
                        t.col = y->right->triple.col;
                        t.row = y->right->triple.row;
                        t.value = -1 * (y->right->triple.value);
                        last = last->right = new MatrixNode(false, &t);
                        s.value += 1;
                        y = y->right;
                        head[t.col]->next = last;
                    }
                    else if (x->right->triple.col == y->right->triple.col) {
                        Triple t;
                        t.col = x->right->triple.col;
                        t.row = x->right->triple.row;
                        t.value = (x->right->triple.value) - (y->right->triple.value);
                        if (t.value == 0) {
                            x = x->right;
                            y = y->right;
                            continue;
                        }
                        last = last->right = new MatrixNode(false, &t);
                        s.value += 1;
                        x = x->right;
                        y = y->right;
                        head[t.col]->next = last;
                    }
                }
                if (y->right != y1) {
                    while (y->right != y1) {
                        Triple t;
                        t.col = y->right->triple.col;
                        t.row = y->right->triple.row;
                        t.value = -1 * (y->right->triple.value);
                        last = last->right = new MatrixNode(false, &t);
                        y = y->right;
                        head[t.col]->next = last;
                        s.value += 1;
                    }
                }
                else if (x->right != x1) {
                    while (x->right != x1) {
                        Triple t;
                        t.col = x->right->triple.col;
                        t.row = x->right->triple.row;
                        t.value = x->right->triple.value;
                        last = last->right = new MatrixNode(false, &t);
                        x = x->right;
                        head[t.col]->next = last;
                        s.value += 1;
                    }
                }
                x = x->right->next;
                y = y->right->next;
                y1 = y;
                x1 = x;
                last->right = head[ycurrentrow];
                ycurrentrow++;
                xcurrentrow++;
                last = head[ycurrentrow];
            }
        }
 
        for (int i = 0; i < b.headnode->triple.col; i++) {
            if (head[i]->next != 0) {
                head[i]->next->down = head[i];
            }
        }
 
        for (int i = 0; i < p - 1; i++) {
            head[i]->next = head[i + 1];
        }
        head[p - 1]->next = a.headnode;
        a.headnode->right = head[0];
        delete[]head;
        cout << a;
        return a;
 
    }
    else {
        cout << "Error dimensions!" << endl;
        return b;
    }
}
 
 
 
const Matrix& Matrix:: operator=(const Matrix& a) {
    headnode = a.headnode;
    av = a.av;
    return *this;
}
 
const Matrix Matrix::Transpose() {
    Matrix a;
    Triple s;
    s.row = headnode->triple.col;
    s.col = headnode->triple.row;
    s.value = headnode->triple.value;
    a.headnode = new MatrixNode(false, &s);
    MatrixNode* x;
    MatrixNode* x1;
    x = headnode->right;
    x1 = headnode->right;
    int p = max(headnode->triple.row, headnode->triple.col);
    MatrixNode** head = new MatrixNode * [p];
    for (int i = 0; i < p; i++) {
        head[i] = new MatrixNode(true, 0);
    }
    MatrixNode** last = new MatrixNode * [p];
    for (int i = 0; i < p; i++) {
        last[i] = head[i];
    }
    while (x != headnode) {
        if (x != 0) {
            while (x->right != x1) {
                Triple t;
                t.row = x->right->triple.col;
                t.col = x->right->triple.row;
                t.value = x->right->triple.value;
                last[t.row] = last[t.row]->right = new MatrixNode(false, &t);
                head[t.col]->next = last[t.row];
                x = x->right;
 
            }
            x = x->right->next;
            x1 = x;
        }
        else {
            x = x->next;
            x1 = x;
        }
    }
 
    for (int i = 0; i < s.row; i++) {
        if (head[i] != 0) {
            last[i]->right = head[i];
        }
    }
 
    for (int i = 0; i < s.col; i++) {
        if (head[i]->next != 0) {
            head[i]->next->down = head[i];
        }
    }
 
    for (int i = 0; i < p - 1; i++) {
        head[i]->next = head[i + 1];
    }
 
    head[p - 1]->next = a.headnode;
    a.headnode->right = head[0];
 
    delete[] head;
    return a;
}
 
Matrix Matrix:: operator*(Matrix& b) {
    Matrix c = b.Transpose();
    if (headnode->triple.row == b.headnode->triple.col) {
        MatrixNode* x = headnode->right;
        MatrixNode* y = c.headnode->right;
        Matrix d;
        Triple s;
        s.row = headnode->triple.row;
        s.col = headnode->triple.row;
        s.value = 0;
        d.headnode = new MatrixNode(false, &s);
        int p = max(headnode->triple.row, c.headnode->triple.col);
        int stack[20][20];
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                stack[i][j] = 0;
            }
        }
        MatrixNode** head = new MatrixNode * [p];
        for (int i = 0; i < p; i++) {
            head[i] = new MatrixNode(true, 0);
        }
        int xcurrentrow = 0;
        int ycurrentrow = 0;
        MatrixNode** last = new MatrixNode * [p];
        for (int i = 0; i < p; i++) {
            last[i] = head[i];
        }
        while (x != headnode) {
            if (x != 0) {
                while (x->right->head != true) {
                    while (y != c.headnode) {
                        if (y != 0) {
                            while (y->right->head != true) {
                                if (x->right->triple.col == y->right->triple.col) {
                                    stack[x->right->triple.row][y->right->triple.row] += (x->right->triple.value) * (y->right->triple.value);
                                }
                                y = y->right;
                            }
                            y = y->right->next;
                            ycurrentrow++;
                        }
                        else {
                            y = y->next;
                        }
                    }
                    y = y->right;
                    x = x->right;
                }
                x = x->right->next;
                xcurrentrow++;
            }
            else {
                x = x->next;
            }
        }
 
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                if (stack[i][j] != 0) {
                    Triple t;
                    t.row = i;
                    t.col = j;
                    t.value = stack[i][j];
                    last[i] = last[i]->right = new MatrixNode(false, &t);
                    head[t.col]->next = last[i];
                }
            }
        }
 
        for (int i = 0; i < p; i++) {
            last[i]->right = head[i];
        }
 
        for (int i = 0; i < p; i++) {
            if (head[i]->next != 0) {
                head[i]->next->down = head[i];
            }
        }
 
        for (int i = 0; i < p - 1; i++) {
            head[i]->next = head[i + 1];
        }
 
        head[p - 1]->next = d.headnode;
        d.headnode->right = head[0];
        delete[] head;
        cout << d;
        return d;
    }
    else {
        cout << "Error dimensions!" << endl;
        return b;
    }
}
 
 
 
 
int main(int argc, const char* argv[]) {
    // insert code here...
 
    char input;
    Matrix a;
    Matrix b;
    while (cin >> input) {
        if (input == '+') {
            cin >> a >> b;
            a + b;
        }
        else if (input == '-') {
            cin >> a >> b;
            a - b;
        }
        else if (input == 'T') {
            cin >> a;
            Matrix c = a.Transpose();
            cout << c;
        }
        else if (input == '*') {
            cin >> a >> b;
            a* b;
        }
    }
}
