#include "Huffman.h"
#include <iostream>

int main()
{
	/*std::string inFile;
	std::string outFile;

	std::cout << "Enter file to Compress : ";
	std::cin >> inFile;

	std::cout << "Enter file name with address to save encoded file : ";
	std::cin >> outFile;*/

	Huffman h("C:/Users/rohit/OneDrive/Desktop/text.txt", "C:/Users/rohit/OneDrive/Desktop/out.cmp");
	h.Compress();

	return 0;
}