#include "LRUCache.h"
#include <iostream>
int main()
{
    LRUCache c(2);
    c.put(1, 1);
    c.put(2, 2);
    c.get(1);
    c.put(3, 3);
    c.get(2);
}
