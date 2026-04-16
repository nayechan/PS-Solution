#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int r, c;
    cin >> r >> c;

    vector<vector<int>> graph(r * c + 1, vector<int>());

    unordered_map<char, pair<int, int>> charToDirection;

    charToDirection['U'] = { -1,0 };
    charToDirection['R'] = { 0,1 };
    charToDirection['D'] = { 1,0 };
    charToDirection['L'] = { 0,-1 };

    for (int i = 0; i < r; ++i)
    {
        string input;
        cin >> input;

        int j = 0;
        for (char ch : input)
        {
            pair<int, int> from = { i,j };
            pair<int, int> to = { i + charToDirection[ch].first, j + charToDirection[ch].second };

            if (0 <= to.first && to.first < r && 0 <= to.second && to.second < c)
                graph[to.first * c + to.second].push_back(from.first * c + from.second);

            else
                graph[r * c].push_back(from.first * c + from.second);

            ++j;
        }
    }

    vector<bool> visited(r * c + 1, false);
    queue<int> target;

    int count = 0;

    visited[r * c] = true;
    target.push(r * c);

    while (!target.empty())
    {
        int current = target.front();
        target.pop();
        for (int to : graph[current])
        {
            if (!visited[to])
            {
                target.push(to);
                visited[to] = true;
                ++count;
            }
        }
    }

    cout << count << endl;

    return 0;
}