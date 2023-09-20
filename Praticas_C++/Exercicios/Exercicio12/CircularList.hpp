#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP

#include <cstddef>
#include <cstdlib>

template <typename T = int, size_t MAX_SIZE = 10>
class CircularList {
   public:
    // Constructor
    CircularList() : actualPos{0}, size{0} {};

    // Destructor
    ~CircularList(){};

    // Functions'
    const T getActualItem() const { return this->list[this->actualPos]; }

    const T next() {
        this->actualPos++;
        if (this->actualPos >= this->size) this->actualPos = 0;

        return this->list[this->actualPos];
    }

    bool push(const T value) {
        if (this->isFull()) return false;

        this->list[this->size] = value;
        this->size++;
        return true;
    }

    bool remove(const T value) {
        if (this->isEmpty()) return false;

        size_t index = 0;
        while (this->list[index] != value) {
            if (index >= this->size) return false;
            index++;
        }

        for (size_t i = index; i < this->size - 1; ++i)
            this->list[i] = this->list[i + 1];

        this->size--;
        return true;
    }

    bool remove() {
        if (this->isEmpty()) return false;

        for (size_t i = this->actualPos; i < this->size - 1; ++i)
            this->list[i] = this->list[i + 1];

        this->size--;
        return true;
    }

    bool isFull() const { return true ? size >= MAX_SIZE : false; }

    bool isEmpty() const { return size == 0; }

   private:
    T list[MAX_SIZE];
    size_t actualPos;
    size_t size;
};
#endif