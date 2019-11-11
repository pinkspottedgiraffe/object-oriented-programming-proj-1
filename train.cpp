#include <cstring>
#include <cstdlib>
#include <iostream>
#include "train.h"

using namespace std;


float ticketprice1=1.4;
float ticketprice2=0.6;
const int maxCapacity=20;

class waggons;
class commuter;


train::train(int N):fines(0),stations(N)			//train constructor
{
	cout << "a train with " << totalWaggons << " waggons was created" << endl;
}

train::~train(){									//train destructor
	cout << "a metro train was destroyed" << endl;
}

void train::printStatistics(){
	for(int i=0;i<totalWaggons; i++){
		fines=fines+waggons_Array[i].get_fines();
	}
	cout << "total fines from train are " << fines << endl;		//prints fines from all of the train
	
	
}

int train::operate(){
	for(int i=0;i<stations-1;i++){					//loop for all stations except the last one
		cout << "In station " << i << endl;
		for(int j=0;j<totalWaggons;j++){			//loop for all the waggons
			cout << "In waggon " << j << endl;
			waggons_Array[j].inStation();
			waggons_Array[j].betweenStations();
			waggons_Array[j].printStatistics();
		}
	}
	cout << "In station " << stations-1 << endl;	//for last station
	for(int j=0;j<totalWaggons;j++){				//removes all passengers from waggons;
		waggons_Array[j].remove_all_com();
	}
	printStatistics();
}



waggons::waggons():numofpeople(0),notickets1(0),notickets2(0),notcaught(0)
{
	comarray=new commuter*[maxCapacity];
	for(int i=0;i<maxCapacity;i++){
		comarray[i]=NULL;
	}
	cout << "A waggon with capacity for " << maxCapacity <<" passengers, was created" << endl;
}

waggons::~waggons()					//waggon destructor
{
	for(int i=0;i<maxCapacity;i++){		//deallocates comarray
		if (comarray[i]!=NULL){
			delete comarray[i];
			comarray[i]=NULL;
		}	
	}
	delete comarray;
	cout << "A waggon was destroyed" << endl;
}

int waggons::inStation(){
	int incoming,outgoing;
	cout << "number of people when train arrives at station: " << numofpeople << endl;
	check=rand()%2;	//1 if they are going to get tickets checked, 0 otherwise
	
	for(int i=0;i<maxCapacity;i++){		
		if(comarray[i]!=NULL){
			int k=comarray[i]->getchecked();		//if ticket of passenger got checked removes passenger and decrements number of people by one
			if(k==1){
				delete comarray[i];
				comarray[i]=NULL;
				numofpeople=numofpeople-1;
			}
		}
	}
	
	if(numofpeople!=0){
		outgoing=rand()%numofpeople;					//gets a random number of people that are going to exit the waggon
		cout << outgoing << "people are getting off " << endl;
		if(outgoing!=0){
			rmvcom(outgoing);				//removes the people from the waggon
		}
	}
	numofpeople=numofpeople-outgoing;			//number of people is decreased by the outgoing number of people
	
	incoming=rand()%(maxCapacity-numofpeople);			//gets a random number of people who will be entering the waggon
	cout << incoming << " people are getting on" << endl;
	if(incoming!=0){
		addcom(incoming);
	}
	numofpeople=numofpeople+incoming;
	cout << "number of people when train leaves the station " << numofpeople << endl;
}

int waggons::rmvcom(int people){				//removes people who are getting of waggon
	int counter=0;
	cout << "removing " << people << " people " << endl;
	for(int i=maxCapacity;i>=0;i--){
		if(comarray[i]!=NULL && counter<people){
			delete comarray[i];
			comarray[i]=NULL;
			counter++;
		}
	}
}

int waggons::addcom(int people){			//adds people who are getting on the waggon
	int counter=0;
	cout << "adding " << people << " people " << endl;
		for(int i=0;i<maxCapacity;i++){
			if(comarray[i]==NULL && counter<people){
				comarray[i]=new commuter();
				counter++;
			}
		}	
}

int waggons::betweenStations(){
	if(check==1){
		cout << "waggons is going to be checked " << endl;			
		for(int i=0;i<maxCapacity;i++){
			if(comarray[i]!=NULL){
				int x=comarray[i]->get_ticket();
				if(x==0){
					int y=comarray[i]->get_concession();		//if waggon is checked and if the person doesn't have a ticket 
					if(y==1){									//counters are incremented by one depending if they are entitled to a concession ticket
						notickets2=notickets2+1;				//and checked data member is set to 1
					}
					else{
						notickets1=notickets1+1;
					}
					comarray[i]->setchecked();					
				}
			}
		}
	}
	else{
		cout << "waggon wasn't checked " << endl;			//if the waggon doesn't get checked it checks to see how many people evaded detection
		for(int i=0;i<maxCapacity;i++){
			if(comarray[i]!=NULL){
				int x=comarray[i]->get_ticket();
				if(x==0){
					notcaught=notcaught+1;
				}
			}
		}
	}
}

void waggons::printStatistics(){													//prints the people who evaded detection
	cout << "people with no tickets who evaded detection " << notcaught << endl;	//the fines that were collected from that waggon
	waggonfines=(notickets1*ticketprice1*60)+(notickets2*ticketprice2*60);			//and the number of people who were found with no tickets
	cout << "fines collected from the waggon " << waggonfines << endl;
	int x=notickets1+notickets2;
	cout << "people who were found with no tickets " << x << endl;
	
}

void waggons::remove_all_com(){				//removes all passengers from the waggon
	for(int i=0;i<maxCapacity;i++){
		if(comarray[i]!=NULL){
			delete comarray[i];
			comarray[i]=NULL;
		}
	}
}

commuter::commuter(){					//commuter constructor
	ticket=rand()%2;					//1 has a ticket , 0 doesn't have a ticket
	concession=rand()%2;				//1 is entitled to concession, 0 isn't entitled to concession
	checked=0;
	//cout << "commuter was created" << " with ticket: " << ticket << " and concession: " << concession << endl;
}

int commuter::get_ticket(){
	return ticket;
}

int commuter::get_concession(){
	return concession;
}

commuter::~commuter(){						//commuter destructor
//	cout << "commuter was destroyed" << endl;
}

void commuter::setchecked(){				//sets checked to 1
	checked=1;
}

int commuter::getchecked(){
	return checked;
}
