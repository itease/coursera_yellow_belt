#include <iostream>
#include <cstdint>
#include <vector>

int main() {
    uint32_t blocks_quantity;
    std::cin >> blocks_quantity;
    uint16_t density;
    std::cin >> density;
    std::vector<uint64_t> blocks_v(blocks_quantity);
    for (uint64_t& block_v : blocks_v) {
        uint16_t w, h, d;
        std::cin >> w >> h >> d;
        block_v = w;
        block_v *= h;
        block_v *= d;
    }
    uint64_t blocks_m = 0;
    for (const uint64_t& block_v : blocks_v) {
        blocks_m += block_v * density;
    }
    std::cout << blocks_m << "\n";

    return 0;
}
