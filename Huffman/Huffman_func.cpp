#include "Huffman_func.h"

int countFrequency(string text)
{
	int count = 0;
	char tab[256] = { 0 };
	for (int i = 0; i < text.length(); i++)
	{
		bool exists = false;
		for (int j = 0; j < count + 1; j++)
		{
			if (tab[j] == text[i])
				exists = true; break;
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
		Node *n = new Node;
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

string decodeText(string codedText, Node* root)
{
	string decodedText = "";
	Node* node = root;
	for (int i = 0; i < codedText.length(); i++)
	{
		if (codedText[i] == '0')
		{
			node = node->left;
		}
		else if (codedText[i] == '1')
		{
			node = node->right;
		}
		if (!node->left && !node->right)
		{
			decodedText += node->letter;
			node = root;
		}
	}
	decodedText += "\0";
	return decodedText;
}

string decodeText(string codedText, string dictFileName)
{
	vector<char> letters;
	vector<string> codes;
	string retText;
	fstream file;
	file.open(dictFileName, ios::in);
	if (file.good() == true)
	{
		string line;
		do
		{
			getline(file, line);
			letters.push_back(line[0]);
			codes.push_back("");

			for (int i = 1; i < line.length(); i++)
				codes.back() += line[i];

		} while (line != "\0");
	}
	else
		cout << "Brak dostepu do pliku" << endl;

	string codedLetter = "";
	for (int i = 0; i < codedText.size(); i++)
	{
		codedLetter += codedText[i];
		for (int j = 0; j < codes.size(); j++)
		{
			if (codedLetter == codes[j])
			{
				retText += letters[j];
				codedLetter = "";
				break;
			}
		}
	}
	return retText;
}
