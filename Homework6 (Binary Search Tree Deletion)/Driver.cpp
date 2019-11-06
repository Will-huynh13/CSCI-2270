#include <iostream>
#include "MovieTree.hpp"
#include <fstream>
#include <sstream>
using namespace std;

void displayMenu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Print the inventory" << endl;
  cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;

}

int main(int argc, char *argv[])
{
  MovieTree run;
  TreeNode *root = NULL;
  string choice;
  string title;

  ifstream file_in;

  file_in.open("Documentaries.csv");

  string tmpline;
  if(file_in.is_open())
  {
    while(getline(file_in,tmpline))
    {
      stringstream lineIN(tmpline);
      string ranking, title, year, rating;
      getline(lineIN,ranking,',');
      getline(lineIN,title,',');
      getline(lineIN,year,',');
      getline(lineIN,rating);

      int IntergerRanking = stoi(ranking);
      int IntegerYear = stoi(year);
      float FloatRating = stof(rating);
      run.addMovie(IntergerRanking,title,IntegerYear,FloatRating);
    }
  }
  file_in.close();

  while(choice != "3")
  {
    displayMenu();
    getline(cin,choice);
    switch(stoi(choice))
    {
      case 1:
      run.printMovieInventory();
      break;

      case 2:
      cout << "Enter a movie title:" << endl;
      getline(cin,title);
      run.deleteMovie(title);
      break;

      case 3:
      cout << "Goodbye!" << endl;
      break;

    }

  }
  return 0;
}
