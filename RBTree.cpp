#include <stdio.h>

class TreeNode{
    public:
        int data; // valor do nó
        bool color; // true == preto, false == vermelho
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : data(val), color(false), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RBTree{
    public:
        TreeNode* root;
        TreeNode* TNULL;
        
        RBTree(){
            TNULL = new TreeNode(0);
            TNULL->color = true; // preto
            TNULL->left = nullptr;
            TNULL->right = nullptr;
            
            root = TNULL;
        }
        
        void inOrderTraversal(){
            inOrderRecursive(this->root);
        }
        
        
        
    private:
        void inOrderRecursive(TreeNode* node){
            if (node != TNULL){
                inOrderRecursive(node->left);
                printf("%d(%s) ", node->data, node->color ? "P" : "V");
                inOrderRecursive(node->right);
            }
        }
};

int main(){
    return 0;
}
