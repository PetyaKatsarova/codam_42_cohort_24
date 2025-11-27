#include "Serializer.hpp"
#include  "Data.hpp"
#include <iostream>
#include <memory> // std::unique_ptr
#include <cstdint>
#include <iomanip>
/**
 * Use serialize() on the address of the Data object and pass its return value to
deserialize(). Then, ensure the return value of deserialize() compares equal to the
original pointer.
 */

 /**
  * Serializing a pointer to a stack object is valid only while that object is alive. Don’t use the raw integer after the object goes out of scope.
Check for nullptr and prefer heap/smart pointers for longer-lived objects.
Prefer printing uintptr_t in hex for address readability.
  */
int main() {
	Data stack = {"Stack data", 42}; // stack allocated, short lived
	Data *p_stack = &stack;

	//std::unique_ptr<Data> uniq_ptr(new Data{"Uniq data", 37}); // heap alloc with new: need to delete
	//Data* p_heap = uniq_ptr.get(); // what we get??

	// de/serialize stack ptr, valid while stack is alive
	uintptr_t raw_stack = Serializer::serialize(p_stack);
	Data* back_stack = Serializer::deserialize(raw_stack);
	std::cout << "Stack ptr: " << raw_stack << std::endl;
	std::cout << "Back ptr: " << back_stack << std::endl;
	std::cout << "stack pointers equal? " << std::boolalpha << (back_stack == p_stack) << '\n';
	return 0;
}
/*
#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <memory>
#include <cstdint>
#include <iomanip>

int main() {
    // stack object (short lived)
    Data stack = {"Stack data", 42};
    Data* p_stack = &stack;

    // heap object
    std::unique_ptr<Data> up(new Data{"Heap data", 22});
    Data* p_heap = up.get();

    // serialize/deserialize stack pointer (valid while 'stack' alive)
    uintptr_t raw_stack = Serializer::serialize(p_stack);
    Data* back_stack = Serializer::deserialize(raw_stack);
    std::cout << "stack pointers equal? " << std::boolalpha << (back_stack == p_stack) << '\n';

    // serialize/deserialize heap pointer (safe while object alive)
    uintptr_t raw_heap = Serializer::serialize(p_heap);
    Data* back_heap = Serializer::deserialize(raw_heap);
    std::cout << "heap pointers equal?  " << (back_heap == p_heap) << '\n';

    // print addresses as hex for readability
    std::cout << "raw_heap (hex): 0x" << std::hex << raw_heap << std::dec << '\n';
    std::cout << "p_heap: " << p_heap << '\n';

    // safely use deserialized pointer while object alive
    if (back_heap) {
        std::cout << "back_heap->str: " << back_heap->str << ", num: " << back_heap->num << '\n';
    }

    // NOTE: do NOT use raw_stack/raw_heap after the corresponding object is destroyed.
    return 0;
}
*/