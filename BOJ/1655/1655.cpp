// 1655 가운데를 말해요 (자력솔 실패)
// 두개의 힙을 활용하고, 스왑하는 아이디어를 떠올려야 함

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    priority_queue<int, vector<int>, less<int>> left;
    priority_queue<int, vector<int>, greater<int>> right;

    bool turn = true; // true : left, false : right

    for(int i=0;i<n;++i)
    {
        int v;
        cin >> v;

        if(turn)
            left.push(v);
        else
            right.push(v);

        if(!left.empty() && !right.empty())
        {
            int _max = right.top();
            int _min = left.top();

            if(_min > _max)
            {
                left.pop();
                right.pop();

                left.push(_max);
                right.push(_min);
            }
        }

        cout << left.top() << "\n";

        turn = !turn;
    }

    return 0;
}