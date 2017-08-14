// libraries
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

void deleteLastCharacter(string &word)
{
	if (word.back() < 65)
	{
		if (word.back() < 48 || word.back() > 57)
		{
			word.pop_back();
		}
	}
}

void lowercaseFirstCharacter(string &word)
{
	if (word.front() >= 65 && word.front() <= 90)
	{
		word.front() += 32;
	}
}

void wordLongestShortest(string &word, string &longest, string &shortest)
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

void numWordsAppearingXTimesOrLess(unordered_map<string, int> &words)
{
	cout << "Enter a number to find out how many words appeared that many times or less. Type -1 to move on: " << endl;
	int count = 0;
	int number;
	while (cin >> number)
	{
		if (number == -1)
		{
			break;
		}
		for (auto it = words.begin(); it != words.end(); ++it)
		{
			if (it->second <= number)
			{
				++count;
			}
		}
		cout << "There were " << count << " words that appeared " << number << " or less times." << endl;
		count = 0;
	}
}

void wordAppearsHowManyTimes(unordered_map<string, int> &words, string &word)
{
	cout << "Enter a word to find out how many times it appears. Type QUIT to move on: " << endl;
	int count = 0;
	while (cin >> word)
	{
		if (word == "QUIT")
		{
			break;
		}
		auto it = words.find(word);
		if (it == words.end())
		{
			count = 0;
		}
		else
		{
			count = words[word];
		}
		cout << "The word " << word << " appears " << count << " times." << endl;
	}
}


void runProgram(unordered_map<string, int> &words)
{
	ifstream file;
	string filename;

	//loop for file opening
	//repeat until valid filename given
	while (true)
	{
		cout << "What is the name of the file? ";
		cin >> filename;
		file.open(filename);
		if (!file.is_open())
		{
			cout << "file could not be opened." << endl;
		}
		else
		{
			break;
		}
	}

	string word;
	pair<string, int> mostUsed;
	string longest;
	string shortest;
	int numWords = 0;

	int i = 0;
	//while the file has words
	while (file >> word)
	{
		//increment the number of words in the doc
		++numWords;
		
		deleteLastCharacter(word);
		lowercaseFirstCharacter(word);

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
			wordLongestShortest(word, longest, shortest);
		}

		auto it = words.find(word);

		//if the word is showing up for the first time
		if (it == words.end())
		{
			//put it in the hash table
			words.emplace(word, 1);
		}
		//otherwise
		else
		{
			//increment the number of times it has appeared
			++words[word];
			//if this word has appeared more times than the one that has appeared
			//the most so far
			if (words[word] > mostUsed.second)
			{
				//make the word the most appeared so far word
				mostUsed.first = word;
				mostUsed.second = words[word];
			}
		}
	}

	//close the file
	file.close();

	//stats begin here
	cout << "-------------- STATS --------------" << endl;
	cout << "There are " << words.size() << " unique words in the document." << endl;
	cout << "There are " << numWords << " words in the document." << endl;
	
	int wordsSize = words.size();
	double factor = double(wordsSize) / double(numWords);
	double average = double(numWords) / double(wordsSize);
	
	cout << "The document has a uniqueness factor of " << factor << "." << endl;
	cout << "Average number of times any given word appeared: " << average << endl;
	cout << "Most used word: " << mostUsed.first << " (used " << mostUsed.second << " times)" << endl;
	cout << "Longest word: " << longest << endl;
	cout << "Shortest word: " << shortest << endl;

	//loop for how many words appeared x many times or less
	numWordsAppearingXTimesOrLess(words);

	//loop for looking up a word to see how many times it appears
	wordAppearsHowManyTimes(words, word);
}

//main
int main()
{
	//declarations
	unordered_map<string, int> words;

	runProgram(words);
	
	return 0;
}