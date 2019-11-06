#include <iostream>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree()
{
  root = NULL;
}
void DeleteTree(MovieNode *tmp)
{
  if(tmp == NULL)
  {
    return;
  }
  DeleteTree(tmp -> leftChild);
  DeleteTree(tmp -> rightChild);
  delete tmp;
}
MovieTree::~MovieTree()
{
  DeleteTree(root);
}
void printHelper(MovieNode *current)
{
  if(current == NULL)
  {
    return;
  }
  else
  {
    printHelper(current -> leftChild);
    cout << "Movie: " << current->title << " " << current->rating << endl;
    printHelper(current -> rightChild);
  }

}
void MovieTree::printMovieInventory()
{
  if(root != NULL)
  {
    printHelper(root);
  }
}

void AddMovieHelper(MovieNode *tmp,MovieNode *insert)
{
  if(tmp -> title >= insert -> title)//left side
  {
    if(tmp -> leftChild == NULL)
    {
      tmp -> leftChild = insert;
    }
    else
    {
      AddMovieHelper(tmp -> leftChild,insert);
    }
  }
  else
  {
    if(tmp -> rightChild == NULL)
    {
      tmp -> rightChild = insert;
    }
    else
    {
      AddMovieHelper(tmp -> rightChild, insert);
    }
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating)
{
  // making a new node
  MovieNode *NewMovie = new MovieNode;
  // link the nodes to the variables
  NewMovie -> ranking = ranking;
  NewMovie -> title = title;
  NewMovie -> year = year;
  NewMovie -> rating =  rating;
  if(root == NULL)
  {
    root = NewMovie;
    return;
  }
  AddMovieHelper(root,NewMovie);
}

MovieNode* MovieTree::search(string title)
{
  MovieNode *tmp = root;
  if(root == NULL)
  {
    return NULL;
  }
  while(tmp != NULL)
  {
     if(tmp -> title == title)
    {
      return tmp;
    }
    if(tmp -> title > title)
    {
      tmp = tmp -> leftChild;
    }
    else
    {
      tmp = tmp -> rightChild;
    }
  }
  return NULL;
}

void MovieTree::findMovie(string title)
{
  MovieNode *found = search(title);
  if(found == NULL)
  {
    cout << "Movie not found." << endl;
    return;
  }
  cout << "Movie Info:" << endl;
  cout << "==================" << endl;
  cout << "Ranking:" << found -> ranking << endl;
  cout << "Title  :" << found -> title << endl;
  cout << "Year   :" << found -> year << endl;
  cout << "rating :" << found -> rating << endl;
}

void queryMoviesHelper(MovieNode *tmp,float rating, int year)
{
  if(tmp == NULL)
  {
    return;
  }
    if(tmp -> rating >= rating && tmp -> year > year)
    {
      cout << tmp->title << "(" << tmp->year << ") " << tmp->rating << endl;
    }

    queryMoviesHelper(tmp -> leftChild, rating, year);
    queryMoviesHelper(tmp -> rightChild, rating, year);
}

void MovieTree::queryMovies(float rating, int year)
{
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  queryMoviesHelper(root,rating,year);
}
 
int averageRatingHelper2(MovieNode *tmp, int counter) // this function will count all the nodes
{
  counter = 0;
  if(tmp != NULL)
  {
    counter++;
    counter += averageRatingHelper2(tmp -> leftChild, counter) + averageRatingHelper2(tmp -> rightChild, counter);
  }
  return counter;
}

double averageRatingHelper(MovieNode *tmp) // this function adds all the nodes together
{
  double i;
  if(tmp == NULL)
  {
      return 0;
  }
  if(tmp != NULL)
  {
    return tmp -> rating + averageRatingHelper(tmp -> leftChild) + averageRatingHelper(tmp -> rightChild);
  }
  return i;
}

void MovieTree::averageRating()
{
if(root == NULL)
{
    cout << "Average rating:0" << endl;
    return;
}
  double average =  averageRatingHelper(root)/averageRatingHelper2(root, 0);
  cout << "Average rating:" << average << endl;
}
