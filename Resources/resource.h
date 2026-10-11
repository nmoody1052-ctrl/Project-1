#ifndef RESOURCE_H
#define RESOURCE_H
#include<string>
using namespace std;
	class Resource{
	public:
		//Default Constructor
		Resource();
		//End

		//Getters
		string getID() const;
		string getName() const;
		string getType() const;
		bool getAvail() const;
		int getCount() const;
		int getWaitCount() const;
		//End

		//Setters
		void setID(const string newID);
		void setName(const string newName);
		void setType(const string newType);
		void setAvail(string newAvail);
		void incremCount();
		void incremWaitCount();
		//End

	private:
		string id;
		string name;
		string typ;
		bool available;
		int reservationCount;
		int waitlistCount;
	};


#endif
