#include <iostream>
#include "MovieTree.hpp"
using namespace std;


MovieTree::MovieTree()
{
  root = NULL;
}

void LLDelete(LLMovieNode *List)
{
  LLMovieNode * next;
  while(List != NULL)
  {
    next = List -> next;
    delete List;
    List = next;
  }
}
void DeleteALL(TreeNode *tmp)
{
  if(tmp == NULL)
  {
    return;
  }
  else
  {
    DeleteALL(tmp -> leftChild);
    LLDelete(tmp -> head);
    DeleteALL(tmp -> rightChild);
    delete tmp;
  }
}

MovieTree::~MovieTree()
{
  DeleteALL(root);
  root = NULL;
}

void printHelper(TreeNode *current)
{
  if(current == NULL)
  {
    return;
  }
  else
  {
    printHelper(current -> leftChild);
    LLMovieNode *t = current -> head;
    cout << "Movies starting with letter: " << current->titleChar << endl;
    while(t != NULL)
    {
      cout << " >> " << t->title << " " << t->rating << endl;
      t = t-> next;
    }
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

void addMovieHelper(TreeNode *current, LLMovieNode *insert)
{
  string s = insert -> title;
  if(current -> titleChar > s[0]) // basically the first letter in the title to be compared
  {
    if(current -> leftChild == NULL)
    {
      TreeNode *t = new TreeNode();
      t -> titleChar = s[0];
      current -> leftChild = t;
      t -> rightChild = NULL;
      t -> leftChild = NULL;
      t -> parent = current;
      t -> head = insert;
    }
    else
    {
      addMovieHelper(current ->leftChild,insert);
    }
  }
  else if(current -> titleChar < s[0])
  {
    if(current -> rightChild == NULL)
    {
      TreeNode *t = new TreeNode();
      t -> titleChar = s[0];
      current -> rightChild = t;
      t -> rightChild = NULL;
      t -> leftChild = NULL;
      t -> parent = current;
      t -> head = insert;
    }
    else
    {
      addMovieHelper(current -> rightChild, insert);
    }
  }
  else
  {
    LLMovieNode *tmp = current -> head;
    LLMovieNode *prev = current -> head;
    while(tmp->title < insert -> title)
    {
      prev = tmp;
      if(tmp->next == NULL){
          tmp = NULL;
          break;
      }
      else
        tmp = tmp->next;
    }
    if(prev == tmp)
    {
      if(prev -> next == NULL)
      {
        insert -> next = prev;
        current -> head = insert;
      }
    }
    else
    {
      prev -> next = insert;
      insert -> next = tmp;
    }
  }
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  LLMovieNode *tmp = new LLMovieNode();
  tmp -> ranking = ranking;
  tmp -> title = title;
  tmp -> year = year;
  tmp -> rating = rating;

  if(root == NULL)
  {

    TreeNode *t  = new TreeNode();
    t -> titleChar = title[0];
    t -> leftChild = NULL;
    t -> rightChild = NULL;
    t -> parent = NULL;
    t -> head = tmp;
    root = t;

  }
  else
  {
    addMovieHelper(root,tmp);
  }
}

TreeNode* getMinValueNode(TreeNode* currNode)
{

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

TreeNode* deleteSearch(TreeNode *root, string title)
{
  if(root == NULL)
  {
    return NULL;
  }
  while(root != NULL)
  {
    if(root -> titleChar == title[0])
    {
      return root;
    }
    if(root -> titleChar > title[0])
    {
      root = root -> leftChild;
    }
    else
    {
      root = root -> rightChild;
    }
  }
  return root;
}

TreeNode* deleteRoot(TreeNode *root, char val)
{
    if(root == NULL)
    {
      return NULL;
    }
    if(root->leftChild == NULL && root->rightChild == NULL)
    {
      delete root;
      root = NULL;
    }
    //TODO Case : Only right child
    else if(root->leftChild == NULL)
    {
      TreeNode *tmp = root;
      root = root -> rightChild;
      delete tmp;
    }
    //TODO Case : Only left child
    else if(root->rightChild == NULL)
    {
      TreeNode *tmp = root;
      root = root -> leftChild;
      delete tmp;
    }
    //TODO Case: Both left and right child
    else
    {
      ///Replace with Minimum from right subtree
      TreeNode *tmp = getMinValueNode(root -> rightChild);
      // root -> titleChar = tmp -> titleChar;
      // root -> head = tmp -> head;
      tmp->parent->leftChild = tmp->rightChild;
      tmp->leftChild = root->leftChild;
      tmp->rightChild = root->rightChild;
      return tmp;

    }
    return root;
}

TreeNode* deleteNode(TreeNode *currNode, char value)
{

  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->titleChar)
  {
    currNode->leftChild = deleteNode(currNode->leftChild, value);
  }
  else if(value > currNode->titleChar)
  {
    currNode->rightChild = deleteNode(currNode->rightChild, value);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode->leftChild == NULL && currNode->rightChild == NULL)
    {
      delete currNode;
      currNode = NULL;
    }
    //TODO Case : Only right child
    else if(currNode->leftChild == NULL)
    {
      TreeNode *tmp = currNode;
      currNode = currNode -> rightChild;
      delete tmp;
    }
    //TODO Case : Only left child
    else if(currNode->rightChild == NULL)
    {
      TreeNode *tmp = currNode;
      currNode = currNode -> leftChild;
      delete tmp;
    }
    //TODO Case: Both left and right child
    else
    {
      ///Replace with Minimum from right subtree
      TreeNode *tmp = getMinValueNode(currNode -> rightChild);
      currNode -> titleChar = tmp -> titleChar;
      currNode -> head = tmp -> head;
      currNode -> rightChild = deleteNode(currNode -> rightChild, tmp -> titleChar);
    }
  }
return currNode;
}

void DeleteLL(TreeNode *current, string title)
 {
     LLMovieNode *temp = new LLMovieNode;
     LLMovieNode *temp2 = new LLMovieNode;
     temp = current -> head;
     if(temp && temp->title == title)
     {
        delete current -> head;
         current -> head = temp -> next;
         return;
     }
     while(temp->next != NULL && temp->next->title != title)
     {
         temp = temp->next;
     }
     if(temp->next != NULL)
     {
         temp2 = temp->next;
         temp->next = temp2->next;
         delete temp2;
         return;
     }
     else
     {
         cout << "Movie: " << temp -> title << " not found, cannot delete." << endl;
     }
 }

void MovieTree::deleteMovie(string title)
{
  TreeNode *tmp = deleteSearch(root,title);
  if(tmp == NULL)
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
    return;
  }
  else
  {
    DeleteLL(tmp,title);
    if(tmp -> head == NULL)
    {
      if (tmp==root)
      { char c = title[0];
        root = deleteRoot(root,c);
      }
      else{
      char c = title[0];
      deleteNode(root,c);
      return;
    }
    }
  }
}
