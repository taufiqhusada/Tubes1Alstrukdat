#include<stdio.h>
#include"multilist.h"

int main(){
	Multilist L;
	CreateEmptyMultilist(&L);
	int n,m,a,b,i;
	scanf("%d", &n);
	scanf("%d", &m);
	for (i = 1; i<=m; ++i){
		scanf("%d %d", &a, &b);
		InsertPair(&L, a, b);
		InsertPair(&L, b, a);
	}
	int q;
	scanf("%d", &q);
	for (i = 1; i<=q; ++i){
		scanf("%d %d", &a, &b);
		if (IsConnectedDirect(L,a,b)) printf("IsConnected %d %d\n",a,b );
		else printf("IsNotConnected %d %d\n",a,b);
	}
	int *arrResult;
	int sizeArr = 0;
	for (i = 1; i<=n; ++i){
		FindAllAdj(L,i,&arrResult,&sizeArr);
		if (sizeArr==0){
			printf("do not have any adj node\n");
		}
		else{
			int j;
			for (j = 1; j<=sizeArr; ++j){
				printf("%d ", arrResult[j]);
			}
			printf("\n");
		}
	}
	return 0;
}