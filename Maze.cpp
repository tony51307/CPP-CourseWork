// Given a m x n Maze, where a value of 1 implies a blocked path, while a 0 means one can walk right on through, please output all possible paths from (0, 0) to (m - 1, n - 1) in alphabetical order.
// If there is no any path to reach exit, output “No path”. Note that the moving directions include North, East, West, and South only.

#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
class Maze{
public:
    void output();
    void findpath(vector<vector<int>> board, vector<int> path, int x, int y, int m, int n);
public:
    vector<vector <int>>pathdirection;
};
 
void Maze:: findpath(vector<vector<int>> board, vector<int> path, int x, int y, int m, int n){
    if(x==m-1&&y==n-1){
        pathdirection.push_back(path);
        return;
    }
     
    board[x][y]=1;
     
    if(x!=0&&board[x-1][y]!=1){
        x--;
        path.push_back(0);
        findpath(board, path, x, y, m, n);
        path.pop_back();
        x++;
    }
     
    if(y!=0&&board[x][y-1]!=1){
        y--;
        path.push_back(1);
        findpath(board, path, x, y, m, n);
        path.pop_back();
        y++;
    }
     
    if(y!=(int)board[x].size()-1&&board[x][y+1]!=1){
        y++;
        path.push_back(2);
        findpath(board, path, x, y, m, n);
        path.pop_back();
        y--;
    }
     
    if(x!=(int)board.size()-1&&board[x+1][y]!=1){
        x++;
        path.push_back(3);
        findpath(board, path, x, y, m, n);
        path.pop_back();
        x--;
    }
}
 
void Maze:: output(){
    if((int)pathdirection.size()>=1){
    for(int i=0;i<(int)pathdirection.size();i++){
        int x=0;
        int y=0;
        cout<<"("<<x<<","<<y<<")";
        for(int j=0;j<(int)pathdirection[i].size();j++){
            if(pathdirection[i][j]==0){
                x--;
            }else if(pathdirection[i][j]==1){
                y--;
            }else if(pathdirection[i][j]==2){
                y++;
            }else if(pathdirection[i][j]==3){
                x++;
            }
            cout<<","<<"("<<x<<","<<y<<")";
        }
        cout<<endl;
    }
    }else{
        cout<<"No path"<<endl;
    }
}
 
 
int main(int argc, const char * argv[]) {  
    int m;
    int n;
    while(cin>>m>>n){
        vector<vector<int>> board;
        for(int i=0;i<m;i++){
            string input;
            cin>>input;
            vector<int> line;
            for(int j=0;j<n;j++){
                line.push_back(input[j]-'0');
            }
            board.push_back(line);
        }
        Maze maze;
        vector<int> path;
        maze.findpath(board, path, 0, 0, m, n);
        maze.output();
    }
}
