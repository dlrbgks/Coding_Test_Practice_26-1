#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Plate {
    int num;
    int x;
    int ymin;
    int ymax;
};

bool over(int a1, int a2, int b1, int b2) {
    return max(a1, b1) <= min(a2, b2);
}

int main() {
    int K, N;
    cin >> K;
    cin >> N;

    vector<Plate> v(N);

    for (int i = 0; i < N; i++) {
        cin >> v[i].num >> v[i].x >> v[i].ymin >> v[i].ymax;
    }

    sort(v.begin(), v.end(), [](Plate a, Plate b) {
        return a.x < b.x;
        });

    vector<int> safe;

    for (int i = 0; i < N; i++) {

        int cnt = 0;

        for (int j = 0; j < i; j++) {

            if (over(v[i].ymin, v[i].ymax,
                v[j].ymin, v[j].ymax)) {

                cnt++;

                if (cnt >= K)
                    break;
            }
        }

        if (cnt < K)
            safe.push_back(v[i].num);
    }

    sort(safe.begin(), safe.end());

    if (safe.empty()) {
        cout << 0;
    }
    else {
        for (int x : safe)
            cout << x << ' ';
    }

    return 0;
}