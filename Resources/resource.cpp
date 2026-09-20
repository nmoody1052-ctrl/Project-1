#include <iostream>
#include "resource.h"
using namespace std;
	//Default Constructor
        Resource::Resource(){
		id = "";
		name = "";
		typ = "";
		available = 0;
	}
        //End

        //Getters
        string Resource::getID() const{
		return id;
	}

        string Resource::getName() const{
		return name;
	}

        string Resource::getType() const{
		return typ;
	}

	bool Resource::getAvail() const{
		return available ;
	}
        //End

        //Setters
        void Resource::setID(const string newID){
		id = newID;
	}

        void Resource::setName(const string newName){
		name = newName;
	}

        void Resource::setType(const string newType){
		typ = newType;
	}

	void Resource::setAvail(string newAvail){
		if(newAvail=="Available"){
			available = true;
		}
		else if(newAvail=="Unavailable"){
			available = false;
		}
		else{
			available = false;
			cout<<"Error: Availablilty automatically set to False\n";
		}
	}
        //End
