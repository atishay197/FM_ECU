#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace  std;
/*	
	a. 	This class simply provides a data structure and necessary functions to load the car related parameters 
		from a file into the working memory.
	b. 	The class contains data members whose values may be needed for calculations or decisions pertaining to
		the project. These parameters are necessarily constant for given run. But, they may change before a 
		run. Editing the file carData.csv will facilitate those changes.
*/

/*
	The following structures encapsulate the data for ease of use.
*/

FILE* carDataFile = fopen("../Build/Input/CarData.csv","r");

struct CGCoordinates
{
	float x;
	float y;
	float z;
};

struct Camber
{
	float front;
	float rear;
};

struct Track
{
	float front;
	float rear;
};

struct TirePressure
{
	float front;
	float rear;
};

struct Suspension
{
	float dampingCoefficient;
	float springConstant;
	float pushRodAngle;
};

class carData
{
	private:
			float carWeight_Data;
			float driverWeight_Data;
			CGCoordinates  CG_Data;
			float wheelbase;
			Track track;
			float wheelDiameter;
			TirePressure tirePressure_Data;
			Camber camber_Data;
			float frontDistribution_Data;
			Suspension suspension_Data;
			float autoXLapTime_Data;
			int eventLapNumber_Data;
	public:
			float getCarData_carWeight();
			float getCarData_driverWeight();
			float getCarData_CGData_x();
			float getCarData_CGData_y();
			float getCarData_CGData_z();
			float getCarData_wheelbase();
			float getCarData_track_front();
			float getCarData_track_rear();
			float getCarData_wheelDiameter();
			float getCarData_tirePressure_front();
			float getCarData_tirePressure_rear();
			float getCarData_camber_front();
			float getCarData_camber_rear();
			float getCarData_frontDistribution();
			float getCarData_suspension_dampingCoefficient();
			float getCarData_suspension_springConstant();
			float getCarData_suspension_pushRodAngle();
			float getCarData_autoXLapTime();
			int	  getCarData_eventLapNumber();
			
			void setCarData_carWeight(float);
			void setCarData_driverWeight(float);
			void setCarData_CGData_x(float);
			void setCarData_CGData_y(float);
			void setCarData_CGData_z(float);
			void setCarData_wheelbase(float);
			void setCarData_track_front(float);
			void setCarData_track_rear(float);
			void setCarData_wheelDiameter(float);
			void setCarData_tirePressure_front(float);
			void setCarData_tirePressure_rear(float);
			void setCarData_camber_front(float);
			void setCarData_camber_rear(float);
			void setCarData_frontDistribution(float);
			void setCarData_suspension_dampingCoefficient(float);
			void setCarData_suspension_springConstant(float);
			void setCarData_suspension_pushRodAngle(float);
			void setCarData_autoXLapTime(float);
			void setCarData_eventLapNumber(int);
			
			
			void readCarDataFromCSV(FILE*);
			void printCarData();
};
/*
-------------------------END-------------------------
*/			
