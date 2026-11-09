#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int u, v, w, x;
    cin >> u >> v >> w >> x;

    int maxi = max({u, v, w, x});

    if(maxi - u != 0){
        cout << maxi - u << " ";
    }
    if(maxi - v != 0){
        cout << maxi - v << " ";
    }
    if(maxi - w != 0){
        cout << maxi - w << " ";
    }
    if(maxi - x != 0){
        cout << maxi - x << " ";
    }
}