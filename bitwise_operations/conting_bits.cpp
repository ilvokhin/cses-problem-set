#include <iostream>
#include <cstdint>

using namespace std;

uint64_t count_one_bits(uint64_t x) {
    uint64_t count = 0;

    while (x > 0) {
        ++count;
        x = x & (x - 1);
    }

    return count;
}

uint64_t solve_simple(uint64_t n) {
    uint64_t count = 0;
    for (uint64_t i = 1; i <= n; ++i)
        count += count_one_bits(i);

    return count;
}

uint64_t solve_fast(uint64_t n) {
    if (n == 0)
        return 0;
    if (n % 2 == 0)
        return solve_fast(n - 1) + count_one_bits(n);
    return 2 * solve_fast(n / 2) + (n + 1)/ 2;
}

int main() {
    uint64_t n;
    cin >> n;

    cout << solve_fast(n) << endl;

    return 0;
}
