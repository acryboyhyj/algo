#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__
#include <vector>
#include <functional>
#include "Heap.h"
template <class T,
          class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class HeapSort
{
public:
    //非原地 默认大顶堆 逐个pop堆顶出去呈降序
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
            result.push_back(std::move(data));
        }

        return result;
    }

    //原地排序由 默认compare是less,会是大顶堆，堆顶将交换到最后，故呈升序
    static void inPlaceSort(std::vector<T> &data)
    {
        data.insert(data.begin(), T());
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
#endif // __HEAPSORT_H__