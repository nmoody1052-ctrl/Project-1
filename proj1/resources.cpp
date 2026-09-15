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
	void Resources::addResource(Resource* newResource){
		resourcesV.push_back(newResource);
		count++;
	}
	//End

	//Find Resource
	Resource* Resources::findResource(string id) const{
		for(int i=0;i<count;i++){
			if(resourcesV.at(i)->getID()==id){
				return resourcesV[i];
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
