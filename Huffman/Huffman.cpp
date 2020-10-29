// Huffman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<map>
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

int main(int argc, char* argv[], char* envp[])
{
	string text = readFile("tekst.txt");
	int size = countFrequency(text);

	vector<Node *> nodes;
	fillList(text, &nodes);
	bubbleSort(&nodes);


	vector<char> letterList;
	for (int i = 0; i < nodes.size(); i++)
	{
		letterList.push_back(nodes[i]->letter);
	}

	Node* root = makeTree(&nodes);
	string codedText = codeText(text, root);
	writeToFile(codedText, "tekst(1).txt");
	saveToDictionary(root, &letterList);
	string decodedText = decodeText(codedText, "dictionary.txt");
	cout << decodedText<< endl;	   
}