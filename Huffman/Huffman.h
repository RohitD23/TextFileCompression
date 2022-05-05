#pragma once
#include <vector>
#include <string>
#include <queue>

struct Node {
	char data;
	unsigned int freq;
	Node *left, *right;
	std::string code;

	Node()
	{
		data = '\0';
		freq = 0;
		left = nullptr;
		right = nullptr;
	}
};

class Huffman
{
public:
	Huffman(const std::string& in, const std::string& out);

	void Compress();

private:
	std::vector<Node*> m_Arr;
	Node* m_Root;
	std::string m_InFilename;
	std::string m_OutFilename;

	struct Compare {
		bool operator()(Node* l, Node* r)
		{
			return l->freq > r->freq;
		}
	};

	std::priority_queue<Node*, std::vector<Node*>, Compare> m_MinHeap;

private:
	void InitializeArr();

	void CreateMinHeap();
	void CreateTree();
	void CreateCodes();
	int binToDec(std::string inStr);
	void SaveEncodedFile();

	void traverse(Node* r, const std::string& s);
};

