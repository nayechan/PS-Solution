#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <chrono>

using namespace std;

int cpm[1002][1002];
int d[1002];
int p[1002];
int parent[1002];
bool visited[1002] = {
    false,
};

vector<int> reconstruct_path(int from, int to)
{
    vector<int> path;

    for (int v = to; v != -1 && v != from; v = parent[v])
    {
        if (v != to)
            path.push_back(v);
    }

    reverse(path.begin(), path.end());

    return path;
}

void augment_matching(int n, const vector<int> &path, vector<int> &matchingIndex)
{
    // Toggle the edges along the augmenting path
    for (int i = 0; i < path.size() - 1; i += 2)
    {
        int u = path[i];
        int v = path[i + 1];

        // If u is matched with v, remove the match
        if (matchingIndex[u] == v)
        {
            matchingIndex[u] = -1;
            matchingIndex[v] = -1;
        }

        else
        {
            // If the person is already matched with a different job, remove the old match
            if (matchingIndex[u] != -1)
            {
                int oldJob = matchingIndex[u];
                matchingIndex[oldJob] = -1;
            }

            // If the job is already matched with a different person, remove the old match
            if (matchingIndex[v] != -1)
            {
                int oldPerson = matchingIndex[v];
                matchingIndex[oldPerson] = -1;
            }

            matchingIndex[u] = v;
            matchingIndex[v] = u;
        }
    }
}

void dijkstra(int n, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> &pq)
{

    d[2 * n] = 0;
    parent[2 * n] = 2 * n;
    pq.push({0, 2 * n});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        if (visited[u])
            continue;

        if (dist > d[u])
            continue;

        visited[u] = true;

        for (int v = 0; v < 2 * n + 2; ++v)
        {
            if (!visited[v] && cpm[u][v] != INT_MAX)
            {
                int cost = cpm[u][v];
                if (d[v] > dist + cost)
                {
                    d[v] = dist + cost;
                    parent[v] = u;
                    pq.push({d[v], v});
                }
            }
        }
    }
}

vector<int> select(const vector<vector<int>> &cost)
{
    auto start = chrono::high_resolution_clock::now();

    int n = cost.size();
    vector<int> matchingIndex(2 * n + 2, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    for (int i = 0; i < 2 * n + 2; ++i)
    {
        d[i] = INT_MAX;
    }
    for (int i = 0; i < 2 * n + 2; ++i)
    {
        parent[i] = -1;
    }
    for (int i = 0; i < 2 * n; ++i)
    {
        p[i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        int min = INT_MAX;
        for (int j = 0; j < n; ++j)
        {
            int _cost = cost[j][i];
            if (_cost < min)
                min = _cost;
        }
        p[i + n] = min;
    }

    for (int i = 0; i < 2 * n + 2; ++i)
    {
        for (int j = 0; j < 2 * n + 2; ++j)
        {
            cpm[i][j] = INT_MAX;
        }
    }

    for (int r = 0; r < n; ++r)
    {
        for (int i = 0; i < 2 * n + 2; ++i)
        {
            d[i] = INT_MAX;
        }
        for (int i = 0; i < 2 * n + 2; ++i)
        {
            parent[i] = -1;
        }
        for (int i = 0; i < 2 * n + 2; ++i)
        {
            visited[i] = false;
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = n; j < 2 * n; ++j)
            {
                cpm[i][j] = cost[i][j - n] - p[i] - p[j];
            }
        }
        for (int i = n; i < 2 * n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matchingIndex[i] == j)
                    cpm[i][j] = -cost[j][i - n] + p[i] + p[j];
                else
                    cpm[i][j] = INT_MAX;
            }
        }
        chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
        cout << "Time taken 2: " << diff.count() << " seconds" << endl;
        start = chrono::high_resolution_clock::now();

        for (int i = 0; i < n; ++i)
        {
            if (matchingIndex[i] == -1)
                cpm[2 * n][i] = 1;
            else
                cpm[2 * n][i] = INT_MAX;
        }

        for (int i = 0; i < n; ++i)
        {
            if (matchingIndex[n + i] == -1)
                cpm[n + i][2 * n + 1] = 1;
            else
                cpm[n + i][2 * n + 1] = INT_MAX;
        }
        diff = chrono::high_resolution_clock::now() - start;
        cout << "Time taken 3: " << diff.count() << " seconds" << endl;
        start = chrono::high_resolution_clock::now();

        dijkstra(n, pq);
        diff = chrono::high_resolution_clock::now() - start;
        cout << "Time taken 4: " << diff.count() << " seconds" << endl;
        start = chrono::high_resolution_clock::now();

        // m <- m xor p
        vector<int> augmenting_path = reconstruct_path(2 * n, 2 * n + 1);
        augment_matching(n, augmenting_path, matchingIndex);

        for (int i = 0; i < n; ++i)
        {
            p[i] = p[i] - d[i];
        }
        for (int i = n; i < 2 * n; ++i)
        {
            p[i] = p[i] + d[i];
        }
        diff = chrono::high_resolution_clock::now() - start;
        cout << "Time taken 5: " << diff.count() << " seconds" << endl;
        start = chrono::high_resolution_clock::now();
    }

    return matchingIndex;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // cin >> cost[i][j];
            cost[i][j] = (rand() % 1000) + 1;
        }
    }
    auto start = chrono::high_resolution_clock::now();
    auto matchingIndex = select(cost);

    int sum = 0;

    for (int i = 0; i < n; ++i)
    {
        int matchedJob = matchingIndex[i] - n;
        // cout << i << " " << matchedJob << '\n';
        sum += cost[i][matchedJob];
    }

    cout << sum << '\n';
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> diff = chrono::high_resolution_clock::now() - start;
    cout << "Time taken: " << diff.count() << " seconds" << endl;
    start = chrono::high_resolution_clock::now();

    return 0;
}