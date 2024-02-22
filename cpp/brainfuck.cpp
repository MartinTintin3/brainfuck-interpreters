#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

int main(int argc, char * argv[]){
    if (argc < 1) {
		std::cerr << "Input file needed\n";
		exit(-1);
	}

	std::ifstream file(argv[1]);
	
	uint8_t buffer[30000] = {0};

	const uintmax_t input_size = std::filesystem::file_size(argv[1]);

	char* input = new char[input_size];

	uint16_t i = 0;
	uint16_t d = 0;

	char c;
	for (; file.get(c); i++) input[i] = c;

	file.close();

	for (i = 0; i < input_size; i++) {
		switch (input[i]) {
			case '>':
				d++;
				break;
			case '<':
				d--;
				break;
			case '+':
				buffer[d]++;
				break;
			case '-':
				buffer[d]--;
				break;
			case '.':
				std::cout << buffer[d];
				break;
			case ',':
				buffer[d] = getchar_unlocked();
				if ((char)buffer[d] == EOF || buffer[d] == 10) buffer[d] = 0;
				break;
			case '[':
				if (buffer[d] == 0) {
					unsigned int counter = 1;
					while (counter > 0) {
						if (i == input_size) {
							std::cerr << "Unmatched '['\n";
							exit(-1);
						}
						i++;
						if (input[i] == '[') counter++;
						else if (input[i] == ']') counter--;
					}
				}
				break;
			case ']':
				if (buffer[d] != 0) {
					unsigned int counter = 1;
					while (counter > 0) {
						if (i == 0) {
							std::cerr << "Unmatched ']'\n";
							exit(-1);
						}
						i--;
						if (input[i] == '[') counter--;
						else if (input[i] == ']') counter++;
					}
				}
				break;
			default:
				break;
		}
	}

	delete[] input;

    return 0;
}