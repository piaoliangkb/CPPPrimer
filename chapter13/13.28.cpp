#include <string>
#include <iostream>

class TreeNode {
public:
    TreeNode(const std::string& s = std::string()) : value(s), count(1), left(nullptr), right(nullptr), use(new size_t(1)) {}

    TreeNode(const TreeNode& rhs)
        : value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right), use(rhs.use)
        {
            ++*use;
        }
    
    TreeNode& operator=(const TreeNode& rhs) {
        ++*rhs.use;
        if(--*use == 0) {
            if (left) {
                delete left;
                left = nullptr;
            }
            if (right) {
                delete right;
                right = nullptr;
            }
            delete use;
            use = nullptr;
        }
        use = rhs.use;
        value = rhs.value;
        left = rhs.left;
        right = rhs.right;
        return *this;
    }

    ~TreeNode() {
        if (--*use == 0) {
            if (left) {
                delete left;
                left = nullptr;
            }
            if (right) {
                delete right;
                right = nullptr;
            }
            delete use;
            use = nullptr;
        }
    }

private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;

    size_t *use;
};

class BinStrTree {
public:
    BinStrTree() : root(new TreeNode("root")) {}

    ~BinStrTree() {
        delete root;
    }

    BinStrTree(const BinStrTree& rhs): root(new TreeNode(*rhs.root)) {}

    BinStrTree& operator=(const BinStrTree& rhs) {
        TreeNode* new_root = new TreeNode(*rhs.root);
        delete root;
        root = new_root;
        return *this;
    }

private:
    TreeNode *root;
};

int main()
{
    BinStrTree bst1, bst2;
    bst2 = bst1;
    BinStrTree bst3 = bst1;
}