#include <string>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX_N = (1 << 20);
int fenwick[MAX_N + 1] = {0, };

void update(int idx, int value)
{
	while (idx <= MAX_N)
	{
		fenwick[idx] += value;
		idx += idx & (-idx);
	}
}

int query(int idx)
{
	int value = 0;
	while (idx)
	{
		value += fenwick[idx];
		idx &= (idx - 1);
	}

	return value;
}

int find_kth(int k, int sz) {
    int idx = 0;
    for (int i = MAX_N; i > 0; i >>= 1) {
        if (idx + i <= sz && fenwick[idx + i] < k) {
            idx += i;
            k -= fenwick[idx];
        }
    }
    return idx + 1;
}

vector<int> solution(vector<string> operations) {
    priority_queue<int, vector<int>, greater<int>> minQ, deletedMin;
    priority_queue<int, vector<int>, less<int>> maxQ, deletedMax;
    
    vector<pair<int,int>> op;
    vector<int> nums;
    
    for(string & _op : operations)
    {
        stringstream ss(_op);
        
        char __op;
        int v;
        
        ss >> __op >> v;
        op.push_back({__op == 'I', v});
        if(__op == 'I') nums.push_back(v);
    }
    
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    
    int sz = 0;
    
    for(auto& [_op, v] : op)
    {
        if(_op)
        {
            int idx = lower_bound(nums.begin(),nums.end(),v)-nums.begin();
            update(idx+1, 1);
            ++sz;
        }
        else
        {
            if(sz == 0)
            {
                continue;
            }
            if(v == -1)
            {
                int idx = find_kth(1, nums.size());
                update(idx, -1);
                --sz;
            }
            else
            {
                int idx = find_kth(sz, nums.size());
                update(idx, -1);
                --sz;
            }
        }
    }
    
    vector<int> answer(2, 0);
    answer[0] = sz==0 ? 0 : nums[find_kth(sz, nums.size())-1];
    answer[1] = sz==0 ? 0 : nums[find_kth(1, nums.size())-1];
    return answer;
}