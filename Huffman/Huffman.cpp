// Huffman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
	Node* left;
	Node* right;
	int count;
	char letter;
};

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

void makeList(string text, Node* ptr)
{

}
void bubbleSort(Node* tab, int n)
{
	bool swapped; // Czy zamieniono w ostatnim obrocie?

	do {
		swapped = false;
		for (int i = 0; i < n - 1; ++i) {
			if (tab[i].count < tab[i + 1].count) {
				swap(tab[i], tab[i + 1]);
				swapped = true;
			}
		}
	} while (swapped);
}

int main()
{

	string text = readFile("tekst.txt");
	/*struct Node nodes[256];
	struct Node* nodePtr = &nodes[0];
	makeList(text, nodePtr);*/


	struct Node nodes[256];
	struct Node* ptr = &nodes[0];
	for (int i = 0; i < 256; i++)
	{
		struct Node n = { NULL, NULL, 0, NULL };
		nodes[i] = n;
	}


	for (int i = 0; i < text.length(); i++)
	{
		bool flag = false;
		for (int j = 0; j < 256; j++)
		{
			if (nodes[j].letter == text[i])
			{
				nodes[j].count++;
				flag = true;
			}
		}
		if (!flag)
		{
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->count = 1;
			ptr->letter = text[i];
			ptr++;
		}
	}

	bubbleSort(nodes, 256);


	for (int i = 0; i < 256; i++)
	{
		cout << "Letter: " << nodes[i].letter << "; count: " << nodes[i].count << endl;
	}



}