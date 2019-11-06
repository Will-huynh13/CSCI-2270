#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

struct wordItem
{
  string word;
  int count;

};

void getStopWords(char *ignoreWordFileName, string ignoreWords[])
{
   ifstream IgnoreWords(ignoreWordFileName);

   if (IgnoreWords.fail())
   {
       exit(0);
   }

   string tempLine;
   int index = 0;
   while (getline(IgnoreWords, tempLine))
   {
     if(index < 50)
     {
       ignoreWords[index] = tempLine;
       index++;
     }
   }
   IgnoreWords.close();
}

bool isStopWord(string word, string ignoreWords[])
{
  int size = 50;
  for(int i = 0; i < 50; i++)
  {
    if(word ==  ignoreWords[i])
    {
      return true;
    }
  }
    return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
    int total=0;
    for(int i = 0; i < length; i++)
    {
        total += uniqueWords[i].count;
    }
    return total;
}

void arraySort(wordItem uniqueWords[], int length)
{
  wordItem temp;
  for(int i = 0; i < length; i++)
  {
    for(int j = 0; j < length -1; j++)
    {
      if(uniqueWords[j+1].count > uniqueWords[j].count)
      {
        temp = uniqueWords[j];
        uniqueWords[j] = uniqueWords[j+1];
        uniqueWords[j+1] = temp;
      }
    }
  }
}

void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
  for(int i = 0; i < topN; i++)
  {
        float result = (double)uniqueWords[i].count/(double)totalNumWords;
        cout << setprecision(4) << fixed << result + 0.00002 << " - " << uniqueWords[i].word << endl;
  }
}

void ArrayDoubling(wordItem * & pointerArray, int * length)
{
  int newLength = * length * 2;
  wordItem * newArray = new wordItem[newLength];
  for (int i = 0; i < * length; i++)
  {
    newArray[i] = pointerArray[i];
  }
  delete[] pointerArray;
  pointerArray = newArray;
  * length = newLength;
}

int main(int argc, char *argv[])
{
  int length = 100;
  wordItem * UniArray = new wordItem[length];
  int index = 0;
  int numDoublings = 0;
  string Word;
  string ignoreWords[100];

  getStopWords(argv[3], ignoreWords);

  ifstream in_file(argv[2]);

  if (in_file.fail())
  {
    cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordFileName.txt" << endl;
  }

  while (in_file >> Word)
  {
    bool sameWord = false;
    if (!isStopWord(Word, ignoreWords))
    {
      for (int i = 0; i < length; i++)
      {
        if (UniArray[i].word == Word)
        {
          UniArray[i].count++;
          sameWord = true;
          break;
        }
      }
      if (index == length)
      {
        ArrayDoubling(UniArray, & length);
        numDoublings++;
      }
      if (!sameWord)
      {
        UniArray[index++].word = Word;
        sameWord = false;
      }
    }
  }
  in_file.close();
  int numTOt = getTotalNumberNonStopWords(UniArray,length)+index;
  arraySort(UniArray, index);
  cout << "Array doubled: " << numDoublings << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << index << endl;
  cout << "#" << endl;
  cout << "Total non-common words: " << numTOt << endl;
  cout << "#" << endl;
  cout << "Probabilities of top " << argv[1] << " most frequent words" << endl;
  cout << "---------------------------------------" << endl;
  printTopN(UniArray,stoi(argv[1]),numTOt);
  return 0;


}
