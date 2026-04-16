#include <iostream>
#include <vector>

using namespace std;

int solution(int n, int row, int column);

int main()
{
    int n, r, c;
    cin >> n >> r >> c;

    cout << solution(n,r,c);
    return 0;
}

int solution(int n, int row, int column)
{
    if(n == 0) return 0;
    const static int pattern[2][2] = {{0,1},{2,3}};

    int blockSize = 1 << (n-1);
    int divr = row / blockSize, divc = column / blockSize;
    int modr = row % blockSize, modc = column % blockSize;

    return pattern[divr][divc] * blockSize * blockSize + solution(n-1, modr, modc);
}