#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int visit(vector<vector<int>> & data, vector<vector<int>> & visited, int row, int column, int m, int n);

int main()
{
    vector<vector<int>> data, visited;
    
    int n, m;

    vector<int> result;

    scanf("%d %d",&n,&m);

    data = vector<vector<int>>(n, vector<int>(m));
    visited = vector<vector<int>>(n, vector<int>(m, 0));

    for(auto & row : data)
    {
        for(auto & element : row)
        {
            scanf("%d",&element);
        }
    }

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            auto currentVisitResult = visit(data, visited, i, j, m, n);

            if(currentVisitResult > 0)
                result.push_back(currentVisitResult);
        }
    }

    if (!result.empty())
    {
        printf("%d\n%d", result.size(), *max_element(result.begin(), result.end()));
    }
    else
    {
        printf("0 0");
    }

    return 0;
}

int visit(vector<vector<int>> & data, vector<vector<int>> & visited, int row, int column, int m, int n)
{
    if(visited[row][column] != 0) return -1;
    if(data[row][column] == 0) return -1;

    set<pair<int, int>> visited_list;
    queue<pair<int, int>> bfs_queue;
    int count = 0;

    vector<int> deltaX = {0, 0, 1, -1};
    vector<int> deltaY = {1, -1, 0, 0};

    bfs_queue.push({row, column});
    visited_list.insert({row, column});

    while(!bfs_queue.empty())
    {
        auto current = bfs_queue.front();
        bfs_queue.pop();
        ++count;

        for(int deltaIndex = 0; deltaIndex < deltaX.size(); ++deltaIndex)        
        {
            int rowToVisit = current.first + deltaY[deltaIndex];
            int columnToVisit = current.second + deltaX[deltaIndex];

            if(rowToVisit < 0 || rowToVisit >= n) continue;
            if(columnToVisit < 0 || columnToVisit >= m) continue;
            if(visited_list.find({rowToVisit, columnToVisit}) != visited_list.end()) continue;
            if(data[rowToVisit][columnToVisit] == 0) continue;

            bfs_queue.push({rowToVisit, columnToVisit});
            visited_list.insert({rowToVisit, columnToVisit});
        }
    }

    for(auto element : visited_list)
    {
        visited[element.first][element.second] = count;
    }

    return count;
}