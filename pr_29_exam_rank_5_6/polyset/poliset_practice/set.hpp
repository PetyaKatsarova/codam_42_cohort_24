#ifndef SET_HPP
#define SET_HPP
#include "searchable_bag.hpp"

class set : public searchable_bag {
    private:
        searchable_bag& sbag;

    public:
        set(searchable_bag& sb);
        set(const set& other);
        set operator=(const set& other);
        ~set();

        bool has(int) const;
        void insert(int);
        void insert(int *, int) ;
        void print() const;
        void clear(); 
        searchable_bag& get_bag() const;
};


#endif 