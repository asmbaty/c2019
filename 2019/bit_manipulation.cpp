// Bit Manipulation
#include <iostream>
#include <bitset>

// Remove the rightmost bit
// i.e 1110011 -> 1110010, 11000 -> 10000
template<typename T>
T remove_the_rightmost_bit(T n)
{
	static_assert(std::is_integral<T>::value && !std::is_signed<T>::value, "type should be an unsigned integer");
	return n & (n - 1);
}

// Returns an unsigned value with all bits set
template<typename T>
constexpr T all_1()
{
	static_assert(std::is_integral<T>::value && !std::is_signed<T>::value, "type should be an unsigned integer");
	return T(-1);
}

template<typename T>
T toggle_bit(T n, int idx)
{
	static_assert(std::is_integral<T>::value && !std::is_signed<T>::value, "type should be an unsigned integer");
	return n ^ (T(1) << idx);
}

// more
// set bit: number |= 1 << x;
// clear bit: number &= ~(1 << x);
// change nth bit to x: ^= (-x ^ number) & (1 << n);


template<typename T>
unsigned number_of_bits(T n)
{
	static_assert(std::is_integral<T>::value && !std::is_signed<T>::value, "type should be an unsigned integer");
	unsigned bits = 0;
	for (; n; ++bits) {
		n &= (n - 1);
	}
	return bits;
}

bool is_power_of_2(int n)
{
	return n && !(n & (n - 1)); // n is not zero; last bit removed results zero
}

int main()
{
	std::cout << remove_the_rightmost_bit(16u) << '\n'; // 0

	unsigned int r = -1;
	while (r != 0u) {
		std::cout << std::bitset<32>(r) << '\n';
		r = remove_the_rightmost_bit(r);
	}

	auto b32 = all_1<unsigned int>();
	auto b64 = all_1<unsigned long long>();
	std::cout << std::bitset<8 * sizeof(b64)>(b64) << std::endl;

	b64 = toggle_bit(b64, 34);
	std::cout << std::bitset<8 * sizeof(b64)>(b64) << std::endl;

	std::cout << "number of bits in the last number: " << number_of_bits(b64) << std::endl;

	return 0;
}