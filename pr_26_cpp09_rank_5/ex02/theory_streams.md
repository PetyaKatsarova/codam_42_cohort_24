A stream = sequence of data you read/write as if it were flowing.

Like:

C: scanf / printf
Java: Scanner, InputStream, BufferedReader

C++ unifies all of this with stream operators.

2. Main stream types

std::istream → input

std::ostream → output

std::stringstream → string as a stream

Concrete examples:

std::cin (keyboard)

std::cout (terminal)

std::istringstream (string → input stream)

3. Operator >> (core concept)

>> means extract one formatted value.

Rules:

Skips whitespace automatically

Stops at whitespace

Fails safely (no crash)

Equivalent to Java: scanner.next()

Equivalent to C: scanf("%s", buf)

4. What std::istringstream does

Turns a string into something you can read token by token.

Conceptually:

"12 -3 45"  →  12 | -3 | 45


So this: iss >> token
means: “Give me the next whitespace-separated piece”
=========================================
ostringstream - A string output stream
Lets you build a std::string using << From <sstream>

std::ostringstream oss;
oss << 1 << " " << 42;
std::string s = oss.str(); // "1 42"
Type-safe (no to_string chains)

Same syntax as std::cout
Automatic formatting

Bad: s += std::to_string(x) + " ";
Good: oss << x << " ";

std::ostringstream oss;
for (int i = 1; i < argc; ++i)
    oss << argv[i] << " ";

std::ostringstream oss;
oss << "Value: " << x;
throw std::runtime_error(oss.str());
or
throw std::runtime_error("Value: " + std::to_string(x));
oss << x	append
oss.str()	get string
oss.str("")	clear buffer
oss.clear()	reset state
ostringstream	write → string
istringstream	string → read
stringstream	both