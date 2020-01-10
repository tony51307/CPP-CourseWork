// Input a list with N elements, and use Heap Sort to do descending sort, and implement following commands:
// heap: Pop the root value, and refresh the heap, reset current element to the root value of the heap tree.
// left: Move current view to left root of subtree, and output current element.
// right: Move current view to right branch, and output current element.
// show: Output current element.

#include <iostream>
#include <vector>
 
using namespace std;
 
class MaxHeap {
public:
    void adjust(int* a, int root, int n) {
        int current = root;
        int e = a[root];
        int child = current * 2;
        while (child <= n) {
            if (child < n && a[child] < a[child + 1]) {
                child++;
            }
            if (a[current] > a[child]) {
                break;
            }
            swap(a[current], a[child]);
            current = child;
            child = current * 2;
        }
        a[current] = e;
    }
 
    void heapify() {
        for(int i=heapsize/2;i>=1;i--){
            adjust(array, i, heapsize);
        }
    }
 
    void heap() {
        swap(array[1], array[heapsize--]);
        adjust(array, 1, heapsize);
        currentpos = 1;
    }
 
    void right() {
        currentpos = currentpos*2+1;
        cout << array[currentpos] << endl;
    }
 
    void left() {
        currentpos = currentpos * 2;
        cout << array[currentpos] << endl;
    }
 
    void show() {
        cout << array[currentpos] << endl;
    }
 
public:
    int heapsize = 0;
    int* array = new int[1000];
    int currentpos = 1;
};
 
int main()
{
    int count;
    cin >> count;
    MaxHeap h;
    for (int i = 1; i <= count; i++) {
        int num;
        cin >> num;
        h.array[i] = num;
        h.heapsize++;
    }
    h.heapify();
    string cmd;
    while (cin >> cmd) {
        if (cmd == "heap") {
            h.heap();
        }
        else if (cmd == "right") {
            h.right();
        }
        else if (cmd == "left") {
            h.left();
        }
        else if (cmd == "show") {
            h.show();
        }
    }
}
