// Main.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "File_operations.h"
#include "Huffman_func.h"

using namespace std;

string readBinFile(string fileName)
{
	string text = "", line;
	fstream file;
	file.open(fileName, ios::in | ios::binary);
	if (file.good() == true)
	{

	}
	else
		cout << "Brak dostepu do pliku" << endl;

	file.close();
	return text;
}

int main(int argc, char* argv[])
{
	string fileName = "tekst.txt";
	string newFileName = "comptext.txt";
	string dictFileName = "dictionary.txt";
	char mode = NULL;

	if (argc == 1)
	{
		std::cout << "Dostepne opcje: " << endl;
		std::cout << "-i plik wejsciowy \n-o plik wyjsciowy \n-t tryb: k-kompresja, d-dekompresja \n-s plik ze slownikiem" << endl;
		std::cout << "Domyslna nazwa pliku wyjsciowego : comptext.txt \nDomyslna nazwa pliku slownika: dictionary.txt" << endl;
	}
	else
	{	
		for (int i = 0; i < argc; i++) 
		{
			if (strcmp(argv[i], "-i") == 0 && argv[i+1]!=NULL)
				fileName = argv[i + 1];
			if (strcmp(argv[i], "-o") == 0 && argv[i + 1] != NULL)
				newFileName = argv[i + 1];
			if (strcmp(argv[i], "-d") == 0 && argv[i + 1] != NULL)
				dictFileName = argv[i + 1];
			if (strcmp(argv[i], "-t") == 0 && argv[i + 1] != NULL)
				mode = *argv[i + 1];
		}

		switch (mode)
		{
		case('k'):
		{
			string text = readFile(fileName);
			if (text.length() < 1)
			{
				cout << "Nieprawidlowa sciezka pliku wejsciowego" << endl;
				break;
			}
			//int size = countFrequency(text);

			vector<Node*> nodes;
			fillList(text, &nodes);
			bubbleSort(&nodes);

			vector<char> letterList;
			for (int i = 0; i < nodes.size(); i++)
			{
				letterList.push_back(nodes[i]->letter);
			}

			Node* root = makeTree(&nodes);
			string codedText = codeText(text, root);
			writeBinFile(codedText, newFileName);
			saveToDictionary(root, &letterList);

			break;
		}

		case('d'):
		{	
			string codedText = readBinFile(fileName);
			string decodedText = decodeText(codedText, dictFileName);
			std::cout << decodedText<< endl;
			writeFile(decodedText, newFileName);
			break;
		}

		default:
		{
			cout << "Nierawidlowy tryb" << endl;
			break;
		}
		}
	}
	return 0;
}