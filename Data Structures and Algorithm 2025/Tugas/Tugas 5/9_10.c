/**
 *      author  : Frenaldy
 *      crreated: 19.04.2025
**/

#include <stdio.h>
#include <stdlib.h>

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

void post_order(treenode* root) {
    if (root) {
        post_order(root->le);
        post_order(root->ri);
        printf("%d ", root->val);
    }
}

void fill_array(int num[], treenode* root, int idx) {
    if(root == NULL) return;
    num[idx] = root->val;

    fill_array(num, root->le, idx * 2);
    fill_array(num, root->ri, idx * 2 + 1);
}

int lsb(int a) {
    return (a & (-a));
}

int msb(int a) {
    return ((a ^ lsb(a)) ? msb(a - lsb(a)) : a);
}

int main() {
    treenode* root = NULL;
    int vals[] = {56, 30, 61, 39, 47, 35, 75, 13, 21, 64, 26, 73, 18};
    int vals_size = sizeof(vals) / sizeof(int), i, num_size;
    
    for (i = 0; i < vals_size; i++) 
        root = insert(root, vals[i]);

    num_size = msb(vals_size) << 2;
    int num[num_size];
    for(i = 1; i <= num_size; i++) 
        num[i] = 0;
    fill_array(num, root, 1);
    
    printf("Post-order output: ");
    post_order(root);

    printf("\nArray num values: ");
    for(i = 1; i <= num_size; i++) 
        if(num[i]) printf("%d ", num[i]);
    printf("\n");
    
    return 0;
}