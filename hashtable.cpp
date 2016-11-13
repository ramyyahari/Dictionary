#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>

using namespace std;


class Word{
	public:
		//int key = 0;
		string word;
		string definition;

	// Calculate the key value for a string	
	static unsigned int key( string s, int M ){
		unsigned int hash = 0;
		for( char c : s)
			hash = 37 * hash + c;
		//cout<<"\nkey is:"<< hash % size;
		return hash % M;
	}
};

class Dictionary{
	public:
	vector < vector<Word> > hashtable;
	int tableSize;
	int previoustableSize;

	// Constructor
	Dictionary(){		
		previoustableSize = 101;
		tableSize = 101;
		hashtable.resize(tableSize);
	}
	
	// Check if a word exists in the table
	bool Contains(string word){
		long key = Word :: key(word,previoustableSize);
		for(auto const& a : hashtable[key]) 
			if( word.compare(a.word) == 0)
				return true;
		return false;
	}
	 
	// Insert a Word into the hashtable
	void Insert(Word newWord){
		long key = Word :: key(newWord.word,tableSize);
		//hashtable.insert( hashtable.begin() + key, newWord); 
		if(Contains(newWord.word)){
			vector<Word> temp = hashtable[key];
		 	for( std::vector<Word>::size_type i = 0; i != temp.size(); i++ ){
		 	//for(vector <Word>::iterator i= temp.begin(); i!= temp.end(); i++){
				if(!newWord.word.compare(temp[i].word))
					temp[i].definition = newWord.definition;		
			}
		}
		hashtable[key].push_back(newWord);
		//cout<<endl<<hashtable[key].word<<" "<<key;
	}

	void Display(){
		for( std::vector< vector<Word>>::size_type i = 0; i != hashtable.size(); i++ ){	 	
			vector<Word> temp = hashtable[i];
			cout<< "\n new chain:"<< i<< endl;
			for( std::vector<Word>::size_type j = 0; j != temp.size(); j++ )
		 		if(temp[j].word=="\0")
					continue;
				else
					cout << endl << temp[j].word << ":" << temp[j].definition;

			}
	}
	
	// Search and delete a word from the table  
	Word Delete(string word){
		long key = Word :: key( word,previoustableSize );
		Word null;
		Word deleted_word;
			
		//cout<<"\nDelete word:"<<word;
		null.word = null.definition = "\0";	
		if(!Contains(word)){
			cout<<"\nWord not found";
			return null;
		}
		for( std::vector< vector<Word>>::size_type i = 0; i != hashtable.size(); i++ ){	 	
			vector<Word> temp = hashtable[i];
			for( std::vector<Word>::size_type j = 0; j != temp.size(); j++ )
		 		if(!word.compare(temp[j].word)){
		 			deleted_word = temp[j];
		 			temp.erase(temp.begin()+j);
		 		}	
		}	
		/* 	
	    for(vector<Word>::iterator i= hashtable[key].begin(); i!= hashtable[key].end(); i++)			
			if(!word.compare(i.word))
				temp = i.word;
		
		//cout<<"\nDeleted Word:"<< hashtable[key].word;
		//hashtable[key] = null;
		hashtable[key].erase(hashtable[key].begin()+i);*/
		return deleted_word;
	}
	
	bool isPrime(int n){
		cout<<"\n in fntin prime:"<<n;
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
		cout<<endl<<newSize;

		previoustableSize=tableSize;
		tableSize = newSize;
		hashtable.resize(newSize);

		for( std::vector< vector<Word>>::size_type i = 0; i != hashtable.size(); i++ ){	 	
			hashtable[i].resize(newSize);
			vector<Word> temp = hashtable[i];

			for( std::vector<Word>::size_type j = 0; j != temp.size(); j++ )
		 		if(temp[j].word=="\0")
		 			continue;
		 		else{
		 			Word reinsert_word = Delete(temp[j].word);
					Insert(reinsert_word);
		 		}
		} 		
		/*	
		for(auto const& a : hashtable) 
			if(a.word=="\0")
				continue;
			else{
				Word temp = Delete(a.word);
				Insert(temp);
			}*/
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
	
	// Open dictionary.json filet
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

	    loadFactor = (float)number_of_words/table.tableSize;
  		if( loadFactor > 1.0){
  			cout<<"\nRehashing table";
  			table.Rehash();
  		}
  	}

  	table.Display();
  	
  	cout<<"\n\nNumber of words in the dictionary: "
  		<< number_of_words
  		<<"\nTable size: "
  		<< table.tableSize
  		<<"\nLoad factor: "
  		<< loadFactor << endl;

  	//table.Delete("WALY");

  	//table.Display();
  	
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
/*
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
*/	

	return 0;
}