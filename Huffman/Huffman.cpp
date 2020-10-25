// Huffman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Huffman_func.h"

using namespace std;

string readFile(string fileName)
{
	string text = "", line;
	fstream file;
	file.open(fileName, ios::in);
	if (file.good() == true)
	{
		do
		{
			getline(file, line);
			text += line;

		} while (line != "");
	}
	else
		cout << "Brak dostepu do pliku" << endl;

	file.close();
	return text;
}

int countOccur(string text)
{
	int count = 0;
	char tab[256] = { 0 };
	for (int i = 0; i < text.length(); i++)
	{
		bool exists = false;
		for (int j = 0; j < count+1; j++)
		{
			if (tab[j] == text[i])
			{
				exists = true;
				break;
			}
		}
		if (!exists)
		{
			tab[count] = text[i];
			count++;
		}
	}

	return count;
}
void printVector(vector<Node*>* tab)
{
	Node** ptr = &tab->front();

	for (int i = 0; i < tab->size(); i++)
	{
		cout << (*ptr)->letter << (*ptr)->count <<" ";
		ptr++;
	}
	cout<<endl;
}

void printTree(Node* root, string b)
{
	if (root->left != NULL)
	{
		printTree(root->left, b = "0");
		cout << root->letter << b;
		printTree(root->right, b = "1");
	}
}

string codeText(string text)
{
	return "";
}
string codeLetter(char letter, Node* root, string code)
{
	

	return code;
}


int main()
{
	string text = readFile("tekst.txt");
	int size = countOccur(text);

	vector<Node *> nodes;
	fillList(text, &nodes);
	bubbleSort(&nodes);
	Node** root = makeTree(&nodes);

	//printTree(*root, "");


}