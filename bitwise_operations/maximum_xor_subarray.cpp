#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <array>

using namespace std;

struct node {
    std::array<std::unique_ptr<node>, 2> to{
        nullptr,
        nullptr
    };
};

class bit_trie {
    node root_;

public:
    void add(uint32_t x) {
        node* cur = &root_;
        for (int nbit = 31; nbit >= 0; --nbit) {
            auto bit = (x >> nbit) & 1U;
            auto& next = cur->to[bit];
            if (next == nullptr)
                next = make_unique<node>();
            cur = next.get();
        }
    }

    uint32_t find_best(uint32_t x) const {
        const node* cur = &root_;
        uint32_t ret = 0;

        for (int nbit = 31; nbit >= 0; --nbit) {
            auto bit = (x >> nbit) & 1U;
            if (cur->to[!bit]) {
                cur = cur->to[!bit].get();
                if ((!bit) == 1)
                    ret |= (1 << nbit);
            } else {
                cur = cur->to[bit].get();
                if (bit == 1)
                    ret |= (1 << nbit);
            }
        }

        return ret;
    }
};

int solve(const vector<int>& v) {
    uint32_t max_xor = 0;
    uint32_t prefix_xor = 0;
    bit_trie trie;

    trie.add(0);

    for (uint32_t x: v) {
        prefix_xor ^= x;
        const uint32_t best = trie.find_best(prefix_xor);
        max_xor = max(max_xor, best ^ prefix_xor);
        trie.add(prefix_xor);
    }

    return max_xor;
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    cout << solve(v) << endl;

    return 0;
}
