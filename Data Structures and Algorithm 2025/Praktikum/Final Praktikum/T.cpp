/**
 *    author:  FrenH
 *    created: 11.06.2025 14:01:53
**/

#include <bits/stdc++.h>
using namespace std;

//Shortcut
#define fp(i, l, r)     for(i = l; i < r; i++)
#define ms(x, y)        memset(x, y, sizeof(x))
#define all(x)          x.begin(), x.end()
#define sc              second
#define fr              first
#define el              '\n'

using dd                = double;
using ll                = long long;
using ull               = unsigned long long;
using pii               = pair<int, int>;
using pll               = pair<ll, ll>;

// Global variabel
const int S = 1e5,
minf = INT_MIN, 
pinf = INT_MAX,
mod = 1e9 + 7;

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

struct AVLNode {
    int data;
    AVLNode *left, *right;
    int height;
};

struct AVL {
private:
    AVLNode *_root;
    unsigned _size;

    AVLNode* _avl_createNode(int value) {
        AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
        newNode->data = value;
        newNode->height =1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    AVLNode* _search(AVLNode *root, int value) {
        while (root != NULL) {
            if (value < root->data)
                root = root->left;
            else if (value > root->data)
                root = root->right;
            else
                return root;
        }
        return root;
    }

    int _getHeight(AVLNode* node){
        if(node==NULL)
            return 0; 
        return node->height;
    }

    int _max(int a,int b){
        return (a > b)? a : b;
    }

    AVLNode* _rightRotate(AVLNode* pivotNode){
        AVLNode* newParrent=pivotNode->left;
        pivotNode->left=newParrent->right;
        newParrent->right=pivotNode;

        pivotNode->height=_max(_getHeight(pivotNode->left),
        _getHeight(pivotNode->right))+1;
        newParrent->height=_max(_getHeight(newParrent->left),
        _getHeight(newParrent->right))+1;
        
        return newParrent;
    }
    
    AVLNode* _leftRotate(AVLNode* pivotNode) {
        AVLNode* newParrent=pivotNode->right;
        pivotNode->right=newParrent->left;
        newParrent->left=pivotNode;

        pivotNode->height=_max(_getHeight(pivotNode->left),
        _getHeight(pivotNode->right))+1;
        newParrent->height=_max(_getHeight(newParrent->left),
        _getHeight(newParrent->right))+1;

        return newParrent;
    }
    
    AVLNode* _leftCaseRotate(AVLNode* node){
        
        cout << "Left Case" << el;
        cout << "PivotNode: " << node->data << el;
        cout << "PivotNode->left: " << node->left->data << el;
        cout << "PivotNode->left->left: " << node->left->left->data << el;

        AVLNode* newnode = _rightRotate(node);

        cout << el << "result:" << el;
        cout << "NewNode: " << newnode->data << el;
        cout << "NewNode->left: " << newnode->left->data << el;
        cout << "NewNode->right: " << newnode->right->data << el;

        return newnode;
    }
    
    AVLNode* _rightCaseRotate(AVLNode* node){

        cout << "Right Case" << el;
        cout << "PivotNode: " << node->data << el;
        cout << "PivotNode->right: " << node->right->data << el;
        cout << "PivotNode->right->right: " << node->right->right->data << el;

        AVLNode* newnode = _leftRotate(node);

        cout << el << "result:" << el;
        cout << "NewNode: " << newnode->data << el;
        cout << "NewNode->left: " << newnode->left->data << el;
        cout << "NewNode->right: " << newnode->right->data << el;

        return newnode;
    }

    AVLNode* _leftRightCaseRotate(AVLNode* node){
        cout << "Left Right Case" << el;
        cout << "PivotNode: " << node->data << el;
        cout << "PivotNode->left: " << node->left->data << el;
        cout << "PivotNode->left->right: " << node->left->right->data << el;

        node->left=_leftRotate(node->left);
        AVLNode* newnode = _rightRotate(node);

        cout << el << "result:" << el;
        cout << "NewNode: " << newnode->data << el;
        cout << "NewNode->left: " << newnode->left->data << el;
        cout << "NewNode->right: " << newnode->right->data << el;

        return newnode;
    }

    AVLNode* _rightLeftCaseRotate(AVLNode* node){
        cout << "Right Left Case" << el;
        cout << "PivotNode: " << node->data << el;
        cout << "PivotNode->right: " << node->right->data << el;
        cout << "PivotNode->right->left: " << node->right->left->data << el;

        node->right=_rightRotate(node->right);
        AVLNode* newnode = _leftRotate(node);

        cout << el << "result:" << el;
        cout << "NewNode: " << newnode->data << el;
        cout << "NewNode->left: " << newnode->left->data << el;
        cout << "NewNode->right: " << newnode->right->data << el;

        return newnode;
    }

    int _getBalanceFactor(AVLNode* node){
        if(node==NULL)
            return 0;
        return _getHeight(node->left)-_getHeight(node->right);
    }

    AVLNode* _insert_AVL(AVLNode* node,int value) {
        
        if(node==NULL)
            return _avl_createNode(value);
        if(value < node->data)
            node->left = _insert_AVL(node->left,value);
        else if(value > node->data)
            node->right = _insert_AVL(node->right,value);
        
        node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

        int balanceFactor=_getBalanceFactor(node);
        
        if(balanceFactor > 1 && value < node->left->data)
            return _leftCaseRotate(node);
        if(balanceFactor > 1 && value > node->left->data)
            return _leftRightCaseRotate(node);
        if(balanceFactor < -1 && value > node->right->data)
            return _rightCaseRotate(node);
        if(balanceFactor < -1 && value < node->right->data)
            return _rightLeftCaseRotate(node);
        
        return node;
    }

    AVLNode* _findMinNode(AVLNode *node) {
        AVLNode *currNode = node;
        while (currNode && currNode->left != NULL)
            currNode = currNode->left;
        return currNode;
    }

    AVLNode* _remove_AVL(AVLNode* node,int value){
        if(node==NULL)
            return node;
        if(value > node->data)
            node->right=_remove_AVL(node->right,value);
        else if(value < node->data)
            node->left=_remove_AVL(node->left,value);
        else{
            AVLNode *temp;
            if((node->left==NULL)||(node->right==NULL)){
                temp=NULL;
                if(node->left==NULL) temp=node->right;  
                else if(node->right==NULL) temp=node->left;
                
                if(temp==NULL){
                    temp=node;
                    node=NULL;
                }
                else
                    *node=*temp;   
                
                free(temp);
            }
            else{
                temp = _findMinNode(node->right);
                node->data=temp->data;
                node->right=_remove_AVL(node->right,temp->data);
            }    
        }

        if(node==NULL) return node;
        
        node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

        int balanceFactor= _getBalanceFactor(node);
        
        if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
            return _leftCaseRotate(node);

        if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
            return _leftRightCaseRotate(node);
    
        if(balanceFactor<-1 && _getBalanceFactor(node->right)<=0) 
            return _rightCaseRotate(node);

        if(balanceFactor<-1 && _getBalanceFactor(node->right)>0) 
            return _rightLeftCaseRotate(node);
        
        return node;
    }

    void _inorder(AVLNode *node) {
        if (node) {
            _inorder(node->left);
            printf("%d ", node->data);
            _inorder(node->right);
        }
    }

public:
    void init() {
        _root = NULL;
        _size = 0U;
    }

    bool isEmpty() {
        return _root == NULL;
    }

    bool find(int value) {
        AVLNode *temp = _search(_root, value);
        if (temp == NULL)
            return false;
        
        if (temp->data == value) return true;
        else return false;
    }

    void insert(int value) {
        if (!find(value)) {
            _root = _insert_AVL(_root, value);
            _size++;
        }
    }

    void remove(int value) {
        if (find(value)) {
            _root = _remove_AVL(_root, value);
            _size--;
        }
    }

    void inorder() {
        this->_inorder(_root);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    AVL avl;
    int n, x;
    avl.init();
    for(cin >> n; n--;) {
        cin >> x;
        avl.insert(x);
    }
    
    return 0;
}