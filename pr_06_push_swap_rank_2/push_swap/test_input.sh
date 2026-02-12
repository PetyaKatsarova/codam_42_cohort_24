#!/bin/bash

echo -e "\n0. Testing with empty str"
./push_swap " "

echo -e "\n1. Testing with normal integers: 1 2 3 4 5 000"
./push_swap 1 2 3 4 5 000

echo -e "\n2. Testing with normal int as one string: \"1 2 3 4 5 000\""
./push_swap "1 2 3 4 5 000"

echo -e "\n3. Testing with a list containing both positive and negative numbers: 3 4 6 8 9 74 -56 +495"
./push_swap 3 4 6 8 9 74 -56 +495

echo -e "\n4. Testing with a list containing negative values that should not be considered as duplicates: 95 99 -9 10 9"
./push_swap 95 99 -9 10 9

echo -e "\n5. Testing with duplicate values: 1 2 3 3 5"
./push_swap 1 2 3 3 5

echo -e "\n6. ** ERROR ** Testing with non-numeric input: 1 2 abc 4 5"
./push_swap 1 2 abc 4 5

echo -e "\n65. ** ERROR ** Testing with empty str: ' ' "
./push_swap 1 2  4 5

echo -e "\n7. ** ERROR ** Testing with values greater than INT_MAX: 1 2147483648 3 4"
./push_swap 1 2147483648 3 4

echo -e "\n8. ** ERROR ** Testing with values smaller than INT_MIN: -2147483649 3 4 5"
./push_swap -2147483649 3 4 5

echo -e "\n9. Testing with boundary values (INT_MAX and INT_MIN): 2147483647 -2147483648 5 6"
./push_swap 2147483647 -2147483648 5 6

echo -e "\n10. ** ERROR ALL ** More tests, should get all errors:"
echo -e "\n10.1 Test with non-numeric input (dog): 1 3 dog 35 80 -3"
./push_swap 1 3 dog 35 80 -3

echo -e "\n10.2 Test with a single letter (a): a"
./push_swap a

echo -e "\n10.3 Test with non-numeric input (67b778): 1 2 3 5 67b778 947"
./push_swap 1 2 3 5 67b778 947

echo -e "\n10.4 Test with non-numeric input in a string (54fhd): \"12 4 6 8 54fhd 4354\""
./push_swap "12 4 6 8 54fhd 4354"

echo -e "\n10.5 Test with incorrect characters (double -): 1 -- 45 32"
./push_swap 1 -- 45 32

echo -e "\n10.6 Test with incorrect number (decimal number): 1 3 58 9 3.3"
./push_swap 1 3 58 9 3.3

echo -e "\n10.7 Test with leading zero (03) with a duplicate 3: 3 03"
./push_swap 3 03

echo -e "\n10.8 Test with duplicate numbers in a string (49 49): \"49 128 50 38 49\""
./push_swap "49 128 50 38 49"

echo -e "\n10.9 Test with decimal number (1.5): 1.5"
./push_swap 1.5

echo -e "\n10.10 Test with value greater than INT_MAX (54867543867438): 54867543867438 3"
./push_swap 54867543867438 3

echo -e "\n10.11 Test with value smaller than INT_MIN (-2147483647765): -2147483647765 4 5"
./push_swap -2147483647765 4 5

echo -e "\n10.12 Test with value greater than INT_MAX in a string (214748364748385): \"214748364748385 28 47 29\""
./push_swap "214748364748385 28 47 29"

echo -e "\n22. End of tests"
