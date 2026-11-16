#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        int BCount = 0;
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                count++;
                BCount = max(BCount, count);
            }
            else {
                count = 0;
            }
        }

        cout << BCount << endl;
    }

    return 0;
}
