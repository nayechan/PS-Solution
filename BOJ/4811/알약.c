#include <stdio.h>
#define v long long
#define g d[n][h]
v d[31][31];
v f(v n,v h){if((n|h)<0)return 0;if(g==-1)g=f(n-1,h+1)+f(n,h-1);return g;}
main(i){memset(d,-1,sizeof(d));d[0][0]=1;while(1){scanf("%d", &i);if(!i)break;printf("%lld\n",f(i,0));}}