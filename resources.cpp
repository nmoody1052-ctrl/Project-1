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
