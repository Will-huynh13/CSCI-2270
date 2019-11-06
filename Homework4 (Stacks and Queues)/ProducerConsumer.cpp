#include "ProducerConsumer.hpp"
#include <iostream>
using namespace std;

ProducerConsumer::ProducerConsumer()
{
  queueFront = -1;
  queueEnd = -1;
}
bool ProducerConsumer::isEmpty()
{
  if(queueFront == -1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool ProducerConsumer::isFull()
{
  if((queueFront == 0 && queueEnd == SIZE - 1) || (queueEnd == (queueFront - 1) % (SIZE - 1)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void ProducerConsumer::enqueue(string item)
{
  if(isFull())
  {
    cout << "Queue full, cannot add new item" << endl;
    return;
  }
  if(isEmpty())
  {
    queueFront = 0;
    queueEnd = 0;
  }
  else
  {
    queueEnd = (queueEnd + 1) % SIZE;
  }
  queue[queueEnd] = item;
}

void ProducerConsumer::dequeue()
{
  if(isEmpty())
  {
    cout << "Queue empty, cannot dequeue an item" << endl;
    return;
  }

  string input = queue[queueFront];
  queue[queueFront] = -1;

  if(queueFront == queueEnd)
  {
    queueEnd = -1;
    queueFront = -1;
  }
  else if(queueFront == SIZE - 1)
  {
    queueFront = 0;
  }
  else
  {
    queueFront++;
  }
}

int ProducerConsumer::queueSize()
{
  if (isEmpty())
  {
    return 0;
  }
  int index = 0;
  if (queueEnd >= queueFront)
  {
    for(int i = queueFront; i <= queueEnd; i++)
    {
      index++;
    }
  }
  else
  {
    for (int i = queueFront; i < SIZE; i++)
    {
      index++;
    }
    for (int i = 0; i <= queueEnd; i++)
    {
      index++;
    }
  }
  return index;
}

string ProducerConsumer::peek()
{
    if(!isEmpty())
    {
      return queue[queueFront];
    }
    else
    {
      cout << "Queue empty, cannot peek" << endl;
      return "";
    }

}
