// libraries
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

// delete a character from a word if it's not a letter
void deleteCharacter(string &word, int charIndex)
{
	// if its not a letter
	if ((word[charIndex] < 65) and 
		(word[charIndex] < 48 || word[charIndex] > 57))
	{
		//erase the character
		word.erase(charIndex, 1);
	}
}

// delete all symbols in a word
void deleteAllSymbols(string &word)
{
	// loop through the word
	for (int i = 0; i < word.size(); ++i)
	{
		// set the size
		int wordSize = word.size();
		// delete the character if it should be
		deleteCharacter(word, i);
		// if the word got smaller
		if (word.size() < wordSize)
		{
			// decrement i
			--i;
		}
	}
}

// lowercase a character
void lowercaseCharacter(string &word, int charIndex)
{
	// if its a letter
	if (word[charIndex] >= 65 and word[charIndex] <= 90)
	{
		// lowercase the letter
		word[charIndex] += 32;
	}
}

// lowercase all the characters
void lowercaseAllCharacters(string &word)
{
	// loop through the word
	for (int i = 0; i < word.size(); ++i)
	{
		// lowercase the character
		lowercaseCharacter(word, i);
	}
}

// find the shortest and longest word
void findLongestShortest(string &word, string &longest, string &shortest)
{
	//if the word is longer than longest, assign it
	if (word.size() > longest.size())
	{
		longest = word;
	}

	//if the word is shorter than the shortest, assign it
	if (word.size() < shortest.size())
	{
		shortest = word;
	}
}

// find the number of words appearing 10 through 1 times or less
void numWordsAppearingXTimesOrLess(unordered_map<string, int> &words, 
	ofstream &fout)
{
	// declare the count variable
	int count = 0;

	fout << "Number of words appearing x times or less:" << endl;

	// loop from 1 to 10, inclusive
	for (int i = 1; i <= 10; ++i)
	{
		// loop over the words
		for (auto it = words.begin(); it != words.end(); ++it)
		{
			// if the word appears less than or equal to i times
			if (it->second <= i)
			{
				// increase the count of words that appear x times or less
				++count;
			}
		}
		// output
		fout << count << " words appeared <= " << i << " times." << endl;
		// reset the count
		count = 0;
	}
}

// see how many times each word appears
void wordAppearsHowManyTimes(unordered_map<string, int> &words, ofstream &fout)
{
	// set the count
	int count = 0;

	fout << "How many times each word appears:" << endl;

	// loop over the words
	for (auto it = words.begin(); it != words.end(); ++it)	
	{
		//print out that the word appears x times
		fout << it->first << ": " << it->second << endl;
	}
}

// check if valid file
void checkFile(ifstream &file, string &filename)
{
	while (true)
	{
		cout << "What is the name of the file? ";
		cin >> filename;
		file.open(filename);
		if (! file.is_open())
		{
			cout << "file could not be opened." << endl;
		}
		else
		{
			break;
		}
	}
}

// stats output function
void outputStats(unordered_map<string, int> &words, ofstream &fout, 
	int numWords, pair<string, int> mostUsed, string longest, string shortest)
{
	int wordsSize = words.size();
	double average = double(numWords) / double(wordsSize);

	// stats begin here
	fout << "STATS:" << endl;
	fout << "There are " << words.size() << " unique words in the document." 
		<< endl;
	fout << "There are " << numWords << " words in the document." << endl;
	fout << "Average number of times any given word appeared: " << average 
		<< endl;
	fout << "Most used word: " << mostUsed.first << " (used " 
		<< mostUsed.second << " times)" << endl;
	fout << "Longest word: " << longest << endl;
	fout << "Shortest word: " << shortest << endl;

	// loop for how many words appeared x many times or less
	numWordsAppearingXTimesOrLess(words, fout);

	// loop for looking up a word to see how many times it appears
	wordAppearsHowManyTimes(words, fout);
}

// run the program
void runProgram(unordered_map<string, int> &words)
{
	// create the filestream and filename
	ifstream file;
	string filename;

	ofstream fout;
	fout.open("output.txt");

	// loop for file opening
	// repeat until valid filename given
	checkFile(file, filename);

	// create the variables
	string word;
	pair<string, int> mostUsed;
	string longest;
	string shortest;
	int numWords = 0;

	int i = 0;
	// while the file has words
	while (file >> word)
	{
		//increment the number of words in the doc
		++numWords;
		
		// delete all symbols from word and lowercase all letters
		deleteAllSymbols(word);
		lowercaseAllCharacters(word);

		// check if the word still has characters
		if (word.size() == 0)
		{
			continue;
		}

		//if this is the first word
		if (i == 0)
		{
			//set all the things equal to the word
			longest = word;
			shortest = word;
			mostUsed.first = word;
			mostUsed.second = 1;
			++i;
		}
		//otherwise
		else
		{
			// find the longest and shortest words
			findLongestShortest(word, longest, shortest);
		}

		// iterator point to the word we are looking at
		auto it = words.find(word);

		// if the word is showing up for the first time
		if (it == words.end())
		{
			// put it in the hash table and set it as seen once
			words.emplace(word, 1);
		}
		// otherwise
		else
		{
			// increment the number of times it has appeared
			++words[word];
			// if this word has appeared more times than the one that 
			// has appeared the most so far
			if (words[word] > mostUsed.second)
			{
				// make the word the most appeared so far word
				mostUsed.first = word;
				mostUsed.second = words[word];
			}
		}
	}

	// close the file
	file.close();

	// output the stats
	outputStats(words, fout, numWords, mostUsed, longest, shortest);

	// close the output file
	fout.close();
}

//main
int main()
{
	unordered_map<string, int> words;

	runProgram(words);
	
	return 0;
}