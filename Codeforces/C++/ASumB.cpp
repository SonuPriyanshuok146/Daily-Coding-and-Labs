#include<iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int q = n%10;
        n /= 10;

        cout << q + n%10 << endl;
    }
    return 0;
}