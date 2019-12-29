#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

vector<string> readWordsFromFile(string);
string pickRandomWord(vector<string> words);

int main()
{
	vector<string> words = readWordsFromFile("slowa.txt");
	string word = pickRandomWord(words);

	for (int i = 0; i < words.size(); i++) 
	{
		cout << "index = " << i << " " << words[i] << endl;
	}

	//cout << words.size() << endl;

	//cout << word;
}


// funkcja wczytujaca wyrazy z pliku linijka po linijce slowo po slowie; zwraca liste slow
vector<string> readWordsFromFile(string path) 
{
	ifstream fileStream(path);
	string word, line;
	vector<string> wordsList;

	if (!fileStream.is_open()) 
	{
		cout << "Nie udalo otworzyc sie pliku." << endl;
	}

	while (fileStream >> ws, getline(fileStream, line))
	{
		stringstream ss(line);

		while (getline(ss, word, ','))
		{
			wordsList.push_back(word);
		}
	}
	fileStream.close();
	
	return wordsList;
}

// funkcja wybierajaca losowe slowo z listy slow; jeszcze nie dziala
string pickRandomWord(vector<string> words) 
{
	int size = words.size();
	string randomWord;

	auto rng = default_random_engine{};
	shuffle(begin(words), end(words), rng);

	randomWord = words[0];

	return randomWord;
}