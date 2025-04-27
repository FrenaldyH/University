/**
 *      author  : Frenaldy
 *      created: 28.04.2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treenode {
    int val;
    struct treenode *le, *ri;
} treenode;

treenode* create_node(int val) {
    treenode* newNode = (treenode*)malloc(sizeof(treenode));
    newNode->le = newNode->ri = NULL;
    newNode->val = val;
    return newNode;
}

treenode* insert(treenode* root, int val) {
    if (!root) 
        return create_node(val);
    if (val < root->val) 
        root->le = insert(root->le, val);
    else if (val > root->val) 
        root->ri = insert(root->ri, val);
    return root;
}

bool cek[3]; int key;
void pre_order(treenode* root) {
    if (root) {
        printf("%d ", root->val);
        pre_order(root->le);
        pre_order(root->ri);
    }
}

void in_order(treenode* root) {
    if (root) {
        in_order(root->le);
        printf("%d ", root->val);
        in_order(root->ri);
    }
}

void post_order(treenode* root) {
    if (root) {
        post_order(root->le);
        post_order(root->ri);
        printf("%d ", root->val);
    }
}

void cek_key(treenode* root) {
    if (root) {
        if(root->val == key) cek[2] = 1;
        cek_key(root->le);
        cek_key(root->ri);
    }
}

int main() {
    int arr[] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91, 9};

    treenode* root = NULL;
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) 
    root = insert(root, arr[i]);

    printf("\nPre-Order:\n");
    pre_order(root);
    printf("\nIn-Order:\n");
    in_order(root);
    printf("\nPost-Order:\n");
    post_order(root);

    printf("\n");
    do{
        for(int i = 0; i < 3; i++) cek[i] = false;
        printf("\nEnter a key number other than zero: ");
        scanf("%d", &key);
        cek_key(root);

        if(cek[0]) 
            printf("Value of key found in tree\n");

        if(cek[1]) 
            printf("Value of key found in tree\n");

        if(cek[2]) 
            printf("Value of key found in tree\n");
        if(!cek[0] && !cek[1] && !cek[2]) printf("Value of key not found in tree\n");

    } while(key);
}