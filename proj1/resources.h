#ifndef RESOURCES_H
#define RESOURCES_H
#include "resource.h"
#include <string>
#include <vector>
using namespace std;
	class Resources{
		private:
			vector<Resource*> resourcesV;
			int count;
		public:
			//Contructor
			Resources();
			//End

			//Add Resource
			void addResource(Resource* newResource);
			//End

			//Find Resource
			Resource* findResource(string id) const;
			//End

			//Getter
			int getCount() const;
			//End

	};

#endif
