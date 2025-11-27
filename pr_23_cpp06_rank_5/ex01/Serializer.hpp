#ifndef SERIALIZER__HPP
#define SERIALIZER__HPP

#include <string>
#include <optional>
#include <cstdint> // uintptr_t

struct Data;

/**
 * Use serialize() on the address of the Data object and pass its return value to deserialize().
 * ensure the return value of deserialize() compares equal to the
original pointer.
 */
class Serializer {
	// default: private
	Serializer() = delete;
	Serializer(const Serializer&) = delete;
	Serializer& operator=(const Serializer&) = delete;
	~Serializer() = delete;

	public:
	//It takes a pointer and converts it to the unsigned integer type uintptr_t.
		static uintptr_t serialize(Data* ptr);
		//It takes an unsigned integer parameter and converts it to a pointer to Data.
		static Data* deserialize(uintptr_t raw);
};

#endif