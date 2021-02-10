#include "wheelLoadsModule.h"

/*
	Setters for the data members.	
*/
void wheelLoad::setWheelLoad_FL(float val)
{
	FL = val;
}

void wheelLoad::setWheelLoad_FR(float val)
{
	FR = val;
}

void wheelLoad::setWheelLoad_RL(float val)
{
	RL = val;
}

void wheelLoad::setWheelLoad_RR(float val)
{
	RR = val;
}

/*
	Getters for the data member.
*/
float wheelLoad::getWheelLoad_FL()
{
	return FL;
}

float wheelLoad::getWheelLoad_FR()
{
	return FR;
}

float wheelLoad::getWheelLoad_RL()
{
	return RL;
}

float wheelLoad::getWheelLoad_RR()
{
	return RR;
}
			

/*
	Non-parameterized Constuctor.
*/
wheelLoad::wheelLoad()
{
	FL = 0.0;
	FR = 0.0;
	RL = 0.0;
	RR = 0.0;
}

/*
	Prints the values of the data members on the standard output
*/
void wheelLoad::printWheelLoad()
{
	cout<<"Wheel Loads :: FL:"<<FL<<"\tFR:"<<FR<<"\tRL:"<<RL<<"\tRR:"<<RR<<endl;;
	return;
}

/*
	Writes the wheel loads into a file
*/
void wheelLoad::writeWheelLoad(FILE* wout)
{
	fprintf(wout,"%f,%f,%f,%f\n",FL,FR,RL,RR);
}

/*
	Calculates wheel loads based on yaw.	
*/
void wheelLoad::calculateWheelLoadYaw(sensorData* prevData, carData* cData)
{
	FL = 0.0;
	FR = 0.0;
	RL = 0.0;
	RR = 0.0;
}

/*
	Calculates wheel loads using suspot.
*/
void wheelLoad::calculateWheelLoadSusPot(sensorData* prevData, sensorData* curData, carData* cData, double elapsed)
{
	float B = cData->getCarData_suspension_dampingCoefficient();
	float K = cData->getCarData_suspension_springConstant();
	float theta = ( cData->getCarData_suspension_pushRodAngle() )*3.1415/180;
	
	/* Commented as the term containing B is not relevant in steadystate
	w->FL = cos(theta) * ( ( B * ( (data->susPot.FL) - (prevData->susPot.FL) ) / elapsed) + ( K * (data->susPot.FL) ) );
	w->FR = cos(theta) * ( ( B * ( (data->susPot.FR) - (prevData->susPot.FR) ) / elapsed) + ( K * (data->susPot.FR) ) );
	w->RL = cos(theta) * ( ( B * ( (data->susPot.RL) - (prevData->susPot.RL) ) / elapsed) + ( K * (data->susPot.RL) ) );
	w->RR = cos(theta) * ( ( B * ( (data->susPot.RR) - (prevData->susPot.RR) ) / elapsed) + ( K * (data->susPot.RR) ) );
	*/
	FL = cos(theta) * ( K * (prevData->getSensorData_susPot_FL()) );
	FR = cos(theta) * ( K * (prevData->getSensorData_susPot_FR()) );
	RL = cos(theta) * ( K * (prevData->getSensorData_susPot_RL()) );
	RR = cos(theta) * ( K * (prevData->getSensorData_susPot_RR()) );
}

/*
	Calculates wheel loads using accelerometer
*/
void wheelLoad::calculateWheelLoadAcceleration(sensorData* prevData, carData* cData)
{
	/*
		Front Track
	*/
	float ef = (cData->getCarData_track_front())/1000;						// m
	
	/*
		Rear Track
	*/
	float er = (cData->getCarData_track_rear())/1000;						// m
	
	/*
		Total car + drive rweight
	*/
	float mv = cData->getCarData_carWeight() + cData->getCarData_driverWeight();// kgs
	
	/*
		Wheelbase of the car
	*/
	float l = (cData->getCarData_wheelbase())/1000;							// m
	/*
		CG z coordinates
	*/
	float h = (cData->getCarData_CGData_z())/1000;							// m
	/*
		CG x coordinates
	*/
	float lf = (cData->getCarData_CGData_x())/1000;							// m
	// Distance between rear wheel and CG
	float lr = l - lf;											// m
	// Logitudnal and lateral acceleration
	float ax = prevData->getSensorData_gForce_longitudnal();					// m/sec^2
	float ay = prevData->getSensorData_gForce_lateral();						// m/sec^2
	// Final wheel load calculation
	// Formula from : http://www.gipsa-lab.grenoble-inp.fr/~moustapha.doumiati/VSD09.pdf
	FL = mv*((lr-h*ax)/l)*(0.5-((h*ay)/(ef)));
	FR = mv*((lr-h*ax)/l)*(0.5+((h*ay)/(ef)));
	RL = mv*((lf+h*ax)/l)*(0.5-((h*ay)/(ef)));
	RR = mv*((lf+h*ax)/l)*(0.5+((h*ay)/(ef)));
}


/*
	Calculates wheel loads
*/
void wheelLoad::calculateWheelLoad(sensorData* prevData, sensorData* curData, carData* cData, double elapsed)
{
	wheelLoad* w[3];	
	
	w[0] = new wheelLoad;
	w[0]->calculateWheelLoadYaw(prevData, cData);
	
	w[1] = new wheelLoad;
	w[1]->calculateWheelLoadSusPot(prevData, curData, cData, elapsed);
	
	w[2] = new wheelLoad;
	w[2]->calculateWheelLoadAcceleration(prevData, cData);
	
	/*
		TO DO : make weightage parameter modifiable
		sum should always be 100
		FILE *weightage_file  = fopen("weightage.txt", "r"); //open weightage_file having editable weights
	*/
	float weightage[3] = {100,0,0};		// {Acceleration,Suspot,Yaw}
	//float modifiedWeightage[3];
	fscanf(weightageFile, "%f %f %f", &weightage[0], &weightage[1], &weightage[2]); 
	//fclose(weightage_file);
	
	//TO-DO Remove this from the loop, 
	//fprintf(weightageFile,"%f, %f, %f", weightage[0], weightage[1], weightage[2]);
	
	/*
		Calculate sum of weightages
	*/
	float weightSum = 0;
	for(int i=0 ; i<3 ; i++)
	{
		weightSum += weightage[i];
		//printf("%f, ", weightage[i]);
	}
	
	/*
		Check if weight != 100 and modify weightage in same ratio
	*/
	if(weightSum != 100)
		for(int i=0 ; i<3 ; i++)
			weightage[i] /= weightSum/100;
	
	/*
		Calculate weighted loads from three provided methods
	*/
	FL = 0.0;
	FR = 0.0;
	RL = 0.0;
	RR = 0.0;
	/*
		Multiply 3 wheel loads by their weightages
	*/
	for(int i=0 ; i<3 ; i++)
	{
		FL += weightage[i]*w[i]->FL/100;
		FR += weightage[i]*w[i]->FR/100;
		RL += weightage[i]*w[i]->RL/100;
		RR += weightage[i]*w[i]->RR/100;
	}

}
/*
-------------------------END-------------------------
*/
