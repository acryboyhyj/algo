#ifndef __HEAP_H__
#define __HEAP_H__

/*默认小顶堆*/
#include <vector>
#include <functional>
#include <assert.h>
#include <iostream>

/*T需要有 T()构造，因为0下标需要插入一个开始的空值 */
/*heap 功能类似优先级队列 2个static函数提供了额外的建堆堆化操作*/
template <class T,
          class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class Heap
{

public:
    //原地建堆 需要增加一个空节点到开头
    static void buildHeap(std::vector<T> &data)
    {
        //先增加一个空节点到开头，数组从后往前处理，堆化则从上到下，叶子节点不需要比较，直接从非叶子节点开始
        int n = data.size() - 1;
        for (int i = n / 2; i >= 1; i--)
        {
            HeapifyToDown(data, n, i);
        }
    }
    //n表示实际的数据个数
    static void HeapifyToDown(std::vector<T> &data, int n, int currentIndex)
    {

        //叶子节点停止
        // while (currentIndex * 2 <= n)
        while (true)
        {
            int chilidIndex = chooseHeapiFynode(data, n, currentIndex);
            if (chilidIndex == currentIndex)
            {
                break;
            }
            else
            {
                std::swap(data[currentIndex], data[chilidIndex]);
                currentIndex = chilidIndex;
                // continue;
            }
        }
    }

public:
    Heap() : _toStringFunc(nullptr)
    {
        _container.push_back(T());
    }

    ~Heap() {}

    void setToStringFunc(std::function<std::string(T &a)> toStringFunc)
    {
        _toStringFunc = std::move(toStringFunc);
    }

    std::string toString()
    {
        assert(_toStringFunc != nullptr);

        std::string result;
        for (int i = 1; i < _container.size(); i++)
        {
            result += _toStringFunc(_container[i]);
            result += " ";
        }
        result += "\n";
        return result;
    }

    void push(T data)
    {
        _container.push_back(data);
        //下往上
        Heapify();
    }

    void pop(T &data)
    {
        //为了满足完全二叉树，只需要最后一个元素替换到顶，然后从上往下堆化
        if (_container.size() >= 2)
        {
            std::swap(_container[1], _container[_container.size() - 1]);
            data = std::move(_container.back());
            _container.pop_back();
            HeapifyToDown(_container, _container.size() - 1, 1);
        }
    }

    void pop()
    {
        if (_container.size() >= 2)
        {
            std::swap(_container[1], _container[_container.size() - 1]);
            _container.pop_back();
            HeapifyToDown(_container, _container.size() - 1, 1);
        }
    }

    bool empty()
    {
        return _container.size() <= 1;
    }

public:
    //从下往上堆化
    void Heapify()
    {
        int currIndex = _container.size() - 1;
        int parentIndex = currIndex / 2;

        //堆顶停止
        while (currIndex > 1)
        {
            //less 默认大顶堆
            if (!Compare()(_container[currIndex], _container[parentIndex]))
            {
                std::swap(_container[currIndex], _container[parentIndex]);
            }
            currIndex = parentIndex;
            parentIndex = currIndex / 2;
        }
    }

private:
    static int chooseHeapiFynode(std::vector<T> &data, int n, int currIndex)
    {
        int leftIndex = currIndex * 2;
        int rightIndex = currIndex * 2 + 1;
        int maxPos = currIndex;

        if (leftIndex <= n && Compare()(data[currIndex], data[leftIndex]))
            maxPos = leftIndex;
        if (rightIndex <= n && Compare()(data[maxPos], data[rightIndex]))
            maxPos = rightIndex;
        return maxPos;
    }

private:
    Container _container;
    std::function<std::string(T &a)> _toStringFunc;
};

#endif // __HEAP_H__