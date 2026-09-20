#include <iostream>
#include "resource.h"
#include "resources.h"
#include <vector>
using namespace std;
	//Contructor
        Resources::Resources(){
		count = 0;
	}
        //End

       	//Add Resource
	void Resources::addResource(const Resource& newResource){
		resourcesV.push_back(newResource);
		count++;
	}
	//End

	//Find Resource
	Resource* Resources::findResource(string id){
		for(int i=0;i<count;i++){
			if(resourcesV[i].getID()==id){
				return &resourcesV[i];
			}
		}
		return nullptr;
	}
	//End

	//Getter
	int Resources::getCount() const{
		return count;
	}
	//End

	//PrintResources
	void Resources::PrintResources() const{
		cout<<"Resources: \n";
		for(int i=0;i<count;i++){
			cout<<"Resource #"<<i+1
			<<"ID: "<<resourcesV[i].getID()<<" | "
			<<"Name: "<<resourcesV[i].getName()<<" | "
			<<"Type: "<<resourcesV[i].getType()<<" | "
			<<"Availability: "<<resourcesV[i].getAvail()<<" | "<<endl;
		}
		cout<<endl;
	}
	//End

