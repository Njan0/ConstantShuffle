#include "CustomIndex.h"

namespace ConstantShuffle {
	CustomIndex::CustomIndex() : CustomIndex(0) { }
	CustomIndex::CustomIndex(int idx) : idx(idx), lastAccess(0) { }
}