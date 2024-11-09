#include <bits/stdc++.h>
using namespace std;
class SGTree{
     vector<int> seg;
     public:
         SGTree(int n){
               seg.resize(4*n+1);
         }
void build(int ind, int low, int high, vector<int> &arr) {
    if (low == high) {
        seg[ind] = arr[low];
        return;
    }

    int mid = low + (high - low) / 2;
    
    build(2 * ind + 1, low, mid, arr);
    build(2 * ind + 2, mid + 1, high, arr);
    
    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    return;
}

int query(int ind, int low, int high, int l, int r) {
    if (l > high || r < low) return INT_MAX;  // No overlap

    if (low >= l && high <= r) return seg[ind];  // Complete overlap

    int mid = low + (high - low) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);
    return min(left, right);
}

void update(int ind, int low, int high, int pos, int val) {
    if (low == high) {
        seg[ind] = val;
        return;
    }

    int mid = low + (high - low) / 2;

    if (pos <= mid) {
        update(2 * ind + 1, low, mid, pos, val);
    } else {
        update(2 * ind + 2, mid + 1, high, pos, val);
    }

    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}
};

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n, 0);
    for (auto &it : arr) cin >> it;
    
    SGTree sg(n);
    sg.build(0,0,n-1,arr);

    // Example query from index 2 to 4
    cout << "Minimum value in range [2, 4]: " << sg.query(0, 0, n - 1, 2, 4) << endl;


    // Update element at index 2 to value 5
    sg.update(0, 0, n - 1, 2,5);

    cout << "Minimum value in range [2, 4]: after update  " << sg.query(0, 0, n - 1, 2, 4) << endl;
    return 0;
}
