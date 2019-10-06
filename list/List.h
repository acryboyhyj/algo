//
// Created by hyjcrydby on 2019/10/5.
//

#pragma once
#include <iostream>
#include <memory>
#include <vector>
/***************
destanation：一个基础可用的模板带头单链表实现，附带lru实现(有容量)以及尾插法（无最大容量）实现
*********************/
const int DEFAULT_SIZE = 10;
template <typename T>
struct ListNode {
    ListNode() : next(nullptr){};
    ListNode(const T& a) : data(a), next(nullptr){};

    T data;
    ListNode<T>* next;
};

template <typename T>
class List {
    // typedef DlistNode<T> Node;
    // typedef DlistNode<T>* pNode;
    friend void print(const std::string& str, ListNode<T>* head);
    friend bool isPalindromeString(List<int>& list);

public:
    List();
    List(int size);
    ~List(void);

    List(const std::vector<T>& v);

    void insertNodeTail(const T& data);
    void InsertNode(const T& data);
    void insertNodeBegin(const T& data);

    ListNode<T>* findPreNode(const T& data);

    void deleteElemAtEnd();
    void deleteElemOpt(ListNode<T>* pre);
    bool isEmpty();

    void printAll();
    ListNode<T>* findTailNode();

    ListNode<T>* getHead() { return m_head; }

private:
    List(const List&);
    List& operator=(const List&);
    ListNode<T>* m_head;
    int m_capaciy;
    int m_size;
};

template <typename T>
List<T>::List()
    : m_head(new ListNode<T>()), m_capaciy(DEFAULT_SIZE), m_size(0) {}
template <typename T>
List<T>::List(int size)
    : m_head(new ListNode<T>()), m_capaciy(size), m_size(0) {}

template <typename T>
List<T>::~List(void) {}

template <typename T>
List<T>::List(const std::vector<T>& v) {
    ListNode<T>* cur = m_head;
    for (const auto& c : v) {
        cur->next = new ListNode<T>(c);
        cur       = cur->next;
    }
    cur->next = nullptr;
}

/***********************
*function：deleteElemOpt
*destination:删除某一位置的节点
* param: pre：删除节点的前驱节点
* return：
***********************/
template <typename T>
void List<T>::deleteElemOpt(ListNode<T>* pre) {
    if (pre == nullptr) {
        return;
    }

    ListNode<T>* cur = pre->next;
    pre->next        = cur->next;
    delete cur;
}

/***********************
*function：InsertNode
*destination:插入节点,LRU实现
* param:
* return：
*
***********************/
template <typename T>
void List<T>::InsertNode(const T& data) {
    ListNode<T>* pre = findPreNode(data);

    if (pre == nullptr) {
        if (m_size >= m_capaciy) {
            deleteElemAtEnd();
        }
        insertNodeBegin(data);

    } else {
        deleteElemOpt(pre);
        insertNodeBegin(data);
    }
}
/***********************
*function：insertNodeTail
*destination:插入节点,尾插法实现
* param:
* return：
*
***********************/
template <typename T>
void List<T>::insertNodeTail(const T& data) {
    ListNode<T>* node = findTailNode();
    node->next        = new ListNode<T>(data);
}
/***********************
*function：findPreNode
*destination:寻找对应元素前一节点
* param: data比较值
* return：pNode , == nullptr maybe不存在，
*           maybe是最后一个元素
***********************/
template <typename T>
ListNode<T>* List<T>::findPreNode(const T& data) {
    for (ListNode<T>* node = m_head; node->next != nullptr; node = node->next) {
        if (node->next->data == data) {
            return node;
        }
    }

    return nullptr;
}
/***********************
*function：deleteElemAtEnd
*destination:删除链表最后一个节点
* param:
* return：
***********************/
template <typename T>
void List<T>::deleteElemAtEnd() {
    if (m_head->next == nullptr) {
        return;
    }
    ListNode<T>* node = m_head;
    while (node->next->next != nullptr) {
        node = node->next;
    }
    //等于最后一个智能指针不放在链表里了，会发生泄漏吗
    delete node->next;
    node->next = nullptr;
    m_size--;
}

/***********************
*function：找到尾巴节点
*destination:
* param:
* return：
***********************/
template <typename T>
ListNode<T>* List<T>::findTailNode() {
    ListNode<T>* node = m_head;
    while (node->next != nullptr) {
        node = node->next;
    }
    return node;
}
template <typename T>
void List<T>::printAll() {
    printf("Dlist:()->");
    for (ListNode<T>* node = m_head->next; node != nullptr; node = node->next) {
        std::cout << node->data << "->";
    }
    std::cout << "nil" << std::endl;
}

template <typename T>
void print(const std::string& str, ListNode<T>* head) {
    printf("%s:()->", str.c_str());
    for (ListNode<T>* node = head; node != nullptr; node = node->next) {
        std::cout << node->data << "->";
    }
    std::cout << "nil" << std::endl;
}

/***********************
*function：insertNodeBegin
*destination:头部插入一个节点
* param:
* return：
***********************/
template <typename T>
void List<T>::insertNodeBegin(const T& data) {
    // pNode head = make_shared<DlistNode<T>>(data);
    ListNode<T>* head = new ListNode<T>(data);
    head->next        = m_head->next;
    m_head->next      = head;
}

template <typename T>
bool List<T>::isEmpty() {
    return m_head->next == nullptr;
}

