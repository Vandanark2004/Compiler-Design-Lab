
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int t=0;
char V[20][20], O[20], input[20];
int v=-1, o=-1;

int pres(char c){
	if(c=='=')return 0;
	if(c=='-'||c=='+')return 1;
	if(c=='*'||c=='/')return 2;
	return -1;
}

void gen(char *a, char *b, char op){
	char r[5];
	if(op=='='){printf("\n%s = %s", a, b);return;}
	sprintf(r, "t%d", t++);
	printf("\n%s = %s %c %s",r, a, op, b);
	strcpy(V[++v], r);
}

void calc(){
	char b[20], a[20], op;
	strcpy(b, V[v--]);
	strcpy(a, V[v--]);
	op=O[o];
	if(op=='='){gen(a, b, '='); strcpy(V[++v], a);}
	else gen(a, b, op);
	o--;
}

int main(){
	printf("Enter input string: ");
	scanf("%s",input);
	char p=0;
	for(int i=0;input[i];i++){
		char c=input[i];
		if(isalnum(c)){
			char temp[]={c, 0};
			strcpy(V[++v], temp);
			p='a';
		}
		else if(c=='('){p='('; O[++o]='(';}
		else if(c==')'){
			while(o>=0 && O[o]!='(')calc();
			o--;
			p=')';
		}
		else {
			if (c=='-' && (p==0||!isalnum(p)||p=='('))strcpy(V[++v], "0");
			while(o>=0 && pres(c)<=pres(O[o]))calc;
			O[++o]=c;
			p=c;
		}
				
	}
	while(o>=0)calc();

	return 0;
}


