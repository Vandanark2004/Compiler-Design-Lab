#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *kw[] = {
    "int", "float", "double", "return", "void", "if", "else", "while", "do",
    "switch", "case", "break", "continue", "char", "for", "typedef", "struct"
};
int nkw = 17;

char arith[] = {'+', '-', '*', '/', '%', '='};
char bit[] = {'^', '&', '!', '|'};
char sym[] = {'(', ')', '{', '}', '[', ']', '.', ';'};
char *logic[] = {"&&", "||", "<", ">", "<=", ">=", "=="};

int lineno = 0;

int isKeyword(char *word) {
    for (int i = 0; i < nkw; i++) {
        if (strcmp(word, kw[i]) == 0)
            return 1;
    }
    return 0;
}

int isArithmetic(char c) {
    for (int i = 0; i < sizeof(arith); i++)
        if (c == arith[i]) return 1;
    return 0;
}

int isBitwise(char c) {
    for (int i = 0; i < sizeof(bit); i++)
        if (c == bit[i]) return 1;
    return 0;
}

int isSymbol(char c) {
    for (int i = 0; i < sizeof(sym); i++)
        if (c == sym[i]) return 1;
    return 0;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[1024];
    int inComment = 0; // flag to track block comments

    if (fp == NULL) {
        printf("File not yet created. Try creating one.\n");
        return 0;
    }

    printf("\n--- TOKENIZATION RESULT ---\n");

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        lineno++;

        // --- Handle block comments ---
        if (inComment) {
            char *end = strstr(buffer, "*/");
            if (end) {
                inComment = 0;
                printf("<%s, COMMENT IGNORED>\n", buffer);
            }
            continue;
        }

        // --- Detect start of block comment ---
        if (strstr(buffer, "/*")) {
            inComment = 1;
            printf("<%s, COMMENT IGNORED>\n", buffer);
            continue;
        }

        // --- Handle single line comments ---
        if (buffer[0] == '/' && buffer[1] == '/') {
            printf("<%s, COMMENT IGNORED>\n", buffer);
            continue;
        }

        // --- Handle preprocessor directive ---
        if (buffer[0] == '#') {
            printf("<%s, PREPROCESSOR DIRECTIVE>\n", buffer);
            continue;
        }

        // --- Tokenize with respect to space ---
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            if (isKeyword(token))
                printf("<%s, KEYWORD>\n", token);
            else if (isalpha(token[0]) || token[0] == '_')
                printf("<%s, IDENTIFIER>\n", token);
            else if (isdigit(token[0]))
                printf("<%s, NUMBER>\n", token);
            else if (strlen(token) == 1 && isArithmetic(token[0]))
                printf("<%s, ARITHMETIC OPERATOR>\n", token);
            else if (strlen(token) == 1 && isBitwise(token[0]))
                printf("<%s, BITWISE OPERATOR>\n", token);
            else if (strlen(token) == 1 && isSymbol(token[0]))
                printf("<%s, DELIMITER>\n", token);
            else
                printf("line %d: error - %s (no match found)\n", lineno, token);

            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    return 0;
}




