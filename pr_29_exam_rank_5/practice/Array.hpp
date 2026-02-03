#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

/**
 * new T[n]() creates an array of n elements and initializes them to their default values (like 0 for numbers, empty for strings).
 * Without the (), you'd get uninitialized garbage values.
 */
template<typename T>
class Array {
private:
    T* 				_data;
    unsigned int 	_size;

public:
    Array() : _data(nullptr), _size(0) {}
    
    Array(unsigned int n) : _data(new T[n]()), _size(n) {}
    
    Array(const Array& other) : _data(new T[other._size]), _size(other._size) {
        for (unsigned int i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _data = new T[_size];
            for (unsigned int i = 0; i < _size; i++)
                _data[i] = other._data[i];
        }
        return *this;
    }
    
    ~Array() { delete[] _data; }
    
	// array subscript operator
    T& operator[](unsigned int i) {
        if (i >= _size)
            throw std::exception();
        return _data[i];
    }
    
    unsigned int size() const { return _size; }
};

#endif