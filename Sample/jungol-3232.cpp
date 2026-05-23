#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int ax1, ay1, ax2, ay2;
    int bx1, by1, bx2, by2;

    cin >> ax1 >> ay1 >> ax2 >> ay2;
    cin >> bx1 >> by1 >> bx2 >> by2;

    int overX = min(ax2, bx2) - max(ax1, bx1);
    int overY = min(ay2, by2) - max(ay1, by1);

    if (overX > 0 && overY > 0) {
        cout << "FACE";
    }
    else if (overX == 0 && overY == 0) {
        cout << "POINT";
    }
    else if (overX < 0 || overY < 0) {
        cout << "NULL";
    }
    else {
        cout << "LINE";
    }

    return 0;
}