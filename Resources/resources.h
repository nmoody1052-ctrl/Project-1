#ifndef RESOURCES_H
#define RESOURCES_H
#include "resource.h"
#include <string>
#include <vector>
using namespace std;
	class Resources{
		private:
			vector<Resource> resourcesV;
			int count;
		public:
			//Contructor
			Resources();
			//End

			//Add Resource
			void addResource(const Resource& newResource);
			//End

			//Find Resource
			Resource* findResource(string id);
			//End

			//Getter
			int getCount() const;
			//End

			//Print
			void PrintResources() const;
			//End
	};

#endif
