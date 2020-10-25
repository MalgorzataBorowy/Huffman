// Huffman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
void printVector(vector<Node>* tab)
{
	Node* ptr = &tab->front();

	for (int i = 0; i < tab->size(); i++)
	{
		cout << ptr->letter << ptr->count <<" ";
		ptr++;
	}
	cout<<endl;
}

Node* makeTree(vector<Node>* tab)
{
	vector<Node>* ptr = tab;
	Node* root = &(ptr->back());
	Node* first = NULL;
	Node* second = NULL;
	while (ptr->size() > 1)
	{
		first = &(ptr->back());
		ptr->pop_back();
		second = &(ptr->back());
		ptr->pop_back();
		root = new Node;
		root->left = first;
		root->right = second;
		root->count = first->count + second->count;
		root->letter = NULL;
		//struct Node n = { first, second, first->count + second->count, NULL };
		//ptr->insert(upper_bound(ptr->begin(), ptr->end(),root,),root);
		for (int i = 0; i < ptr->size(); i++)
		{
			if ((ptr->begin() + i)->count < root->count)
			{
				ptr->insert(ptr->begin()+i, *root);
				break;
			}
		}
		if (ptr->size() < 1)
		{
			ptr->insert(ptr->begin(), *root);
		}
		//ptr->push_back(*root);
		//bubbleSort(ptr);
		printVector(ptr);
	}
	root = &(ptr->back());
	return  root;
}

void printTree(Node* root)
{
	if (!root->left) cout << root->letter << " "<< root->count<<endl;
	else
	{
		cout << root->letter << " " << root->count << endl;
		printTree(root->left);
		printTree(root->right);
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

	vector<Node> nodes;
	//vector<>
	fillList(text, &nodes);
	bubbleSort(&nodes);

	Node* root = makeTree(&nodes);

	printVector(&nodes);


}