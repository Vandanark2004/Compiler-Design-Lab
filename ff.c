#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n_prod=0, n_nt=0;
char prod[50][50], nt[50], first[50][50], follow[50][50];
int visiting_first[50]; /* guard to prevent infinite recursion in FIRST */

void add(char *set, char c){ 
    if(c!='\0' && !strchr(set,c)){ 
        int l=strlen(set); set[l]=c; set[l+1]='\0'; 
    } 
}

int idx(char c){ 
    for(int i=0;i<n_nt;i++) if(nt[i]==c) return i; 
    return -1; 
}

void elim_lr(int i){
    char A=nt[i], New='Z'-n_nt+1;
    char alpha[20][20], beta[20][20];
    int a=0,b=0, lr=0;
    for(int j=0;j<n_prod;j++)
        if(prod[j][0]==A)
            if(strlen(prod[j])>=4 && prod[j][3]==A){ /* ensure rhs exists */
                strcpy(alpha[a++],&prod[j][4]); lr=1;
            } else strcpy(beta[b++],&prod[j][3]);
    if(lr){
        int k=0;
        for(int j=0;j<n_prod;j++) if(prod[j][0]!=A) strcpy(prod[k++],prod[j]);
        n_prod=k;
        for(int j=0;j<b;j++) sprintf(prod[n_prod++],"%c->%s%c",A,beta[j],New);
        for(int j=0;j<a;j++) sprintf(prod[n_prod++],"%c->%s%c",New,alpha[j],New);
        sprintf(prod[n_prod++],"%c->#",New);
        nt[n_nt++]=New;
    }
}

void first_set(int i){
    /* guard against infinite mutual recursion */
    if(visiting_first[i]) return;
    visiting_first[i] = 1;

    char A=nt[i];
    for(int j=0;j<n_prod;j++) if(prod[j][0]==A){
        char *rhs=&prod[j][3];
        for(int k=0;rhs[k];k++){
            char s=rhs[k];
            if(!isupper((unsigned char)s)||s=='#'){ add(first[i],s); break; }
            int si=idx(s);
            if(si==-1) { add(first[i], s); break; } /* defensive */
            if(strlen(first[si])==0) first_set(si);
            int eps=0;
            for(int l=0;l<strlen(first[si]);l++){
                if(first[si][l]=='#') eps=1; else add(first[i],first[si][l]);
            }
            if(!eps) break;
            if(k==strlen(rhs)-1 && eps) add(first[i],'#');
        }
    }

    visiting_first[i] = 0;
}

void follow_set(int i){
    char A=nt[i]; if(i==0) add(follow[i],'$');
    for(int j=0;j<n_prod;j++){
        char *rhs=&prod[j][3]; int lhs=idx(prod[j][0]);
        for(int k=0;rhs[k];k++) if(rhs[k]==A){
            int p=k+1, eps=1;
            while(p<strlen(rhs) && eps){
                eps=0; char s=rhs[p];
                if(!isupper((unsigned char)s)){ add(follow[i],s); break; }
                int si=idx(s);
                if(si == -1){ add(follow[i], s); break; } /* defensive */
                for(int l=0;l<strlen(first[si]);l++)
                    if(first[si][l]=='#') eps=1; else add(follow[i],first[si][l]);
                p++;
            }
            if(k==strlen(rhs)-1 || eps)
                if(lhs >= 0) /* defensive: ensure lhs valid */
                    for(int l=0;l<strlen(follow[lhs]);l++) add(follow[i],follow[lhs][l]);
        }
    }
}

int main(){
    int n; printf("Enter number of productions: "); scanf("%d",&n);
    printf("Enter productions (A->α, use # for epsilon):\n");
    for(int i=0;i<n;i++) scanf("%s",prod[i]);
    n_prod=n;

    // collect non-terminals
    for(int i=0;i<n;i++) if(idx(prod[i][0])==-1) nt[n_nt++]=prod[i][0];

    // eliminate left recursion
    int ini=n_nt; for(int i=0;i<ini;i++) elim_lr(i);

    printf("\nGrammar after eliminating left recursion:\n");
    for(int i=0;i<n_prod;i++) printf("%s\n",prod[i]);

    // FIRST
    int ch=1;
    while(ch){
        ch=0;
        for(int i=0;i<n_nt;i++){
            int l=strlen(first[i]);
            first_set(i);
            if(strlen(first[i])>l) ch=1;
        }
    }
    printf("\nFIRST sets:\n");
    for(int i=0;i<n_nt;i++) printf("FIRST(%c) = { %s }\n",nt[i],first[i]);

    // FOLLOW
    ch=1;
    while(ch){
        ch=0;
        for(int i=0;i<n_nt;i++){
            int l=strlen(follow[i]);
            follow_set(i);
            if(strlen(follow[i])>l) ch=1;
        }
    }
    printf("\nFOLLOW sets:\n");
    for(int i=0;i<n_nt;i++) printf("FOLLOW(%c) = { %s }\n",nt[i],follow[i]);
    return 0;
}

