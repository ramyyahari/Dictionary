#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;


class Word{
	public:
		//int key = 0;
		string word;
		string definition;

	// Calculate the key value for a string	
	int key(string w){

	return 0;
	}

	// Parse json to get Word
	Word getWord(string w){

		Word temp;

		//cout<<"String is:"<<w;
		size_t word_start = w.find('"', 0)+1;
		size_t word_end = w.find('"', word_start)+1;
		size_t definition_start = w.find('"', word_end)+1;
		size_t definition_end = w.find('"', definition_start)+1; 

		temp.word = w.substr(word_start , word_end - word_start -1);
		temp.definition = w.substr(definition_start, definition_end - definition_start -1);

		//cout<<"\nWord:"<<temp.word<<"\nDefinition:"<< temp.definition<<endl;
		return temp;
	}

};

class Dictionary{
	public:
	vector <Word> hashtable;


	// Insert a Word into the hashtable
	void Insert(Word newWord){

		int key = Word :: key(newWord.word);


	}

	// Check if a word exists in the table
	bool Contains(string word){

		return false;
	}

	// Search and delete a word from the table  
	void Delete(string word){

	return;
	}

	// If table has high load factor then rehash
	void Rehash(){

	}
};
	int main(int argc, char *argv[]){
	/*
	if(strcmp(argv[1],"dictionary.json")!=0){
		cout<<"please run as \n./a.out dictionary.json\n";
		return 0;
	}*/

	fstream f;
	string tmp;

	Word temp;
	Dictionary table;
	// Open dictionary.json file
    f.open(argv[1]);

    //Loop to parse through the file
    while(!f.eof()){	
        getline(f,tmp); 
        Word newWord = temp.getWord(tmp); 
  		table.Insert(newWord);
  	}

	return 0;
	}