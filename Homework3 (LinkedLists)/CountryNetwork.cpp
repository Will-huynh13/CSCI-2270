/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
 bool CountryNetwork::isEmpty()
 {
     return (head == NULL);
 }

/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
 void CountryNetwork::insertCountry(Country* previous, string countryName)
 {
     Country *NewCountry = new Country();
     NewCountry->name = countryName;

     if(previous == NULL)
     {
         NewCountry->next = head;
         head = NewCountry;
         cout << "adding: " << countryName << " (HEAD) " << endl;
     }
      else
      {
         NewCountry->next = previous->next;
         previous->next = NewCountry;
         cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
     }
 }

/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
 void CountryNetwork::deleteCountry(string countryName)
  {
      Country *temp = new Country;
      Country *temp2 = new Country;
      temp = head;
      if(temp && temp->name == countryName)
      {
          head = head->next;
          return;
      }

      while(temp->next != NULL && temp->next->name != countryName)
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
          cout << "Country does not exist." << endl;
      }
  }


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
 void CountryNetwork::loadDefaultSetup()
 {
    insertCountry(head,"United States");
    Country *tmp = new Country;
    tmp = head;
    insertCountry(tmp,"Canada");
    tmp = tmp->next;
    insertCountry(tmp,"Brazil");
    tmp = tmp->next;
    insertCountry(tmp,"India");
    tmp = tmp->next;
    insertCountry(tmp,"China");
    tmp = tmp->next;
    insertCountry(tmp,"Australia");
 }


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
 Country* CountryNetwork::searchNetwork(string countryName)
 {
     Country *tmp = head;

     while(tmp != NULL && tmp->name != countryName)
     {
         tmp = tmp->next;
     }
     if(tmp != NULL)
     {
         return tmp;
     }
     else
     {
         return NULL;
     }
 }

/*
 * Purpose: deletes all countries in the network temping at the head country.
 * @param none
 * @return none
 */
 void CountryNetwork::deleteEntireNetwork()
 {
    Country *tmp = new Country;
    while(head->next != NULL)
    {
        tmp = head->next;
        cout << "deleting: " << head->name << endl;
        delete head;
        head = tmp;
    }
    cout << "deleting: " << head->name << endl;
    head = NULL;
    cout << "Deleted network" << endl;
    cout << "Path cleaned" << endl;
    cout << "Goodbye!" << endl;
 }


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
 void CountryNetwork::transmitMsg(string receiver, string message)
 {
    Country *SentMessage = new Country;
    SentMessage = head;

     if(head == NULL)
    {
         cout << "Empty list" << endl;
     }
    else
    {
        while(SentMessage != NULL && SentMessage->name != receiver)
        {
            SentMessage->numberMessages = SentMessage->numberMessages + 1;
            SentMessage->message = message;
            cout << SentMessage->name << " [# messages received: " << SentMessage->numberMessages << "] received: " << SentMessage->message << endl;
            SentMessage = SentMessage->next;
        }
        SentMessage->numberMessages = SentMessage->numberMessages +1;
        SentMessage->message = message;
        cout << SentMessage->name << " [# messages received: " << SentMessage->numberMessages << "] received: " << SentMessage->message << endl;
        }
 }


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
 void CountryNetwork::printPath()
 {
     if(isEmpty())
     {
         cout << "Nothing in path!" << endl;
         return;
     }

     cout << "== CURRENT PATH ==" << endl;
     Country *tmp = head;

     while(tmp != NULL)
     {
         cout << tmp->name << " -> ";
         tmp = tmp->next;
     }
     cout << "NULL" << endl << "===" << endl;
     cout << endl;
 }


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
 void CountryNetwork::reverseEntireNetwork()
 {
      Country *current = head;
      Country *prev = NULL, *next = NULL;
      while (current != NULL)
      {
          next = current->next;
          current->next = prev;
          prev = current;
          current = next;
      }
      head = prev;
 }
