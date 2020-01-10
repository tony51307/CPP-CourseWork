// Description:
// Given T is a graph with n vertices. The edges of T are undirected. Each edge in T has a non-negative length. Write a C++ program to read the tree T and calculate shortest distance from a specified vertex s to all the other vertexes. You should print out not only the distance but also the path from s to every vertex.
// The input may exist multiple edges between two vertexes. The printing format is the same as Sample Output. You should design a class called Graph to store vertices and edges.

// Input:
// First Line: n e s    n is number or vertexes    e is number of edges    s is the starting vertex
// Second Line ~ (n + 1)th Line: p q d
// P and q are non-negative integers indicating the vertex of the defined edge <p, q>, and d is the length of the edge

 
#include <iostream>
#include <vector>
 
using namespace std;
 
class Graph {
public:
    void setGraph(int v, int e, int s) {
        vertex = v;
        edge = e;
        startpoint = s;
        array = new int* [v + 1];
        for (int i = 0; i <= vertex; i++) {
            array[i] = new int[v + 1];
            for (int j = 0; j <= vertex; j++) {
                array[i][j] = 0;
            }
        }
    }
 
    void add(int a, int b, int d) {
        if (array[a][b] == 0 || array[a][b] > d) {
            array[a][b] = d;
            array[b][a] = d;
        }
    }
 
    void shortestPath() {
        int *path=new int[vertex + 1] ;
        int* distance = new int[vertex + 1];
        bool *visited = new bool[vertex + 1];
        for (int i = 1; i <= vertex; i++) {
            distance[i] = array[startpoint][i];
            visited[i] = false;
            path[i] = startpoint;
        }
 
        visited[startpoint] = true;
         
        while (!allvisited(visited)) {
            int pos = minD(visited,distance);
            visited[pos] = true;
            for (int i = 1; i <= vertex; i++) {
                if (array[pos][i] != 0) {
                    if (distance[pos] + array[pos][i] < distance[i] || distance[i] == 0) {
                        distance[i] = distance[pos] + array[pos][i];
                        path[i] = pos;
                    }
                }
            }
        }
 
        for (int i = 1; i <= vertex; i++) {
            if (i != startpoint) {
                cout << "Distance of " << startpoint << " to " << i << ": " << distance[i] << endl;
                cout << "Path: ";
                vector<int> stack;
                int num = i;
                stack.push_back(num);
                while (path[num] != startpoint) {
                    num = path[num];
                    stack.push_back(num);
                }
                stack.push_back(startpoint);
                while (!stack.empty()) {
                    cout << stack.back() << " ";
                    stack.pop_back();
                }
                cout << endl;
            }
        }
    }
 
    int minD(bool *visited, int *distance) {
        int num = 0;
        int min = 10000;
        for (int i = 1; i <= vertex; i++) {
            if (distance[i] != 0 && visited[i] != true && distance[i] < min) {
                num = i;
                min = distance[i];
            }
        }
        return num;
    }
 
    bool allvisited(bool* visited) {
        for (int i = 1; i <= vertex; i++) {
            if (visited[i] != true) {
                return false;
            }
        }
        return true;
    }
public:
    int** array;
    int vertex;
    int edge;
    int startpoint;
};
 
int main()
{
    int v;
    int e;
    int s;
    while (cin >> v >> e >> s) {
        Graph g;
        g.setGraph(v, e, s);
        for (int i = 1; i <= e; i++) {
            int a;
            int b;
            int d;
            cin >> a >> b >> d;
            g.add(a, b, d);
        }
        g.shortestPath();
    }
}
 
