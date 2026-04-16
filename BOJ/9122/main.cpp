#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

void test()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> vertices(n); // first : distance, second : index

    for (int i = 0; i < m; ++i)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        --from; --to;

        vertices[from].push_back({ cost, to });
    }

    int s, f;
    cin >> s >> f;
    --s; --f;

    // fist : distance, second : count
    vector<vector<pair<int, int>>> distanceCount(n, vector<pair<int, int>>(2, { INT_MAX,0 }));

    auto comp = [](
        const tuple<pair<int, int>, pair<int, int>, int>& a,
        const tuple<pair<int, int>, pair<int, int>, int>& b)
        {
            if (get<0>(a) != get<0>(b))
            {
                return get<0>(a) > get<0>(b);
            }
            if (get<1>(a) != get<1>(b))
            {
                return get<1>(a) > get<1>(b);
            }
            return get<2>(a) > get<2>(b);
        };

    // first : shortest distance, second : second shortest distance, third : index
    priority_queue<
        tuple<pair<int, int>, pair<int, int>, int>,
        vector<tuple<pair<int, int>, pair<int, int>, int>>,
        decltype(comp)
    > pq(comp);

    pq.push({ {0,1},{INT_MAX,0},s });
    distanceCount[s][0] = { 0,1 };

    while (!pq.empty())
    {
        pair<int, int> distCount1 = get<0>(pq.top());
        pair<int, int> distCount2 = get<1>(pq.top());
        int _index = get<2>(pq.top());

        pq.pop();

        if (
            distanceCount[_index].size() >= 2 &&
            distanceCount[_index][0].first < distCount1.first &&
            distanceCount[_index][1].first < distCount2.first)
            continue;

        for (pair<int, int> p : vertices[_index])
        {
            pair<int, int> newDistCount1 = { distCount1.first + p.first, distanceCount[_index][0].second };
            pair<int, int> newDistCount2 = { distCount2.first + p.first, distanceCount[_index][0].second };

            pair<int, int> oldDistCount1 = distanceCount[p.second][0];
            pair<int, int> oldDistCount2 = distanceCount[p.second][1];

            bool changed = false;

            for (pair<int, int>& dc : distanceCount[p.second])
            {
                if (dc.first == newDistCount1.first)
                {
                    changed = true;
                    dc.second += distanceCount[_index][0].second;
                    newDistCount1.first = INT_MAX;
                    newDistCount1.second = 0;
                }
                if (dc.first == newDistCount2.first)
                {
                    changed = true;
                    dc.second += distanceCount[_index][1].second;
                    newDistCount2.first = INT_MAX;
                    newDistCount2.second = 0;
                }
            }
            distanceCount[p.second].push_back(newDistCount1);
            distanceCount[p.second].push_back(newDistCount2);

            sort(distanceCount[p.second].begin(), distanceCount[p.second].end());
            distanceCount[p.second].resize(2);

            if (distanceCount[p.second][0] != oldDistCount1 ||
                distanceCount[p.second][1] != oldDistCount2)
                pq.push({
                    distanceCount[p.second][0],
                    distanceCount[p.second][1],
                    p.second
                    });
        }
    }

}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        test();
    }
    return 0;
}