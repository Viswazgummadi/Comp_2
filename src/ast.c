// src/ast.c
#include "ast.h"
#include <stdlib.h>
#include <string.h>

ASTNode* createNumNode(int num) {
    printf("Creating NUM_NODE with value: %d\n", num);

    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for NUM_NODE\n");
        exit(1);
    }
    node->type = NUM_NODE;
    node->value = num;
    node->left = NULL;  // Initialize left and right to NULL
    node->right = NULL;
    return node;
}

ASTNode* createVarNode(char *name) {
    printf("Creating VAR_NODE with name: %s\n", name);
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for VAR_NODE\n");
        exit(1);
    }
    node->type = VAR_NODE;
    node->varName = strdup(name);
    node->left = NULL;  // Initialize left and right to NULL
    node->right = NULL;
    return node;
}

ASTNode* createOpNode(NodeType op, ASTNode *left, ASTNode *right) {
    printf("Creating OP_NODE with type: %d\n", op);
    ASTNode *node = malloc(sizeof(ASTNode));

    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for OP_NODE\n");
        exit(1);
    }
    node->type = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* createAssignNode(char *name, ASTNode *expr) {
    printf("Creating ASSIGN_NODE for variable: %s\n", name? name : "NULL");
    ASTNode *node = malloc(sizeof(ASTNode));

    if (!node) {
        fprintf(stderr, "Error: Failed to allocate memory for ASSIGN_NODE\n");
        exit(1);
    }
    node->type = ASSIGN_NODE;
//    node->varName = strdup(name);
    node->varName = name ? strdup(name) : NULL;
    node->left = expr;
    node->right = NULL;
    return node;
}


/*
void freeAST(ASTNode *node) {
    if (!node) return;
    freeAST(node->left);
    freeAST(node->right);
    if (node->type == VAR_NODE || node->type == ASSIGN_NODE) {
        free(node->varName);
    }
    free(node);
}
*/


void freeAST(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case ASSIGN_NODE:
        case VAR_NODE:
            if (node->varName) {
                free(node->varName);
                node->varName = NULL;  // Prevent double free
            }
            freeAST(node->left);
            break;
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
            freeAST(node->left);
            freeAST(node->right);
            break;
    }
    free(node);
}

