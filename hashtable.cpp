#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

class Word{
	public:
		string word;
		string definition;

	// Calculate the key value for a string	
	static unsigned int key( string word, int size ){
		unsigned int hash = 0;
		for( char c : word)
			hash = 37 * hash + c;
		return hash % size;
	}
};

class Dictionary{
	public:
	vector < vector<Word> > hashtable;
	int tableSize;
	
	// Constructor
	Dictionary(){		
		tableSize = 101;
		//Allocating memory 
		hashtable.resize(tableSize);
	}
	
	// Check if a word exists in the table
	bool Contains ( string word ){
		long key = Word :: key( word,tableSize );
		// Looping through table
		for( auto const& temp : hashtable[key] ) 
			if( word.compare ( temp.word ) == 0 )
				return true;
		return false;
	}
	 
	// Insert a Word into the hashtable
	void Insert(Word newWord){
		long key = Word :: key( newWord.word,tableSize );
		if( Contains(newWord.word) ){
			vector<Word> temp = hashtable[key];
		 	for( std::vector<Word>::size_type i = 0; i != temp.size() ; i++ ){
				if( !newWord.word.compare( temp[i].word ) )
					temp[i].definition = newWord.definition;		
			}
		}
		hashtable[key].push_back(newWord);
	}

	void Display(){
		for( std::vector< vector<Word>>::size_type i = 0; i != hashtable.size(); i++ ){	 	
			vector<Word> temp = hashtable[i];
			cout<< "\n new chain:"<< i<< endl;
			for( std::vector<Word>::size_type j = 0 ; j != temp.size(); j++ )
		 		if( temp[j].word == "\0" )
					continue;
				else
					cout << endl << temp[j].word << ":" << temp[j].definition;

			}
	}
	
	// Search and delete a word from the table  
	Word Delete( string word ){
		long key = Word :: key( word, tableSize );
		Word null;
		Word deleted_word;
			
		null.word = null.definition = "\0";	
		if( !Contains(word) ){
			cout<<"\nWord not found";
			return null;
		}
		for( std::vector< vector<Word>>::size_type i = 0 ; i != hashtable.size() ; i++ ){	 	
			vector<Word> temp = hashtable[i];
			for( std::vector<Word>::size_type j = 0 ; j != temp.size() ; j++ )
		 		if( !word.compare(temp[j].word) ){
		 			deleted_word = temp[j];
		 			temp.erase( temp.begin()+j );
		 		}	
		}	
		
		return deleted_word;
	}
	
	bool isPrime(int n){
		for( int i=2; i <= n/2; i++)
			if( n % i == 0 )
				return false;
		return true;
	}

	// If table has high load factor then rehash
	void Rehash(){
		int newSize = 2*tableSize;
		while(!isPrime(newSize))
			newSize++;
		
		//Temporary vector to hold all words while rehashing table
		vector<Word> newList;
		
		for( std::vector< vector<Word>>::size_type i = 0 ; i != hashtable.size() ; i++ ){	 		
			vector<Word> temp_word = hashtable[i];
			for( std::vector<Word>::size_type j = 0 ; j != temp_word.size() ; j++ )
		 		if( temp_word[j].word == "\0" )
		 			continue;
		 		else
					newList.push_back( temp_word[j] );
		 				
		}
		hashtable.erase( hashtable.begin(),hashtable.end() ); 
		tableSize = newSize;
		hashtable.resize( newSize );

		for( auto const& a : newList ) 
			Insert(a);
	}
};


// Parse json to get Word
Word getWord(string w){
	
	Word temp;
	size_t word_start = w.find( '"', 0 )+1;
	size_t word_end = w.find( '"', word_start )+1;
	size_t definition_start = w.find( '"', word_end )+1;
	size_t definition_end = w.find( '"', definition_start )+1; 

	temp.word = w.substr( word_start , word_end - word_start -1 );
	temp.definition = w.substr( definition_start , definition_end - definition_start -1 );
	return temp;
}

int main(int argc, char *argv[]){
	
	if(strcmp(argv[1],"dictionary.json")!=0){
		cout<<"please run as \n./a.out dictionary.json\n";
		return 0;
	}

	fstream f;
	string tmp;
	float loadFactor = 0.0;
    int number_of_words= 0;
	
	Dictionary table;
	
	// Open dictionary.json file
    f.open(argv[1]);
  	
    //Loop to  parse through the file
    while(!f.eof()){	
        getline( f,tmp ); 
        if(tmp=="\0")
        	break;
        Word newWord = getWord(tmp);
        if( !table.Contains(newWord.word) )
        	number_of_words++;
        table.Insert( newWord );
	    loadFactor = (float) number_of_words / table.tableSize;
  		if( loadFactor > 1.0)
  			table.Rehash();
  	}

  	cout<<"\nNumber of words in the dictionary: "
  		<< number_of_words
  		<<"\nTable size: "
  		<< table.tableSize
  		<<"\nLoad factor: "
  		<< loadFactor << endl<< endl;

  	string input_word;	
  	
  	//Querying mode

  	cout<<"\nEnter word:";
  		
	while(cin >> input_word){ 		
  		for(int i=0 ; input_word[i] ; i++)
			if(islower( input_word[i]) )
				input_word[i]=toupper( input_word[i] );
		if( table.Contains( input_word ) ){
  			int key = Word :: key( input_word , table.tableSize );
  			vector<Word> temp = table.hashtable[key];
			for( std::vector<Word>::size_type i = 0 ; i != temp.size() ; i++ ){
				if( !input_word.compare( temp[i].word ) )
					cout<< temp[i].word << ": "<< temp[i].definition << endl;
			}
		}
  		else
  			cout<<"Doesn't contain word\n";
  	cout<<"\nEnter word:"; 	
  	}
	return 0;
}