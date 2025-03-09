#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV,
    NUM_NODE, VAR_NODE, ASSIGN_NODE
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int value;         // For NUM_NODE
        char *varName;     // For VAR_NODE/ASSIGN_NODE
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
        };                 // For operators
    };
} ASTNode;

ASTNode* createNumNode(int num);
ASTNode* createVarNode(char *name);
ASTNode* createOpNode(NodeType op, ASTNode *left, ASTNode *right);
ASTNode* createAssignNode(char *name, ASTNode *expr);
void freeAST(ASTNode *node);


#endif
