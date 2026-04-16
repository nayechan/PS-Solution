#define v long long
v a[128][64];
v f(v k,v n){if(k*n<1)return k!=0;if(a[k][n]==~0ULL)a[k][n]=f(k-1,n-1)+f(k+1,n-1);return a[k][n];}
main(k,n){memset(a,~0ULL,sizeof(a));scanf("%d%d",&k,&n);printf("%lld",f(k,n));}