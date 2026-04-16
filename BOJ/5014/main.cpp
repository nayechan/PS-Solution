#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int f,s,g,u,d;
    cin >> f >> s >> g >> u >> d;

    vector<bool> visited(f+1, false);

    queue<int> target;
    target.push(s);
    visited[s] = true;

    int round = 0;
    bool found = false;

    while(!target.empty())
    {
        int size = target.size();

        for(int i=0;i<size;++i)
        {
            int current = target.front();
            target.pop();

            if(current == g)
            {
                found = true;
                break;
            }

            if(current + u <= f && !visited[current+u])
            {
                target.push(current+u);
                visited[current+u] = true;
            }
            if(current - d >= 1 && !visited[current-d])
            {
                target.push(current-d);
                visited[current-d] = true;
            }
        }

        if(found) break;
        ++round;
    }

    if(found)
        cout << round << endl;
    
    else
        cout << "use the stairs" << endl;

    return 0;
}