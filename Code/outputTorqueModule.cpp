#include "outputTorqueModule.h"

/*
	Setters for the data members
*/
void outputTorque::setOutputTorque_RL(float RL)
{
	this->RL = RL;
}

void outputTorque::setOutputTorque_RR(float RR)
{
	this->RR = RR;
}	
			
/*
	Getters for the data members
*/
float outputTorque::getOutputTorque_RL()
{
	return RL;
}

float outputTorque::getOutputTorque_RR()
{
	return RR;
}


/*
	Prints output torque values to standard output.
*/
void outputTorque::printOutputTorque()
{
	printf("Output Torque :: RL : %f :: RR : %f\n", RL, RR);
	return;
}

/*
	Prints output torque to a file.
*/
void outputTorque::writeOutputTorque(FILE* outfile)
{
	fprintf(outfile,"%f,%f\n", RL, RR);
}
	
// TO DO complete function to fetch data from map
float outputTorque::getOuterWheelTorque(float TPS, float load, float slip, float turningRadius, float wheelSpeed,arrayDivider a[5])
{
	// Initialize array value struct with cur divisions and values needed for interpolation
	arrayValueStruct avs = arrayValueStruct(TPS, load, slip, turningRadius, wheelSpeed, 5, a);
	// get map fetcher stucture from calculated array svalue structure
	mapFetcherStruct outerMap = mapFetcherStruct(avs);
	// printMapFetcherStruct(outerMap);
	mapData outerWheelTorqueData = getDataFromOuterWheelMap(outerMap);
	// return after interpolating value depending on it's inclination toward's lower/higher value.
	return interpolateFromMap(outerWheelTorqueData,outerMap,avs); 
}

// complete function to fetch data from map
float outputTorque::getInnerWheelTorque(float TPS, float load, float slip, float turningRadius, float wheelSpeed, arrayDivider a[5])
{
	// Initializr array value struct with cur divisions and values needed for interpolation
	arrayValueStruct avs = arrayValueStruct(TPS, load, slip, turningRadius, wheelSpeed,5, a);
	// get map fetcher stucture from calculated array svalue structure
	mapFetcherStruct innerMap = mapFetcherStruct(avs);
	// printMapFetcherStruct(innerMap);
	mapData innerWheelTorqueData = getDataFromInnerWheelMap(innerMap);
	// return after interpolating value depending on it's inclination toward's lower/higher value.
	return interpolateFromMap(innerWheelTorqueData,innerMap,avs); 
}

// complete function to fetch data from map
void outputTorque::getStraightLineTorque(float TPS, float load, float slip, float wheelSpeed, arrayDivider a[5])
{
	RR = 100;
	RL = 100;
}

// strip required parameter from incoming data and call getTorque function to get R and L wheel data
void outputTorque::getDataFromTorqueMap(sensorData* data, wheelLoad* load, float wheelbase, arrayDivider a[5])
{
	
	// Get values from different sensors
	float TPS = (data->getSensorData_throttle_TPS1() + data->getSensorData_throttle_TPS2())/2; 
	float Rslip = 100 * ( (data->getSensorData_wheelSpeed_FR()/data->getSensorData_wheelSpeed_RR()) - 1 );
	float Lslip = 100 * ( (data->getSensorData_wheelSpeed_FL()/data->getSensorData_wheelSpeed_RL()) - 1 );
	float turningRadius = calculateTurningRadius(data->getSensorData_steeredAngle(), wheelbase); 
	// TO DO create fethcer for fetching data from map Outer, Inner or Straight
	// TO DO See, if 5 is appropriate value for not being straigth line, this is being doublechecked here.
	if(data->getSensorData_steeredAngle() > 3)
	{
		RL = getOuterWheelTorque(TPS, load->getWheelLoad_RL(), Lslip, turningRadius, data->getSensorData_wheelSpeed_RL(), a);	
		RR = getInnerWheelTorque(TPS, load->getWheelLoad_RR(), Rslip, turningRadius, data->getSensorData_wheelSpeed_RR(), a);	
	}
	else if(data->getSensorData_steeredAngle() < -3)
	{
		RR = getOuterWheelTorque(TPS, load->getWheelLoad_RR(), Rslip, turningRadius, data->getSensorData_wheelSpeed_RR(), a);	
		RL = getInnerWheelTorque(TPS, load->getWheelLoad_RL(), Lslip, turningRadius, data->getSensorData_wheelSpeed_RL(), a);	
	}
	else
	{
		// only average wheel speeds considered as straight line will not require Torque Vectoring
		float avgWheelSpeed = (data->getSensorData_wheelSpeed_RR() + data->getSensorData_wheelSpeed_RL())/2;
		float avgWheelLoad= (load->getWheelLoad_RR() + load->getWheelLoad_RL())/2;
		getStraightLineTorque(TPS, avgWheelLoad, (Rslip+Lslip)/2, avgWheelSpeed, a);
	}
}

