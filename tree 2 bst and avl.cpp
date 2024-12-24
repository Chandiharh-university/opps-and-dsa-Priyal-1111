#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Tree Node Structure
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Inorder Traversal to collect values
void collectValues(TreeNode* root, vector<int>& values) {
    if (root == nullptr) return;
    collectValues(root->left, values);
    values.push_back(root->data);
    collectValues(root->right, values);
}

// Build BST from sorted values
TreeNode* buildBST(vector<int>& values, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    TreeNode* root = new TreeNode(values[mid]);
    root->left = buildBST(values, start, mid - 1);
    root->right = buildBST(values, mid + 1, end);

    return root;
}

// Get height of the tree
int getHeight(TreeNode* root) {
    if (root == nullptr) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// Rotate Right for AVL
TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Rotate Left for AVL
TreeNode* rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// Get Balance Factor for AVL
int getBalanceFactor(TreeNode* root) {
    if (root == nullptr) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

// Insert into AVL Tree
TreeNode* insertAVL(TreeNode* root, int data) {
    if (root == nullptr) return new TreeNode(data);

    if (data < root->data)
        root->left = insertAVL(root->left, data);
    else if (data > root->data)
        root->right = insertAVL(root->right, data);
    else
        return root;

    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && data < root->left->data)
        return rotateRight(root);

    // Right Right Case
    if (balance < -1 && data > root->right->data)
        return rotateLeft(root);

    // Left Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Convert to AVL Tree
TreeNode* convertToAVL(TreeNode* bstRoot) {
    vector<int> values;
    collectValues(bstRoot, values);
    TreeNode* avlRoot = nullptr;
    for (int val : values) {
        avlRoot = insertAVL(avlRoot, val);
    }
    return avlRoot;
}

// Display Tree (Inorder Traversal)
void displayTree(TreeNode* root) {
    if (root == nullptr) return;
    displayTree(root->left);
    cout << root->data << " ";
    displayTree(root->right);
}

int main() {
    // Manually creating a simple tree
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(20);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(30);
    root->left->right = new TreeNode(15);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(7);

    cout << "Original Tree (Inorder): ";
    displayTree(root);
    cout << endl;

    // Collect values and build BST
    vector<int> values;
    collectValues(root, values);
    sort(values.begin(), values.end());
    TreeNode* bstRoot = buildBST(values, 0, values.size() - 1);

    cout << "Binary Search Tree (Inorder): ";
    displayTree(bstRoot);
    cout << endl;

    // Convert BST to AVL Tree
    TreeNode* avlRoot = convertToAVL(bstRoot);

    cout << "AVL Tree (Inorder): ";
    displayTree(avlRoot);
    cout << endl;

    return 0;
}
