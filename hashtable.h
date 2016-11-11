#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

class Word{
	public:
		string word;
		string definition;

		int key(string w);
		Word getWord(string w);

};

class Dictionary{
	public:
		vector

		void Insert(Word newWord);
		bool Contains(string word);
		Word Delete(string word);
		void Rehash();

}

#endif