#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node* left, * right, * parent;

    Node(int data) : data(data) {
        parent = left = right = nullptr;
        color = RED;
    }
};

class RBTree {
private:
    Node* root;

    void rotateLeft(Node*& pt) {
        Node* pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node*& pt) {
        Node* pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

       
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                   
                    rotateRight(grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

          
            else {
                Node* uncle_pt = grand_parent_pt->left;

                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    void inorderHelper(Node* root) {
        if (root == nullptr) return;

        inorderHelper(root->left);
        cout << root->data << " ";
        inorderHelper(root->right);
    }

public:
    RBTree() : root(nullptr) {}

    void insert(const int& data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixViolation(pt);
    }

    Node* BSTInsert(Node* root, Node* pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    RBTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);

    cout << "Inorder Traversal of Created Tree\n";
    tree.inorder();

    return 0;
}