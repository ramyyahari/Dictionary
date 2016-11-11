#include <iostream>
#include <string.h>
//#include <cstring>
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
		//cout<<"\nkey is:"<< hash % size;
		return hash % size;
	}
};

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
		//hashtable.insert( hashtable.begin() + key, newWord); 
		hashtable[key] = newWord;
		//cout<<"\nSize after insert:"<<hashtable.size();
	}

	void Display(){
		for(auto const& a : hashtable) 
			/*if(a.word=="\0")
				continue;
			else*/
				cout << endl << a.word << ":" << a.definition;
	}
	
	// Check if a word exists in the table
	bool Contains(string word){
		int key = Word :: key(word,tableSize);
		//cout<<"\nLooking for word "<< word << "\nKey:"<< key << endl;
		//cout<<"\nmeaning exists: "<<hashtable[key].definition;
		if( !word.compare(hashtable[key].word))
			return true;
		return false;
	}
	
	// Search and delete a word from the table  
	Word Delete(string word){
		int key = Word :: key(word,tableSize);
		Word temp;
			
		if(!Contains(word)){
			return temp;
		}
		
		temp = hashtable[key];
		hashtable.erase( hashtable.begin() + key);
		return temp;
	}
	
	bool isPrime(int n){
		for( int i=2; i < n; i++)
			if( n % i == 0 )
				return false;
		return true;
	}

	// If table has high load factor then rehash
	void Rehash(){

		int newSize = 2*tableSize;
		
		//cout<< "\n\n\n\n\n\n\n\n\n\nRehashing table\n\n\n\n\n\n\n\n\n\n";
		
		while(!isPrime(newSize))
			newSize++;
		tableSize = newSize;
		hashtable.resize(newSize);

		for(auto const& a : hashtable) 
			if(a.word=="\0")
				continue;
			else{
				Word temp = Delete(a.word);
				Insert(temp);
			}
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

int main(int argc, char *argv[]){
	/*
	if(strcmp(argv[1],"dictionary.json")!=0){
		cout<<"please run as \n./a.out dictionary.json\n";
		return 0;
	}*/

	fstream f;
	string tmp;
	float loadFactor = 0.0;
    int number_of_words= 0;
	//Word temp;
	Dictionary table;
	
	// Open dictionary.json file
    f.open(argv[1]);
  	
    //Loop to parse through the file
    while(!f.eof()){	
        getline(f,tmp); 
        if(tmp=="\0")
        	break;
        Word newWord = getWord(tmp);
        if(!table.Contains(newWord.word))
        	number_of_words++;
        table.Insert(newWord);
  		//number_of_words= table.hashtable.size()-table.tableSize;
	    //number_of_words= table.hashtable.size();
		
	    loadFactor = (float)number_of_words/table.tableSize;
  		if( loadFactor > 1.0)
  			table.Rehash();
  	}

  	table.Display();
  	
  	cout<<"\n\nNumber of words in the dictionary: "
  		<< number_of_words
  		<<"\nTable size: "
  		<< table.tableSize
  		<<"\nLoad factor: "
  		<< loadFactor << endl;
  	
  	/*
  	if(table.Contains("EXPLAIN")){
  			int key = Word :: key("EXPLAIN",table.tableSize);
			cout<< table.hashtable[key].word << ": "<< table.hashtable[key].definition << endl;
  		}
  	if(table.Contains("WALY")){
  			int key = Word :: key("WALY",table.tableSize);
			cout<< table.hashtable[key].word << ": "<< table.hashtable[key].definition << endl;
  		}
  	if(table.Contains("PLASTERY")){
  			int key = Word :: key("PLASTERY",table.tableSize);
			cout<< table.hashtable[key].word << ": "<< table.hashtable[key].definition << endl;
  		}
  	if(table.Contains("HONEYLESS")){
  			int key = Word :: key("HONEYLESS",table.tableSize);
			cout<< table.hashtable[key].word << ": "<< table.hashtable[key].definition << endl;
  		}
  	if(table.Contains("LINGUISTICS")){
  			int key = Word :: key("LINGUISTICS",table.tableSize);
			cout<< table.hashtable[key].word << ": "<< table.hashtable[key].definition << endl;
  		}
  	
  	*/

  	string input_word;	
  	
	while(1){
  		cout<<"Enter word:";
  		cin >> input_word;
  		//cout<< endl<<input_word;
  		//if(c.eof())
  		//	break;
  		char c;
  		for(int i=0 ; input_word[i] ; i++)
			if(islower(input_word[i]))
				input_word[i]=toupper(input_word[i]);
			if(table.Contains(input_word)){
  			int key = Word :: key(input_word,table.tableSize);
			cout<< table.hashtable[key].word << ": "<< table.hashtable[key].definition << endl;
  		}
  		else
  			cout<<"Doesn't contain word\n";
  	}
	

	return 0;
}