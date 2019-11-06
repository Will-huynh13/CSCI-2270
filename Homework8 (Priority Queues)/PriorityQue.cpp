#include <iostream>
#include "PriorityQueue.hpp"
#include <queue>
#include <string>

using namespace std;

PriorityQueue::PriorityQueue(int queueSize)
{
   currentQueueSize = 0;
   maxQueueSize = queueSize;
   priorityQueue = new GroupNode[maxQueueSize];

}

PriorityQueue::~PriorityQueue()
{
   delete [] priorityQueue;
}

int parent(int index) //helper function to find the index of parent
{
  return (index-1)/2;
}

int leftChild(int index)
{
  return ((2*index) + 1);
}

int rightChild(int index)
{
  return ((2*index) + 2);
}

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

bool isGreater(GroupNode currentGroup, GroupNode group2)
{
   if(currentGroup.groupSize > group2.groupSize)
   {
      return true;
   }
   if(currentGroup.groupSize == group2.groupSize)
   {
      if(currentGroup.cookingTime > group2.cookingTime)
      {
         return true;
      }
      return false;
   }
   return false;

}

void PriorityQueue::enqueue(std::string _groupName, int _groupSize, int _cookingTime)
{
   if(currentQueueSize == maxQueueSize)
   {
      cout << "Heap full, cannot enqueue" << endl;
   }
   else
   {
      currentQueueSize++;
      int i = currentQueueSize -1;
      priorityQueue[i].groupName = _groupName;
      priorityQueue[i].groupSize = _groupSize;
      priorityQueue[i].cookingTime = _cookingTime;

      if(i != 0 && isGreater(priorityQueue[parent(i)] ,priorityQueue[i]))
      {
         swap(priorityQueue[i], priorityQueue[parent(i)]);
         repairUpward(parent(i));
      }

   }
}

void PriorityQueue::dequeue()
{
   if(currentQueueSize == 0)
   {
      cout << "Heap empty, cannot dequeue" << endl;
   }
   else
   {
      priorityQueue[0] = priorityQueue[currentQueueSize-1];
      currentQueueSize--;
      repairDownward(0);
   }
}

GroupNode PriorityQueue::peek()
{
   if(isEmpty())
   {
      cout << "Heap empty, cannot peek" << endl;
   }
   return priorityQueue[0];
}

bool PriorityQueue::isFull()
{
   if(currentQueueSize == maxQueueSize)
   {
      return true;
   }
   else
   {
      return false;
   }

}

bool PriorityQueue::isEmpty()
{
   if(currentQueueSize == 0)
   {
      return true;
   }
   else
   {
      return false;
   }
}

void PriorityQueue::repairUpward(int nodeIndex)
{
   while(nodeIndex != 0 && isGreater(priorityQueue[parent(nodeIndex)],priorityQueue[nodeIndex]))
   {
      swap(priorityQueue[nodeIndex], priorityQueue[parent(nodeIndex)]);
      nodeIndex = parent(nodeIndex);
   }
}

void PriorityQueue::repairDownward(int nodeIndex)
{
   int left = leftChild(nodeIndex);
   int right = rightChild(nodeIndex);
   int smallest  = nodeIndex;

   if(left < currentQueueSize && isGreater(priorityQueue[nodeIndex], priorityQueue[left]))
   {
      smallest = left;
   }

   if(right < currentQueueSize && isGreater(priorityQueue[smallest],priorityQueue[right]))
   {
      smallest = right;
   }

   if(smallest != nodeIndex)
   {
      swap(priorityQueue[nodeIndex], priorityQueue[smallest]);
      repairDownward(smallest);
   }
}
