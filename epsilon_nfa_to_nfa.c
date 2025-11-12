/*
 * Program: NFA to NFA Conversion with Epsilon Closure (Epsilon-Transition Elimination)
 * -----------------------------------------------------------------------------------
 * Description:
 * This program eliminates epsilon (ε) transitions from a given Non-deterministic Finite Automaton (NFA)
 * and constructs an equivalent NFA without epsilon transitions.
 *
 * Working:
 * 1. The user provides:
 *      - The list of input symbols (including 'e' for epsilon).
 *      - The number of states.
 *      - The state transitions in the format: from symbol to.
 * 2. The program:
 *      - Stores transitions in a 3D array: trans[state][symbol][next_state].
 *      - Computes epsilon closure for each state using a transitive closure approach.
 *      - For each input symbol (except epsilon), it finds all transitions reachable through
 *        epsilon paths before and after consuming that symbol.
 *      - Constructs a new transition table (nfa[][][]) representing the equivalent NFA without epsilons.
 * 3. Finally, it displays the new NFA transitions in the form:
 *      q<state> --<symbol>--> { list of reachable states }.
 *
 * Input Format:
 *   - Number of symbols
 *   - List of symbols (e.g., 0 1 e)
 *   - Number of states
 *   - Number of transitions
 *   - Transitions in the form: from symbol to
 *     (Example: 0 e 1)
 *
 * Output Format:
 *   Displays the equivalent NFA transitions without epsilon moves:
 *   Example:
 *     q0--0-->{ q1 q3 }
 *     q0--1-->{ q2 }
 *     q1--0-->{ q3 }
 *
 * Example Run:
 *   Input:
 *     Enter no of symbols: 3
 *     Enter symbols: 0 1 e
 *     Enter no of states: 4
 *     Enter no of trans: 7
 *     Enter from char to:
 *     0 1 1
 *     1 1 0
 *     0 e 2
 *     2 0 3
 *     3 0 2
 *     2 1 4
 *     4 0 2
 *
 *   Output:
 *     q0--0-->{ q3 }
 *     q0--1-->{ q1 q4 }
 *     q1--0-->{ q3 }
 *     q1--1-->{ q1 q4 }
 *     q2--0-->{ q2 q3 }
 *     q2--1-->{ q4 }
 *     q3--0-->{ q2 q3 }
 *     q3--1-->{ q4 }
 *     q4--0-->{ q2 q3 }
 *     q4--1-->{ q4 }
 *
 * Notes:
 * - The algorithm effectively removes epsilon transitions by pre- and post-closure computation.
 * - This is an essential preprocessing step for converting an NFA (with ε) into DFA.
 *
 * Author: Vandana
 * Date: 2025-11-12
 */

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




