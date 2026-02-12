std::deque (double-ended queue):

Dynamic array split into chunks
Fast insertion/deletion at both ends (front & back)
Random access via [] operator
Elements not contiguous in memory (worse cache performance than vector)
No reallocation when growing
std::list (doubly-linked list):

Each element is a separate node with pointers to prev/next
Fast insertion/deletion anywhere (if you have iterator)
No random access - must traverse from start/end
Worst cache performance - nodes scattered in memory
High memory overhead (2 pointers per element)
For your exercise:

Vector: Best for Ford-Johnson (cache-friendly, random access)
Deque: Second choice (decent performance, different container requirement)
List: Bad choice (no random access, slow binary search)

*** DEQUE ***
Deque is NOT one array - it's multiple chunks.

O(1) insertion/deletion at BOTH ends (front & back)
Vector: only fast at back
No reallocation when growing - adds new chunks
Vector: copies all elements when resizing
Random access with [] - like array/vector
Non-contiguous memory - elements split across chunks
Worse cache performance than vector

Vector: [████████████] (one block)
Deque:  [████] [████] [████] (multiple blocks)

Trade-off:
Fast at both ends but slower element access than vector (pointer jumps between chunks).