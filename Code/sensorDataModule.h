/*
	a. 	This class provides a data structure to load the sensor data into the working memory.
	b.	The class provides the necessary members and routines to enable reading data from
		sensorData.csv during simulation, and later it will include routines for reading data from the CANbus. 
*/

/*
	The following structures encapsulate the data for ease of use.
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

FILE* sensorDataFile = fopen("../Build/Input/sensorDataFile.csv","r");

struct WheelSpeed
{
	float FL;
	float FR;
	float RL;
	float RR;
};
struct GForce
{
	float longitudnal;
	float lateral;
	float vertical;
};
struct BrakePressure
{
	float front;
	float rear;
};
struct Throttle
{
	float TPS1;
	float TPS2;
};
struct Suspot
{
	float FL;
	float FR;
	float RL;
	float RR;
};	


class sensorData
{
	/*
		TO-DO:
				Add roll and pitch.
	*/	
	private:
			bool exists;						// True/False
			float currentTime;					// s
			int distance;						// m
			BrakePressure brakePressure;		// kPa
			float driveSpeed;					// km/h
			WheelSpeed wheelSpeed;				// km/h
			GForce gForce;						// G
			float gyroYawVelocity;				// deg/s
			float steeredAngle;					// deg
			Throttle throttle;					// %
			Suspot susPot;						//mm
			float batterySOC;
			int currentLapNumber;
			
	public:
			bool 	getSensorData_exists();
			float 	getSensorData_currentTime();
			int 	getsensorData_distance();
			float 	getSensorData_brakePressure_front();
			float 	getSensorData_brakePressure_rear();
			float 	getSensorData_driveSpeed();
			float 	getSensorData_wheelSpeed_FL();
			float 	getSensorData_wheelSpeed_FR();
			float 	getSensorData_wheelSpeed_RL();
			float 	getSensorData_wheelSpeed_RR();
			float	getSensorData_gForce_longitudnal();
			float	getSensorData_gForce_lateral();
			float	getSensorData_gForce_vertical();
			float 	getSensorData_gyroYawVelocity();
			float 	getSensorData_steeredAngle();
			float	getSensorData_throttle_TPS1();
			float	getSensorData_throttle_TPS2();
			float 	getSensorData_susPot_FL();
			float 	getSensorData_susPot_FR();
			float 	getSensorData_susPot_RL();
			float 	getSensorData_susPot_RR();
			float 	getSensorData_batterySOC();
			int 	getSensorData_currentLapNumber();
			
			void 	setSensorData_exists(bool);
			void 	setSensorData_currentTime(float);
			void	setsensorData_distance(int);
			void 	setSensorData_brakePressure_front(float);
			void 	setSensorData_brakePressure_rear(float);
			void 	setSensorData_driveSpeed(float);
			void 	setSensorData_wheelSpeed_FL(float);
			void 	setSensorData_wheelSpeed_FR(float);
			void 	setSensorData_wheelSpeed_RL(float);
			void 	setSensorData_wheelSpeed_RR(float);
			void	setSensorData_gForce_longitudnal(float);
			void	setSensorData_gForce_lateral(float);
			void	setSensorData_gForce_vertical(float);
			void 	setSensorData_gyroYawVelocity(float);
			void 	setSensorData_steeredAngle(float);
			void	setSensorData_throttle_TPS1(float);
			void	setSensorData_throttle_TPS2(float);
			void 	setSensorData_susPot_FL(float);
			void 	setSensorData_susPot_FR(float);
			void 	setSensorData_susPot_RL(float);
			void 	setSensorData_susPot_RR(float);
			void 	setSensorData_batterySOC(float);
			void 	setSensorData_currentLapNumber(float);
			
			sensorData(sensorData*);
			sensorData();
			void printSensorData();
			void readSensorDataFromCSV(char*);
};
/*
-------------------------END-------------------------
*/	
			
