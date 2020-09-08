#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__
#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <functional>
#include <assert.h>
#include <queue>
template <class T>
struct Node
{
    Node(T _value) : value(_value), left(nullptr), right(nullptr)
    {
        // std::cout << "new: " << value << std::endl;
    }
    ~Node()
    {
        // std::cout << "~new: " << value << std::endl;
    }
    T value;
    Node<T> *left;
    Node<T> *right;
};

template <class T>
int deepth(Node<T> *tree)
{
    if (tree == nullptr)
    {
        return 0;
    }
    else
    {
        return std::max(tree->left, tree->right) + 1;
    }
}

enum class Location
{
    Left = 0,
    Right = 1
};

/* 非默认类型 必须重载< 和 == 符号 以及to_string回调 有深拷贝需要有复制构造*/
template <class T>
class BinarySearchTree
{
public:
    using pnode = Node<T> *;

    BinarySearchTree() : root(nullptr), _toStringFunc(nullptr)
    {
    }

    ~BinarySearchTree()
    {
        desdroyTreeInternal(root);
    }

    void setToStringFunc(std::function<std::string(T &a)> toStringFunc)
    {
        _toStringFunc = std::move(toStringFunc);
    }

    void insert(T data)
    {
        insert(root, data);
    }

    Node<T> *find(T data)
    {
        select(root, data);
    }

    void del(T data);

    std::string toString()
    {
        std::string result;
        print(result, root, "", "");
        return result;
    }

    void preorder(std::function<void(T &)> doFunc)
    {
        preoderInternal(root, doFunc);
    }

    void midderOrder(std::function<void(T &)> doFunc)
    {
        midderOrderInternal(root, doFunc);
    }

    void behindOrder(std::function<void(T &)> doFunc)
    {
        behindOrderInternal(root, doFunc);
    }
    void levelOrder(std::function<void(T &)> doFunc);

    pnode getPrev(T data);

    pnode getbehind(T data);

private:
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

    void preoderInternal(pnode tree, std::function<void(T &)> &doFunc)
    {
        if (tree == nullptr)
        {
            return;
        }

        doFunc(tree->value);
        preoderInternal(tree->left, doFunc);
        preoderInternal(tree->right, doFunc);
    }

    void midderOrderInternal(pnode tree, std::function<void(T &)> &doFunc)
    {
        if (tree == nullptr)
        {
            return;
        }
        midderOrderInternal(tree->left, doFunc);
        doFunc(tree->value);
        midderOrderInternal(tree->right, doFunc);
    }

    void behindOrderInternal(pnode tree, std::function<void(T &)> &doFunc)
    {
        if (tree == nullptr)
        {
            return;
        }
        behindOrderInternal(tree->left, doFunc);
        behindOrderInternal(tree->right, doFunc);
        doFunc(tree->value);
    }

private:
    void print(std::string &buffer, Node<T> *tree, std::string prefix, std::string childrenPrefix)
    {
        assert(_toStringFunc != nullptr);
        if (tree == nullptr)
        {
            return;
        }
        buffer += prefix;
        buffer += _toStringFunc(tree->value);
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

private:
    void insert(pnode &tree, T &data)
    {
        if (tree == nullptr)
        {
            tree = new Node<T>(data);
            return;
        }

        if (data < tree->value)
            insert(tree->left, data);

        else
            insert(tree->right, data);
    }

    pnode select(pnode &tree, T &data)
    {
        if (tree == nullptr)
        {
            return nullptr;
        }
        pnode p = tree;
        while (p != nullptr)
        {
            if (data > p->value)
                p = p->right;
            else if (data < p->value)
                p = p->left;
            else
                return p;
        }
    }

    void delElement(pnode &curnode, pnode &parent, Location &location);

private:
    Node<T> *root;
    std::function<std::string(T &a)> _toStringFunc;
};

template <class T>
void BinarySearchTree<T>::del(T data)
{
    pnode parent = root;
    pnode curnode = root;
    Location location = Location::Left; //当前节点在父节点的位置
    while (curnode != nullptr)
    {
        if (curnode->value == data)
        {
            delElement(curnode, parent, location);
            return;
        }
        else if (data < curnode->value)
        {
            parent = curnode;
            location = Location::Left;
            curnode = curnode->left;
        }
        else
        {
            parent = curnode;
            location = Location::Right;
            curnode = curnode->right;
        }
    }
}

template <class T>
void BinarySearchTree<T>::levelOrder(std::function<void(T &)> doFunc)
{
    std::queue<Node<T> *> q;
    if (root == nullptr)
    {
        return;
    }

    q.push(root);
    while (!q.empty())
    {
        pnode n = q.front();
        q.pop();
        doFunc(n->value);
        if (n->left != nullptr)
        {
            q.push(n->left);
        }
        if (n->right != nullptr)
        {
            q.push(n->right);
        }
    }
}

template <class T>
typename BinarySearchTree<T>::pnode BinarySearchTree<T>::getPrev(T data)
{
    pnode parent = nullptr;
    pnode curnode = root;
    while (curnode != nullptr)
    {
        if (curnode->value == data)
        {
            return parent;
        }
        else if (data < curnode->value)
        {
            parent = curnode;
            curnode = curnode->left;
        }
        else
        {
            parent = curnode;
            curnode = curnode->right;
        }
    }
    return nullptr;
}

template <class T>
typename BinarySearchTree<T>::pnode BinarySearchTree<T>::getbehind(T data)
{
    pnode parent = nullptr;
    pnode curnode = root;
    while (curnode != nullptr)
    {
        if (curnode->value == data)
        {
            if (curnode->left)
            {
                return curnode->left;
            }
            if (curnode->right)
            {
                return curnode->right;
            }
            return nullptr;
        }
        else if (data < curnode->value)
        {
            curnode = curnode->left;
        }
        else
        {
            curnode = curnode->right;
        }
    }
    return nullptr;
}

template <class T>
void BinarySearchTree<T>::delElement(typename BinarySearchTree<T>::pnode &curnode, typename BinarySearchTree<T>::pnode &parent, Location &location)
{
    //叶子节点
    if (curnode->left == nullptr && curnode->right == nullptr)
    {
        if (location == Location::Left)
        {
            delete curnode;
            parent->left = nullptr;
        }
        else
        {
            delete curnode;
            parent->right = nullptr;
        }

        return;
    }

    //当前节点只有左儿子，父节点直接接上
    if (curnode->left != nullptr && curnode->right == nullptr)
    {

        if (location == Location::Left)
        {
            parent->left = curnode->left;
            delete curnode;
        }
        else
        {
            parent->right = curnode->left;
            delete curnode;
        }

        return;
    }

    //当前节点只有右儿子，父节点直接接上右儿子
    if (curnode->left == nullptr && curnode->right != nullptr)
    {
        if (location == Location::Left)
        {
            parent->left = curnode->right;
            delete curnode;
        }
        else
        {
            parent->right = curnode->right;
            delete curnode;
        }
        return;
    }

    //当前节点既有左儿子也有右儿子，要找左儿子最靠右边的或者右儿子最靠左边的和被删除节点替换(只替换值)
    if (curnode->left != nullptr && curnode->right != nullptr)
    {
        typename BinarySearchTree<T>::pnode temp = curnode->left;
        typename BinarySearchTree<T>::pnode tempParent = curnode;
        while (temp->right != nullptr)
        {
            tempParent = temp;
            temp = temp->right;
        }
        std::swap(temp->value, curnode->value);
        tempParent->right = nullptr;
        delete temp;
        return;
    }
}

#endif // __BINARYSEARCHTREE_H__
