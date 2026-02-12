-fsanitize=address (AddressSanitizer)
Detects:

Use-after-free

Use-after-return

Heap buffer overflow

Stack buffer overflow

Global buffer overflow

Double free

Invalid free

Memory leaks (with ASAN_OPTIONS=detect_leaks=1)

Recommended for:
General memory safety issues.