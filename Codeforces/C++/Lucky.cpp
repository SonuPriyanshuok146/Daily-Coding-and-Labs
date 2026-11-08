#include<iostream>
#include<string>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        string str;
        cin >> str;
        int temp = stoi(str);

        int ans = 0;

        for(int i = 0; i < 6; i++){
            int r = temp % 10;
            if(i < 3){
                ans += r;
            }else{
                ans -= r;
            }
            temp /= 10;
        }

        if(ans == 0){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}