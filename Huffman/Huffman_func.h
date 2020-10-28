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

string readFile(string fileName);
void writeToFile(string text, string fileName);
int countOccur(string text);
void printVector(vector<Node*>* tab);
void fillList(string text, vector<Node*>* tab);
void bubbleSort(vector<Node*>* tab);
Node* makeTree(vector<Node*>* tab);
bool codeLetter(char letter, Node* root, string code, string& retCode);
string codeText(string text, Node* root);