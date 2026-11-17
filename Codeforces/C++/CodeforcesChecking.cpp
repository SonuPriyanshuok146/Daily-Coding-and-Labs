#include<iostream>
#include<string>
using namespace std;

int main(){
    int t;
    cin >> t;
    string s = "codeforces";

    while(t--){
        char ch;
        cin >> ch;
        if(s.find(ch) != string::npos){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}