###### THEORY

Variadic functions are functions that can take a variable number of arguments.The variadic function consists of at least one fixed variable and then an ellipsis(…) as the last parameter.

int function_name(data_type variable_name, ...);
#include <stdarg.h>
header provides three key macros to handle variadic arguments:

va_list: A type to hold information about variable arguments.
va_start: Initializes a va_list object.
va_arg: Retrieves the next argument in the list.
va_end: Cleans up the va_list object.
----------------------------------------------------------------

va_list, va_start, va_arg, and va_end Macros:

    va_list: This is a data type used to declare a variable that will store the list of arguments.
    va_start: Initializes the va_list variable to be used for traversing the additional arguments.
    va_arg: Fetches the next argument from the list. It also requires specifying the type of the argument that is expected.
    va_end: Cleans up the va_list variable after all arguments have been processed.

    