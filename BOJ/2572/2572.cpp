#include <iostream>
#include <vector>

using namespace std;

int dp(vector<vector<int>>& scoreDp, vector<char>& cardOrder, vector<vector<pair<int, char>>>& graph, int remaining, int current)
{
    if (remaining == 0)
        return 0;

    if (scoreDp[remaining][current] != -1)
        return scoreDp[remaining][current];

    int n = cardOrder.size();
    char currentCard = cardOrder[n - remaining];

    int result = 0;
    for (pair<int, char>& p : graph[current])
    {
        int localResult = dp(scoreDp, cardOrder, graph, remaining - 1, p.first);
        if (p.second == currentCard)
        {
            localResult += 10;
        }

        if (localResult > result)
        {
            result = localResult;
        }
    }

    scoreDp[remaining][current] = result;
    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<char> cardOrder(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> cardOrder[i];
    }

    int m, k;
    cin >> m >> k;

    vector<vector<pair<int, char>>> graph(m + 1);
    for (int i = 0; i < k; ++i)
    {
        int from, to;
        char color;

        cin >> from >> to >> color;

        --from;
        --to;

        graph[from].push_back({ to, color });
        graph[to].push_back({ from, color });
    }

    vector<vector<int>> scoreDp(n + 1, vector<int>(m, -1));
    for (int i = 0; i < m; ++i)
        scoreDp[0][i] = 0;

    int result = dp(scoreDp, cardOrder, graph, n, 0);

    cout << result << '\n';

    return 0;
}