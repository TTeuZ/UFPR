#include <iostream>

#include "CircularList.hpp"

int main() {
    CircularList<int> list1;
    CircularList<double, 5> list2;
    CircularList<std::string> list3;

    list1.push(10);
    list1.push(20);
    list1.push(30);

    list2.push(1.0);
    list2.push(2.0);
    list2.push(3.0);
    list2.push(4.0);
    list2.push(5.0);
    list2.push(6.0);

    list3.push("Pão");
    list3.push("de");
    list3.push("Batata");

    int value{list1.getActualItem()};
    for (int i = 0; i < 6; ++i) {
        std::cout << value << std::endl;
        value = list1.next();
    }

    double value2{list2.getActualItem()};
    for (int i = 0; i < 10; ++i) {
        std::cout << value2 << std::endl;
        value2 = list2.next();
    }

    std::string value3{list3.getActualItem()};
    for (int i = 0; i < 6; ++i) {
        std::cout << value3 << std::endl;
        value3 = list3.next();
    }

    list1.remove(10);
    value = list1.getActualItem();
    for (int i = 0; i < 4; ++i) {
        std::cout << value << std::endl;
        value = list1.next();
    }

    list3.remove();
    value3 = list3.getActualItem();
    for (int i = 0; i < 4; ++i) {
        std::cout << value3 << std::endl;
        value3 = list3.next();
    }

    return 0;
}
