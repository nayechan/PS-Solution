#include <iostream>

using namespace std;

int get_result(int a, int b)
{
    if(b == 0)
        return 1;
    
    if(b == 1)
        return a;

    if(b % 2 == 1)
        return (get_result(a, b-1) * a) % 10;
    
    int result = get_result(a, b/2);
    return (result * result) % 10;
}

int main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;++i)
    {
        int a, b;
        cin >> a >> b;

        int result = get_result(a, b) % 10; 

        if(result == 0) result = 10;

        cout << result << endl;
    }

}