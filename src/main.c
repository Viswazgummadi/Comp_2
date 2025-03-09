#include "ast.h"
#include "symbol.h"
#include <stdio.h>
#include <stdint.h>

extern FILE *yyin;
extern int yyparse();
extern ASTNode *root;
extern int yydebug;


SymbolTable symTable;


ASTNode *root = NULL;

// Add these prototypes
/*
void semanticCheck(ASTNode *node);
void generateCode(ASTNode *node, FILE *out);
void printAST(ASTNode *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("Node Type: %d\n", node->type);
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);
}
*/





int debug = 0;  // Set to 1 to enable debug output

#define DEBUG_PRINT(...) \
    do { if (debug) printf(__VA_ARGS__); } while (0)





void printAST(ASTNode *node, int depth) {
    if (!node) {
        DEBUG_PRINT("%*sNULL node\n", depth * 2, "");
        return;
    }
    

    DEBUG_PRINT("%*sNode Type: %d", depth * 2, "", node->type);

    if ((uintptr_t)node < 1000) {  // Check for suspiciously small pointer values
        printf("%*sInvalid node pointer: %p\n", depth * 2, "", (void*)node);
        return;
    }




    
    switch (node->type) {
        case NUM_NODE:
            DEBUG_PRINT(" (Value: %d)", node->value);
            break;
        case VAR_NODE:
            printf(" (Variable: %s)", node->varName ? node->varName : "NULL");
            break;
//        case ASSIGN_NODE:
  //          printf(" (Assign to: %s)", node->varName ? node->varName : "NULL");
    //        break;


        case ASSIGN_NODE:
            printf(" (%s: %s)", 
                   node->type == VAR_NODE ? "Variable" : "Assign to",
                   node->varName ? node->varName : "NULL");
            break;

        case OP_ADD:
            printf(" (Addition)");
            break;

        case OP_SUB:
            printf(" (Subtraction)");
            break;

        case OP_MUL:
            printf(" (Multiplication)");
            break;

        case OP_DIV:
            printf(" (Division)");
            break;

        default:
            printf(" (Unknown operation)");
            break;
    }
    
    printf("\n");
    
    if (node->left) {
        printf("%*sLeft:\n", (depth + 1) * 2, "");
        printAST(node->left, depth + 2);
    } else {
        printf("%*sLeft: NULL\n", (depth + 1) * 2, "");
    }
    
    if (node->right) {
        printf("%*sRight:\n", (depth + 1) * 2, "");
        printAST(node->right, depth + 2);
    } else {
        printf("%*sRight: NULL\n", (depth + 1) * 2, "");
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening input file");
        return 1;
    }
    printf("Input file opened successfully\n");
    initSymbolTable(&symTable);



    yydebug = 1;  // Enable debug output

    printf("Parsing input file...\n");

//    yyparse();



    if (yyparse() != 0) {
        fprintf(stderr, "Parse failed\n");
        return 1;
    }

    if (root == NULL) {
        fprintf(stderr, "Error: AST root is NULL\n");
        return 1;
    }


    printf("AST Structure:\n");
    printAST(root, 0);



    semanticCheck(root);
    
    printf("section .text\n");
    printf("global _start\n\n");
    printf("_start:\n");
    generateCode(root, stdout);
    printf("    mov ebx, eax\n");    // Exit code
    printf("    mov eax, 1\n");      // sys_exit
    printf("    int 0x80\n");
    
    fclose(yyin);
    freeAST(root);
    return 0;
}
