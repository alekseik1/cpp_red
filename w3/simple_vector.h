#pragma once

#include <cstdlib>
#include <iostream>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector(): _begin(nullptr), _size(0), _capacity(0) {}
    explicit SimpleVector(size_t size): _begin(new T[size + 1]), _capacity(size + 1), _size(size) {}
    ~SimpleVector() {
        _free();
    }

    T& operator[](size_t index) { return _begin[index]; }
    const T& operator[](size_t index) const { return _begin[index]; }

    T* begin() { return _begin; }
    T* end() { return _begin + _size; }

    const T* begin() const { return _begin; }
    const T* end() const { return _begin + _size; }

    size_t Size() const { return _size; }
    size_t Capacity() const { return _capacity; }
    void PushBack(const T& value) {
//        std::cout << "PUSH_BACK: begin\n";
        if (_size == 0) _realloc(1);
        if (_size == _capacity) _realloc(2*_capacity);
        _begin[_size] = value;
        ++_size;
//        std::cout << "PUSH_BACK: printing _data\n";
//        _debug_print();
//        std::cout << "PUSH_BACK: done\n";
    }

    void _debug_print() {
        std::cout << "_begin is: ";
        for (auto i = _begin; i != _begin + _size; ++i) std::cout << *i << " ";
        std::cout << std::endl;
    }
private:
    T* _begin = nullptr;
    size_t _capacity = 0;
    size_t _size = 0;
    void _realloc(size_t new_capacity) {
//        std::cout << "realloc from " << _capacity << " to " << new_capacity << std::endl;
        T* new_begin = new T[new_capacity];
        // Copy
        if (_begin != nullptr) std::copy(_begin, _begin + _capacity, new_begin);
        // Free
        _free();
        _begin = new_begin;
        _capacity = new_capacity;
//        std::cout << "REALLOC:\n";
//        _debug_print();
//        std::cout << "REALLOC: done\n";
    }


    void _free() { delete[] _begin; }
};