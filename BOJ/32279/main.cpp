#include <iostream>
#include <vector>

using namespace std;

int get(vector<int> &v, int i, int p, int q, int r, int s)
{
    if(v[i]!=0)
        return v[i];
    
    if(i%2)
        return r*get(v,i/2,p,q,r,s)+s;

    return p*get(v,i/2,p,q,r,s)+q;
}

int main()
{
    int n,p,q,r,s;
    cin>>n>>p>>q>>r>>s;

    vector<int> v(n+1,0);
    cin>>v[1];

    int sum = 0;
    for(int i=1;i<=n;++i)
    {
        sum+=get(v,i,p,q,r,s);
    }
    cout << sum << endl;

    return 0;
}