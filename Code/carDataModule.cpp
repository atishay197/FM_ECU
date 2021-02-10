#include "carDataModule.h"



/*
	a. 	A simple routine to print car data to the terminal. Prints the members' values.
	b. 	For debugging purposes.
*/
void carData::printCarData()
{
	float totalWeight = carWeight_Data + driverWeight_Data;
	float frontWeight = frontDistribution_Data * totalWeight;
	float rearWeight = totalWeight - frontWeight;
	cout<<"Car Data:"<<endl;
	cout<<"Total Weight:"<<totalWeight<<"\t";
	cout<<"Driver Weight:"<<driverWeight_Data<<"\t";
	cout<<"Car Weight:"<<frontWeight<<"\t";
	cout<<"Front Weight:"<<frontWeight<<"\t";
	cout<<"Rear Weight:"<<rearWeight<<"\t";
	cout<<endl;
	cout<<"CG:"<<"\t"<<"x:"<<CG_Data.x<<"\t"<<"y:"<<CG_Data.y<<"\t"<<"z:"<<CG_Data.z<<endl;
	cout<<"Wheelbase:"<<wheelbase<<endl;
	cout<<"Track:"<<"\t"<<"front:"<<track.front<<"\t"<<"rear:"<<track.rear<<endl;
	cout<<"Wheel Diameter:"<<wheelDiameter<<endl;
	cout<<"Tire Pressure"<<"\t"<<"front:"<<tirePressure_Data.front<<"\t"<<"rear:"<<tirePressure_Data.rear<<endl;
	cout<<"Camber:"<<"\t"<<"front:"<<camber_Data.front<<"\t"<<"rear:"<<camber_Data.rear<<endl;
	cout<<"Front Distribution:"<<frontDistribution_Data<<endl;
	cout<<"Damping Coefficient"<<suspension_Data.dampingCoefficient<<endl;
	cout<<"Spring Constant:"<<suspension_Data.springConstant<<endl;
	cout<<"Push/Pull Rod angle:"<<suspension_Data.pushRodAngle<<endl;
	cout<<"Autocross Lap time:"<<autoXLapTime_Data<<endl;
	cout<<"Event Lap Number:"<<eventLapNumber_Data<<endl;
}



/*
	a. 	A simple routine to read car data from the file.
	b. 	Reads data into a pointer to the object of class carData,
		so that passing to a function is done by call by reference.		
*/
void carData::readCarDataFromCSV(FILE* carDataFile)
{
	char buffer[1000];
    if(fgets(buffer, 1000, carDataFile) != NULL)
    {
        carWeight_Data = atof(strtok(buffer, ","));
        driverWeight_Data = atof(strtok(NULL, ","));
        CG_Data.x = atof(strtok(NULL, ","));
        CG_Data.y = atof(strtok(NULL, ","));
        CG_Data.z = atof(strtok(NULL, ","));
        wheelbase = atof(strtok(NULL, ","));
        track.front = atof(strtok(NULL, ","));
        track.rear = atof(strtok(NULL, ","));
        wheelDiameter = atof(strtok(NULL, ","));
        tirePressure_Data.front = atof(strtok(NULL, ","));
        tirePressure_Data.rear = atof(strtok(NULL, ","));
        camber_Data.front = atof(strtok(NULL, ","));
        camber_Data.rear = atof(strtok(NULL, ","));
        frontDistribution_Data = atof(strtok(NULL, ","));
		suspension_Data.dampingCoefficient = atof(strtok(NULL, ","));
		suspension_Data.springConstant = atof(strtok(NULL, ","));
		suspension_Data.pushRodAngle = atof(strtok(NULL, ","));
		autoXLapTime_Data = atof(strtok(NULL, ","));
		eventLapNumber_Data = atof(strtok(NULL, ","));
        fclose(carDataFile);
     }	
}


/*
	Setters for the data members.
*/
float carData::getCarData_carWeight()
{
	return carWeight_Data;
}

float carData::getCarData_driverWeight()
{
	return driverWeight_Data;
}

float carData::getCarData_CGData_x()
{
	return CG_Data.x;
}

float carData::getCarData_CGData_y()
{
	return CG_Data.y;
}

float carData::getCarData_CGData_z()
{
	return CG_Data.z;
}

float carData::getCarData_wheelbase()
{
	return wheelbase;
}

float carData::getCarData_track_front()
{
	return track.front;
}

float carData::getCarData_track_rear()
{
	return track.rear;
}

float carData::getCarData_wheelDiameter()
{
	return wheelDiameter;
}

float carData::getCarData_tirePressure_front()
{
	return tirePressure_Data.front;
}

float carData::getCarData_tirePressure_rear()
{
	return tirePressure_Data.rear;
}

float carData::getCarData_camber_front()
{
	return camber_Data.front;
}

float carData::getCarData_camber_rear()
{
	return camber_Data.rear;
}

float carData::getCarData_frontDistribution()
{
	return frontDistribution_Data;
}

float carData::getCarData_suspension_dampingCoefficient()
{
	return suspension_Data.dampingCoefficient;
}

float carData::getCarData_suspension_springConstant()
{
	return suspension_Data.springConstant;
}

float carData::getCarData_suspension_pushRodAngle()
{
	return suspension_Data.pushRodAngle;
}

float carData::getCarData_autoXLapTime()
{
	return autoXLapTime_Data;
}

int carData::getCarData_eventLapNumber()
{
	return eventLapNumber_Data;
}
			

/*
	Setters for the data members.
*/
void carData::setCarData_carWeight(float val)
{
	carWeight_Data = val;
}

void carData::setCarData_driverWeight(float val)
{
	driverWeight_Data = val;
}

void carData::setCarData_CGData_x(float val)
{
	CG_Data.x = val;
}

void carData::setCarData_CGData_y(float val)
{
	CG_Data.y = val;
}
void carData::setCarData_CGData_z(float val)
{
	CG_Data.z = val;
}

void carData::setCarData_wheelbase(float val)
{
	wheelbase = val;
}

void carData::setCarData_track_front(float val)
{
	track.front = val;	
}

void carData::setCarData_track_rear(float val)
{
	track.rear = val;
}

void carData::setCarData_wheelDiameter(float val)
{
	wheelDiameter = val;
}


void carData::setCarData_tirePressure_front(float val)
{
	tirePressure_Data.front = val;
}

void carData::setCarData_tirePressure_rear(float val)
{
	tirePressure_Data.rear = val;
}

void carData::setCarData_camber_front(float val)
{
	camber_Data.front = val;
}

void carData::setCarData_camber_rear(float val)
{
	camber_Data.rear = val;
}

void carData::setCarData_frontDistribution(float val)
{
	frontDistribution_Data = val;
}

void carData::setCarData_suspension_dampingCoefficient(float val)
{
	suspension_Data.dampingCoefficient = val;
}

void carData::setCarData_suspension_springConstant(float val)
{
	suspension_Data.springConstant = val;
}

void carData::setCarData_suspension_pushRodAngle(float val)
{
	suspension_Data.pushRodAngle = val;
}

void carData::setCarData_autoXLapTime(float val)
{
	autoXLapTime_Data = val;
}

void carData::setCarData_eventLapNumber(int val)
{
	eventLapNumber_Data = val;
}
/*
-------------------------END-------------------------
*/			
