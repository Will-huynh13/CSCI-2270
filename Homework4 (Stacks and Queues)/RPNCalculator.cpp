#include "RPNCalculator.hpp"
#include <iostream>
using namespace std;

RPNCalculator::RPNCalculator()
{
  stackHead = NULL;
}

RPNCalculator::~RPNCalculator()
{
  while(!isEmpty())
  {
      pop();
  }
  stackHead = NULL;
}

bool RPNCalculator::isEmpty()
{
  if(stackHead == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void RPNCalculator::push(float number)
{
    Operand *tmp = new Operand;
    tmp -> number = number;
    tmp -> next = NULL;
    if(stackHead == NULL)
    {
      stackHead = tmp;
    }
    else
    {
      tmp -> next = stackHead;
      stackHead = tmp;
    }
}

void RPNCalculator::pop()
{
  if(!isEmpty())
  {
    Operand *tmp = NULL;
    tmp = stackHead;
    stackHead = tmp -> next;
    delete tmp;
  }
  else
  {
    cout<<"Stack empty, cannot pop an item."<<endl;
  }
}

Operand* RPNCalculator::peek()
{
  if(!isEmpty())
  {
    return stackHead;
  }
  else
  {
    cout << "Stack empty, cannot peek." <<endl;
    return NULL;
  }

}

bool RPNCalculator::compute(string symbol)
{
  if(symbol == "*" || symbol == "+")
  {
    if(!isEmpty())
    {
      Operand *tmp = stackHead;
      if(tmp)
      {
        float calculation1 = tmp -> number;
        pop();
        Operand *tmp2 = stackHead;
        if(tmp2 != NULL)
        {
          float calculation2 = tmp2 -> number;
          pop();
          if(symbol == "*")
          {
            float multi = calculation1 * calculation2;
            push(multi);
            return true;
          }
          else if(symbol == "+")
          {
            float add = calculation1 + calculation2;
            push(add);
            return true;
          }
        }
        else
        {
          cout << "err: not enough operands" << endl;
          push(calculation1);
          return false;
        }
    }
    else
    {
      cout << "err: not enough operands" << endl;
      return false;
    }
  }
  else
  {
    cout << "err: not enough operands" << endl;
    return false;
  }
}
else
{
  cout << "err: invalid operation" << endl;
  return false;
}
}
