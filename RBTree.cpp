#include <iostream>
#include <cstdio>

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
    TreeNode* NIL;

    bool sucessorReplace = true; // true para sucessor, false para predecessor

    RBTree() {
        NIL = new TreeNode(-1);
        NIL->color = BLACK;
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;
        root = NIL;
    }

    TreeNode* findNode(int key) {
        TreeNode* current = root;
        while (current != NIL && key != current->data) {
            if (key < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return current;
    }

    TreeNode* sucessor(TreeNode* node) {
        if (node->right != NIL) {
            node = node->right;
            while (node->left != NIL) {
                node = node->left;
            }
            return node;
        }
        TreeNode* ancestor = node->parent;
        while (ancestor != NIL && node == ancestor->right) {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }


    TreeNode* predecessor(TreeNode* node) {
        if (node->left != NIL) {
            node = node->left;
            while (node->right != NIL) {
                node = node->right;
            }
            return node;
        }
        TreeNode* ancestor = node->parent;
        while (ancestor != NIL && node == ancestor->left) {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }

    void transplant(TreeNode* u, TreeNode* v) {
        if (u->parent == NIL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != NIL) v->parent = u->parent;
    }

    void deleteNode(int key) {
        TreeNode* targetNode = findNode(key);
        if (targetNode == NIL) {
            cout << "Valor " << key << " não encontrado na árvore." << endl;
            return;
        }

        TreeNode* replacementNode;
        TreeNode* movedNode = targetNode;
        bool originalColor = movedNode->color;

        if (targetNode->left == NIL) {
            replacementNode = targetNode->right;
            transplant(targetNode, targetNode->right);
        } else if (targetNode->right == NIL) {
            replacementNode = targetNode->left;
            transplant(targetNode, targetNode->left);
        } else {
            sucessorReplace ? movedNode = sucessor(targetNode->right) : movedNode = predecessor(targetNode->left);
            originalColor = movedNode->color;
            replacementNode = movedNode->right;

            if (movedNode->parent == targetNode) {
                if (replacementNode != NIL) replacementNode->parent = movedNode;
            } else {
                transplant(movedNode, movedNode->right);
                movedNode->right = targetNode->right;
                if (movedNode->right != NIL) movedNode->right->parent = movedNode;
            }

            transplant(targetNode, movedNode);
            movedNode->left = targetNode->left;
            if (movedNode->left != NIL) movedNode->left->parent = movedNode;
            movedNode->color = targetNode->color;
        }

        // Verificar se o nó removido era a raiz
        if (targetNode == root) {
            root = replacementNode;
        }

        delete targetNode;

        // Se a cor original do nó removido era preto, precisamos corrigir a árvore
        if (originalColor == BLACK) {
            fixDelete(replacementNode);
        }

        // Garantir que a raiz seja sempre preta
        if (root != NIL) {
            root->color = BLACK;
        }

        cout << "Remoção do valor " << key << " concluída." << endl;
        preOrderTraversal();
    }

    void fixDelete(TreeNode* currentNode) {
        TreeNode* sibling;
        while (currentNode != root && currentNode->color == BLACK) {
            if (currentNode == currentNode->parent->left) {
                sibling = currentNode->parent->right;

                if (sibling->color == RED) {
                    switchColor(sibling, BLACK);
                    switchColor(currentNode->parent, RED);
                    leftRotate(currentNode->parent);
                    sibling = currentNode->parent->right;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    switchColor(sibling, RED);
                    currentNode = currentNode->parent;
                } else {
                    if (sibling->right->color == BLACK) {
                        switchColor(sibling->left, BLACK);
                        switchColor(sibling, RED);
                        rightRotate(sibling);
                        sibling = currentNode->parent->right;
                    }

                    switchColor(sibling, currentNode->parent->color);
                    switchColor(currentNode->parent, BLACK);
                    switchColor(sibling->right, BLACK);
                    leftRotate(currentNode->parent);
                    currentNode = root;
                }
            } else {
                sibling = currentNode->parent->left;
                if (sibling->color == RED) {
                    switchColor(sibling, BLACK);
                    switchColor(currentNode->parent, RED);
                    rightRotate(currentNode->parent);
                    sibling = currentNode->parent->left;
                }

                if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    switchColor(sibling, RED);
                    currentNode = currentNode->parent;
                } else {
                    if (sibling->left->color == BLACK) {
                        switchColor(sibling->right, BLACK);
                        switchColor(sibling, RED);
                        leftRotate(sibling);
                        sibling = currentNode->parent->left;
                    }

                    switchColor(sibling, currentNode->parent->color);
                    switchColor(currentNode->parent, BLACK);
                    switchColor(sibling->left, BLACK);
                    rightRotate(currentNode->parent);
                    currentNode = root;
                }
            }
        }
        currentNode->color = BLACK;  // A raiz deve sempre ser preta
    }



    void insert(int key) {
        TreeNode* newNode = new TreeNode(key);
        newNode->parent = NIL;
        newNode->data = key;
        newNode->left = NIL;
        newNode->right = NIL;
        newNode->color = RED;

        TreeNode* parentCandidate = NIL;
        TreeNode* currentNode = this->root;

        while (currentNode != NIL) {
            parentCandidate = currentNode;
            if (newNode->data < currentNode->data) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }

        newNode->parent = parentCandidate;
        if (parentCandidate == NIL) {
            root = newNode;
        } else if (newNode->data < parentCandidate->data) {
            parentCandidate->left = newNode;
        } else {
            parentCandidate->right = newNode;
        }

        if (newNode->parent == NIL) {
            newNode->color = BLACK;
        } else {
            fixInsert(newNode);
        }

        preOrderTraversal();
    }

    void searchTree(int key) {
        if (this->root == NIL) {
            cout << "A árvore está vazia." << endl;
            return;
        }

        cout << "Início da busca para o valor " << key << " na raiz " << this->root->data << endl;
        searchTreeHelper(this->root, key);
    }

    void leftRotate(TreeNode* nodeToRotate) {
        if (nodeToRotate == NIL || nodeToRotate->right == NIL) {
            return;
        }

        TreeNode* pivot = nodeToRotate->right;
        nodeToRotate->right = pivot->left;
        if (pivot->left != NIL) {
            pivot->left->parent = nodeToRotate;
        }
        pivot->parent = nodeToRotate->parent;
        if (nodeToRotate->parent == NIL) {
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
        if (nodeToRotate == NIL || nodeToRotate->left == NIL) {
            return;
        }

        TreeNode* pivot = nodeToRotate->left;
        nodeToRotate->left = pivot->right;
        if (pivot->right != NIL) {
            pivot->right->parent = nodeToRotate;
        }
        pivot->parent = nodeToRotate->parent;
        if (nodeToRotate->parent == NIL) {
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
        if (root == NIL) {
            cout << "Árvore vazia.";
        } else {
            preOrderRecursive(this->root);
        }
        cout << endl;
    }

    void switchColor(TreeNode* node, bool color) {
        if (node == NIL) return;
        node->color = color;
    }

    void fixInsert(TreeNode* nodeToFix) {
        TreeNode* uncle;
        while (nodeToFix->parent->color == RED) {
            TreeNode* grandparent = nodeToFix->parent->parent;

            if (nodeToFix->parent == grandparent->right) {
                uncle = grandparent->left;
                if (uncle->color == RED) {
                    switchColor(uncle, BLACK);
                    switchColor(nodeToFix->parent, BLACK);
                    switchColor(grandparent, RED);
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
                    switchColor(uncle, BLACK);
                    switchColor(nodeToFix->parent, BLACK);
                    switchColor(grandparent, RED);
                    nodeToFix = grandparent;
                } else {
                    if (nodeToFix == nodeToFix->parent->right) {
                        nodeToFix = nodeToFix->parent;
                        leftRotate(nodeToFix);
                    }
                    switchColor(nodeToFix->parent, BLACK);
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            }
            if (nodeToFix == root) break;
        }
        root->color = BLACK;
    }

    void preOrderRecursive(TreeNode* node) {
        if (node != NIL) {
            printf("%s%d(%s)%s ", 
                node->color ? BLACK_COLOR : RED_COLOR, 
                node->data, 
                node->color ? "P" : "V", 
                RESET_COLOR);
            preOrderRecursive(node->left);
            preOrderRecursive(node->right);
        }
    }

    void searchTreeHelper(TreeNode* node, int key) {
        if (node == NIL) {
            cout << "Nó " << key << " não encontrado na árvore." << endl;
            return;
        }
        if (key == node->data) {
            cout << "Nó " << key << " encontrado na árvore." << endl;
            return;
        }
        if (key < node->data) {
            cout << "Procurando à esquerda do nó " << node->data << endl;
            searchTreeHelper(node->left, key);
        } else {
            cout << "Procurando à direita do nó " << node->data << endl;
            searchTreeHelper(node->right, key);
        }
    }
};

int main() {
    RBTree tree;
    tree.sucessorReplace = true; // true para usar sucessor, false para predecessor
    int value;

    while (true) {
        cout << "\nMenu :\n1 - Inserir\n2 - Buscar\n3 - Remover\n0 - Sair\nOpção: ";
        int choice;
        if (!(cin >> choice)) break;

        switch (choice) {
        case 1:
            cout << "Valor para inserir: ";
            cin >> value;
            if (value >= 0) tree.insert(value);
            else cout << "Apenas valores positivos." << endl;
            break;
        case 2:
            cout << "Valor para buscar: ";
            cin >> value;
            tree.searchTree(value);
            break;
        case 3:
            cout << "Valor para remover: ";
            cin >> value;
            tree.deleteNode(value);
            break;
        case 0:
            return 0;
        default:
            cout << "Opção inválida." << endl;
        }
    }
    return 0;
}
