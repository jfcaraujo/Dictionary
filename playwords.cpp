// PROGRAM 2 - Class 3 Group 10
// Carlos Manuel Coelho Nunes
// Joao Filipe Carvalho de Araujo

#include <iostream> // cout, cin, cerr
#include <fstream> // ifstream
#include <string> // string, getline, find, erase
#include <vector> //vector
#include <ctime> // time
#include <algorithm> // random_shuffle
using namespace std; // std::

string checkIfInputIsValid(string input); // See if the input of a string is valid
string convertToUpperCase(string input); // Put all input in Uppercase
bool checkIfWordExists(string input, vector<string> headlines); // See if the word input by the user exists in the file, only use for program1
bool wildcardMatch(const char *str, const char *strWild); // Implements a matching algorithm for two C-strings, one of which may have wildcards
void program1(vector<string> headlines); // Program 1 - Check if the word exists
void program2(vector<string> headlines); // Program 2 - Guess the scrambled word
void program3(vector<string> headlines); // Program 3 - Words which can be built with the letters given by the user"
void program4(vector<string> headlines); // Program 4 - Build a valid word with the given letters
void program5(vector<string> headlines); // Program 5 - Match the given wildcard string

int main()
{
	int choice; // Choose the program wanted
	bool validoperation = false; 
	vector<string> headlines; // Dictionary
	string line, filename;
	ifstream file;
	cout << "Welcome to PLAYWORDS" << endl;
	cout << "Name of dictionaty ? ", cin >> filename; // Input name of dictionary
	file.open(filename, fstream::in);  // Open dictionary
	if (file.fail())
	{
		cout << "File not found" << endl;
		return 0;
	} 
	cout << "Loading..." << endl;
	while (getline(file, line)) 
		headlines.push_back(line); // Send all the headlines, while existing, to variable of type string
	while (not (validoperation))
	{
		cout << "Programs: " << endl;
		cout << "1. Check if the word exists" << endl;
		cout << "2. Guess the scrambled word" << endl;
		cout << "3. Words which can be built with the letters given by the user" << endl;
		cout << "4. Build a valid word with the given letters" << endl;
		cout << "5. Match the given wildcard string" << endl;
		cout << "Please choose program (1-5): ", cin >> choice, cout << endl;

		if (cin.fail()) 
		{
			cin.clear();
			cin.ignore(100, '\n');
			choice = 10;
		}
		switch (choice) 
		{
		case 1:
			program1(headlines);
			validoperation = true;
			break;
		case 2:
			program2(headlines);
			validoperation = true;
			break;
		case 3:
			program3(headlines);
			validoperation = true;
			break;
		case 4:
			program4(headlines);
			validoperation = true;
			break;
		case 5:
			program5(headlines);
			validoperation = true;
			break;
		default: cout << "That is not a valid program. ";
		}
	}
	return 0;
}

// 1. Check if the word exists
void program1(vector<string> headlines) 
{
	bool wordExists = false; 
	string input;
	cout << "Enter a word: ", cin >> input;
	input = checkIfInputIsValid(input); // Calls function to see if the user input is not valid
	input = convertToUpperCase(input); // Calls function to put every letter in uppercase
	wordExists = checkIfWordExists(input, headlines); // Calls function to see if the input exist in dictionary

	if (wordExists) cout << "The word \"" << input << "\" exists." << endl;
	else cout << "The word does not exists." << endl;
	return;
}

// 2. Guess the scrambled word
void program2(vector<string> headlines)
{
	string word, wordUnshuffle, input;
	int count = 1, random;

	srand(time_t(NULL)); // Initialize random seed
	random = rand() % headlines.size();
	word = headlines[random];
	wordUnshuffle = word; // Original word
	random_shuffle(word.begin(), word.end()); // Shuffled word
	cout << "Try do guess the following word (you have 3 guesses):" << endl << word << endl; // Shows Shuffled word
	while (count <= 3)
	{
		cout << "Guess number " << count << ": ", cin >> input;
		input = checkIfInputIsValid(input); //checks if the input is valid
		input = convertToUpperCase(input); // Puts all letters into uppercase
		if (input.compare(wordUnshuffle) == 0) // Compares shuffled word with original word
		{
			cout << "Congratulations, you found the word!" << endl;
			break;
		}
		else {
			if (count == 3) cout << "I am sorry but you could not find the correct word." << endl;
			else cout << "That is not the correct word, please try again." << endl;
		}
		count++;
	}
	return;
}

// 3. Words which can be built with the letters given by the user
void program3(vector<string> headlines)
{
	string input, word;
	int count; //number of letters of the input matched 
	int count2 = 0; //number of words that match found
	cout << "Please input the letters: ", cin >> input;
	input = checkIfInputIsValid(input);
	input = convertToUpperCase(input);
	for (unsigned int i = 0; i < headlines.size(); i++) // Searches in every word of the file
	{
		count = 0;
		word = headlines[i]; //
		if (input.size() == word.size())
			for (unsigned int x = 0; x < input.size(); x++) // Checks every letter of the input
			{
				if (word.find(input[x]) != -1) // If it finds that letter of the input in the word from the file
				{
					count++;
					word.erase(word.find(input[x]), 1);
				}
				if (count == input.size()) // If it matched all the letter of the input with the ones from the word from the file
				{
					count2++;
					cout << headlines[i] << endl;
				}
			}
	}
	if (count2 == 0) // If there are no words
		cout << "There are no words.\n";
	else cout << "There are no more words.\n";
}

