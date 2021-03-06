#include "File_operations.h"

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

string readBinFile(string fileName)
{
	string text = "", line;
	fstream file;
	file.open(fileName, ios::in | ios::binary | ios::ate);
	vector<char> buffer;
	vector<char> bits;
	if (file.good() == true)
	{
		int size = file.tellg();
		file.seekg(0, ios::beg);
		buffer.resize(size);
		bits.resize(size*10);
		file.read(buffer.data(), size);
		cout.write(buffer.data(), buffer.size());

		for (int i = 0; i < buffer.size() * 8; i++) {
			bits[i] = ((1 << (i % 8)) & (buffer[i / 8])) >> (i % 8);
		}

		for (auto i = bits.begin(); i != bits.end(); i++)
		{
			if (*i == '\0')
				*i = '0';
			else if (*i == '\x1')
				*i = '1';
			text += *i;
		}
		cout << text;
	}
	else
		cout << "Brak dostepu do pliku" << endl;

	file.close();
	return text;
}

void writeFile(string text, string fileName)
{
	fstream file;
	file.open(fileName, ios::out);
	if (file.good() == true)
		file << text;
	else
		cout << "Brak dostepu do pliku" << endl;

	file.close();
}

void writeBinFile(string text, string fileName)
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

void saveToDictionary(Node* root, vector<char>* tab)
{
	Node* tree = root;
	vector<string> codes(tab->size());
	vector<char>* letters = tab;
	string text = "";
	for (int i = 0; i < tab->size(); i++)
	{
		codeLetter(letters->at(i), tree, "", codes[i]);
		text += letters->at(i) + codes[i] + '\n';
	}

	fstream file;
	file.open("dictionary.txt", ios::out);
	if (file.good() == true)
		file << text;
	else
		cout << "Brak dostepu do pliku" << endl;

	file.close();
}