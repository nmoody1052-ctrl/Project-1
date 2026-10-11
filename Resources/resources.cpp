#include <iostream>
#include "resource.h"
#include "resources.h"
#include <vector>
using namespace std;

	//Merge Sort by Popularity
	void mergeByPopulariy(vector<Resource>& v, vector<Resource>& left, vector<Resource>& right){
		size_t i = 0, j = 0, k = 0;

		while(i < left.size() && j < right.size()){
			if((left[i].getsCount()+left[i].getWaitCount()) <= (right[j].getsCount()+right[i].getWaitCount())){
				v[k++] = left[i++];
			}
			else{
				v[k++] = right[j++];
			}
		}

		while(i < left.size()) v[k++] = left[i++];
		while(j < right.size()) v[k++] = right[j++];
	}

	void mergeSortByPopularity(vector<Resource>& v){
		if(v.size() <= 1) return;

		int mid = v.size() / 2;
		vector<Resource> left(v.begin(), v.begin() + mid);
		vector<Resource> right(v.begin() + mid, v.end());

		mergeSortByPopularity(left);
		mergeSortByPopularity(right);

		mergeByPopulariy(v, left, right);
	}
	//End

	//Merge Sort by Name
	void mergeByName(vector<Resource>& v, vector<Resource>& left, vector<Resource>& right){
		size_t i = 0, j = 0, k = 0;

		while(i < left.size() && j < right.size()){
			if(left[i].getName() <= right[j].getName()){
				v[k++] = left[i++];
			}
			else{
				v[k++] = right[j++];
			}
		}

		while(i < left.size()) v[k++] = left[i++];
		while(j < right.size()) v[k++] = right[j++];
	}

	void mergeSortByName(vector<Resource>& v){
		if(v.size() <= 1) return;

		int mid = v.size() / 2;
		vector<Resource> left(v.begin(), v.begin() + mid);
		vector<Resource> right(v.begin() + mid, v.end());

		mergeSortByName(left);
		mergeSortByName(right);

		mergeByName(v, left, right);
	}
	//End

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

	//Find Resource via ID
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
		cout<<"------------------------Resources------------------------\n";
		for(int i=0;i<count;i++){
			cout<<"Resource #"<<i+1<<" | "
			<<"ID: "<<resourcesV[i].getID()<<" | "
			<<"Name: "<<resourcesV[i].getName()<<" | "
			<<"Type: "<<resourcesV[i].getType()<<" | ";

			if(resourcesV[i].getAvail()){
				cout<<"Availability: Available | \n";
			}
			else{
				cout<<"Availability: Unavailable | \n";
			}

			cout<<"Number of Reservations: "<<resourcesV[i].getsCount()<<" | "
			<<"Number of Waitlists: "<<resourcesV[i].getWaitCount()<<" | "
			<<"Total Popularity (Reservations+Waitlists): "<<resourcesV[i].getWaitCount()+resourcesV[i].getsCount()<<" | "
			<<endl<<
			"-------------------------------------------------------------------------\n";
		}
		cout<<endl;
	}
	//End

	//Merge Sort By Name
	void Resources::sortByName() {
		mergeSortByName(resourcesV);
	}
	//End

	//Merge Sort By Popularity (number of reservations)
	void Resources::sortByPopularity() {
		mergeSortByPopularity(resourcesV);
	}
	//End