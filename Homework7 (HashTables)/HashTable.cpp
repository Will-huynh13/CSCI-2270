#include "HashTable.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

HashTable::HashTable(int TableSize)
{
  this -> hashTableSize = TableSize;
  hashTable =  new wordItem *[hashTableSize];
  for(int i = 0; i < TableSize; i++)
  {
    hashTable[i] = NULL;
  }

}

HashTable::~HashTable()
{
  for(int i = 0; i < hashTableSize; i++)
  {
    wordItem *tmp = hashTable[i];
    while(tmp != NULL)
    {
      wordItem *tmp2 = tmp -> next;
      delete tmp;
      tmp = tmp2;
    }
  }
  delete[] hashTable;

}

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable)
{
  ifstream IgnoreWords(ignoreWordFileName);

  if(IgnoreWords.fail())
  {
    exit(0);
  }

  string temp;

  while(getline(IgnoreWords,temp))
  {
    stopWordsTable.addWord(temp);
  }

  IgnoreWords.close();
}

unsigned int HashTable::getHash(std::string word)
{
  unsigned int hashValue = 5381;
  int length = word.length();
  for (int i=0;i<length;i++)
  {
  hashValue=((hashValue<<5)+hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

void HashTable::addWord(std::string word)
{
  wordItem *NewWord = new wordItem;
  NewWord -> word = word;
  NewWord -> next = NULL;
  NewWord -> count = 1;
  int hash = getHash(word);
  wordItem *tmp = hashTable[hash];
  if(tmp != NULL)
  {
    numCollisions = numCollisions + 1;
    NewWord -> next = hashTable[hash];
    hashTable[hash] = NewWord;
  }
  else
  {
    hashTable[hash] = NewWord;
  }
  numItems++;
}

wordItem* HashTable::searchTable(std::string word)
{
    wordItem* temp = hashTable[getHash(word)];
    while(temp != NULL && temp->word != word)
    {
        temp=temp->next;
    }
    return temp;
}

bool isStopWord(std::string word,HashTable &stopWordsTable)
{
  return stopWordsTable.isInTable(word);
}

bool HashTable::isInTable(std::string word)
{
  bool isInTable;

  wordItem *tmp = searchTable(word);
  if(tmp == NULL)
  {
    isInTable = false;
  }
  else
  {
    isInTable = true;
  }
  return isInTable;
}

void HashTable::incrementCount(std::string word)
{
  wordItem *tmp = searchTable(word);
  tmp -> count += 1;
}

void HashTable::printTopN(int n)
{
    wordItem* Arr[n];
    int ItemsInArray = 0;
    int minimumValue = 0;

    for (int i = 0;i < hashTableSize;i++)
    {
        wordItem* temp = hashTable[i];
        while(temp != nullptr)
        {

            if(temp->count > minimumValue)
            {
                int j = ItemsInArray;
                while(j > 0 && (temp->count > Arr[j-1]->count))
                {
                    Arr[j] = Arr[j-1];
                    j = j - 1;
                }
                Arr[j] = temp;
                ItemsInArray = min(ItemsInArray + 1, n);
                minimumValue = Arr[ItemsInArray - 1]->count;
            }
            temp = temp->next;
        }
    }
    for(int i = 0; i < n;i++)
    {
        cout << setprecision(4) << fixed << double(Arr[i]->count)/double(getTotalNumWords()) << " - " << Arr[i]->word << endl;
    }
    return;
}

int HashTable::getNumCollisions()
{
  return numCollisions;
}

int HashTable::getNumItems()
{
  return numItems;

}

int HashTable::getTotalNumWords()
{
    int count = 0;
    for(int i = 0;i<hashTableSize;i++)
    {
        wordItem* temp = hashTable[i];
        while(temp != NULL)
        {
            count += temp->count;
            temp = temp->next;
        }
    }
    return count;
}
