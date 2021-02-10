#include "sensorDataModule.h"

/*
	Getter functions for each data member.
*/
bool sensorData::getSensorData_exists()
{
	return exists;
} 

float sensorData::getSensorData_currentTime()
{
	return currentTime;
}

int sensorData::getsensorData_distance()
{
	return distance;
}

float sensorData::getSensorData_brakePressure_front()
{
	return brakePressure.front;
}

float sensorData::getSensorData_brakePressure_rear()
{
	return brakePressure.rear;
}

float sensorData::getSensorData_driveSpeed()
{
	return driveSpeed;
}

float sensorData::getSensorData_wheelSpeed_FL()
{
	return wheelSpeed.FL;
}

float sensorData::getSensorData_wheelSpeed_FR()
{
	return wheelSpeed.FR;
}

float sensorData::getSensorData_wheelSpeed_RL()
{
	return wheelSpeed.RL;
}

float sensorData::getSensorData_wheelSpeed_RR()
{
	return wheelSpeed.RR;
}

float sensorData::getSensorData_gForce_longitudnal()
{
	return gForce.longitudnal;
}

float sensorData::getSensorData_gForce_lateral()
{
	return gForce.lateral;
}

float sensorData::getSensorData_gForce_vertical()
{
	return gForce.vertical;
}

float sensorData::getSensorData_gyroYawVelocity()
{
	return gyroYawVelocity;
}

float sensorData::getSensorData_steeredAngle()
{
	return steeredAngle;
}

float sensorData::getSensorData_throttle_TPS1()
{
	return throttle.TPS1;
}

float sensorData::getSensorData_throttle_TPS2()
{
	return throttle.TPS2;
}

float sensorData::getSensorData_susPot_FL()
{
	return susPot.FL;
}

float sensorData::getSensorData_susPot_FR()
{
	return susPot.FR;
}

float sensorData::getSensorData_susPot_RL()
{
	return susPot.RL;
}

float sensorData::getSensorData_susPot_RR()
{
	return susPot.RR;
}

float sensorData::getSensorData_batterySOC()
{
	return batterySOC;
}

int sensorData::getSensorData_currentLapNumber()
{
	return currentLapNumber;
}


/*
	Setters for each data  member.
*/
void sensorData::setSensorData_exists(bool ex)
{
	exists = ex;
}

void sensorData::setSensorData_currentTime(float time)
{
	currentTime = time;
}

void sensorData::setsensorData_distance(int dist)
{
	distance = dist;
}

void sensorData::setSensorData_brakePressure_front(float front)
{
	brakePressure.front = front;
}

void sensorData::setSensorData_brakePressure_rear(float rear)
{
	brakePressure.rear = rear;
}

void sensorData::setSensorData_driveSpeed(float drivespeed)
{
	driveSpeed = drivespeed;
}

void sensorData::setSensorData_wheelSpeed_FL(float fl)
{
	wheelSpeed.FL = fl;
}

void sensorData::setSensorData_wheelSpeed_FR(float fr)
{
	wheelSpeed.FR = fr;
}

void sensorData::setSensorData_wheelSpeed_RL(float rl)
{
	wheelSpeed.RL = rl;
}

void sensorData::setSensorData_wheelSpeed_RR(float rr)
{
	wheelSpeed.RR = rr;
}

void sensorData::setSensorData_gForce_longitudnal(float longitudnal)
{
	gForce.longitudnal = longitudnal;
}

void sensorData::setSensorData_gForce_lateral(float lateral)
{
	gForce.lateral = lateral;
}

void sensorData::setSensorData_gForce_vertical(float vertical)
{
	gForce.vertical = vertical;
}

void sensorData::setSensorData_gyroYawVelocity(float yaw)
{
	gyroYawVelocity = yaw;
}

void sensorData::setSensorData_steeredAngle(float steeredangle)
{
	steeredAngle = steeredangle;
}

void sensorData::setSensorData_throttle_TPS1(float tps)
{
	throttle.TPS1 = tps;
}

void sensorData::setSensorData_throttle_TPS2(float tps) 
{
	throttle.TPS2 = tps;
}

void sensorData::setSensorData_susPot_FL(float fl)
{
	susPot.FL = fl;
}

void sensorData::setSensorData_susPot_FR(float fr)
{
	susPot.FR = fr;
}

void sensorData::setSensorData_susPot_RL(float rl)
{
	susPot.RL = rl;
}

void sensorData::setSensorData_susPot_RR(float rr)
{
	susPot.RR = rr;
}

void sensorData::setSensorData_batterySOC(float soc)
{
	batterySOC = soc;
}

void sensorData::setSensorData_currentLapNumber(float cln)
{
	currentLapNumber = cln;
}

			
/*
	a. 	A copy constructor for the class sensorData that copies the data from prev, an object of
		the same class, to the currently declared object.
	b.	To be used to assign the current values to the object for use as prevData for the next iteration
		of the main loop in torqueVectoring.cpp
*/
sensorData::sensorData(sensorData* prev)
{
	this->exists = prev->exists;
	this->currentTime = prev->currentTime;
	this->distance = prev->distance;
	this->brakePressure = prev->brakePressure;
	this->driveSpeed = prev->driveSpeed;
	this->wheelSpeed = prev->wheelSpeed;
	this->gForce = prev->gForce;
	this->gyroYawVelocity = prev->gyroYawVelocity;
	this->steeredAngle = prev->steeredAngle;
	this->throttle = prev->throttle;
	this->susPot = prev->susPot;
	this->batterySOC = prev->batterySOC;
	this->currentLapNumber = prev->currentLapNumber;
}



