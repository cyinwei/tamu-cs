#include "Heap.h"
#include "Digraph.h"
#include "Dijkstra.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

int main()
{	
	//intro
	cout<<"Hello! Welcome to Yinwei (Charlie) Zhang's implementation of Dijkstra's algorithm.\n"
		<<"This is for Biplab and Dr. Leyk's CSCE 221 class' final.\n\n"
		<<"Please enter a graph input file name (random_sparse.txt)\n";
	string input;
	while(cin>>input && (input!="quit" && input!="q")){
		try{
			ifstream in(input.c_str());
			if(!in.is_open()) throw runtime_error("File cannot be found. Try again");
			else{
				cout<<"File found! Which vertex do you want to set as your source?\n";
				cin>>input;
				int source = stoi(input);
				Digraph dg(in);
				Dijkstra alg(dg, source); 
				cout<<"\nDijkstra's algorithm is loaded with source ["<<source<<"]!\n"
						<<"Commands: \"show\" to see all the least paths.\n"
						<<"          \"vertex\" to show a particular vertex (+ path).\n"
						<<"          \"comparisons\" to show the number of comparisons.\n";

				while(cin>>input && input!="quit" && input!="q"){
					if(input == "s"||input == "show"){
						cout<<alg;
					}
					else if(input == "v"||input == "vertex"){
						cout<<"Which vertex from the source ["<<source<<"] do you want?\n\n";
						cin>>input;
						int v = stoi(input);
						alg.displayDistance(cout, v, true);
					} 
					else if(input == "c"||input == "comparisons"){
						cout<<"The algorithm has "<<alg.getTotalCount()<<"total comparisons, with "
							<<alg.getDecreaseCount()<<" from the decrease key, and "<<alg.getRemoveCount()
							<<" from the remove function.\n";
					}
					if(input!="quit" || input!="q"){
						cout<<"-----------------------------------------------------------------------"<<endl
							<<"You can try again, or type quit to quit.\n\n";
					}		
				}
				cout<<"\nYou can enter a new input file and specify a new vertex if you want,"
					<<"type quit to quit (for real)"<<endl;	
			}
		}
		catch(exception& e){ 
			cout<<"Error: "<<e.what()<<"."<<endl
				<<"Let's go all the way back to our input file."<<endl;
		}
	}	
}	