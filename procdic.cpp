// PROGRAM 1 - Class 3 Group 10
// Carlos Manuel Coelho Nunes
// Joao Filipe Carvalho de Araujo

#include <iostream> // cout, cin, cerr
#include <fstream> // ifstream, ofstream
#include <vector> // vector, .push_back, .size, .begin, .end, .erase
#include <string> // string, getline
#include <algorithm> // sort, unique
using namespace std; // std::

bool charcheck(string line); // Checks if line contains a headline
bool charcheck2(string line); // Checks if the line only contains valid characters
void pointgenerator(vector<string> headlines); // Generates a point per 100 headlines
string spacecheck(string line); // Removes spaces in the first and last position of line
vector<string>write(string filename); // Passes all the file lines into the vector headlines
vector<string>errorcheck(vector<string> headlines); // Checks every string in headlines and returns a vector with only simple words

int main()
{
	vector<string> headlines; //vector with all the headlines 
	string line;
	ifstream file; // Open dictionary
	ofstream newfile; // Open and create a new dictionary
	string filename;

	//searches file to open
	cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
	cout << "=======================================" << endl << endl;
	cout << "Dictionary file ? ", cin >> filename;

	//if file isn't found ends the program
	if (file.fail()) {
		cout << "File not found" << endl;
		return 0;
	}

	//creation of vector headlines with 
	headlines = write(filename);

	//new file creation
	cout << "Word list file ? ", cin >> filename;
	cout << endl;
	newfile.open(filename, fstream::out);

	//error search and letters and points generator
	headlines = errorcheck(headlines);
	pointgenerator(headlines);

	//sorting words
	cout << endl;
	cout << "Number of Simple Words = " << headlines.size() << endl;
	cout << "Sorting words ..." << endl;
	sort(headlines.begin(), headlines.end());

	//removing duplicate words
	cout << "Removing duplicate words ..." << endl;
	headlines.erase(unique(headlines.begin(), headlines.end()), headlines.end());

	cout << "Number of non-duplicate Words = " << headlines.size() << endl;
	cout << "Saving words into file" << endl;

	//saving word by word in new file
	for (unsigned int i = 0; i < headlines.size(); i++)
		newfile << headlines[i] << endl;

	//end of program
	cout << "End of processing." << endl;
	file.close();
	newfile.close();
	return 0;
}


///////////////////////////////////////////////////////////////////////////
////////////////////Auxiliar Function//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// Checks if line contains a headline
bool charcheck(string line) 
{ 
	for (unsigned int i = 0; i < line.size(); i++) //for every character in line
	{
		char c = line[i];
		if (not (c == '-' || c == ' ' || c == '\'' || c == ';' || (c >= 'A' && c <= 'Z')))
			return false;
	}
	return true;
}
// Checks if the line only contains valid characters
bool charcheck2(string line)
{ 
	if (line.find("\'") == -1 && line.find("-") == -1 && line.find(" ") == -1 && line.find("'") == -1 && not(line.empty()))
		return true;
	else return false;
}
// Generates a point per 100 headlines
void pointgenerator(vector<string> headlines)
{  
	char currentLetter = headlines[0][0];
	int headlinesFound = 0;
	cout << endl << currentLetter << endl;
	for (unsigned int i = 0; i < headlines.size(); i++) { //for every string in headlines
		if (currentLetter != headlines[i][0] && (int)headlines[i][0]==(int)currentLetter+1 ) {  //if it is a new letter and if the letter is the letters after the previous letter
			currentLetter = headlines[i][0];
			cout <<endl << currentLetter << endl;
			headlinesFound = 0;
		}
		headlinesFound++;
		if (headlinesFound == 100) {
			cout << '.';
			headlinesFound = 0;
		}
	}
	return;
}
// Removes spaces in the first and last position of line
string spacecheck(string line) 
{ 
		if (line.find(' ') == 0)
			line.erase(0, 1);
		if (line.find(' ') == (line.size() - 1))
			line = line.substr(0, line.size() - 2);
	return line;
}
// Passes all the file lines into the vector headlines
vector<string> write(string filename) 
{ 
	ifstream file;
	string line;
	vector<string> headlines;
	file.open(filename, fstream::in);
	while (getline(file, line)) {
		if (charcheck(line))
			headlines.push_back(line);
	}
	return headlines;
}
// Checks every string in headlines and returns a vector with only simple words
vector<string> errorcheck(vector<string> headlines) 
{
	vector<string> headlinesfixed;
	string aux;
	for (unsigned int i = 0; i < headlines.size(); i++) { //for every string in headlines
		string line = headlines[i];
		if ((line.find(";")) == -1) { //if it doesn't find ";"
			line = spacecheck(line);
			if (charcheck2(line))  
				headlinesfixed.push_back(line);
		}
		else {  //if it finds ";"
			while ((line.find(";")) != -1) {  //while line contains ";"
				aux = line.substr(line.find(";") + 1, string::npos);  //aux = everything after the first ";"
				line.erase(line.find(";"));
				line = spacecheck(line);
				if (charcheck2(line))
					headlinesfixed.push_back(line);
				line = aux;
			}
			line = spacecheck(line);
			if (charcheck2(line)) {
				headlinesfixed.push_back(line);
			}
		}
	}
	return headlinesfixed;
}