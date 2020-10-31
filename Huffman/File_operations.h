#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Huffman_func.h"
using namespace std;

string readFile(string fileName);
void writeFile(string text, string fileName);
void writeBinFile(string text, string fileName);
void saveToDictionary(Node* root, vector<char>* tab);