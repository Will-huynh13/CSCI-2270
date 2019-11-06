#include "CountryNetwork.hpp"
#include <string>
using namespace std;

void displayMenu();
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

int main(int argc, char *argv[])
{
  CountryNetwork run;
  Country *head = NULL;
  string choice;
  string StringToCountry;
  string msg;
  string name;
  string name2;


      while (choice != "8")
      {
              displayMenu();
              getline(cin, choice);
              switch (stoi(choice))
              {
                  case 1:
                      run.loadDefaultSetup();
                  case 2:
                      run.printPath();
                      break;
                  case 3:
                      cout << "Enter name of the country to receive the message: " << endl;
                      getline(cin,StringToCountry);
                      cout << endl;
                      cout << "Enter the message to send: " << endl;
                      getline(cin,msg);
                      run.transmitMsg(StringToCountry,msg);
                      break;

                  case 4:
                  			cout << "Enter a new country name:" << endl;
                  			getline(cin, name);
                  			cout << "Enter the previous country name (or First):" << endl;
                  			getline(cin, name2);
                  			if (name2 == "First")
                        {
                  				head = NULL;
                  			}
                        else
                        {
                  				head = run.searchNetwork(name2);
                  				while (head == NULL)
                          {
                  					cout << "INVALID country...Please enter a VALID previous country name:" << endl;
                  					getline(cin, name2);
                  					if (name2 == "First")
                            {
                  						head = NULL;
                  						break;
                  					}
                  					head = run.searchNetwork(name2);
                  				}
                  			}

                  			cout << endl;
                  			run.insertCountry(head, name);
                  			run.printPath();

                      break;
                  case 5:
                      cout << "Enter a country name:" << endl;
                			getline(cin, name);
                			run.deleteCountry(name);
                			run.printPath();
                  case 6:
                      run.reverseEntireNetwork();
                      run.printPath();
                      break;

                  case 7:
                      run.deleteEntireNetwork();
                      break;


                  case 8:

                  			cout << "Quitting... cleaning up path: " << endl;
                  			run.printPath();
                  			if (!run.isEmpty())
                        {
                  				run.deleteEntireNetwork();
                  			}
                  			if (run.isEmpty())
                        {
                  				cout << "Path cleaned" << endl;
                  			}
                  			else
                        {
                  				cout << "Error: Path NOT cleaned" << endl;
                    		}
                        cout << "Goodbye!" << endl;
                        break;
                    	}
                    }
                  }
