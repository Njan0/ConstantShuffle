#pragma once
#include <cstdint>

namespace ConstantShuffle {
    class CustomIndex {
    public:
        int idx;
        uintmax_t lastAccess;

        CustomIndex();
        CustomIndex(int idx);
    };
}