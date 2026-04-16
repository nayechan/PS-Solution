#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<vector<int>> cost(n+1, vector<int>(n+1));
    for (int i = 1;i <= n;++i)
    {
        for (int j = 1;j <= n;++j)
        {
            cin >> cost[i][j];
        }
    }

    vector<int> pi(n + 1), pj(n + 1);
    vector<int> assignment(n + 1);
    vector<int> predecessorJob(n + 1);

    // 각각의 행에 대해 매칭 수행
    for (int i = 1; i <= n; ++i) {
        assignment[0] = i; // 편의를 위해, 시작점을 현재 행의 값으로 지정
        int currentJ = 0; // 현재 탐색 중인 열

        vector<int> minCostReduction(n + 1, INT_MAX); // 각 열의 최소 비용 감소값
        vector<bool> jobVisited(n + 1, false); // 방문 여부

        // 목표하는 열(작업)을 찾을 때까지 반복
        do {
            jobVisited[currentJ] = true; //현재 열을 방문함
            int currentI = assignment[currentJ]; // 현재 열에 할당된 행을 가져옴
            int delta = INT_MAX; // 조정을 위한 델타 값
            int nextJob = -1; // 다음 탐색 작업

            for (int j = 1; j <= n; ++j)
            {
                // 아직 방문하지 않은 열이라면,
                if (!jobVisited[j]) {
                    // 포텐셜을 비용에서 빼서 감소된 비용 계산
                    int reducedCost = cost[currentI][j] - pi[currentI] - pj[j];

                    // 계산된 비용 감소값이 기존 최소값보다 작다면
                    if (reducedCost < minCostReduction[j])
                    {
                        minCostReduction[j] = reducedCost; // 최소 비용 감소값 업데이트
                        predecessorJob[j] = currentJ; // j의 이전 작업은 현재 작업임.
                    }

                    // 현재까지의 최소 비용 감소값보다 작다면
                    if (minCostReduction[j] < delta)
                    {
                        delta = minCostReduction[j]; // delta 업데이트
                        nextJob = j; // 다음으로 탐색할 열은 j열임.
                    }
                }
            }
                

            for (int j = 0; j <= n; ++j)
            {
                if (jobVisited[j]) // 방문한 열일 경우
                {
                    pi[assignment[j]] += delta; // 현재 열에 할당된 행의 포텐셜을 증가하고
                    pj[j] -= delta; // 현재 열의 포텐셜을 감소
                }
                else
                {
                    // 방문하지 않은 경우, 포텐셜 조정에 따라 비용감소 업데이트
                    minCostReduction[j] -= delta;
                }
            }
            
            // 다음 열(작업)으로 이동
            currentJ = nextJob;
        } while (assignment[currentJ] != 0); //현재 열이 매칭될 때까지 반복

        // 증강 경로를 따라 매칭 업데이트
        do {
            int previousJob = predecessorJob[currentJ]; // 현재 열의 이전 열을 가져옴
            assignment[currentJ] = assignment[previousJob]; //currentJ 열의 할당된 행을 previousJob에 할당된 행으로 변경
            currentJ = previousJob; // 현재 작업을 이전 작업으로 업데이트
        } while (currentJ); // 증강 경로의 시작점에 도달할 때까지 반복
    }

    int sum = 0;
    for(int i=1;i<=n;++i)
    {
        //cout << assignment[i] << " " << i << " : " << cost[assignment[i]][i] << endl;
        sum += cost[assignment[i]][i];
    }

    cout << sum << endl;

	return 0;
}