#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int hasDuplicateNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    if ((root->left && root->data == root->left->data) || (root->right && root->data == root->right->data)) {
        return 1;
    }

    return hasDuplicateNodes(root->left) || hasDuplicateNodes(root->right);
}

int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(2);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(2);

    if (hasDuplicateNodes(root)) {
        printf("Ima pone dva vurha s ednakvi stoinosti v dyrvo.\n");
    } else {
        printf("Niama dva vurha s ednakvi stoinosti v dyrvo.\n");
    }

    return 0;
}
