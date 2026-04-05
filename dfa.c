#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 20
#define MAX_PRODUCTIONS 20
#define MAX_SYMBOLS 20
#define MAX_SET 50

typedef struct {
    char lhs;
    char rhs[MAX_PRODUCTIONS][MAX_SYMBOLS];
    int prod_count;
} Rule;

Rule grammar[MAX_RULES];
Rule clean_grammar[MAX_RULES];
int g_count = 0, cg_count = 0;

char first_set[MAX_RULES][MAX_SET];
char follow_set[MAX_RULES][MAX_SET];

/* Check for Non-Terminals */
int is_nt(char c) { return (c >= 'A' && c <= 'Z'); }

int find_rule(char nt) {
    for (int i = 0; i < g_count; i++)
        if (grammar[i].lhs == nt) return i;
    return -1;
}

void add_to_set(char *set, char sym) {
    if (sym != '\0' && !strchr(set, sym)) {
        int len = strlen(set);
        set[len] = sym;
        set[len + 1] = '\0';
    }
}

/* Core Algorithm: Removal of Left Recursion */
void eliminate_recursion() {
    for (int i = 0; i < g_count; i++) {
        char A = grammar[i].lhs;
        char prime = A + 1; // Standard original logic for E' generation
        
        char alpha[MAX_PRODUCTIONS][MAX_SYMBOLS], beta[MAX_PRODUCTIONS][MAX_SYMBOLS];
        int ac = 0, bc = 0;

        for (int j = 0; j < grammar[i].prod_count; j++) {
            if (grammar[i].rhs[j][0] == A)
                strcpy(alpha[ac++], grammar[i].rhs[j] + 1);
            else
                strcpy(beta[bc++], grammar[i].rhs[j]);
        }

        if (ac > 0) {
            clean_grammar[cg_count].lhs = A;
            clean_grammar[cg_count].prod_count = 0;
            for (int j = 0; j < bc; j++)
                sprintf(clean_grammar[cg_count].rhs[clean_grammar[cg_count].prod_count++], "%s%c", beta[j], prime);
            cg_count++;

            clean_grammar[cg_count].lhs = prime;
            clean_grammar[cg_count].prod_count = 0;
            for (int j = 0; j < ac; j++)
                sprintf(clean_grammar[cg_count].rhs[clean_grammar[cg_count].prod_count++], "%s%c", alpha[j], prime);
            strcpy(clean_grammar[cg_count].rhs[clean_grammar[cg_count].prod_count++], "#");
            cg_count++;
        } else {
            clean_grammar[cg_count++] = grammar[i];
        }
    }
}

/* FIRST Calculation */
void compute_first() {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < cg_count; i++) {
            for (int j = 0; j < clean_grammar[i].prod_count; j++) {
                char sym = clean_grammar[i].rhs[j][0];
                if (!is_nt(sym)) {
                    int old_len = strlen(first_set[i]);
                    add_to_set(first_set[i], sym);
                    if (strlen(first_set[i]) > old_len) changed = 1;
                } else {
                    for (int k = 0; k < cg_count; k++) {
                        if (clean_grammar[k].lhs == sym) {
                            for (int x = 0; x < strlen(first_set[k]); x++) {
                                int old_len = strlen(first_set[i]);
                                add_to_set(first_set[i], first_set[k][x]);
                                if (strlen(first_set[i]) > old_len) changed = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

/* FOLLOW Calculation */
void compute_follow() {
    add_to_set(follow_set[0], '$');
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < cg_count; i++) {
            for (int j = 0; j < clean_grammar[i].prod_count; j++) {
                char *prod = clean_grammar[i].rhs[j];
                for (int k = 0; prod[k] != '\0'; k++) {
                    if (is_nt(prod[k])) {
                        int idxB = -1;
                        for (int x = 0; x < cg_count; x++) if (clean_grammar[x].lhs == prod[k]) idxB = x;
                        if (idxB == -1) continue;
                        int old_len = strlen(follow_set[idxB]);

                        if (prod[k + 1] != '\0') {
                            char next = prod[k+1];
                            if (!is_nt(next)) {
                                if (next != '#') add_to_set(follow_set[idxB], next);
                            } else {
                                int idxN = -1;
                                for (int x = 0; x < cg_count; x++) if (clean_grammar[x].lhs == next) idxN = x;
                                int has_eps = 0;
                                for (int x = 0; x < strlen(first_set[idxN]); x++) {
                                    if (first_set[idxN][x] == '#') has_eps = 1;
                                    else add_to_set(follow_set[idxB], first_set[idxN][x]);
                                }
                                if (has_eps) for (int x = 0; x < strlen(follow_set[i]); x++) add_to_set(follow_set[idxB], follow_set[i][x]);
                            }
                        } else {
                            for (int x = 0; x < strlen(follow_set[i]); x++) add_to_set(follow_set[idxB], follow_set[i][x]);
                        }
                        if (strlen(follow_set[idxB]) > old_len) changed = 1;
                    }
                }
            }
        }
    }
}

void print_set(char *set) {
    printf("{ ");
    for (int i = 0; i < strlen(set); i++) {
        printf("%c%s", set[i], (i == strlen(set) - 1) ? "" : ", ");
    }
    printf(" }");
}

int main() {
    int n;
    printf("Enter number of rules: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char in[100];
        scanf("%s", in);
        char lhs = in[0];
        int idx = find_rule(lhs);
        if (idx == -1) {
            idx = g_count++;
            grammar[idx].lhs = lhs;
            grammar[idx].prod_count = 0;
        }
        char *token = strtok(in + 2, "|");
        while (token) {
            strcpy(grammar[idx].rhs[grammar[idx].prod_count++], token);
            token = strtok(NULL, "|");
        }
    }

    eliminate_recursion();
    compute_first();
    compute_follow();

    printf("\n Productions after removing Left Recursion\n");
    for (int i = 0; i < cg_count; i++) {
        printf("%c -> ", clean_grammar[i].lhs);
        for (int j = 0; j < clean_grammar[i].prod_count; j++)
            printf("%s%s", clean_grammar[i].rhs[j], (j == clean_grammar[i].prod_count - 1) ? "" : " | ");
        printf("\n");
    }

    printf("\n%-15s | %-25s | %-25s\n", "Non Terminal", "First Set", "Follow Set");
    printf("-----------|----------------------|----------------------\n");
    for (int i = 0; i < cg_count; i++) {
        printf("%-10c | ", clean_grammar[i].lhs);
        print_set(first_set[i]);
        printf("%*s | ", (int)(20 - (strlen(first_set[i])*3)), ""); // Padding
        print_set(follow_set[i]);
        printf("\n");
    }
    printf(" \n# indicates Epsilon\n");
    return 0;
}