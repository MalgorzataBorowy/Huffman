#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node
{
	Node* left;
	Node* right;
	int count;
	char letter;
};
void fillList(string text, vector<Node*>* tab);
void bubbleSort(vector<Node*>* tab);
Node** makeTree(vector<Node*>* tab);