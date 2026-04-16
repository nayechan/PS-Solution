#include <iostream>

void test()
{
    int a, b;
    scanf("%d %d", &a, &b);

    printf("yes\n");
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;++i)
    {
        test();
    }
    return 0;
}