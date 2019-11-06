#include <iostream>
#include "MovieTree.hpp"
#include <fstream>
#include <sstream>
using namespace std;

void displayMenu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Query movies" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;
}

int main(int argc, char *argv[])
{
  MovieTree run = MovieTree();
  MovieNode *root = NULL;
  int choice;
  string title;
  int year;
  double rating;
  string array[4];

  ifstream file_in;

  file_in.open(argv[0]);

  string tmpline;
  int counter=0;
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
      run.addMovieNode(IntergerRanking,title,IntegerYear,FloatRating);
    }
  }
  file_in.close();

  while(choice != 5)
  {
    displayMenu();
    cin >> choice;
    cin.ignore();
    switch(choice)
    {
      case 1:
      cout << "Enter title:" << endl;
      getline(cin,title);
      //cin.ignore();
      run.findMovie(title);
      break;

      case 2:
      cout << "Enter minimum rating:" << endl;
      cin >> rating;
      cout << "Enter minimum year:" << endl;
      cin >> year;
      run.queryMovies(rating,year);
      break;

      case 3:
      run.printMovieInventory();
      break;

      case 4:
      run.averageRating();
      break;

      case 5:
      cout << "Goodbye!" << endl;
      break;

    }

  }
  return 0;
}
