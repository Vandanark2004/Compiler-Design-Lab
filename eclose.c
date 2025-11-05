
#include<stdio.h>

int eps[20][20], trans[20][20], nt, ne=0, n;

int main(){
	int from, to;
	char sym;
	printf("Enter no of ststes: ");
	scanf("%d", &n);
	printf("Enter no of transitions: ");
	scanf("%d", &nt);
	printf("\nEnter each of the transitions: ");
	for(int i=0;i<nt;i++){
		scanf("%d %c %d", &from, &sym, &to);
		if(sym=='e'){ trans[from][to]=1;ne++;}
	}
	for(int i=0;i<n;i++){
		eps[i][i]=1;
		for(int j=0;j<n;j++)
			if(trans[i][j])eps[i][j]=1;
	}
			
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(eps[i][k]&&eps[k][j])eps[i][j]=1;
			}
		}
	}
	for(int i=0;i<n;i++){
		printf("\nepsilon(%d)={", i);
		for(int j=0;j<n;j++){
			if(eps[i][j])printf(" %d", j);
		}
		printf("}");
	}

	return 0;
}


