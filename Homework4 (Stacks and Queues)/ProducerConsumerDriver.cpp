/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
  cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer run;
  int choice;
	string a,b,c;
	int number;
	int counter  =0;
      while (choice != 3)
      {
              menu();
              cin >> choice;
              switch (choice)
              {
                  case 1:
											cout << "Enter the number of items to be produced:" << endl;
											cin >> number;
										for(int i = 0; i < number; i++)
											{
												cout << "Item" << i + 1 << ":" << endl;
												cin >> a;
												run.enqueue(a);
											}
											break;
                  case 2:
											cout << "Enter the number of items to be consumed:" << endl;
											cin >> number;
												for(int i = 0; i < number;i++)
												{
													if(run.isEmpty())
													{
														cout << "No more items to consume from queue" << endl;
													}
													else
													{
														cout << "Consumed: " << run.peek() << endl;
														run.dequeue();
													}
												}
                      break;
                  case 3:
									cout << "Number of items in the queue:" << run.queueSize() << endl;
                      break;
										}
									}
								}
