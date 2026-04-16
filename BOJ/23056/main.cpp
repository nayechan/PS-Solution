#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;

    vector<int> count(n, 0);

    auto cmp = [](const pair<int,string> &a, const pair<int,string> &b){
        if(a.first != b.first)
            return a.first > b.first;

        if(a.second.size() != b.second.size())
            return a.second.size() > b.second.size();
            
        return a.second > b.second;
    };

    priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)> blue(cmp), white(cmp);
    
    string name;
    int team;

    while(true){
        cin >> team >> name;
        if(team == 0 && name == "0") break;
        if(count[team-1] >= m) continue;
        if(team % 2 == 1)
            blue.push({team, name});
        else
            white.push({team, name});
        ++count[team-1];
    }

    while(!blue.empty())
    {
        pair<int,string> p = blue.top();
        cout << p.first << " " << p.second << endl;
        blue.pop();
    }

    while(!white.empty())
    {
        pair<int,string> p = white.top();
        cout << p.first << " " << p.second << endl;
        white.pop();
    }

    return 0;
}