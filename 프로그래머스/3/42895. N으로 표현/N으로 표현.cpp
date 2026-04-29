#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int N, int number) {
    
    vector<vector<int>> num(10);
    vector<int> used(1000000, 0);
    
    int current = N;
    for(int i=1;i<=6;++i)
    {
        num[i].push_back(current);
        used[current] = i;
        current*=10;
        current+=N;
    }
    
    for(int i=2;i<=8;++i)
    {
        for(int j=1;j<=i-1;++j)
        {
            for(auto &e1 : num[j])
            {
                for(auto &e2 : num[i-j])
                {
                    vector<int> target = {e1+e2, e1-e2, e1*e2};
                    if(e2 != 0) target.push_back(e1/e2);
                    for(int t=0;t<target.size();++t)
                    {
                        if(0 <= target[t] && target[t] < 1000000 && !used[target[t]])
                        {
                            num[i].push_back(target[t]);
                            used[target[t]] = i;
                        }
                    }
                }
            }
        }
    }
    
    int answer = used[number];
    if(answer == 0) answer = -1;
    return answer;
}