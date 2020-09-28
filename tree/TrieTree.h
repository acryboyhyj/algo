#ifndef __TRIETREE_H__
#define __TRIETREE_H__
#include <map>
#include <string>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
struct TrieNode;
void printMap(std::map<char, TrieNode *>& m);
struct TrieNode
{
    TrieNode(char _val) : val(_val){

    }

    void put(char key)
    {
       if (links.count(key) > 0)
       {
           return;
       }
       else 
       {
           val = key;
           links[key] = new TrieNode(key);
       }
        
    }

    bool isExsited(char key)
    {
        return links.count(key) > 0;
    }

    TrieNode* nextLink(char key)
    {
        if (links.count(key) > 0)
        {
            return links[key];
        }
        else 
        {
            return nullptr;
        }
     
    }

    std::vector<std::string> printAll()
    {
    
        std::vector<std::string> result;
        for(auto &link:links)
        {
            std::vector<std::string> childstrings = link.second->printAll();
            if (!childstrings.empty())
            {
                for (auto &str : childstrings)
                {
                    std::string cur(1, link.first);
                    cur += str;
                    result.push_back(cur);
                }
            }
            else
            {
                std::string cur(1, link.first);
                result.push_back(cur);
            }
        }


        return result;
    }

    bool isEnd()
    {
        return links.empty();
    }
    char val;
 
    std::map<char, TrieNode *> links;
};
void printMap(std::map<char, TrieNode *> &m)
{
    for(const auto& c:m)
    {
        std::cout << c.first << " ";
    }
    std::cout << endl;
}class TrieTree
{
public:
    TrieTree()
    {
        root = new TrieNode('#');
    }

    ~TrieTree()
    {
        destoryTrieTree(root);
    }

    void insert(std::string s)
    {
        if(s.empty())
            return;

        TrieNode *p = root;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if(p->isExsited(s[i]))
            {
                p = p->nextLink(s[i]);
            }
            else 
            {
                p->put(s[i]);
                p = p->nextLink(s[i]);

            }
        }
        return;
    }

    bool search(std::string s)
    {
        TrieNode *node = searchPrefix(s);
        return node != nullptr && node->isEnd();
    }
    bool startWith(std::string s)
    {
        TrieNode* node = searchPrefix(s);
        return node != nullptr;
    }
    void print()
    {
        std::vector<std::string> result = root->printAll();
        for(const auto& s: result)
        {
            std::cout << s << std::endl;
        }
    }
private:
    TrieNode*  searchPrefix(std::string s)
    {
        if (s.empty())
            return nullptr;

        TrieNode *p = root;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (p == nullptr)
            {
                return nullptr;
            }
            if (p->isExsited(s[i]))
            {
                p = p->nextLink(s[i]);
            }
            else
            {
                return nullptr;
            }
        }
        return p;
       
    }
    void destoryTrieTree(TrieNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        for(auto & link : node->links)
        {
            destoryTrieTree(link.second);
        }

        delete node;
    }
    private: 
    TrieNode *root;
};
#endif // __TRIETREE_H__