#include "TestToggle.h"
#ifdef Trie_Tree
#include "TrieTree.h"

int main()
{
    TrieTree tree;
    tree.insert("apple");
    tree.insert("appabc");
    tree.insert("abc");
    tree.print();

    std::cout << tree.search("") << std::endl;
    std::cout << tree.search("apple") << std::endl;
    std::cout << tree.search("ab") << std::endl;
    std::cout << tree.search("abc") << std::endl;
    std::cout << tree.search("app") << std::endl;
  std::cout << "````````````````````````````````````" << std::endl;
    std::cout << tree.startWith("") << std::endl;
    std::cout << tree.startWith("apple") << std::endl;
    std::cout << tree.startWith("ab") << std::endl;
    std::cout << tree.startWith("abc") << std::endl;
    std::cout << tree.startWith("app") << std::endl;
    std::cout << tree.startWith("pp") << std::endl;
    std::cout << tree.startWith("apd") << std::endl;
    return 0;
}

#endif