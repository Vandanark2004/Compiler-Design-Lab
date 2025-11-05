
#include<stdio.h>

int trans[20][20][20], n, closure[20][20], ns, nfa[20][20][20], nt;
char sym[20];

int idx(char c){
	for(int i=0;i<ns;i++)if(sym[i]==c)return i;
	return -1;
}

int main(){
	int i, j, k, from, to, m, s;
	char c;
	printf("Enter no of symbols: ");
	scanf("%d",&ns);
	printf("\nEnter symbols: ");
	for(i=0;i<ns;i++)scanf(" %c", &sym[i]);	
	//sym[0]='0';sym[1]='1', sym[2]='e';
	printf("\nEnter no of states: ");
	scanf("%d",&n);
	printf("\nEnter no of trans: ");
	scanf("%d",&nt);
	printf("\nEnter from char to: ");
	for(i=0;i<nt;i++){
		scanf("%d %c %d", &from, &c, &to);	
		trans[from][idx(c)][to]=1;
	}
	for(i=0;i<n;i++){
		closure[i][i]=1;
		for(j=0;j<n;j++)if(trans[i][idx('e')][j])closure[i][j]=1;
	}
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(closure[i][k]&&closure[k][j])closure[i][j]=1;
				
	for(i=0;i<n;i++)
		for(s=0;s<ns;s++)if(sym[s]!='e')
			for(j=0;j<n;j++)if(closure[i][j])
				for(k=0;k<n;k++)if(trans[j][s][k])
					for(m=0;m<n;m++)if(closure[k][m])nfa[i][s][m]=1;
					
	for(i=0;i<n;i++)
		for(s=0;s<ns;s++)if(sym[s]!='e'){
			printf("\nq%d--%c-->{", i, sym[s]);
			for(j=0;j<n;j++)if(nfa[i][s][j])printf(" q%d ", j);
			printf("}");		
		}
	return 0;
}




