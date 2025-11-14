
#include<stdio.h>

int D[1024][10], trans[10][10][10], fin[10], vis[1024], sym[10];
int n, m, init, fs, t;

void nfatodfa(){
	int q[1024], f=0, r=0;
	int init_mask=(1<<init);
	q[r++]=init_mask;
	while(f<r){
		int s=q[f++];
		for(int a=0;a<m;a++){
			int ns=0;
			for(int i=0;i<n;i++)
				if(s&(1<<i))
					for(int j=0;j<n;j++)
						if(trans[i][a][j])ns|=(1<<j);
			D[s][a]=ns;
			if(ns && !vis[ns]){
				q[r++]=ns;
				vis[ns]=1;
			}
		}
	}
	vis[0]=1;
	for(int a=0;a<m;a++)
		D[0][a]=0;
}

void pr(int x){
	printf("{");
	int e=1;
	for(int i=0;i<n;i++){
		if(x&(1<<i)){
			printf(" q%d", i);
			e=0;
		}
	}
	if(e==1)printf("phi");
	printf("}");
}

int main(){
	int a, b, c;
	printf("\nEnter no of states: ");scanf("%d",&n);
	printf("\nEnter no of symbols: ");scanf("%d",&m);
	for(int i=0;i<m;i++)sym[i]=i;
	printf("\nEnter initial state: ");scanf("%d",&init);
	printf("\nEnter no of final states: ");scanf("%d",&fs);
	printf("\nEnter final states: \n");
	for(int i=0;i<fs;i++){scanf("%d",&a);fin[a]=1;}
	printf("\nEnter no of transitions: ");scanf("%d",&t);
	printf("\nEnter trans: from sym to\n");
	for(int i=0;i<t;i++){
		scanf("%d %d %d",&a, &b, &c);
		trans[a][b][c]=1;
	}
	nfatodfa();
	
	printf("\n--------------DFA TABLE--------------\n\t");
	for(int a=0;a<m;a++)printf("\t%d",a);
	
	for(int s=0;s<(1<<n);s++){
		printf("\n");
		if(vis[s]){
			int isfs=0, init_mask=(1<<init);
			for(int i=0;i<n;i++)if((s&(1<<i)) && fin[i])isfs=1;
			
			if(s&init_mask)printf("->");else printf("  ");
			if(isfs)printf("*");else printf(" ");
			
			pr(s);
			printf("\t");
			for(int a=0;a<m;a++)
				pr(D[s][a]);
		}
		printf("\n");
	}
	
	return 0;
}

