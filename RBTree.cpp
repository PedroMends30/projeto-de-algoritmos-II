#include <iostream>

#define RED false
#define BLACK true

#define RED_COLOR "\033[31m"
#define BLACK_COLOR "\033[30m"
#define RESET_COLOR "\033[0m"

using namespace std;

class TreeNode {
public:
    int data;
    bool color;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RBTree {
public:
    TreeNode* root;
    TreeNode* TNULL;

    RBTree() {
        TNULL = new TreeNode(0);
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void insert(int key) {
        TreeNode* newNode = new TreeNode(key);
        newNode->parent = nullptr;
        newNode->data = key;
        newNode->left = TNULL;
        newNode->right = TNULL;
        newNode->color = RED;

        TreeNode* parentCandidate = nullptr;
        TreeNode* currentNode = this->root;

        while (currentNode != TNULL) {
            parentCandidate = currentNode;
            if (newNode->data < currentNode->data) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }

        newNode->parent = parentCandidate;
        if (parentCandidate == nullptr) {
            root = newNode;
        } else if (newNode->data < parentCandidate->data) {
            parentCandidate->left = newNode;
        } else {
            parentCandidate->right = newNode;
        }

        if (newNode->parent == nullptr) {
            newNode->color = BLACK;
        } else if (newNode->parent->parent != nullptr) {
            balanceTree(newNode);
        }

        // Impressão após a modificação completa
        preOrderTraversal();
    }

    void leftRotate(TreeNode* nodeToRotate) {
        cout<< "\nRotação à esquerda do nó " << nodeToRotate->data << endl;
        TreeNode* pivot = nodeToRotate->right;
        nodeToRotate->right = pivot->left;
        if (pivot->left != TNULL) {
            pivot->left->parent = nodeToRotate;
        }
        pivot->parent = nodeToRotate->parent;
        if (nodeToRotate->parent == nullptr) {
            this->root = pivot;
        } else if (nodeToRotate == nodeToRotate->parent->left) {
            nodeToRotate->parent->left = pivot;
        } else {
            nodeToRotate->parent->right = pivot;
        }
        pivot->left = nodeToRotate;
        nodeToRotate->parent = pivot;
    }

    void rightRotate(TreeNode* nodeToRotate) {
        cout<< "\nRotação à direita do nó " << nodeToRotate->data << endl;
        TreeNode* pivot = nodeToRotate->left;
        nodeToRotate->left = pivot->right;
        if (pivot->right != TNULL) {
            pivot->right->parent = nodeToRotate;
        }
        pivot->parent = nodeToRotate->parent;
        if (nodeToRotate->parent == nullptr) {
            this->root = pivot;
        } else if (nodeToRotate == nodeToRotate->parent->right) {
            nodeToRotate->parent->right = pivot;
        } else {
            nodeToRotate->parent->left = pivot;
        }
        pivot->right = nodeToRotate;
        nodeToRotate->parent = pivot;
    }

    void preOrderTraversal() {
        preOrderRecursive(this->root);
        cout << endl;
    }

private:
    void balanceTree(TreeNode* nodeToFix) {
        TreeNode* uncle;
        while (nodeToFix->parent->color == RED) {
            TreeNode* grandparent = nodeToFix->parent->parent;

            if (nodeToFix->parent == grandparent->right) {
                uncle = grandparent->left; 
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    nodeToFix->parent->color = BLACK;
                    grandparent->color = RED;
                    nodeToFix = grandparent;
                } else {
                    if (nodeToFix == nodeToFix->parent->left) {
                        nodeToFix = nodeToFix->parent;
                        rightRotate(nodeToFix);
                    }
                    nodeToFix->parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            } else {
                uncle = grandparent->right;
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    nodeToFix->parent->color = BLACK;
                    grandparent->color = RED;
                    nodeToFix = grandparent;
                } else {
                    if (nodeToFix == nodeToFix->parent->right) {
                        nodeToFix = nodeToFix->parent;
                        leftRotate(nodeToFix);
                    }
                    nodeToFix->parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            }
            if (nodeToFix == root) break;
        }
        root->color = BLACK;
    }

    void preOrderRecursive(TreeNode* node) {
        if (node != TNULL) {
            printf("%s%d(%s)%s ", 
                node->color ? BLACK_COLOR : RED_COLOR, 
                node->data, 
                node->color ? "P" : "V", 
                RESET_COLOR);
            preOrderRecursive(node->left);
            preOrderRecursive(node->right);
        }
    }
};

int main() {
    RBTree tree;
    int value;

    while (true) {
        cout << "Digite um valor para inserir (ou -1 para sair): ";
        if (!(cin >> value)) break;
        
        if (value == -1) {
            break;
        } else if (value >= 0) {
            tree.insert(value);
        } else {
            cout << "Valor inválido." << endl;
        }
    }

    return 0;
}
