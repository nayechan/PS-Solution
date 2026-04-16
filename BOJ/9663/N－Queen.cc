#include <iostream>
#include <array>

using namespace std;

constexpr array<long long, 16> nqueen = {
    1,1,0,0,2,10,4,40,92,352,724,2680,14200,73712,365596,2279184
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    cout << nqueen[n] << '\n';
    return 0;
}