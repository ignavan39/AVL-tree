#include <iostream>
#include "AVLTree.h"
#include "AVLTree.cpp"
int main() {
    dictionary d;
    d.insert("22");
    d.insert("22");
    d.insert("123121");
    d.insert("12312");
    d.insert("&88");
    d.insert("2123");
    d.remove("22");
    dictionary d1(d);
    int i = d1.find("22");
    std::cout << d1 << std::endl;
    std::cout << i << std::endl;
    std::cout<< d1.size()<<std::endl;
    return 0;
}
