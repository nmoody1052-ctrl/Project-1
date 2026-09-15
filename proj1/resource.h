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
		//End

		//Setters
		void setID(const string newID);
		void setName(const string newName);
		void setType(const string newType);
		void setAvail(bool newAvail);
		//End
	private:
		string id;
		string name;
		string typ;
		bool available;
	};


#endif
