
/**
 * our program must be able to use a positive integer sequence as an argument.
• Your program must use the merge-insert sort algorithm to sort the positive integer
sequence.
To clarify, yes, you need to use the Ford-Johnson algorithm.
(source: Art Of Computer Programming, Vol.3. Merge Insertion,
Page 184.)
• If an error occurs during program execution, an error message should be displayed
on the standard error.
You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.
It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.
 */

 #include <iostream>
 #include <vector>
 #include <algorithm>
 #include <utility> // std::pair??

void printArr(std::vector<int>& arr) {
	std::cout << "[";
	for (size_t i = 0; i < arr.size(); i++) {
		std::cout << arr[i];
		if (i < arr.size() - 1) std::cout << ", ";
	}
	std::cout << "]\n";
}

void printPairs(const std::vector<std::pair<int, int>>& pairs) {
	std::cout << "Pairs: ";
	for (const auto& p : pairs) { // doesnt take in int
		std::cout << "(" << p.first << ", " << p.second << ")";
	}
	std::cout << "\n";
}

// Step 1: Create pairs with larger element first
std::vector<std::pair<int, int>> makePairs(const std::vector<int>& arr, int& oddEl) {
	std::vector<std::pair<int, int>> pairs;

	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		if (arr[i] < arr[i+1]) {
			pairs.push_back({arr[i+1], arr[i]}); 
		} else {
			pairs.push_back({arr[i], arr[i+1]});
		}
	}
	oddEl = (arr.size() % 2 == 1 ? arr.back() : -1); // save odd el if arr has odd len
	return pairs;
}

// step 2: sort pairs by their first(larger) el
void sortPairs(std::vector<std::pair<int, int>>& pairs) {
	std::sort(pairs.begin(), pairs.end());
}

// c++ main.cpp && ./a.out
 int main() {
	std::vector<int> arr = {1, 3, 442, 3, 43, 8};
	printArr(arr);

	int oddEl;
	std::vector<std::pair<int, int>> pairs = makePairs(arr, oddEl); // &?
	printPairs(pairs);
	sortPairs(pairs);
	printPairs(pairs);
	return 0;
 }