#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100


char op_stack[MAX_TOKENS];
int op_top = -1;

void push_op(char c) { op_stack[++op_top] = c; }
char pop_op()        { return op_stack[op_top--]; }
char peek_op()       { return op_stack[op_top]; }

long long num_stack[MAX_TOKENS];
int num_top = -1;

void push_num(long long n) { num_stack[++num_top] = n; }
long long pop_num()        { return num_stack[num_top--]; }


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int infix_to_postfix(char tokens[][20], int n, char output[][20], int *out_len) {
    op_top = -1;
    *out_len = 0;

    for (int i = 0; i < n; i++) {
        char *t = tokens[i];

        if (isdigit(t[0])) {
            strcpy(output[(*out_len)++], t);
        }
     
        else if (t[0] == '(') {
            push_op('(');
        }
        
        else if (t[0] == ')') {
            while (op_top != -1 && peek_op() != '(') {
                output[*out_len][0] = pop_op();
                output[*out_len][1] = '\0';
                (*out_len)++;
            }
            if (op_top == -1) return -1;
            pop_op(); 
        }
       
        else {
            while (op_top != -1 && peek_op() != '(' &&
                   precedence(peek_op()) >= precedence(t[0])) {
                output[*out_len][0] = pop_op();
                output[*out_len][1] = '\0';
                (*out_len)++;
            }
            push_op(t[0]);
        }
    }

    while (op_top != -1) {
        if (peek_op() == '(') return -1; 
        output[*out_len][0] = pop_op();
        output[*out_len][1] = '\0';
        (*out_len)++;
    }

    return 0; 
}


int evaluate_postfix(char output[][20], int out_len, long long *res) {
    num_top = -1;

    for (int i = 0; i < out_len; i++) {
        char *t = output[i];

    
        if (isdigit(t[0])) {
            push_num(atoll(t));
        }
     
        else {
            long long b = pop_num();
            long long a = pop_num();

            if (t[0] == '/' && b == 0) return -2; 

            if (t[0] == '+') push_num(a + b);
            else if (t[0] == '-') push_num(a - b);
            else if (t[0] == '*') push_num(a * b);
            else if (t[0] == '/') push_num(a / b);
        }
    }

    *res = pop_num();
    return 0; 
}


int main(void) {
    char line[300];
    if (!fgets(line, sizeof(line), stdin)) return 0;

    char tokens[MAX_TOKENS][20];
    int token_count = 0;

    char *tok = strtok(line, " \t\r\n");
    while (tok) {
        strcpy(tokens[token_count++], tok);
        tok = strtok(NULL, " \t\r\n");
    }

    if (token_count == 0) return 0;

    char output[MAX_TOKENS][20];
    int out_len = 0;

    if (infix_to_postfix(tokens, token_count, output, &out_len) != 0) {
        printf("ERROR: UNBALANCED\n");
        return 0;
    }

   
    long long result = 0;
    if (evaluate_postfix(output, out_len, &result) != 0) {
        printf("ERROR: DIV BY ZERO\n");
        return 0;
    }

    printf("%lld\n", result);
    return 0;
}