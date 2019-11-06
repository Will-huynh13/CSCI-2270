#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "PriorityQueue.hpp"
using namespace std;


void displayMenu()
{
   cout << "============Main Menu============" << endl;
   cout << "1. Get group information from file" << endl;
   cout << "2. Add a group to Priority Queue" << endl;
   cout << "3. Show next group in the queue" << endl;
   cout << "4. Serve Next group" << endl;
   cout << "5. Serve Entire Queue" << endl;
   cout << "6. Quit" << endl
}


int main(int argc, char *argv[])
{
   PriorityQueue priorityQueue(stoi(argv[1]));
   string choice;
   int QueueSize = stoi(argv[1]);
   string filename;
   int totalCookTime = 0;

   while(choice != "6")
   {
      displayMenu();
      getline(cin,choice);
      switch(stoi(choice))
      {
         case 1:
         {
            cout << "Enter filename:" << endl;
            getline(cin,filename);
            ifstream file_in;
            file_in.open(filename);
            string templine;
            if(file_in.is_open())
            {
               while(getline(file_in,templine))
               {
                  stringstream lineIN(templine);
                  string name, size, time;
                  getline(lineIN,name,' ');
                  getline(lineIN,size,' ');
                  getline(lineIN,time,' ');

                  int PartySize  = stoi(size);
                  int _Time = stoi(time);
                  priorityQueue.enqueue(name,PartySize,_Time);
               }
            }
         file_in.close();
                  break;
      }


         case 2:
         {
            string name, g, time;
            if(!priorityQueue.isFull())
            {
               cout << "Enter Group Name:" << endl;
               getline(cin, name);
               cout << "Enter Group Size:" << endl;
               getline(cin, g);
               cout << "Enter Estimated Cooking Time:" << endl;
               getline(cin, time);

               int _g = stoi(g);
               int _time = stoi(time);
               priorityQueue.enqueue(name,_g,_time);
            }
            break;
         }

         case 3:
         {
            if(!priorityQueue.isEmpty())
            {
               cout << "Group Name: " << priorityQueue.peek().groupName << endl;
               cout << "Group Size: " << priorityQueue.peek().groupSize << endl;
               cout << "Group Time: "<< priorityQueue.peek().cookingTime << endl;
            }
            else
            {
               cout << "Heap empty, nothing to peek" << endl;
            }
            break;

         }
         case 4:
         {
            totalCookTime += priorityQueue.peek().cookingTime;
            cout << "Group Name: " << priorityQueue.peek().groupName<< " - Total Cook Time for the Group: "<< totalCookTime << endl;
            priorityQueue.dequeue();
            break;
         }

         case 5:
         {
            while(!priorityQueue.isEmpty())
            {
               totalCookTime += priorityQueue.peek().cookingTime;
               cout << "Group Name: " << priorityQueue.peek().groupName<< " - Total Cook Time for the Group: "<< totalCookTime << endl;
               priorityQueue.dequeue();
            }


            break;
         }

         case 6:
         {
            cout << "Goodbye!" << endl;
         }

      }
   }


}
