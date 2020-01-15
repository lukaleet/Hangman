#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

void game(string);
void printHangman(int guessCounter);
string changeLetters(string, string, string);
bool isCharInside(string, string);
string makeWordSecret(string);
vector<string> readWordsFromFile(string);
string pickRandomWord(vector<string>);

int main()
{
	char input;
	cout << "Witaj w grze w wisielca." << endl;
	while (true) 
	{
		cout << "Chcesz zagrac? y/n" << endl;
		cin >> input;
		input = tolower(input);
		if (input == 'y')
		{
			system("cls");
			vector<string> words = readWordsFromFile("slowa.txt");
			string word = pickRandomWord(words);

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
	int guessCounter = 0;
	int amountOfGuesses = 6;

	cout << "Wylosowane slowo ma " << randomWord.size() << " liter" << endl;
	cout << "(Jesli chcesz opusic trwajaca gre wpisz 'q')" << endl;

	string secretWord = makeWordSecret(randomWord);

	while(true) 
	{
		if(secretWord == randomWord) 
		{
			cout << "Wylosowanym slowem bylo: " << randomWord << "." << " Wygrales!" << endl;
			break;
		}
		else if (guessCounter == 6) 
		{
			cout << "Wylosowanym slowem bylo: " << randomWord << "." << " Przegrales!" << endl;
			break;
		}

		cout << "Zostalo Ci " << amountOfGuesses << " prob" << endl;
		string playerInput;
		cin >> playerInput;

		// input na male litery
		transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::tolower);
		if (playerInput == "q")
		{
			system("cls");
			break;
		}
		if (isCharInside(randomWord, playerInput)) 
		{
			secretWord = changeLetters(randomWord, secretWord, playerInput);
		}
		else 
		{
			amountOfGuesses--;
			guessCounter++;
			printHangman(guessCounter);
		}
		cout << secretWord << endl;
	}
}

void printHangman(int guessCounter)
{
	{
		switch (guessCounter)
		{
		case 6:
			cout << endl << endl
				<< "   +----+     " << endl
				<< "   |    |     " << endl
				<< "   |    O     " << endl
				<< "   |   /|\\   " << endl
				<< "   |   / \\   " << endl
				<< "   |Przegrales " << endl
				<< "  ============" << endl << endl;
			break;

		case 5:
			cout << endl << endl
				<< "   +----+  " << endl
				<< "   |    |  " << endl
				<< "   |    O  " << endl
				<< "   |   /|\\ " << endl
				<< "   |     \\ " << endl
				<< "   |       " << endl
				<< "  ============" << endl << endl;
			break;

		case 4:
			cout << endl << endl
				<< "   +----+  " << endl
				<< "   |    |  " << endl
				<< "   |    O  " << endl
				<< "   |   /|\\ " << endl
				<< "   |       " << endl
				<< "   |       " << endl
				<< "  =============" << endl << endl;
			break;

		case 3:
			cout << endl << endl
				<< "   +----+  " << endl
				<< "   |    |  " << endl
				<< "   |    O  " << endl
				<< "   |   /|  " << endl
				<< "   |       " << endl
				<< "   |       " << endl
				<< "  =============" << endl << endl;
			break;

		case 2:
			cout << endl << endl
				<< "   +----+  " << endl
				<< "   |    |  " << endl
				<< "   |    O  " << endl
				<< "   |    |  " << endl
				<< "   |       " << endl
				<< "   |       " << endl
				<< "  =============" << endl << endl;
			break;

		case 1:
			cout << endl << endl
				<< "   +----+  " << endl
				<< "   |    |  " << endl
				<< "   |       " << endl
				<< "   |       " << endl
				<< "   |       " << endl
				<< "   |       " << endl
				<< "  =============" << endl << endl;
			break;
		}
	}
}

// funkcja zmieniajaca gwiazdki w stringu na input gracza
string changeLetters(string randomWord, string secretWord, string playerInput) 
{
	for (int i = 0; i < randomWord.size(); i++) 
	{
		for (int j = 0; j < playerInput.size(); j++) 
		{
			if (randomWord[i] == playerInput[j])
			{
				secretWord[i] = playerInput[j];
			}
		}
	}

	return secretWord;
}

// funkcja boolowska sprawdzajaca czy litera jest w wylosowanym slowie
bool isCharInside(string word, string character) 
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