#include "Heap.h"
#include "TestToggle.h"
#include <queue>
#include <vector>
#include <functional>
#include "HeapSort.h"
#ifdef HEAPAPPLY_TEST
void print(std::vector<int> &r)
{
    for (const auto &c : r)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}
std::vector<int> TopK(std::vector<int> data, size_t k)
{

    //大顶堆建堆
    std::vector<int> result;
    data.insert(data.begin(), 0);
    Heap<int>::buildHeap(data);
    int n = data.size() - 1;
    int num = k;
    while (num > 0)
    {
        //n为从后往前的要堆化的数组的数据个数

        std::swap(data[1], data[n]);
        num--;
        n--;
        Heap<int>::HeapifyToDown(data, n, 1);
    }
    data.erase(data.begin());

    for (int i = data.size() - 1; i > 0 && k > 0; i--)
    {
        result.push_back(data[i]);
        k--;
    }
    return result;
}
std::vector<int> TopK1(std::vector<int> data, size_t k)
{
    //大顶堆建堆
    std::vector<int> result;

    HeapSort<int>::inPlaceSort(data);
    for (size_t i = data.size() - 1; i > 0 && k > 0; i--)
    {
        result.push_back(data[i]);
        k--;
    }

    return result;
}
//合并k个有序数组，每个数组长度都为k
struct HeapNode
{
    HeapNode() : value(-1), x(-1), y(-1) {}
    HeapNode(int _value, int _x, int _y) : value(_value), x(_x), y(_y) {}
    bool operator>(const HeapNode &rhs) const
    {
        return this->value > rhs.value;
    }
    int value;
    int x;
    int y;
};
std::vector<int> mergeKorderArrary(std::vector<std::vector<int>> &data)
{

    Heap<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> heap;

    //k个数组的第一个元素存入堆
    for (size_t i = 0; i < data.size(); i++)
    {
        heap.push(HeapNode(data[i][0], i, 0));
    }
    std::vector<int> result;

    HeapNode node;
    while (!heap.empty())
    {
        heap.pop(node);
        result.push_back(node.value);

        if (node.y + 1 < (int)data[node.x].size())
        {
            heap.push(HeapNode(data[node.x][node.y + 1], node.x, node.y + 1));
        }
    }
    return result;
}

void topkTest(std::vector<int> data)
{
    std::vector<int> r = TopK(data, 5);
    for (const auto &c : r)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::vector<int> r1 = TopK1(data, 5);
    for (const auto &c : r1)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void mergeKorderArraryTest()
{
    std::vector<std::vector<int>> v{
        {1, 3, 5, 7},
        {2, 4, 6},
        {0, 8, 9, 10, 11}};

    std::vector<int> result = mergeKorderArrary(v);
    print(result);
}
int main()
{
    std::vector<int> v{66, 33, 17, 21, 16, 13, 15, 89, 9, 5, 6, 43, 7, 8, 1, 2, 22, 100, 300};
    // topkTest(v);
    mergeKorderArraryTest();
    return 0;
}
#endif