// Fetches data from the torque map and informs the ML map modifier to modify map
void outputTorque::preventSlip(sensorData* prevData, sensorData* data, carData* cData, double elapsed, wheelLoad* wLoad, arrayDivider a[5])
{
	// Calculate average front Wheel and rear Wheel speeds for slip calculations
	float avgF = (data->getSensorData_wheelSpeed_FL() + data->getSensorData_wheelSpeed_FR()) / 2;
	float avgR = (data->getSensorData_wheelSpeed_RL() + data->getSensorData_wheelSpeed_RR()) / 2;
	// TO DO Replace maxOutOfRange with a slip tracker feature so that algo can learn
	// This is the maximum value that the wheel loads can be off 
	// Eg: if it is 5. rear wheel speed = 100 and front wheel speed = 93 continuous slip evaluation is 
	// 		informed about the complete misallignment in wheel speeds thus allowing it to sent an arbitrary 
	// 		high slip value torque, whish is decreased via a fractional multiplier.
	float maxOutOfRange = 5;
	// 
	if(!inRange(avgR,avgF,maxOutOfRange))	// TO DO replace this 10 with feature which is modifiable/mappable
	{
		float Rslip = 100 * ( (data->getSensorData_wheelSpeed_FR()/data->getSensorData_wheelSpeed_RR()) - 1 );
		float Lslip = 100 * ( (data->getSensorData_wheelSpeed_FL()/data->getSensorData_wheelSpeed_RL()) - 1 );
		// int group = slipCluster((Rslip+Lslip)/2);
		// TO DO : Add a learner which keeps track of slip to modify MAP
		// float fractionalMultiplier = 1 - group*0.1;
		float fractionalMultiplier = 0.9;
		//printf("Slip\n");
		// fractionalMultiplier = sendToLearner(Rslip,Lslip);
		getDataFromTorqueMap(data, wLoad, cData->getCarData_wheelbase(), a);
		RR *= fractionalMultiplier; 
		RL *= fractionalMultiplier; 
	}
	else
		getDataFromTorqueMap(data, wLoad, cData->getCarData_wheelbase(), a);
	// calculateWheelLoad(prevData,data,cData,elapsed)
	//float batteryMultiplier = returnBatteryMultipler(data,cData,elapsed);
	//float brakeMultiplier = returnBrakeMultiplier(data, cData, elapsed);
}


void outputTorque::torqueVectoring(sensorData* prevData, sensorData* data, carData* cData, double elapsed, arrayDivider sensorDivisions[5])
{
	// TO DO Neural networks to be used here
	
	// Assign steering angles for case detemination
	float maxStraightAngle = 5; // Changed for testing purposes only
	float minhairpinAngle = 20;

	int mode;
	
	// Calculate wheel load for current sensor data
	wheelLoad* wLoad;
	wLoad->calculateWheelLoad(prevData,data,cData,elapsed);

	// write wheel load to file
	wLoad->writeWheelLoad(wout);
	
	// mode determination
	if( abs(data->getSensorData_steeredAngle()) < maxStraightAngle ) mode = 1; 		//straight
	else if(abs(data->getSensorData_steeredAngle()) > minhairpinAngle) mode = 2;	//hairpin

	
	
	// prevent slip gets data from map and calculates output torque
	preventSlip(prevData,data,cData,elapsed,wLoad,sensorDivisions);
	
	// neural network and feedback need to be sent after the output torque has been output to the motor controll
	// This feedback and logging mechanism will start running after output thus not hindering performance
	// TO DO possibility of fork() operation for running this on a seperate thread
	switch (mode)
	{
		case 1 :		// straight
		{
			// TO DO : 0.9 and 1.1 in terms of % via machine learning algorithm
			// if(output->RL/output->RR < 0.9)
			// 	output->RR=0.9*output->RL;
			// else if(output->RL/output->RR > 1.1)
			// 	output->RR=output->RL/1.1;
			writeOutputTorque(outp);
		}
		case 2 :		// hairpin
		{

		}
		default:
		{

		}
	}	
}
/*
-------------------------END-------------------------
*/
