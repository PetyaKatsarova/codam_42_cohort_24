#include <array>
#include <iostream>

int main() {
    std::array<int, 4> arr = {10, 20, 30, 40};
    for (size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
    arr.fill(5);  // sets all elements to 5
    std::cout << arr.front() << " " << arr.back() << "\n";
    return 0;
}
