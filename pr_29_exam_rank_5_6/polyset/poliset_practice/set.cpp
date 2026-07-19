#include "set.hpp"

set::set(searchable_bag& sb) : sbag(sb) {}

set::set(const set& other) : sbag(other.sbag) {
    
}
set set::operator=(const set& other) {
    if (this == &other)
        sbag = other.sbag;
    return *this;
}

set::~set() {}

bool set::has(int n) const {
    return sbag.has(n);
}

void set::insert(int n) {
    if (!sbag.has(n))
        this->insert(n);
}

void set::insert(int *arr, int s)  {
    for (int i = 0; i < s; i++) {
        sbag.insert(arr[i]);
    }
}

void set::print() const {
    sbag.print();
}

void set::clear() {
    sbag.clear();
}

searchable_bag& set::get_bag() const {
    return sbag;
}