//
// Created by hyjcrydby on 2019/10/7.
//
//动态扩容数组模板类

#ifndef ARRAY_DYNAMIC_ARRAY_H
#define ARRAY_DYNAMIC_ARRAY_H

#include <memory>
#include <initializer_list>
#include <iostream>

template<typename T>
class DanymicArray {
public:
    DanymicArray() = delete;

    explicit DanymicArray(int capacity) : m_capacity(capacity), m_head(new T[m_capacity]()) {};

    explicit DanymicArray(std::initializer_list<T> l) : m_capacity(l.size()), m_size(l.size()),
                                                        m_head(new T[m_capacity]()) {
        std::copy(l.begin(), l.end(), m_head);
    };

    ~DanymicArray() {
        if (m_head != nullptr) {
            delete[] m_head;
        }

    }

    void swap(DanymicArray &other) {
        using std::swap;
        swap(m_head, other.m_head);
        swap(m_size, other.m_size);
        swap(m_capacity, other.m_capacity);
    }

    DanymicArray(const DanymicArray<T> &rhs) {
        m_capacity = rhs.m_capacity;
        m_head = new T[rhs.m_capacity];
        m_size = rhs.m_size;
        std::copy(rhs.m_head, rhs.m_head + rhs.m_size, m_head);
    }

    //DanymicArray 与 DanymicArray<T> 一样，编译器自动绑定
    //这里既是拷贝赋值运算符又是移动赋值运算符
    DanymicArray &operator=(DanymicArray rhs) {
        using std::swap;
        swap(*this, rhs);
        return *this;
    }

    DanymicArray(DanymicArray &&rhs) noexcept
            : m_capacity(rhs.m_capacity), m_head(rhs.m_head), m_size(rhs.m_size) {
        rhs.m_capacity = 0;
        rhs.m_head = nullptr;
        rhs.m_size = 0;
    }


    template<typename func>
    void traverse(func doTraverse) {

        for (int i = 0; i < m_capacity; i++) {
            doTraverse(m_head[i]);
        }
    }
    //是否应该允许用户在size-capacity中间直接用下标赋值，应该允许
    T &operator[](int i) {
        if (i >= m_capacity) {
            throw "index out of range";
        } else {
            return m_head[i];
        }
    }


    void pushBack(const T& val){
        if (m_size >= m_capacity){
            m_size = m_capacity;
            m_capacity = m_capacity*2;
            T* new_head = new T[m_capacity];
            std::copy(m_head, m_head+m_size, new_head);
            delete []m_head;
            m_head = new_head;
        }
        m_head[m_size++] = val;
    }

private:

    int m_capacity;
    int m_size;
    T *m_head;


};

//自己的命令空间,函数模板不能偏特化，此为重载
template<typename T>
void swap(DanymicArray<T> &lhs, DanymicArray<T> &rhs) {
    lhs.swap(rhs);
}

#endif //ARRAY_DYNAMIC_ARRAY_H
