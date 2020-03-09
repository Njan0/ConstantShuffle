#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include "CustomIndex.h"
#include <random>

namespace ConstantShuffle {
	template<class T, std::size_t N, class RandomFunc>
	struct ShuffleArray
	{
	private:
		size_t dividerIdx; // Index from which the list is unsorted
		uintmax_t shuffleCount; // Increments on each shuffle

		std::array<CustomIndex, N> indices; // maps index to data
		std::array<T, N> data;

		RandomFunc& r;

	public:
		ShuffleArray(RandomFunc&& r) : dividerIdx(N), shuffleCount(0), indices(), data(), r(r) {
			for (size_t i = 0; i < N; ++i) {
				indices[i] = CustomIndex(i);
			}
		}

	private:
		
		// Update index if shuffled since last access
		void updateIdx(size_t idx) {
			CustomIndex& ci = indices[idx];

			// if already up-to-date do nothing
			if (ci.lastAccess == shuffleCount)
				return;

			std::uniform_int_distribution<size_t> distr(dividerIdx, N - 1ul);
			size_t newData = distr(r);

			if (newData != dividerIdx)
				std::swap(data[dividerIdx], data[newData]);

			ci.idx = dividerIdx;
			ci.lastAccess = shuffleCount;
			++dividerIdx;
		}

	public:

		T& at(size_t pos) {
			if (pos >= N)
				throw std::out_of_range("Index out of range.");

			return (*this)[pos];
		}

		T& operator[](size_t pos) {
			updateIdx(pos);
			return data[indices[pos].idx];
		}

		T& front() {
			return (*this)[0];
		}

		T& back() {
			return (*this)[N - 1];
		}

		constexpr bool empty() {
			return N == 0;
		}

		constexpr size_t size() {
			return N;
		}

		constexpr size_t max_size() {
			return N;
		}

		constexpr void fill(const T& value) {
			data.fill(value);
		}

		void shuffle() {
			++shuffleCount;
			dividerIdx = 0;
		}
	};
}
