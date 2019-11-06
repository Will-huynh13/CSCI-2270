#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
   Graph g;
   vector<string> citynames;
   int number;
   ifstream in_file;
   in_file.open(argv[1]);
   string templine;
   string templine2;
   if(in_file.is_open())
   {
      getline(in_file,templine);
      stringstream ss(templine);

      while(getline(ss,templine2,','))
      {
         if(templine2 != "cities")
         {
            g.addVertex(templine2);
            citynames.push_back(templine2);
         }
      }
      int counter = 0;
      while(getline(in_file,templine))
      {
         int counter2 = 0;
         istringstream ss2(templine);
         getline(ss2, templine2, ',');

         while(getline(ss2, templine2, ','))
         {
            istringstream(templine2) >> number;
            if(number > 0)
            {
               cout << " ... Reading in " << citynames[counter] << " -- " << citynames[counter2] << " -- " << number << endl;
               g.addEdge(citynames[counter], citynames[counter2], number);

            }
            counter2++;
         }
         counter++;
      }
   }

   cout << "------------------------------ " << endl
   << "Breadth First Traversal" << endl
   << "------------------------------" << endl;
   g.printBFT();
   cout << "------------------------------ " << endl
   << "Depth First Traversal" << endl
   << "------------------------------"<< endl;
   g.printDFT();
   cout << "------------------------------ " << endl
   << "Display Edges" << endl
   << "------------------------------"<< endl;
   g.displayEdges();
   return 0;
}
