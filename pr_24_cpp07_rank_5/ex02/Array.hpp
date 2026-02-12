#ifndef ARRAYTEMPLATE__HPP
#define ARRAYTEMPLATE__HPP

template <typename T>
class Array {
        T*              arr;
        unsigned int    len;

    public:
        Array();
        Array(unsigned int len);
        Array(const Array& other);
        ~Array();

        Array& operator=(const Array& other);
        // SUBSCRIPT OPERATOR = Array indexing using [] brackets, makes arr behave like built-in arr
        T& operator[](unsigned int index) const;

        unsigned int size() const;
};

#include "Array.tpp"

#endif