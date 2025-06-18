// Reflector: A
// Rotors: I-II-III
// Plugboard: A-R, G-K, O-X
// Key: 
// Ring setting:
// Message: A -> X

#include <unordered_map>
#include <iostream>
#include <array>
#include <string>

int to_index(char c) 
{
	return c - 'A';
}

char to_char(int i)
{
	return 'A' + i;
}

class Plugboard
{
public:
	std::array<int, 26> swaps;

public:

	Plugboard(const std::unordered_map<char, char>& swap_map)
	{
		for (int i = 0; i < 26; ++i)
		{
			swaps[i] = i;
		}

		for (const std::pair<char, char>& pair : swap_map)
		{
			int pos_a = to_index(pair.first);
			int pos_b = to_index(pair.second);
			swaps[pos_a] = pos_b;
			swaps[pos_b] = pos_a;
		}

	}

	int swap(int input_position) const
	{
		if (input_position >= 0 && input_position < 26)
		{
			return swaps[input_position];
		}
		return input_position; //return if not A-Z
	}
};

class Rotor
{
public:
	char notch;
	std::array<int, 26> wiring;

public:
	Rotor(const std::string& wiring_str, const char rotor_notch)
	{
		notch = rotor_notch;
		for (int i = 0; i < 26; ++i)
		{
			wiring[i] = to_index(wiring_str[i]);
		}
	}

	int swap_forward(int input_position) const
	{
		int letter_idx = wiring[input_position]; //Letter at position i
		return letter_idx;
	}

	int swap_backward(int input_position) const
	{
		auto it = std::find(wiring.begin(), wiring.end(), input_position);
		if (it != wiring.end())
			return static_cast<int>(it - wiring.begin());
		return -1;
	}
};

class Reflector
{
public:
	std::array<int, 26> wiring;
public:
	Reflector(const std::string& wiring_str)
	{
		for (int i = 0; i < 26; ++i)
		{
			wiring[i] = to_index(wiring_str[i]);
		}
	}

	int reflect(int input_position) const
	{
		int letter_idx = wiring[input_position];
		return letter_idx;
	}
};

int main()
{
	std::unordered_map<char, char> swaps = {
		{'A', 'R'},
		{'G', 'K'},
		{'O', 'X'}
	};

	const Plugboard plugboard(swaps);

	const Rotor rotor_I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q');
	const Rotor rotor_II("AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E');
	const Rotor rotor_III("BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V');

	const Reflector reflector_A("EJMZALYXVBWFCRQUONTSPIKHGD");
	const Reflector reflector_B("YRUHQSLDPXNGOKMIEBFZCWVJAT");
	const Reflector reflector_C("FVPJIAOYEDRZXWGCTKUQSBNMHL");


	char input = 'A';
	int input_pos = to_index(input);

	int signal = plugboard.swap(input_pos);

	signal = rotor_III.swap_forward(signal);
	signal = rotor_II.swap_forward(signal);
	signal = rotor_I.swap_forward(signal);

	signal = reflector_A.reflect(signal);

	signal = rotor_I.swap_backward(signal);
	signal = rotor_II.swap_backward(signal);
	signal = rotor_III.swap_backward(signal);

	signal = plugboard.swap(signal);

	char output = to_char(signal);

	std::cout << "Input: " << input << '\n' << "Output: " << output << std::endl;
}