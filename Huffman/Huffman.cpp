#include "Huffman.h"

#include <fstream>

Huffman::Huffman(const std::string& in, const std::string& out)
	: m_Root(nullptr), m_InFilename(in), m_OutFilename(out)
{
	m_Arr.resize(128);
	InitializeArr();
}

void Huffman::InitializeArr()
{
	for (int i = 0; i < 128; i++)
	{	
		m_Arr[i] = new Node();
		m_Arr[i]->data = i;
	}
}

void Huffman::Compress()
{
	CreateMinHeap();
	CreateTree();
	CreateCodes();
	SaveEncodedFile();
}

void Huffman::CreateMinHeap()
{
	std::fstream stream(m_InFilename, std::ios::in);

	char c;
	while (stream.get(c))
	{
		m_Arr[c]->freq++;
	}

	stream.close();

	for (int i = 0; i < 128; i++)
	{
		if(m_Arr[i]->freq > 0)
			m_MinHeap.push(m_Arr[i]);
	}
}

void Huffman::CreateTree()
{
	std::priority_queue <Node*, std::vector<Node*>, Compare> tempPQ(m_MinHeap);

	while (tempPQ.size() != 1)
	{
		Node* left = tempPQ.top();
		tempPQ.pop();

		Node* right = tempPQ.top();
		tempPQ.pop();

		m_Root = new Node();
		m_Root->left = left;
		m_Root->right = right;
		m_Root->freq = left->freq + right->freq;

		tempPQ.push(m_Root);
	}
}

void Huffman::CreateCodes()
{
	traverse(m_Root, "");
}

int Huffman::binToDec(std::string inStr) {
	int res = 0;
	for (auto c : inStr) {
		res = res * 2 + c - '0';
	}
	return res;
}

void Huffman::SaveEncodedFile()
{
	std::fstream inFile(m_InFilename, std::ios::in);
	std::fstream outFile(m_OutFilename, std::ios::out);
	std::string in = "";
	std::string s = "";
	char id;

	std::priority_queue <Node*, std::vector<Node*>, Compare> tempPQ(m_MinHeap);
	while (!tempPQ.empty())
	{
		Node* curr = tempPQ.top();
		tempPQ.pop();

		in += curr->data;
		in += (char)binToDec(curr->code);
	}

	in += (char)-1;

	//Saving codes of every charachter appearing in the input file
	while (inFile.get(id)) {
		s += m_Arr[id]->code;
		//Saving decimal values of every 8-bit binary code
		while (s.length() > 8) {
			in += (char)binToDec(s.substr(0, 8));
			s = s.substr(8);
		}
	}

	//Finally if bits remaining are less than 8, append 0's
	int count = 8 - s.length();
	if (s.length() < 8) {
		s.append(count, '0');
	}
	in += (char)binToDec(s);
	//append count of appended 0's
	in += (char)count;

	//write the in string to the output file
	outFile.write(in.c_str(), in.size());
	inFile.close();
	outFile.close();
}

void Huffman::traverse(Node* r, const std::string& s)
{
	if (!r->left && !r->right)
	{
		r->code = s;
		return;
	}

	traverse(r->left, s + '0');
	traverse(r->right, s + '1');
}
