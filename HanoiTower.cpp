#include <iostream>
using namespace std;
 
void Hanoi(int num, int start, int middle, int dest) {
    if (num == 1) {
        cout << "Move disk " << num << " From tower " << start << " to tower " << dest << endl;
        return;
    }
    Hanoi(num - 1, start, dest, middle);
    cout << "Move disk " << num << " From tower " << start << " to tower " << dest << endl;
    Hanoi(num - 1, middle, start, dest);
}

int main()
{
    int num;
    while (cin >> num) {
        Hanoi(num, 2, 3, 1);
    }
}
