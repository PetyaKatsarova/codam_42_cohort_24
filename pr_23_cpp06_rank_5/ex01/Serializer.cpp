#include "Serializer.hpp"
#include "Data.hpp"
#include <cstdint> // uintptr_t

/**
 * uintptr_t / intptr_t (header <cstdint>)
Integer types guaranteed wide enough to hold a pointer’s bit pattern on typical platforms.
Use when you need to store or manipulate pointer bits as an integer (printing, hashing, bit-masking, low-level serialization).
 */

 /**
  * reinterpret_cast
Use reinterpret_cast<uintptr_t>(p) to convert pointer→integer.
Use reinterpret_cast<T*>(n) to convert integer→pointer.
Converting pointer→integer→pointer is allowed if the integer type can hold the pointer value; on typical systems uintptr_t exists and works. Still be careful: converting arbitrary integer to pointer can be undefined behavior.
  */

  /**
   * struct Data {
	std::string str;
	int num;
	};
   */


   //takes a pointer and converts it to the unsigned integer type uintptr_t
uintptr_t Serializer::serialize(Data *ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}