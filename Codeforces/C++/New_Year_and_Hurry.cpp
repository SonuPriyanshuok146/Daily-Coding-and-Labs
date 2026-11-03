#include<iostream>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    int timeleft = 240 - k;
    int solved = 0;
    int timespent = 0;

    for(int i = 1; i <= n; i++){
        timespent += 5*i;

        if(timespent <= timeleft){
            solved++;
        }else{
            break;
        }
    }
    cout << solved << endl;
    return 0;
}