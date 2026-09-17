#pragma once
#include <cstddef>
#include <array>
using namespace std;

//namespace nn makes sure the code inside of it is exclusive to its scope, and most importantly prevents name collisions. can be accessed with nn::
namespace nn {
	template <typename T, size_t Rows, size_t Cols>
	class matrix final{
	public:
		static_assert(Rows > 0U, "Matrix must have at least 1 row");
		static_assert(Cols > 0U, "Matrix must have at least 1 column");

		static constexpr size_t rows = Rows;
		static constexpr size_t cols = Cols;
		static constexpr size_t totalElements = Rows * Cols;

		constexpr matrix() noexcept = default;
		// two overloads of operator() — one returning T&, one returning const T&. Both constexpr, both noexcept.
		[[nodiscard]] constexpr T& operator()(size_t r, size_t c) noexcept {
			return data[index(r, c)];
		}

		[[nodiscard]] constexpr const T& operator()(size_t r, size_t c) const noexcept {
			return data[index(r, c)];
		}


	private:
		array<T, totalElements> data{};

		// row-major flattening. Given (r, c), return the flat index.
		[[nodiscard]] static constexpr size_t index(size_t r, size_t c) noexcept {
			return (r * Cols) + c;
		}


	};

	template <typename T, size_t M, size_t K, size_t N>
	[[nodiscard]] constexpr matrix<T, M, N> operator*(const matrix<T, M, K>& a, const matrix<T, K, N>& b) noexcept {
		matrix<T, M, N> result{};
		for (size_t i = 0; i < M; ++i) {//Row of the output, also which row of matrix a
			for (size_t j = 0; j < N; ++j) {//Col of output, also which col of matrix b
				T sum = T{};//means "a zero of whatever type T is" Written that way so it works for any T
				for (size_t l = 0; l < K; ++l) {//steps along row i of a and down column matrix j of matrix b
					sum += a(i, l) * b(l, j);
				}//inner(K)

				result(i, j) = sum;

			}//middle(N)

		}//outer(M)
		return result;
	}

	template<typename T, size_t Rows, size_t Cols>
	[[nodiscard]] constexpr matrix<T, Rows, Cols> operator+(const matrix<T, Rows, Cols>& a, const matrix<T, Rows, Cols>& b) noexcept {
		matrix<T, Rows, Cols> result{};

		for (size_t i = 0; i < Rows; ++i) {
			for (size_t j = 0; j < Cols; ++j) {
				result(i, j) = a(i, j) + b(i, j);
			}
		}
		return result;
	}

	//scalar activation function
	template <typename T>
	[[nodiscard]] constexpr T relu(T x) noexcept {
		if (x > T{}) {
			return x;
		}
		else {
			return T{};
		}
	}

	//matrix  activation function
	template<typename T, size_t Rows, size_t Cols>
	[[nodiscard]] constexpr matrix <T, Rows, Cols> relu(const matrix<T, Rows, Cols> &m) noexcept {
		matrix<T, Rows, Cols> result{};
		for (size_t i = 0; i < Rows; ++i) {
			for (size_t j = 0; j < Cols; ++j) {
				result(i, j) = relu(m(i, j));
			}
		}
		return result;
	}
}