// 4. Build a valid word with the given letters
void program4(vector<string> headlines)
{
	string input;
	// Number of ocurrences per letter
	vector<int> letters(26);
	for (unsigned int i = 0; i < headlines.size(); i++) // For each word in the file 
	{
		string line = headlines[i];
		for (unsigned int x = 0; x < line.size(); x++) // For each letter in the word
		{
			int p = (int)line[x] - (int)'A';
			letters.at(p)++;
		}
	}
	// Number of times each letter appears and vector to remove letters from
	vector<string> lettersnew;
	for (int i = 0; i < 26; i++) // For each letter in the alphabet
	{  
		letters.at(i) = 2 * letters[i] / *min_element(letters.begin(), letters.end());
		for (int x = 0; x < letters[i]; x++)  // For the number of times each letter appears
			lettersnew.push_back(string(1, (char)i + (int)'A'));
	}
	// Letters for the user build the word
	srand((unsigned int)time(NULL)); // Initialize random seed
	string letterstochoose;
	cout << "Input the number of letters: ", cin >> input;
	for (int i = 0; i < stoi(input); i++) // For the number of letters inputed
	{
		int random = rand() % (lettersnew.size() - 1 - i);
		letterstochoose.append(lettersnew[random]);
		cout << letterstochoose[i];
		lettersnew.erase(lettersnew.begin() + random);
	}
	// Receiving word
	cout << endl << "Enter the word: ", cin >> input;
	input = checkIfInputIsValid(input);
	input = convertToUpperCase(input);
	if (checkIfWordExists(input, headlines)) // Testing if the word exists in the file
	{ 
		for (unsigned int i = 0; i < input.size(); i++) // For each letter of the word inputed
		{ 
			if (letterstochoose.find(input[i]) != -1)  // Testing if the word can be built with the letters given 
				letterstochoose.erase(letterstochoose.find(input[i]), 1);
			else 
			{
				cout << "You can't construct that word with the letters given." << endl;
				return;
			}
		}
		cout << "You won the game!" << endl;
	}
	else cout << "The word doesn't exist." << endl;
	return;
}

// 5. Match the given wildcard string
void program5(vector<string> headlines)
{
	string input; // User input
	input = checkIfInputIsValid(input);
	int count = 0; // Number of words found
	cout << "Please write the word: ", cin >> input;
	for (unsigned int i = 0; i < headlines.size(); i++)
		if (wildcardMatch(headlines[i].c_str(), input.c_str())) 
		{
			cout << headlines[i] << endl;
			count++;
		}
	if (count == 0) // If there are no words
		cout << "There are no words.\n";
	else cout << "There are no more words.\n";
}

///////////////////////////////////////////////////////////////////////////
//////////////////////Auxilary functions///////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// Check if the user input is valid for inputs type strings
string checkIfInputIsValid(string input)
{
	bool digitFound = false;

	while (1)
	{
		digitFound = false;
		for (unsigned int i = 0; i < input.size(); i++)
			if (isdigit(input[i])) 
			{
				digitFound = true;
				break;
			}

		if (digitFound)
		{
			cerr << "What you typed is not a word. Please enter one: ";
			cin >> input;
		}
		else break;
	}
	return input;
}

// Convert all letters to uppercase
string convertToUpperCase(string input) 
{

	for (unsigned int i = 0; i < input.size(); i++)
		input[i] = toupper(input[i]);
	return input;
}

// Check if the word exist in the dictionary
bool checkIfWordExists(string input, vector<string> headlines) 
{
	for (unsigned int i = 0; i < headlines.size(); i++)
		if (input == headlines[i])
			return true;
	return false;
}

// Implements a matching algorithm for two C-strings, one of which may have wildcards
bool wildcardMatch(const char *str, const char *strWild)
{
	//////////////////////////////////////////////////////////////////////////
	// WildcardMatch
	// str - Input string to match
	// strWild - Match mask that may contain wildcards like ? and *
	//
	// A ? sign matches any character, except an empty string.
	// A * sign matches any string inclusive an empty string.
	// Characters are compared caseless.
	//
	// ADAPTED FROM:
	// https://www.codeproject.com/Articles/188256/A-Simple-Wildcard-Matching-Function
	//
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild)
	{
		// Single wildcard character
		if (*strWild == '?')
		{
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			// Need to do some tricks.
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.
			// Because we eat one character from the match string,
			// the recursion will stop.
			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;
			// 2. Chance we eat the next character and try it again,
			// with a wildcard * match. This is done by recursion.
			// Because we eat one character from the string,
			// the recursion will stop.
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		}
		else
		{
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}