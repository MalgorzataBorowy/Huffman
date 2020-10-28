#include "Huffman_func.h"

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

void writeToFile(string text, string fileName)
{
	fstream file;
	char* buffer = new char[text.length()];
	file.open(fileName, ios::out | ios::binary);
	if (file.good() == true)
	{
		unsigned char buffer = 0;
		int count = 0;
		int i = 0;
		while (text[i] != '\0')
		{
			buffer = buffer | ((text[i++] - '0') << (7 - count));
			count++;
			if (count == 8)
			{
				count = 0;
				file << buffer;
				buffer = 0;
			}
		}
		if (count != 0)
			file << buffer;

	}
	file.close();
}

int countOccur(string text)
{
	int count = 0;
	char tab[256] = { 0 };
	for (int i = 0; i < text.length(); i++)
	{
		bool exists = false;
		for (int j = 0; j < count + 1; j++)
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
		cout << (*ptr)->letter << (*ptr)->count << " ";
		ptr++;
	}
	cout << endl;
}

void fillList(string text, vector<Node *> *tab)
{
	vector<Node*>* ptr = tab;

	for (int i = 0; i < text.length(); i++)
	{
		bool exists = false;
		for (int j = 0; j < ptr->size(); j++)
		{
			if (ptr->at(j)->letter == text[i])
			{
				ptr->at(j)->count++;
				exists = true;
				break;
			}
		}
		if (!exists)
		{
			Node* n = NULL;
			n = new Node;
			n->left = NULL;
			n->right = NULL;
			n->count = 1;
			n->letter = text[i];

			//struct Node n = { NULL, NULL, 1, text[i] };
			ptr->push_back(&*n);
		}
	}
}

void bubbleSort(vector<Node*>* tab)
{
	bool swapped; // Czy zamieniono w ostatnim obrocie?
	Node** ptr = &tab->front();

	do {
		swapped = false;
		ptr = &tab->front();
		for (int i = 0; i < tab->size() - 1; ++i) {
			if ((*ptr)->count < (*(ptr + 1))->count) {
				swap(*ptr, *(ptr+1));
				swapped = true;
			}
			ptr++;
		}
	} while (swapped);
}

Node* makeTree(vector<Node*>* tab)
{
	vector<Node*>* ptr = tab;
	Node** root = &(ptr->back());
	Node** first = NULL;
	Node** second = NULL;
	while (ptr->size() > 1)
	{
		first = &(ptr)->back();
		ptr->pop_back();
		second = &(ptr)->back();
		ptr->pop_back();
		Node* n = new Node;
		n->left = *first;
		n->right = *second;
		n->count = (*first)->count + (*second)->count;
		n->letter = NULL;

		ptr->push_back(*&n);
		bubbleSort(ptr);
	}
	root = &(ptr->back());
	return  *root;
}

bool codeLetter(char letter, Node* root, string code, string &retCode)
{
	if (!root->left)
	{
		if (letter != root->letter) return false;
		else
		{
			retCode = code;
			return true;
		}
	}
	else
		return codeLetter(letter, root->left, code + "0", retCode) || codeLetter(letter, root->right, code + "1", retCode);
}

string codeText(string text, Node* root)
{
	string codedText = "";
	for (int i = 0; i < text.length(); i++)
	{
		string code = "";
		bool codeed = codeLetter(text[i], root, "", code);
		codedText = codedText + code;
	}
	return codedText;
}