#include "Huffman_func.h"

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

Node** makeTree(vector<Node*>* tab)
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
	return  root;
}