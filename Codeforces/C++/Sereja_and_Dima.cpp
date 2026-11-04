#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    vector<int> arr(t);

    for (int i = 0; i < t; i++) {
        cin >> arr[i];
    }

    int serejaS = 0, DimaS = 0;
    int left = 0, right = t - 1;

    for (int i = 0; i < t; i++) {
        if (arr[left] > arr[right]) {
            if (i % 2 == 0) {
                serejaS += arr[left];
            } else {
                DimaS += arr[left];
            }
            left++;
        } 
        else {
            if (i % 2 == 0) {
                serejaS += arr[right];
            } else {
                DimaS += arr[right];
            }
            right--;
        }
    }

    cout << serejaS << " " << DimaS << endl;

    return 0;
}
