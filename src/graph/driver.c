#include<stdio.h>
#include"multilist.h"

int main(){
	Multilist L;
	CreateEmptyMultilist(&L);
	int n,a,b,i;
	scanf("%d", &n);
	for (i = 1; i<=n; ++i){
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
	return 0;
}