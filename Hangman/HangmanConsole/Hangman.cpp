#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

void game(string);
bool isCharInside(string, char);
string makeWordSecret(string);
vector<string> readWordsFromFile(string);
string pickRandomWord(vector<string>);

int main()
{
	char input;
	while (true) 
	{
		cout << "Witaj w grze w wisielca." << endl;
		cout << "Chcesz zagrac? y/n" << endl;
		cin >> input;
		input = tolower(input);
		if (input == 'y')
		{
			vector<string> words = readWordsFromFile("slowa.txt");
			string word = pickRandomWord(words);

			//testowe printowanie
			//for (int i = 0; i < words.size(); i++)
			//{
			//	cout << "index = " << i << " " << words[i] << endl;
			//}

			//cout << word << endl;
			game(word);
		}
		else if (input == 'n') 
		{
			break;
		}
		else 
		{
			cout << "Nie zrozumialem :(" << endl;
		}
	}
}

void game(string randomWord) 
{
	int guessCounter = randomWord.size();

	cout << "Wylosowane slowo ma " << randomWord.size() << " liter" << endl;

	string secretWord = makeWordSecret(randomWord);

	while(true) 
	{
		if(secretWord == randomWord) 
		{
			cout << "Wylosowanym slowem bylo: " << randomWord << "." << " Wygrales!" << endl;
			break;
		}
		else if (guessCounter == 0) 
		{
			cout << "Wylosowanym slowem bylo: " << randomWord << "." << " Przegrales!" << endl;
			break;
		}

		cout << "Zostalo Ci " << guessCounter << " prob" << endl;
		char playerInput;
		cin >> playerInput;
		playerInput = tolower(playerInput);
		if (playerInput == 'q')
		{
			break;
		}
		if (isCharInside(randomWord, playerInput)) 
		{
			for (int i = 0; i < randomWord.size(); i++)
			{
				if (randomWord[i] == playerInput)
				{
					secretWord[i] = playerInput;
				}
			}		
		}
		else 
		{
			guessCounter--;
		}
		cout << secretWord << endl;
	}
}

// funkcja boolowska sprawdzajaca czy litera jest w wylosowanym slowie
bool isCharInside(string word, char character) 
{
	return word.find(character) != string::npos;
}

// funkcja zwracajaca stringa zlozonego z gwiazdek, o dlugosci wylosowanego slowa
string makeWordSecret(string randomWord) 
{
	string secretWord;

	for (int i = 0; i < randomWord.size(); i++) 
	{
		secretWord.push_back('*');
	}

	return secretWord;
}

// funkcja wczytujaca wyrazy z pliku linijka po linijce slowo po slowie; zwraca liste slow
vector<string> readWordsFromFile(string path) 
{
	ifstream fileStream(path);
	string word, line;
	vector<string> wordsList;

	if(!fileStream.is_open()) 
	{
		cout << "Nie udalo otworzyc sie pliku." << endl;
	}

	while(fileStream >> ws, getline(fileStream, line))
	{
		stringstream ss(line);

		while(getline(ss, word, ','))
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			wordsList.push_back(word);
		}
	}
	fileStream.close();
	
	return wordsList;
}

// funkcja wybierajaca losowe slowo z listy slow
string pickRandomWord(vector<string> words) 
{
	random_device randomDevice;

	auto rng = default_random_engine{randomDevice()};
	shuffle(begin(words), end(words), rng);

	string randomWord = words[0];

	return randomWord;
}