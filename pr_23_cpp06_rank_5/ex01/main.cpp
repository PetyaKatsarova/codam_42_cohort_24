#include "Serializer.hpp"
#include  "Data.hpp"
#include <iostream>    // std::cout, std::cerr, std::boolalpha (printing/logging)
#include <memory>      // std::unique_ptr (smart pointer owning heap Data)
#include <cstdint>     // std::uintptr_t (holds pointer bits as integer)
#include <iomanip>     // std::hex, std::dec, std::setprecision (output formatting)
/**
 * Use serialize() on the address of the Data object and pass its return value to
deserialize(). Then, ensure the return value of deserialize() compares equal to the
original pointer.
 */

 /**
 * shallow equality: the deserialized pointer should have the same address (point to the same object) as the original pointer — not a deep copy of the object. */

 /**
  * std::unique_ptr<Data> uniq_ptr(new Data{"Uniq data", 37});

uniq_ptr owns the Data object and will delete it automatically when uniq_ptr is destroyed.
unique_ptr cannot be copied, only moved.
use std::make_unique<Data>("Uniq data", 37) (preferred).
Data* p_heap = uniq_ptr.get();

p_heap is a non‑owning observer pointer — it does NOT manage lifetime.
Do NOT delete p_heap. Deleting it will double‑free when uniq_ptr destroys the object.
p_heap becomes dangling when uniq_ptr is reset/moved/destroyed.

auto uniq_ptr = std::make_unique<Data>("Uniq data", 37);

auto deduces the type at compile time. Here it becomes std::unique_ptr<Data>.
uniq_ptr is the smart‑pointer object that owns the heap Data.
&uniq_ptr

the address of the unique_ptr variable itself (where the smart‑pointer object lives, typically on the stack).
printing &uniq_ptr shows the address of that unique_ptr object — NOT the address of the Data it owns.
p_heap (Data *p_heap = uniq_ptr.get();)

p_heap is a raw, non‑owning pointer to the Data object on the heap.
printing p_heap shows the address of the owned Data.
-------------------------------------------------------
-- boolalpha:    bool b = true;

    std::cout << b << '\n';                // prints: 1
    std::cout << std::boolalpha << b << '\n'; // prints: true
    bool c = false;
    std::cout << c << '\n';                // prints: false
    std::cout << std::noboolalpha << b << '\n'; // prints: 1
  */
 int main() {
	Data stack = {"Stack data", 42}; // stack allocated, short lived
	Data *p_stack = &stack;

	// de/serialize stack ptr, valid while stack is alive
	uintptr_t raw_stack = Serializer::serialize(p_stack);
	Data* back_stack = Serializer::deserialize(raw_stack);

	std::cout << "Stack ptr as int: " << raw_stack << std::endl;
	std::cout << " Stack addr: " << p_stack << "\n";
	std::cout << "Back ptr ad: " << back_stack << std::endl;
	std::cout << "stack pointers equal? " << std::boolalpha << (back_stack == p_stack) << '\n';

	std::cout << "*** unique ptr ***\n";
	//auto uniq_ptr = std::make_unique<Data>("Uniq data", 37); // owns heap data, need constructor for this

	//new allocates heap memory here, but no leak because unique_ptr owns and deletes it automatically.
	auto uniq_ptr = std::unique_ptr<Data>(new Data{"Uniq ptr", 222});
	Data *p_heap = uniq_ptr.get(); // non-owning observer

	uintptr_t raw = Serializer::serialize(p_heap);
	Data* restored = Serializer::deserialize(raw);
	std::cout << "uniq_ptr adr: " << &uniq_ptr << "\n";
	std::cout << "     raw adr: " << raw << '\n';
	std::cout << "  p_heap adr: " << p_heap << '\n';
	std::cout << "restored adr: " << restored << '\n';
	std::cout << "heap pointers equal? " << std::boolalpha << (p_heap == restored) << '\n';
	return 0;
}
