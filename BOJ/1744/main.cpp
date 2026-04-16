#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, less<int>> positive_num;
    priority_queue<int, vector<int>, greater<int>> negative_num;

    int n, sum = 0;
    scanf("%d",&n);
    for(int i=0; i<n; ++i)
    {
        int input;
        scanf("%d",&input);

        if(input < 0)
            negative_num.push(input);
        
        else
            positive_num.push(input);
    }

    while(positive_num.size() >= 2)
    {
        int a = positive_num.top();
        positive_num.pop();

        int b = positive_num.top();
        positive_num.pop();
        
        if(b==0){
            positive_num.push(0);
            sum += a;
        }
        else if(a==1 || b==1)
        {
            sum += a;
            sum += b;
        }
        else{
            sum += (a * b);
        }
    }
    while(negative_num.size() >= 2)
    {
        int a = negative_num.top();
        negative_num.pop();

        int b = negative_num.top();
        negative_num.pop();

        sum += (a * b);
    }


    // 1, 1
    if(positive_num.size() == 1 && negative_num.size() == 1)
    {
        if(positive_num.top() == 0)
        {
            sum += (positive_num.top() * negative_num.top());
        }
        else
        {
            sum += positive_num.top();
            sum += negative_num.top();
        }
    }


    // 0, 1 / 1, 0
    else if(positive_num.size() == 1)
    {
        sum += positive_num.top();
    }

    else if(negative_num.size() == 1)
    {
        sum += negative_num.top();
    }

    printf("%d",sum);

    return 0;
}