// Please define and implement a class called String and provide commands as follows:
// freq: show frequency of each of the distinct characters in the string. (if character count < 1, shows nothing.)
// find str: show string str’s first position in the string. (if str not found, shows -1.)
// del start length: remove length characters beginning at start, and show result.
// chdel c: remove char c in string, and show result.

#include <iostream>
using namespace std;

class String{
public:
    friend istream& operator>>(istream& is, String& string);
    friend ostream& operator<<(ostream& os, String& string);
    friend bool operator==(const String& lhs, const String& rhs);
    
    int Find(String x){
        for(int i=0;i<length;i++){
            int num=i;
            int num2=0;
            for(int j=0;j<x.length;j++){
                if(array[num]==x.array[j]){
                    num++;
                    num2++;
                }else if(array[num]!=x.array[j]||num+(x.length-j+1)>length+1){
                    break;
                }
            }
            if(num2==x.length){
                return i;
            }
        }
        return -1;
    }
    
    void Delete(int start,int l){
        if(length-start-l<0){
            return;
        }
        
        char *newarray=new char[225];
        int i=0;
        int j=0;
        while(i<start){
            newarray[j++]=array[i];
            i++;
        }
        i+=l;
        while(i<length){
            newarray[j++]=array[i];
            i++;
        }
        array=newarray;
        array=new char[225];
        copy(newarray,newarray+length,array);
        length=j;
    }
    
    void chdel(char d){
        for(int i=0;i<length;i++){
            if(array[i]==d){
                Delete(i,1);
            }
        }
    }
    
    void freq(){
        int ch[26]={0};
        
        for(int i=0;i<length;i++){
            ch[array[i]-'a']++;
        }
        
        for(int i=0;i<26;i++){
            if(ch[i]>0){
                cout<<(char)(i+'a')<<" "<<ch[i]<<endl;
            }
        }
    }
    
    
public:
    char *array;
    int length;
};

istream& operator>>(istream& is, String& string){
    string.array=new char[225];
    int num=0;
        is>>string.array;
    int count=0;
    while(string.array[num]){
        count++;
        num++;
    }
    string.length=count;
    return is;
}

ostream& operator<<(ostream& os, String& string){
    for(int i=0;i<string.length;i++){
        os<<string.array[i];
    }
    return os;
}

bool operator==(const String& lhs, const String& rhs){
    if(lhs.length!=rhs.length){
        return false;
    }
    for(int i=0;i<lhs.length;i++){
        if(lhs.array[i]!=rhs.array[i]){
            return false;
        }
    }
    return true;
}


int main(int argc, const char * argv[]) {
    String s;
    cin>>s;
    string command;
    while(cin>>command){
        if(command=="freq"){
            s.freq();
        }else if(command=="chdel"){
            char x;
            cin>>x;
            s.chdel(x);
            cout<<s<<endl;
        }else if(command=="del"){
            int a;
            int b;
            cin>>a;
            cin>>b;
            s.Delete(a,b);
            cout<<s<<endl;
        }else if(command=="find"){
            String x;
            cin>>x;
            cout<<s.Find(x)<<endl;
        }
    }
    return 0;
}
