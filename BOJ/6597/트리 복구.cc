#include <iostream>
#include <unordered_map>

using namespace std;

void printInverse(string& preOrder, string& inOrder, unordered_map<char, int>& charToIndex, int preS, int preE, int inS, int inE)
{
	if (preS > preE) {
		return;
	}
	int pos = charToIndex[preOrder[preS]];
	int lLen = pos - inS;
	int rLen = inE - pos;

	printInverse(preOrder, inOrder, charToIndex, preS + 1, preS + lLen, inS, pos - 1);
	printInverse(preOrder, inOrder, charToIndex, preS+lLen+1, preE, pos+1, inE);
	cout << inOrder[pos];
}

int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		unordered_map<char, int> charToIndex;

		int i = 0;
		for (const auto& e : b)
		{
			charToIndex[e] = i++;
		}

		printInverse(a, b, charToIndex, 0, a.size()-1, 0, b.size()-1);
		cout << '\n';
	}
	return 0;
}