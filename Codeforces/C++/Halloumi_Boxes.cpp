#include<iostream>
#include<vector>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);

        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }

        if(k >= 2){
            cout << "YES" << endl;
        }else{
            bool sorted = true;
            for(int i = 1; i < n; i++){
                if(arr[i] < arr[i-1]){
                    sorted = false;
                    break;
                }
            }
            cout << (sorted ? "YES" : "NO") << endl;
        }
    }
    return 0;
}