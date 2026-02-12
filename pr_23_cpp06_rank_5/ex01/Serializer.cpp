#include "Serializer.hpp"
#include "Data.hpp"
#include <cstdint> // uintptr_t

/**
 * uintptr_t / intptr_t (header <cstdint>)
Integer types guaranteed wide enough to hold a pointer’s bit pattern on typical platforms.
Use when you need to store or manipulate pointer bits as an integer (printing, hashing, bit-masking, low-level serialization).
 */

  /**
   * struct Data {
	std::string str;
	int num;
	};
   */

   /**
	* reinterpret_cast<uintptr_t>(ptr) takes the pointer value (its raw address bits) and reinterprets those bits as an unsigned integer of type uintptr_t.
    serialize stores the address as an integer; deserialize does the reverse (reinterpret_cast<Data*>(raw)).
    */

uintptr_t Serializer::serialize(Data *ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}