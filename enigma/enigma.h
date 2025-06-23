#pragma once

#include <array>
#include <string>
#include <unordered_map>

namespace enigma {

	int to_index(char c);
	char to_char(int i);

	class Plugboard {
	public:
		std::array<int, 26> swaps;
		Plugboard(const std::unordered_map<char, char>& swap_map);
		int swap(int input_position) const;
	};

	class Rotor {
	public:
		char notch;
		std::array<int, 26> wiring;
		Rotor(const std::string& wiring_str, const char rotor_notch);
		int swap_forward(int input_position) const;
		int swap_backward(int input_position) const;
	};

	class Reflector {
	public:
		std::array<int, 26> wiring;
		Reflector(const std::string& wiring_str);
		int reflect(int input_position) const;
	};

} // namespace enigma