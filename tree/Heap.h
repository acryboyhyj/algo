#ifndef __HEAP_H__
#define __HEAP_H__

/*默认小顶堆*/
#include <vector>
#include <functional>
#include <assert.h>
#include <iostream>
//堆排序写在后面
template <class T,
          class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class Heap
{
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
    //原地建堆
    static void buildHeap(std::vector<T> &data)
    {
        //先增加一个空节点到开头，数组从后往前处理，堆化则从上到下，叶子节点不需要比较，直接从非叶子节点开始
        data.insert(data.begin(), T());
        int n = data.size() - 1;
        for (int i = n / 2; i >= 1; i--)
        {
            HeapifyToDown(data, n, i);
        }
    }

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

template <class T,
          class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class HeapSort
{
public:
    //非原地 逐个pop出堆顶，故是降序
    static std::vector<T> Sort(std::vector<T> &data)
    {
        Heap<T, Container, Compare> heap;
        heap.setToStringFunc([](int &a) -> std::string {
            return std::to_string(a);
        });
        for (int i = 0; i < data.size(); i++)
        {
            heap.push(data[i]);
        }
        std::vector<T> result;
        while (!heap.empty())
        {
            T data;
            heap.pop(data);
            std::cout << " !" << heap.toString() << std::endl;
            result.push_back(std::move(data));
        }

        return result;
    }

    //原地 逐个将堆顶与末尾值交换，在从上往下特化，故是升序
    static void inPlaceSort(std::vector<T> &data)
    {
        Heap<T, Container, Compare>::buildHeap(data);

        int k = data.size() - 1;
        while (k > 1)
        {
            std::swap(data[1], data[k]);
            k--;
            Heap<T, Container, Compare>::HeapifyToDown(data, k, 1);
        }
        data.erase(data.begin());
    }
};
#endif // __HEAP_H__