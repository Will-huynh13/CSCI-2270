#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::addVertex(string cityName)
{
   vertex v;
   v.name = cityName;
   vertices.push_back(v);
}

void Graph::addEdge(string city1, string city2, int distance)
{
   Edge e;
   e.distance = distance;
   for(int i = 0; i < vertices.size();i++)
   {
      if(vertices[i].name == city1)
      {
         for(int j =0; j < vertices.size(); j++)
         {
            if(vertices[j].name == city2 && i != j)
            {
                e.v = &vertices[j];
               vertices[i].Edges.push_back(e);
            }
         }
      }
   }
}

void Graph::displayEdges()
{
   for(int i = 0; i < vertices.size(); i++)
   {
      cout << vertices[i].name << "-->";
      for(int j = 0; j < vertices[i].Edges.size(); j++)
      {
        cout << vertices[i].Edges[j].v->name << " " << "(" << vertices[i].Edges[j].v.distance << " miles)";
        if(j != vertices[i].Edges.size() - 1)
        {
           cout << "***";
        }
      }
      cout << endl;
   }
}
void Graph::setAllVerticesUnvisited()
{
   for(int i = 0; i < vertices.size(); i++)
   {
      vertices[i].Edges = false;
   }
}

void Graph::printBFT()
{
    setAllVerticesUnvisited();
   for(int i = 0; i < vertices.size(); i++)
   {
      if(!vertices[i].visited)
      {
         BFT_traversal(&vertices[i]);
      }
   }
}

void Graph::BFT_traversal(vertex *v)
{

   v -> visited = true;

   queue<vertex*> q;

   q.push(v);

   vertex *newQ;

   while(!q.empty())
   {
      newQ = q.front();
      q.pop();
      std::cout << newQ->name << endl;

      for (int j = 0; j < newQ->Edges.size();j++)
      {
         if(!newQ->Edges[j].v->visited)
         {
            newQ->Edges[j].v->visited = true;
            q.push(newQ->Edges[j].v);
         }
      }
   }
}

void Graph::printDFT()
{
    setAllVerticesUnvisited();
   for(int i = 0; i < vertices.size(); i++)
   {
      if(!vertices[i].visited)
      {
        DFT_traversal(&vertices[i]);
      }
   }
}

void Graph::DFT_traversal(vertex *v)
{
   v -> visited = true;
   std::cout << v->name << endl;

   for(int i = 0; i < v->Edges.size(); i++)
   {
      if(!v->Edges[i].v->visited)
      {
         DFT_traversal(v->Edges[i].v);
      }
   }
}


vertex* Graph::findVertex(string name)
{
   for(int i = 0; i < vertices.size();i++)
   {
      if(vertices[i].name == name)
      {
         return &vertices[i];
      }
   }
   return NULL;
}
