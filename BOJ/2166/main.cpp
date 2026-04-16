#include <iostream>
#include <vector>

using namespace std;

long long area(const vector<pair<int,int>>& point) {
    long long x1 = point[0].first;
    long long y1 = point[0].second;

    long long x2 = point[1].first;
    long long y2 = point[1].second;

    long long x3 = point[2].first;
    long long y3 = point[2].second;

    long long area = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    return area;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<pair<int,int>> polygon;
    polygon.reserve(n);

    for(int i=0;i<n;++i)
    {
        int inputX, inputY;
        cin >> inputX >> inputY;

        polygon.push_back({inputX, inputY});
    }

    long long sum = 0;

    for(int i=1; i<n-1; ++i)
    {
        vector<pair<int,int>> triangle = {polygon[0], polygon[i], polygon[i+1]};
        sum += area(triangle);
    }

    if(sum < 0) sum *= -1;

    cout << fixed;
    cout.precision(1);
    cout << (double)sum / 2 << endl;

    return 0;
}