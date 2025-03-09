#include "ast.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

extern SymbolTable symTable;

void semanticCheck(ASTNode *node) {
//    if (!node) return;
    
    if (!node) {
        fprintf(stderr, "Error: NULL node encountered in semantic analysis\n");
        return;
    }

    printf("Semantic check for node type: %d\n", node->type);


    switch(node->type) {
        case ASSIGN_NODE:

            if (!node->varName || strlen(node->varName) == 0) {
                fprintf(stderr, "Error: Assignment to a variable with no name\n");
                exit(1);
            }

            if (!findSymbol(&symTable, node->varName)) {
            addSymbol(&symTable, node->varName, INT_TYPE);



            printf("Added variable '%s' to symbol table.\n", node->varName);



//    fprintf(stderr, "Undefined variable: %s\n", node->varName);
//                exit(1);


            }
            semanticCheck(node->left);
            break;
            
        case OP_ADD: case OP_SUB: case OP_MUL: case OP_DIV:
            semanticCheck(node->left);
            semanticCheck(node->right);
            // Add type checking logic here
            break;
            
        case VAR_NODE:
            if (!findSymbol(&symTable, node->varName)) {
                fprintf(stderr, "Undefined variable: %s\n", node->varName);
                exit(1);
            }
            break;
            
        case NUM_NODE:
            // No semantic checks needed for numbers
            break;

        default:
            fprintf(stderr, "Unknown AST node type: %d\n", node->type);
            exit(1);
    }
}
