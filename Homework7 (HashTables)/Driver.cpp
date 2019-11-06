#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "HashTable.hpp"
using namespace std;


int main(int argc, char *argv[])
{
  HashTable stopWordsTable(STOPWORD_TABLE_SIZE);
  HashTable ht(atoi(argv[4]));
  getStopWords(argv[3], stopWordsTable);

  ifstream file_in;
  file_in.open(argv[2]);
  if(file_in.is_open())
  {
    string str;
    while(file_in >> str)
    {
      if(!isStopWord(str, stopWordsTable))
      {
        if(ht.isInTable(str))
        {
          ht.incrementCount(str);
        }
        else
        {
          ht.addWord(str);
        }
      }
    }
  }
  else
  {
    cout << "Cannot open file." << endl;
  }
  ht.printTopN(atoi(argv[1]));
  cout << "#" << endl;
  cout << "Number of collisions: " << ht.getNumCollisions() << endl;
  cout << "#"<<endl;
  cout << "Unique non-stop words: " << ht.getNumItems() << endl;
  cout << "#" << endl;
  cout << "Total non-stop words: " << ht.getTotalNumWords() << endl;
  return 0;
}
