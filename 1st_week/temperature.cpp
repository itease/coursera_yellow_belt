#include <iostream>
#include <cstdint>
#include <vector>

int main() {
    int32_t n;
    std::cin >> n;
    std::vector<int32_t> temperature_values(n);
    int64_t sum = 0;
    for (int32_t& value : temperature_values) {
        std::cin >> value;
        sum += value;
    }
    int32_t average = sum / n;
    int32_t values_high_average = 0;
    for (const int32_t& temperature_value : temperature_values) {
        if (temperature_value > average) {
            ++values_high_average;
        }
    }
    std::cout << values_high_average << "\n";
    for (size_t  i = 0; i < temperature_values.size(); ++i) {
        if (temperature_values[i] > average) {
            std::cout << i << " ";
        }
    }

    return 0;
}