/*
	a. 	A parameterless constructor for the class sensorData, that simply initializes he object with default
		values for the members.
	b. 	To be used before the main loop in torqueVectoring.cpp to get prevData for the first iteration of the main
		loop.
*/
sensorData::sensorData()
{
	this->exists = 0;
	this->currentTime = 0.0;
	this->distance = 0;
	this->brakePressure.front = 0;
	this->brakePressure.rear = 0;
	this->driveSpeed = 0.0;
	this->wheelSpeed.FL = 0.0;
	this->wheelSpeed.FR = 0.0;
	this->wheelSpeed.RL = 0.0;
	this->wheelSpeed.RR = 0.0;
	this->gForce.longitudnal = 0.0;
	this->gForce.lateral = 0.0;
	this->gForce.vertical = 0.0;
	this->gyroYawVelocity = 0.0;
	this->steeredAngle = 0.0;
	this->throttle.TPS1 = 0.0;
	this->throttle.TPS2 = 0.0;
	this->susPot.FL = 0.0;
	this->susPot.FR = 0.0;
	this->susPot.RL = 0.0;
	this->susPot.RR = 0.0;
	this->batterySOC = 100.0;
	this->currentLapNumber = 1;
}



/*
	a. 	A simple routine to print car data to the terminal. Prints the members' values.
	b. 	For debugging purposes.
*/
void sensorData::printSensorData()
{
	cout<<"Exists:"<<"\t";
	if (exists) cout<<"True"<<endl; 
	else cout<<"False"<<endl;
	cout<<"Current Time:\t"<<currentTime<<endl;
	cout<<"Travelled Distance:\t"<<distance<<endl;
	cout<<"Brake Pressue:\t"<<"Front:"<<brakePressure.front<<"\t"<<"Rear:"<<brakePressure.rear<<endl;
	cout<<"Vehicle Speed:\t"<<driveSpeed<<endl;
	cout<<"Wheel Speed:\t"<<"FL:"<<wheelSpeed.FL<<"\t"<<"FR:"<<wheelSpeed.FR<<"\t"<<"RL:"<<wheelSpeed.RL<<"\t"<<"RR:"<<wheelSpeed.RR<<endl;
	cout<<"GForce:\t"<<"Longitudnal:"<<gForce.longitudnal<<"\t"<<"Lateral:"<<gForce.lateral<<"\t"<<"Vertical:"<<gForce.vertical<<endl;
	cout<<"Yaw Rate:\t"<<gyroYawVelocity<<endl;
	cout<<"Steered Angle:\t"<<steeredAngle<<endl;
	cout<<"Throttle:\t"<<"TPS1:"<<throttle.TPS1<<"\t"<<"TPS2:"<<throttle.TPS2<<endl;
	cout<<"SusPot:\t"<<"FL:"<<susPot.FL<<"\t"<<"FR:"<<susPot.FR<<"\t"<<"RL:"<<susPot.RL<<"\t"<<"RR:"<<susPot.RR<<endl;
	cout<<"State of Charge:\t"<<batterySOC<<endl;
	cout<<"Current Lap:\t"<<currentLapNumber<<endl;
}



/*	
	a. 	A simple routine to read sensor data from the file.
	b. 	Reads data into an object of class sensorData, pointed to by pointer,
		so that passing to a function is done by call by reference.		
*/
void sensorData::readSensorDataFromCSV(char buffer[1000])
{
	exists = true;
    currentTime = atof(strtok(buffer, ","));
    distance = atoi(strtok(NULL, ","));
    brakePressure.front = atoi(strtok(NULL, ","));
    brakePressure.rear = atoi(strtok(NULL, ","));
    driveSpeed = atof(strtok(NULL, ","));
    wheelSpeed.FL = atof(strtok(NULL, ","));
    wheelSpeed.FR = atof(strtok(NULL, ","));
    wheelSpeed.RL = atof(strtok(NULL, ","));
    wheelSpeed.RR = atof(strtok(NULL, ","));
    gForce.longitudnal = atof(strtok(NULL, ","));
    gForce.lateral = atof(strtok(NULL, ","));
    gForce.vertical = atof(strtok(NULL, ","));
    gyroYawVelocity = atof(strtok(NULL, ","));
    steeredAngle = atof(strtok(NULL, ","));
    throttle.TPS1 = atof(strtok(NULL, ","));
    throttle.TPS2 = (throttle.TPS1)+(throttle.TPS1*(((float)(rand()%30)-15)/1000));
    susPot.FL = atof(strtok(NULL, ","));
    susPot.FR = atof(strtok(NULL, ","));
    susPot.RL = atof(strtok(NULL, ","));
    susPot.RR = atof(strtok(NULL, ","));
    batterySOC = atof(strtok(NULL, ","));
    currentLapNumber = atoi(strtok(NULL, ","));
}
/*
-------------------------END-------------------------
*/		
