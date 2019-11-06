/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

int main()
{
  // TODO - Declare a stack to hold the operands
  RPNCalculator Stack;
  string input;

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    cin >> input;
    if(input == "=")
    {
      if(!Stack.isEmpty())
      {
        float output = Stack.peek() -> number;
        Stack.pop();
        if(Stack.isEmpty() ==  false)
        {
          cout << "invalid expression" << endl;
          break;
        }
        else
        {
          Stack.push(output);
          cout << output << endl;
          break;
        }
      }
      else
      {
        cout<<"No operands: Nothing to evaluate";
        return 0;
      }
    }
    if(isNumber(input))
    {
      Stack.push(stof(input));
    }
    else
    {
      Stack.compute(input);
    }



  }

  return 0;
}
