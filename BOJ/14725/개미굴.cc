#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

using namespace std;

struct Node {
    map<string, unique_ptr<Node>> next;
};

void dfs(Node* current, int level = 0)
{
    for (const auto& [nextKey, nextNode] : current->next)
    {
        for (int i = 0; i < level * 2; ++i)
            cout << "-";
        cout << nextKey << "\n";

        dfs(nextNode.get(), level + 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    unique_ptr<Node> root = make_unique<Node>();
    Node* current;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int count;
        cin >> count;
        current = root.get();

        for (int j = 0; j < count; ++j)
        {
            string str;
            cin >> str;
            if (current->next.find(str) == current->next.end())
            {
                current->next[str] = make_unique<Node>();
            }
            current = current->next[str].get();
        }
    }

    dfs(root.get());

    return 0;
}