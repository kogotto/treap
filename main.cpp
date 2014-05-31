/**
  * Didenko Yakov
  * APO-11
  *
  * module 3
  * task #2_4
  *
  */

#include <iostream>
#include <queue>

using namespace std;


typedef int key_t;
typedef struct {} data_t;


class TNaivBinaryTree {
public:
    TNaivBinaryTree() :
        root(0)
    {}

    ~TNaivBinaryTree() {
        free(root);
    }

    void insert(key_t key, data_t data = data_t()) {
        node_t * node = new node_t(key, data);
        insert(&root, node);
    }

    template<class action_t>
    void inOrderTraverse(const action_t & action) {
        inOrderTraverse(root, action);
    }

    template<class action_t>
    void preOrderTraverse(const action_t & action) {
        preOrderTraverse(root, action);
    }

    template<class action_t>
    void postOrderTraverse(const action_t & action) {
        postOrderTraverse(root, action);
    }

    template<class action_t>
    void levelOrderTraverse(const action_t & action) {
        queue<node_t *> traverseQueue;
        traverseQueue.push(root);
        while (!traverseQueue.empty()) {
            node_t * current = traverseQueue.front();
            traverseQueue.pop();
            if (current == 0) {
                continue;
            }

            action(current->key, current->data);
            traverseQueue.push(current->left);
            traverseQueue.push(current->right);
        }
    }

private:
    struct node_t {
        node_t(key_t key, data_t data) :
            key(key),
            data(data),
            left(0),
            right(0)
        {}

        key_t key;
        data_t data;
        node_t * left;
        node_t * right;
    };

    static void insert(node_t ** root, node_t * node) {
        if (*root == 0) {
            *root = node;
            return;
        }

        if (node->key < (*root)->key) {
            insert(&((*root)->left), node);
        } else {
            insert(&((*root)->right), node);
        }
    }

    template<class action_t>
    static void inOrderTraverse(node_t * node, const action_t & action) {
        if (node == 0) {
            return;
        }

        inOrderTraverse(node->left, action);
        action(node->key, node->data);
        inOrderTraverse(node->right, action);
    }

    template<class action_t>
    static void preOrderTraverse(node_t * node, const action_t & action) {
        if (node == 0) {
            return;
        }

        action(node->key, node->data);
        preOrderTraverse(node->left, action);
        preOrderTraverse(node->right, action);
    }

    template<class action_t>
    static void postOrderTraverse(node_t * node, const action_t & action) {
        if (node == 0) {
            return;
        }

        postOrderTraverse(node->left, action);
        postOrderTraverse(node->right, action);
        action(node->key, node->data);
    }

    static void free(node_t * node) {
        if (node == 0) {
            return;
        }

        free(node->left);
        free(node->right);

        delete node;
    }

    node_t * root;
};


void printNode(key_t key, data_t) {
    cout << key << " ";
}

int main()
{
    TNaivBinaryTree naiveTree;

    size_t size = 0;
    cin >> size;
    for (size_t i = 0; i < size; ++i) {
        key_t key;
        cin >> key;
        naiveTree.insert(key);
    }

    naiveTree.levelOrderTraverse(printNode);
    return 0;
}

