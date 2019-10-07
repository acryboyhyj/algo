//
// Created by hyjcrydby on 2019/10/7.
//

#include "dynamic_array.h"
#include <iostream>
#include <memory>


template  <typename T, typename func>
void wrapPrint(std::string& before, DanymicArray<T>& array, func doTraverse)
{
    std::cout << before;
    array.traverse(doTraverse);
    std::cout << std::endl;

}

int main()
{
    const auto printTravse = [&] (auto item) { std::cout << item << " ";};
    DanymicArray<int> array1{1,2,3,4};
    std::string format{"test initializer list constructor: "};
    wrapPrint(format, array1, printTravse);

    DanymicArray<int> array2(5);
    format = "constructor: ";
    wrapPrint(format, array2, printTravse);

    DanymicArray<int> array3(array1);
    format = "copy constructor: ";
    wrapPrint(format, array3, printTravse);


    DanymicArray<int> array4(10);
    array4 = array1;
    format = "copy assignment: ";
    wrapPrint(format, array4, printTravse);

    DanymicArray<int> array5(std::move(array4));
    format = "move constructor: ";
    wrapPrint(format, array5, printTravse);
    format = "after move constructor array4: ";
    wrapPrint(format, array4, printTravse);

    DanymicArray<int> array6(5);
    array6 = std::move(array5);
    format = "move assignment: ";
    wrapPrint(format, array6, printTravse);

    array6[3] = 1;
    format = "array6[3] = 1: ";
    wrapPrint(format, array6, printTravse);

    array6.pushBack(1);
    format = "insert a node when fullsize: ";
    wrapPrint(format, array6, printTravse);
    return 0;
}
