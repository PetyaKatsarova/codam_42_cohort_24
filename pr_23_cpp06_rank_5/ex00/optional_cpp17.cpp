#include <optional>
#include <iostream>

std::optional<int> divide(int a, int b) {
    if (b == 0)
        return std::nullopt;  // No value (error case)
    return a / b;             // Has value (success)
}

int main() {
    auto result = divide(10, 0);
    
    if (result.has_value()) {
        std::cout << "Result: " << result.value() << '\n';  // 5
    } else {
        std::cout << "Division failed\n";
    }
    
    // Or more concisely:
    if (result)
        std::cout << "Result: " << *result << '\n';
}