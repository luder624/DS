#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define COMPARE(x,y) ((x)>(y))?-1: ((x)==(y))?0:1) 
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))//int x,int y,temp 

void perm (char* list,int i,int n){
	int j,temp;
	if(i==n){
		for(j=0;j<=n;j++)
			printf("%c",list[j]);
		printf("	\n");
	}
	else{
		for(j=i;j<=n;j++){
			SWAP(list[i],list[j],temp);
			perm(list,i+1,n);
			SWAP(list[i],list[j],temp);
		}
	}
}

int main(int argc, char *argv[]) {
	char list[4]={'a','b','c','d'};//放入字元需要用單引號 
	perm(list,0,3);
	return 0;
}
