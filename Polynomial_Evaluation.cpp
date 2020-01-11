// Please design and implement a class template called Polynomial with requirements as follows:
// 1. Use dynamically allocated memory to store the coefficients and you should free the memory when the object is destroyed. (Do not use STL to implement.)
// 2. Design a member function to evaluate the polynomial with parameter X.
// 3. The coefficient and X’s type will be one of int, float or double.
// 4. Set std::cout.precision when you are output floating number. (Set float to 6, double to 10.)
// Input: Input the Type, Degree, Coefficients array and X.

#include <iostream>
#include <iomanip>
 
using namespace std;
 
template <class t>
class poly{
public:
    poly(int d){
        degree=d;
        array=new t[d+1];
    }
     
    t eval(t x){
        t result=0;
        for(int i=0;i<=degree;i++){
            if(i==0){
                result+=array[i];
            }else{
                t power=1;
                for(int j=0;j<i;j++){
                    power*=x;
                }
                result=result+array[i]*power;
            }
        }
        return result;
    }
public:
    t *array;
    int degree;
};
 
int main(int argc, const char * argv[]) {
    string type;
    while(cin>>type){
        if(type=="int"){
            int d;
            cin>>d;
            poly<int> p(d);
            for(int i=0;i<=d;i++){
                int num;
                cin>>num;
                p.array[i]=num;
            }
            int x;
            cin>>x;
            cout<<p.eval(x)<<endl;
        }else if(type=="double"){
            int d;
            cin>>d;
            poly<double> p(d);
 
            for(int i=0;i<=d;i++){
                double num;
                cin>>num;
                p.array[i]=num;
            }
            double x;
            cin>>x;
             
            cout<<setprecision(10)<<p.eval(x)<<endl;
        }else if(type=="float"){
            int d;
            cin>>d;
            poly<float> p(d);
 
            for(int i=0;i<=d;i++){
                float num;
                cin>>num;
                p.array[i]=num;
            }
            float x;
            cin>>x;
             
            cout<<setprecision(6)<<p.eval(x)<<endl;
        }
    }
    return 0;
}
