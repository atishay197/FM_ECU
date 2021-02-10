
#include "sensorDataModule.h"
#include "carDataModule.h"
#include <math.h>

FILE* outp = fopen("../Build/Input/outputTorque.csv","w");
FILE* wout = fopen("../Build/Input/wheel.csv","w");
FILE* weightageFile  = fopen("../Build/Input/weightage.txt", "r+");

/*
	a. 	Contains the data structure to store the calculated wheel loads. 
	b. 	Used for determining wheelloads.
*/

class wheelLoad
{
	private:
			float FL;
			float FR;
			float RL;
			float RR;
	public:
			
			void setWheelLoad_FL(float);
			void setWheelLoad_FR(float);
			void setWheelLoad_RL(float);
			void setWheelLoad_RR(float);
			
			float getWheelLoad_FL();
			float getWheelLoad_FR();
			float getWheelLoad_RL();
			float getWheelLoad_RR();
			
			wheelLoad();
			void printWheelLoad();
			void writeWheelLoad(FILE*);
			void calculateWheelLoadYaw(sensorData*, carData*);
			void calculateWheelLoadSusPot(sensorData*, sensorData*, carData*, double);
			void calculateWheelLoadAcceleration(sensorData*, carData*);
			void calculateWheelLoad(sensorData*, sensorData*, carData*, double);
			
};
/*
-------------------------END-------------------------
*/	
