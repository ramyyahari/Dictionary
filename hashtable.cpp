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
	static unsigned int key( string w, int size ){

		unsigned int hash = 0;
		for( char c : w)
			hash = 37 * hash + c;
		cout<<"\nkey is:"<< hash % size;
		return hash % size;
	}

	
};

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

class Dictionary{
	public:
	vector <Word> hashtable;
	int tableSize;

	// Constructor

	Dictionary(){
		tableSize = 101;
		hashtable.resize(tableSize);
	}
	// Insert a Word into the hashtable
	void Insert(Word newWord){
		int key = Word :: key(newWord.word,tableSize);
		//hashtable.push_back(newWord);
		hashtable.insert( hashtable.begin() + key, newWord); 

	}

	void Display(){
		for(auto const& a : hashtable) 
			cout << endl << a.word << ":" << a.definition;
	}
	/*
	// Check if a word exists in the table
	bool Contains(string word){
		int key = Word :: key(word,tableSize);
		if( strcmp(hashtable[key].word,word) == 0 )
			return true;
		return false;
	}

	// Search and delete a word from the table  
	void Delete(string word){
		int key = Word :: key(word,tableSize);
		hashtable[key].word = "\0";
		hashtable[key].definition = "\0";
	return;
	}

	// If table has high load factor then rehash
	void Rehash(){

	}*/
};
	int main(int argc, char *argv[]){
	/*
	if(strcmp(argv[1],"dictionary.json")!=0){
		cout<<"please run as \n./a.out dictionary.json\n";
		return 0;
	}*/

	fstream f;
	string tmp;
	int loadFactor = 0;
	//Word temp;
	Dictionary table;
	
	// Open dictionary.json file
    f.open(argv[1]);

    int number_of_words= 0;
  	
    //Loop to parse through the file
    while(!f.eof()){	
        getline(f,tmp); 
        if(tmp=="\0")
        	break;
        cout<<endl<<tmp;
        Word newWord = getWord(tmp);
        table.Insert(newWord);
  		//loadFactor = number_of_words/table.tableSize;
  		//number_of_words= table.hashtable.size()/sizeof(temp);
  	}

  	table.Display();
  	cout<<"\nNumber of words in the dictionary: "
  		<< number_of_words
  		<<"\n Table size: "
  		<< table.tableSize
  		<<"\n Load factor: "
  		<< loadFactor;

	return 0;
	}