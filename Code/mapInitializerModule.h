#include <math.h>
#include <stdio.h>
/*
	a.	A collection of functions to create a map.
	b.	Used to create a dummy map. Later functions will be added to
		create somewhat usable maps.
*/

class mapInitializer
{
	public:
			int calculateDataPoints(int);
			char* returnMapValue(float, char*);
			void createOuterWheelMap(FILE*);
			void createInnerWheelMap(FILE*);
};
/*
----------;---------------END-------------------------
*/
