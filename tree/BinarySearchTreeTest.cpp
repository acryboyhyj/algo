#include "BinarySearchTree.h"
#include "TestToggle.h"
#ifdef BST_TEST
void nodeintTest()
{
    BinarySearchTree<int> tree;
    tree.setToStringFunc([](int &a) -> std::string {
        return std::to_string(a);
    });
    std::vector<int> v{20, 10, 5, 15, 13, 12, 14, 16, 30, 25, 23, 26};

    for (const auto c : v)
    {
        tree.insert(c);
    }

    std::cout << tree.toString() << std::endl;
    std::cout << "`````````````` del5` levelnode```````````````````````" << std::endl;
    tree.del(5);
    std::cout << tree.toString() << std::endl;
    std::cout << "`````````````````insert5`````````````````````" << std::endl;

    tree.insert(5);
    std::cout << tree.toString() << std::endl;
    std::cout << "```````````````````del 15``two chilad node`````````````````" << std::endl;

    tree.del(15);
    std::cout << tree.toString() << std::endl;
    std::cout << "```````````````````insert15```````````````````" << std::endl;
    tree.insert(15);

    std::cout << "```````````````````delete 30 one chaild node```````````````````" << std::endl;
    tree.del(30);
}

struct Obj
{
    Obj(int _key, int _value) : key(_key), value(_value)
    {
    }

    ~Obj() {}

    bool operator<(Obj &rhs)
    {
        return this->key < rhs.key;
    }
    bool operator==(Obj &rhs)
    {
        return this->key == rhs.key;
    }

    friend std::ostream &operator<<(std::ostream &output,
                                    const Obj &D)
    {
        output << "k:" << D.key << " v:" << D.value;
        return output;
    }

    int key;
    int value;
};
std::string toString(Obj &o)
{
    std::string result;
    result += std::to_string(o.key);
    result += "-" + std::to_string(o.value);
    return result;
}
void ObjTest()
{
    BinarySearchTree<Obj> tree;
    //用到打印树的字符串需要提供 toString()
    tree.setToStringFunc(toString);
    std::vector<Obj> v{{20, 1}, {10, 1}, {5, 1}, {15, 1}, {13, 1}, {12, 1}, {14, 1}, {16, 1}, {30, 1}, {25, 1}, {23, 1}, {26, 1}};

    for (const auto c : v)
    {
        tree.insert(c);
    }

    std::cout << tree.toString() << std::endl;
    std::cout << "`````````````` del5` levelnode```````````````````````" << std::endl;
    tree.del(Obj(5, 1));
    std::cout << tree.toString() << std::endl;
    std::cout << "`````````````````insert5`````````````````````" << std::endl;

    tree.insert(Obj(5, 1));
    std::cout << tree.toString() << std::endl;
    std::cout << "```````````````````del 15``two chilad node`````````````````" << std::endl;

    tree.del(Obj(15, 1));
    std::cout << tree.toString() << std::endl;
    std::cout << "```````````````````insert15```````````````````" << std::endl;
    tree.insert(Obj(15, 1));

    std::cout << "```````````````````delete 30 one chaild node```````````````````" << std::endl;
    tree.del(Obj(30, 1));
}

void orderTest()
{
    BinarySearchTree<int> tree;
    tree.setToStringFunc([](int &a) -> std::string {
        return std::to_string(a);
    });
    std::vector<int> v{20, 10, 5, 15, 13, 12, 14, 16, 30, 25, 23, 26};

    for (const auto c : v)
    {
        tree.insert(c);
    }
    std::cout << tree.toString() << std::endl;
    std::cout << "prev "
              << " ";
    tree.preorder([](int &e) {
        std::cout << e << " ";
    });
    std::cout << std::endl;
    std::cout << "mid "
              << " ";
    tree.midderOrder([](int &e) {
        std::cout << e << " ";
    });

    std::cout << std::endl;
    std::cout << "behind "
              << " ";
    tree.behindOrder([](int &e) {
        std::cout << e << " ";
    });

    std::cout << std::endl;
    std::cout << "level "
              << " ";
    tree.levelOrder([](int &e) {
        std::cout << e << " ";
    });
    std::cout << std::endl;
    Node<int> *p = tree.getPrev(13);
    std::cout << "13 prev:" << p->value << std::endl;

    p = tree.getPrev(20);
    assert(p == nullptr);

    p = tree.getPrev(4);
    assert(p == nullptr);
}
int main()
{
    // nodeintTest();
    // ObjTest();
    orderTest();
    return 0;
}
#endif