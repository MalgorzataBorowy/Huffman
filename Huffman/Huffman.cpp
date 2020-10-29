// Huffman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<map>
#include "Huffman_func.h"

using namespace std;

int main(int argc, char* argv[])
{
	string fileName = "tekst.txt";
	string newFileName = "comptext.txt";
	string dictFileName = "dictionary.txt";
	char mode = NULL;

	if (argc <= 1)
	{
		cout << "Dostepne opcje: " << endl;
		cout << "-i plik wejsciowy \n-o plik wyjsciowy \n-t tryb: k-kompresja, d-dekompresja \n-s plik ze slownikiem";
	}
	else
	{	
		for (int i = 0; i < argc; i++) 
		{
			//cout << argv[i] << " - " << i << "\n";
			if (strcmp(argv[i], "-i") == 0 && argv[i + 1])
				fileName = argv[i + 1];
			if (strcmp(argv[i], "-o") == 0 && argv[i + 1])
				newFileName = argv[i + 1];
			if (strcmp(argv[i], "-d") == 0 && argv[i + 1])
				dictFileName = argv[i + 1];
			if (strcmp(argv[i], "-t") == 0 && argv[i + 1])
				mode = (char)argv[i + 1];

		}

		switch (mode)
		{
		case('k'):

			break;
		case('d'):

			break;
		default:
			break;
		}



		/*if (argc > 1 && strcmp(argv[1], "-c") == 0) 
		{
				cout << "It works!\n";
		}*/
	}

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
	return 0;
}