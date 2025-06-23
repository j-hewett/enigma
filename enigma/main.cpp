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
#include "enigma.h"


int main()
{
	std::unordered_map<char, char> swaps = {
		{'A', 'R'},
		{'G', 'K'},
		{'O', 'X'}
	};

	const enigma::Plugboard plugboard(swaps);

	const enigma::Rotor rotor_I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q');
	const enigma::Rotor rotor_II("AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E');
	const enigma::Rotor rotor_III("BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V');

	const enigma::Reflector reflector_A("EJMZALYXVBWFCRQUONTSPIKHGD");
	const enigma::Reflector reflector_B("YRUHQSLDPXNGOKMIEBFZCWVJAT");
	const enigma::Reflector reflector_C("FVPJIAOYEDRZXWGCTKUQSBNMHL");


	char input = 'H';
	int input_pos = enigma::to_index(input);

	int signal = plugboard.swap(input_pos);

	signal = rotor_III.swap_forward(signal);
	signal = rotor_II.swap_forward(signal);
	signal = rotor_I.swap_forward(signal);

	signal = reflector_A.reflect(signal);

	signal = rotor_I.swap_backward(signal);
	signal = rotor_II.swap_backward(signal);
	signal = rotor_III.swap_backward(signal);

	signal = plugboard.swap(signal);

	char output = enigma::to_char(signal);

	std::cout << "Input: " << input << '\n' << "Output: " << output << std::endl;
}