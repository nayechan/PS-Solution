#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// 트리의 높이
	int height;
	cin >> height;

	// 0번 인덱스를 미사용, 1번 인덱스를 루트 노드로 가정하면 2^(h+1)개의 노드가 필요
	int size = 2<<height;
	vector<int> data(2<<height);
	vector<int> additionalWeight(2<<height, 0);

	// 모든 가중치의 합
	int result = 0;
	data[1] = 0;

	for(int i=2;i<size;++i)
	{
		cin >> data[i];
	}

	// 가장 리프노트부터 순회
	for(int currentHeight=height-1;currentHeight>=0;--currentHeight)
	{
		int minIndex = 1<<currentHeight;
		int maxIndex = (2<<currentHeight)-1;

		for(int element=minIndex;element<=maxIndex;++element)
		{
			// 가중치의 전체 합이 최대가 되도록 (감소는 불가능하므로) 계산
			int localMax = max(
				data[element*2]+additionalWeight[element*2], 
				data[element*2+1]+additionalWeight[element*2+1]
			);

			data[element*2] = localMax-additionalWeight[element*2];
			data[element*2+1] = localMax-additionalWeight[element*2+1];
			additionalWeight[element] = localMax;

			result += data[element*2];
			result += data[element*2+1];
		}
	}

	cout << result << endl;

	return 0;
}