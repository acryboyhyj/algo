#include "Heap.h"
#include "TestToggle.h"
#include <queue>
#include <functional>
#include "HeapSort.h"
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

    std::cout << "createHeap:" << heap.toString() << std::endl;

    std::priority_queue<int> queue;
    for (auto &i : v)
    {
        queue.push(i);
    }

    std::string result;
    std::cout << "priority quuee: ";

    while (!queue.empty())
    {
        result += std::to_string(queue.top());
        queue.pop();
        result += " ";
    }
    std::cout << result << std::endl;
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

    std::cout << "HeapSort<int>::Sort(v)";
    for (const auto &c : r)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::vector<int> v1{33, 17, 21, 16, 13, 15, 9, 5, 6, 7, 8, 1, 2, 22};
    HeapSort<int>::inPlaceSort(v1);
    std::cout << "HeapSort<int>::inPlaceSort(v1);";
    for (const auto &c : v1)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
//降序，使用小顶堆
void HeapSortDesc()
{
    std::vector<int> v1{33, 17, 21, 16, 13, 15, 9, 5, 6, 7, 8, 1, 2, 22};
    HeapSort<int, std::vector<int>, std::greater<int>>::inPlaceSort(v1);
    std::cout << "HeapSort<int, std::vector<int>, std::greater<int>>::inPlaceSort(v1);";
    for (const auto &c : v1)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
//使用自定义对象,必须重载bool < (const obj&,const obj&) const .如使用std::less会调用 <
// std::greater 会调用 >
struct Obj
{
    Obj() : key(0), value(0) {}
    Obj(int _key, int _value) : key(_key), value(_value)
    {
    }
    Obj(int _key) : key(_key), value(1)
    {
    }

    ~Obj() {}

    bool operator<(const Obj &rhs) const
    {
        return this->key < rhs.key;
    }
    bool operator>(const Obj &rhs) const
    {
        return this->key > rhs.key;
    }
    // bool operator==(Obj &rhs)
    // {
    //     return this->key == rhs.key;
    // }

    friend std::ostream &operator<<(std::ostream &output,
                                    const Obj &D)
    {
        output << D.key << "-" << D.value;
        return output;
    }

    int key;
    int value;
};

void HeapObj()
{
    Heap<Obj> heap;
    heap.setToStringFunc([](Obj &a) -> std::string {
        return std::to_string(a.key) + "-" + std::to_string(a.value);
    });
    std::vector<Obj> v{{33}, {17}, {21}, {16}, {13}, {15}, {9}, {5}, {6}, {7}, {8}, {1}, {2}, {22}};
    for (auto &i : v)
    {
        heap.push(i);
    }
    std::cout << "HeapObj toString:";
    std::cout << heap.toString() << std::endl;

    std::vector<Obj> v1{{33}, {17}, {21}, {16}, {13}, {15}, {9}, {5}, {6}, {7}, {8}, {1}, {2}, {22}};
    HeapSort<Obj, std::vector<Obj>, std::greater<Obj>>::inPlaceSort(v1);
    std::cout << "HeapSort<Obj, std::vector<Obj>, std::greater<Obj>>::inPlaceSort:";
    for (const auto &c : v1)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::vector<Obj> v2{{33}, {17}, {21}, {16}, {13}, {15}, {9}, {5}, {6}, {7}, {8}, {1}, {2}, {22}};
    HeapSort<Obj>::inPlaceSort(v2);
    std::cout << "HeapSort<Obj>::inPlaceSort(v2):";
    for (const auto &c : v2)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

int main()
{
    createHeap(); //
    // HeapDeleTop();
    HeapSortTest();
    HeapObj();
    return 0;
}
#endif