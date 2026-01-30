*delete is an operator that is used to destroy array and non-array(pointer) objects which are dynamically created by the new operator.

delete can be used by either using the delete operator or delete [ ] operator.
The new operator is used for dynamic memory allocation which stores variables on heap memory.
This means the delete operator deallocates memory from the heap.
The pointer to the object is not destroyed, the value or memory block pointed by the pointer is destroyed.
The delete operator has void return type which means it does not return any value.

------------------------------------------------------------------------------------
clear()	Cleans up internal data (array/tree nodes)	Frees data owned by the object
delete	Calls destructor + frees the object itself	Frees the object allocated with new

delete a;
 Calls: a->~searchable_array_bag()
   └─> calls: array_bag::~array_bag()
       └─> calls: delete[] this->data
 Then frees the object itself

 * std::set is an associative container that contains a sorted set of unique objects of type Key. Sorting is done using the key comparison function Compare. Search, removal, and insertion operations have logarithmic complexity. Sets are usually implemented as Red–black trees.
 