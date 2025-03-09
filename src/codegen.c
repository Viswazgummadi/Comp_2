#include "ast.h"
#include "symbol.h"
#include <stdio.h>

extern SymbolTable symTable;

void generateCode(ASTNode *node, FILE *out) {
//    if (!node) return;
    if (!node) {
        fprintf(stderr, "Error: NULL node encountered in code generation\n");
        return;
    }

    printf("Generating code for node type: %d\n", node->type);

    switch(node->type) {
        case ASSIGN_NODE:
            generateCode(node->left, out);
            fprintf(out, "mov [%s], eax\n", node->varName);
            break;
            
        case OP_ADD:
            generateCode(node->left, out);
            fprintf(out, "push rax\n");
            generateCode(node->right, out);
            fprintf(out, "pop rbx\n");
            fprintf(out, "add eax, ebx\n");
            break;
            
        case NUM_NODE:
            fprintf(out, "mov eax, %d\n", node->value);
            break;
            
        case VAR_NODE:
            fprintf(out, "mov eax, [%s]\n", node->varName);
            break;
            
        case OP_SUB:
            generateCode(node->left, out);
            fprintf(out, "    push rax\n");
            generateCode(node->right, out);
            fprintf(out, "    pop rbx\n");
            fprintf(out, "    sub eax, ebx\n");
            break;

        case OP_MUL:
            generateCode(node->left, out);
            fprintf(out, "    push rax\n");
            generateCode(node->right, out);
            fprintf(out, "    pop rbx\n");
            fprintf(out, "    imul eax, ebx\n");
            break;

        case OP_DIV:
            generateCode(node->left, out);
            fprintf(out, "    push rax\n");
            generateCode(node->right, out);
            fprintf(out, "    pop rbx\n");
            fprintf(out, "    xor edx, edx\n"); // Clear remainder register
            fprintf(out, "    div ebx\n");      // Divide EAX by EBX
            break;

        default:
            fprintf(stderr, "Error: Unknown AST node type: %d\n", node->type);
    }
}
