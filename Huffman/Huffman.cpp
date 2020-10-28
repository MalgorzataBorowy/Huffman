// Huffman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Huffman_func.h"

using namespace std;

void printTree(Node* root, string b)
{
	if (root->left != NULL)
	{
		printTree(root->left, b = "0");
		cout << root->letter << b;
		printTree(root->right, b = "1");
	}
}

int main()
{
	string text = readFile("tekst.txt");
	int size = countOccur(text);

	vector<Node *> nodes;
	fillList(text, &nodes);
	bubbleSort(&nodes);
	Node* root = makeTree(&nodes);
	string codedText = codeText(text, root);
	writeToFile(codedText, "tekst(1).bin");
	//printTree(root, "");

	   
}