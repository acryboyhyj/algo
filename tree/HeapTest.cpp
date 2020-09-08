#include "Heap.h"
#include "TestToggle.h"
#include <queue>
#ifdef HEAP_TEST
void createHeap()
{
    Heap<int> heap;
    heap.setToStringFunc([](int &a) -> std::string {
        return std::to_string(a);
    });
    std::vector<int> v{33, 17, 21, 16, 13, 15, 9, 5, 6, 7, 8, 1, 2, 22};
    for (auto &i : v)
    {
        heap.push(i);
    }

    std::cout << heap.toString();

    // std::priority_queue<int> queue;
    // for (auto &i : v)
    // {
    //     queue.push(i);
    // }

    // std::string result;
    // while (!queue.empty())
    // {
    //     result += std::to_string(queue.top());
    //     queue.pop();
    //     result += " ";
    // }
    // std::cout << result << std::endl;
}

void HeapDeleTop()
{
    Heap<int> heap;
    heap.setToStringFunc([](int &a) -> std::string {
        return std::to_string(a);
    });
    std::vector<int> v{33, 17, 21, 16, 13, 15, 9, 5, 6, 7, 8, 1, 2, 22};
    for (auto &i : v)
    {
        heap.push(i);
    }

    std::cout << "1!:" << heap.toString() << std::endl;

    heap.pop();
    std::cout << "2!:" << heap.toString() << std::endl;
    heap.pop();
    std::cout << "3!:" << heap.toString() << std::endl;
}

void HeapSortTest()
{
    std::vector<int> v{33, 17, 21, 16, 13, 15, 9, 5, 6, 7, 8, 1, 2, 22};
    std::vector<int> r = HeapSort<int>::Sort(v);
    for (const auto &c : r)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::vector<int> v1{33, 17, 21, 16, 13, 15, 9, 5, 6, 7, 8, 1, 2, 22};
    HeapSort<int>::inPlaceSort(v1);
    for (const auto &c : v1)
    {
        std::cout << c << " ";
    }
}
int main()
{
    // createHeap(); //
    // HeapDeleTop();
    HeapSortTest();
    return 0;
}
#endif