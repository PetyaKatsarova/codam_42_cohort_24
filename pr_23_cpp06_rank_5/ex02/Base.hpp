#ifndef BASE__HPP
#define BASE__HPP

/**
 the compiler will generate default special members for you:
default constructor (if no other ctor declared)
copy constructor / copy assignment (unless inhibited)
move constructor / move assignment (generated under the usual rules)
destructor (you already have virtual ~Base() = default; — that's inline
 */
class Base {
	public:
		virtual ~Base() = default;
};

#endif