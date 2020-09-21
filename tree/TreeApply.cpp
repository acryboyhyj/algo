#include "Heap.h"
#include "TestToggle.h"
#include <queue>
#include <vector>
#include <functional>
#include "HeapSort.h"

#ifdef TREE_TEST
void print(std::vector<int> &r)
{
    for (const auto &c : r)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

struct Node
{

    Node(int _value) : value(_value), left(nullptr), right(nullptr)
    {
        // std::cout << "new: " << value << std::endl;
    }
    ~Node()
    {
        // std::cout << "~new: " << value << std::endl;
    }
    int value;
    Node *left;
    Node *right;
};
using pnode = Node *;
void desdroyTreeInternal(pnode tree)
{
    if (tree != nullptr)
    {
        desdroyTreeInternal(tree->left);
        tree->left = nullptr;
        desdroyTreeInternal(tree->right);
        tree->right = nullptr;
        delete tree;
        tree = nullptr;
    }
}
void inverTreeInternal(pnode tree);
void inverTree(pnode root)
{
    if (root == nullptr)
    {
        return;
    }

    inverTreeInternal(root);
}

void inverTreeInternal(pnode tree)
{
    if (tree == nullptr)
    {
        return;
    }
    pnode temp = tree->left;
    tree->left = tree->right;
    tree->right = temp;

    inverTreeInternal(tree->left);
    inverTreeInternal(tree->right);
}

pnode createCompleteBinarytree(std::vector<int> &data)
{
    if (data.size() <= 0)
    {
        return nullptr;
    }
    std::queue<pnode> q;
    size_t i = 0;
    pnode root = new Node(data[i++]);
    q.push(root);
    pnode temp;
    while (!q.empty() && i < data.size())
    {
        temp = q.front();
        q.pop();
        if (i < data.size())
        {
            temp->left = new Node(data[i++]);
            q.push(temp->left);
        }
        if (i < data.size())
        {
            temp->right = new Node(data[i++]);
            q.push(temp->right);
        }
    }

    return root;
}
void print(std::string &buffer, pnode tree, std::string prefix, std::string childrenPrefix)
{

    if (tree == nullptr)
    {
        return;
    }
    buffer += prefix;
    buffer += std::to_string(tree->value);
    buffer += '\n';

    if (tree->left != nullptr)
    {
        print(buffer, tree->left, childrenPrefix + "├──L ", childrenPrefix + "│    ");
    }
    if (tree->right != nullptr)
    {
        print(buffer, tree->right, childrenPrefix + "├──R ", childrenPrefix + "│    ");
    }
}
std::string toString(pnode root)
{
    std::string result;
    print(result, root, "", "");
    return result;
}

void invertTreeTest()
{
    std::vector<int> v{4, 2, 7, 1, 3, 6, 9};
    pnode root = createCompleteBinarytree(v);
    std::cout
        << toString(root) << std::endl;
    inverTree(root);
    std::cout << toString(root) << std::endl;

    std::vector<int> v1{4, 2, 7, 1, 3, 6};
    pnode tree1 = createCompleteBinarytree(v1);
    std::cout
        << toString(tree1) << std::endl;
    inverTree(tree1);
    std::cout << toString(tree1) << std::endl;
    desdroyTreeInternal(tree1);
}
bool validateBSTInternal(pnode tree);
bool validateBST(pnode root)
{
    if (root == nullptr)
        return false;

    validateBSTInternal(root);
}
bool validateBSTInternal(pnode tree)
{
    bool flag = true;
    if (tree->left)
    {
        flag = validateBSTInternal(tree->left);
        if (!flag)
        {
            return false;
        }

        flag = tree->value > tree->left->value ? true : false;
        if (!flag)
        {
            return false;
        }
    }
    if (tree->right)
    {

        flag = validateBSTInternal(tree->right);
        if (!flag)
        {
            return false;
        }

        flag = tree->value < tree->right->value ? true : false;
        if (!flag)
        {
            return false;
        }
    }

    return flag;
}
void validateBSTtest()
{
    std::vector<int> v{3, 1, 5};
    pnode root = createCompleteBinarytree(v);
    std::cout
        << toString(root) << std::endl;
    std::cout << "1:" << validateBST(root) << std::endl;

    pnode root1 = new Node(8);
    root1->left = new Node(5);
    root1->right = new Node(10);
    pnode temp = root1->right;
    temp->left = new Node(9);
    temp->right = new Node(13);

    std::cout
        << toString(root1) << std::endl;

    std::cout << "2:" << validateBST(root1) << std::endl;
    desdroyTreeInternal(root);
    desdroyTreeInternal(root1);
}

int main()
{
    validateBSTtest();
    return 0;
}
#endif