/*
 * Program: Epsilon Closure Computation for ε-NFA
 * ---------------------------------------------
 * Description:
 * This program computes the epsilon (ε) closure for each state in a Non-deterministic Finite Automaton (NFA).
 * The epsilon closure of a state includes the state itself and all states reachable from it using 
 * only epsilon (ε) transitions.
 *
 * Working:
 * - The user enters the number of states and transitions.
 * - Each transition is read as: <from_state> <symbol> <to_state>.
 * - If the symbol is 'e', it represents an epsilon transition.
 * - The program constructs an adjacency matrix to store epsilon transitions, 
 *   then applies a transitive closure (Floyd–Warshall-like approach) to find 
 *   all reachable states through epsilon paths.
 * - Finally, it displays the epsilon closure for each state.
 *
 * Input Format:
 *   Number of states
 *   Number of transitions
 *   List of transitions in the format: from symbol to
 *   (Example: 0 e 1)
 *
 * Output Format:
 *   Displays epsilon closure of each state in the format:
 *   epsilon(i) = { list_of_reachable_states }
 *
 * Example:
 *   Input:
 *     3
 *     3
 *     0 e 1
 *     1 e 2
 *     0 e 2
 *
 *   Output:
 *     epsilon(0) = { 0 1 2 }
 *     epsilon(1) = { 1 2 }
 *     epsilon(2) = { 2 }
 *
 * Author: Vandana
 * Date: 2025-11-12
 */


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


