#include <iostream>

using namespace std;

bool subsolution(int n, int currentN, int k, int r, int c)
{

    if(r==0 && c==0)
        return false;

    currentN /= n;

    int blockR = r/currentN;
    int blockC = c/currentN;

    int outlineSize = (n-k)/2;

    if(outlineSize <= blockR && blockR < n-outlineSize && outlineSize <= blockC && blockC < n-outlineSize)
        return true;
    
    return subsolution(n, currentN, k, r%currentN, c%currentN);
}

int main()
{
    int s, n, k;
    cin >> s >> n >> k;

    int r1, r2, c1, c2;
    cin >> r1 >> r2 >> c1 >> c2;

    int maxSize = 1;
    for(int i=0;i<s;++i)
    {
        maxSize *= n;
    }

    for(int i=r1;i<=r2;++i)
    {
        for(int j=c1;j<=c2;++j)
        {
            bool result = subsolution(n, maxSize, k, i, j);

            if(result)
                cout << "1";
            else
                cout << "0";
        }
        cout << endl;
    }

    return 0;
}