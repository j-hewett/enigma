#include "enigma.h"
#include <algorithm>

namespace enigma {

	int to_index(char c) {
		return c - 'A';
	}

	char to_char(int i) {
		return 'A' + i;
	}

	Plugboard::Plugboard(const std::unordered_map<char, char>& swap_map) {
		for (int i = 0; i < 26; ++i)
			swaps[i] = i;
		for (const auto& pair : swap_map) {
			int pos_a = to_index(pair.first);
			int pos_b = to_index(pair.second);
			swaps[pos_a] = pos_b;
			swaps[pos_b] = pos_a;
		}
	}

	int Plugboard::swap(int input_position) const {
		if (input_position >= 0 && input_position < 26)
			return swaps[input_position];
		return input_position;
	}

	Rotor::Rotor(const std::string& wiring_str, const char rotor_notch) {
		notch = rotor_notch;
		for (int i = 0; i < 26; ++i)
			wiring[i] = to_index(wiring_str[i]);
	}

	int Rotor::swap_forward(int input_position) const {
		return wiring[input_position];
	}

	int Rotor::swap_backward(int input_position) const {
		auto it = std::find(wiring.begin(), wiring.end(), input_position);
		if (it != wiring.end())
			return static_cast<int>(it - wiring.begin());
		return -1;
	}

	Reflector::Reflector(const std::string& wiring_str) {
		for (int i = 0; i < 26; ++i)
			wiring[i] = to_index(wiring_str[i]);
	}

	int Reflector::reflect(int input_position) const {
		return wiring[input_position];
	}

} // namespace enigma