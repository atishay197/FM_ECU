#include "mapDataLayer.h"
#include "batteryModule.h"
#include "brakeModule.h"
// All calculative functions

float decreaseBy(float value, float percentage)
{
	return value*percentage/100;
}

// check if value1 is within +/- percentage of value 2
bool inRange(float value1, float value2 , float percentage)
{
	float maxval2 = value2 * 0.01 * (100 + percentage);
	float minval2 = value2 * 0.01 * (100 - percentage);
	// if value less than ninimum permitted value
	// or
	// greater than maximum possible value
	// then return false
	if(value1 <= minval2 || value1 >= maxval2)
		return false;
	return true;
}

// bring value 1 within some percantage of value 2 
float bringInRange(float value1, float value2, float percentage)
{
	// Eg: percentage = 5
	// if 1st value is greater than second value
	// return ((100 + 5)/100)*value2 = 1.05*value2
	// else if second is greater than 1st
	// return ((100-5)/100)*value2 = 0.95*value2
	if(!inRange(value1,value2,percentage))
		return value1>value2?value2*(100+percentage)*0.01:value2*(100-percentage)*0.01;
}

// Find average value of 2 TPSes
float getAvgTPS(struct Throttle t)
{
	return ( t.TPS1 + t.TPS2 ) / 2;
}

// Calculate turning radious given the steeredAngle
float calculateTurningRadius(float steeredAngle,float wheelbase)
{
	float turnRadius;
	if (steeredAngle != 0)
		turnRadius = (wheelbase/tan((3.1415*steeredAngle)/180));  
	//tan function from math.h, will give negative radius for left turn
	else if (steeredAngle == 0)
		turnRadius = 99999;
	// printf("%f \n",turnRadius);	
	return turnRadius;
}

// Returns weighted wheel loads 
// Eg: Weight of loads : 50,35,15
// Final weight returned = 0.5*w1 + 0.35*w2 + 0.15*w3 for all 4 wheels
wheelLoad* returnWeightedLoads(wheelLoad* w[3], float weightage[3])
{
	wheelLoad* wFinal = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	wFinal->FL = 0;
	wFinal->FR = 0;
	wFinal->RL = 0;
	wFinal->RR = 0;
	// multiply 3 wheel loads by their weightages
	for(int i=0 ; i<3 ; i++)
	{
		wFinal->FL += weightage[i]*w[i]->FL/100;
		wFinal->FR += weightage[i]*w[i]->FR/100;
		wFinal->RL += weightage[i]*w[i]->RL/100;
		wFinal->RR += weightage[i]*w[i]->RR/100;
	}
	return wFinal;
}

// TO DO : Add other ways of calculating wheel Loads
// 			1. WheelLoad from Yaw
// 			2. Wheel Load from suspot 

wheelLoad* calculateWheelLoadAcceletarion(loggedData* data, carData* cData)
{
	wheelLoad* w = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	// Front Track
	float ef = (cData->track.front)/1000;						// m
	// Rear Track
	float er = (cData->track.rear)/1000;						// m
	// Total car + drive rweight
	float mv = cData->carWeight + cData->driverWeight; 			// kgs
	// Wheelbase of the car
	float l = (cData->wheelbase)/1000;							// m
	// CG z coordinates
	float h = (cData->cg.z)/1000;								// m
	// CG x coordinates
	float lf = (cData->cg.x)/1000;								// m
	// Distance between rear wheel and CG
	float lr = l - lf;											// m
	// Logitudnal and lateral acceleration
	float ax = data->gForce.longitudnal;						// m/sec^2
	float ay = data->gForce.lateral;							// m/sec^2
	// Final wheel load calculation
	// Formula from : http://www.gipsa-lab.grenoble-inp.fr/~moustapha.doumiati/VSD09.pdf
	w->FL = mv*((lr-h*ax)/l)*(0.5-((h*ay)/(ef)));
	w->FR = mv*((lr-h*ax)/l)*(0.5+((h*ay)/(ef)));
	w->RL = mv*((lf+h*ax)/l)*(0.5-((h*ay)/(ef)));
	w->RR = mv*((lf+h*ax)/l)*(0.5+((h*ay)/(ef)));
	return w;
}

// TO DO : complete this function
// This function is not being currently used
wheelLoad* calculateWheelLoadYaw(loggedData* data, carData* cData)
{
	wheelLoad* w = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	return w;
}

// TO DO : complete this function
wheelLoad* calculateWheelLoadSusPot(loggedData* prevData, loggedData* data, carData* cData, double elapsed)
{
	wheelLoad* w = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	float B = cData->suspension.dampingCoeff;
	float K = cData->suspension.springConstant;
	float theta = (cData->suspension.pRodAngle)*3.1415/180;
	
	/* Commented as the term containing B is not relevant in steadystate
	w->FL = cos(theta) * ( ( B * ( (data->susPot.FL) - (prevData->susPot.FL) ) / elapsed) + ( K * (data->susPot.FL) ) );
	w->FR = cos(theta) * ( ( B * ( (data->susPot.FR) - (prevData->susPot.FR) ) / elapsed) + ( K * (data->susPot.FR) ) );
	w->RL = cos(theta) * ( ( B * ( (data->susPot.RL) - (prevData->susPot.RL) ) / elapsed) + ( K * (data->susPot.RL) ) );
	w->RR = cos(theta) * ( ( B * ( (data->susPot.RR) - (prevData->susPot.RR) ) / elapsed) + ( K * (data->susPot.RR) ) );
	*/
	w->FL = cos(theta) * ( K * (data->susPot.FL) );
	w->FR = cos(theta) * ( K * (data->susPot.FR) );
	w->RL = cos(theta) * ( K * (data->susPot.RL) );
	w->RR = cos(theta) * ( K * (data->susPot.RR) );
	//printWheelLoad(w);
	return w;
}

wheelLoad* calculateWheelLoad(loggedData* prevData, loggedData* data, carData* cData, double elapsed)
{
	wheelLoad* w[3];	// wheelLoad from acceleration, SusPot, yaw
	// TO DO : Write function for calculating loads via Yaw and susPot
	w[0] = calculateWheelLoadAcceletarion(data,cData);
	w[1] = calculateWheelLoadSusPot(prevData,data,cData,elapsed);
	// This method will be deprecated until proper calculation are possible
	w[2] = calculateWheelLoadYaw(data,cData);
	// TO DO : make weightage parameter modifiable
	// sum should always be 100
	// FILE *weightage_file  = fopen("weightage.txt", "r"); //open weightage_file having editable weights
	float weightage[3] = {100,0,0};		// {Acceleration,Suspot,Yaw}
	// fscanf(weightage_file, "%f %f %f", &weightage[0], &weightage[1], &weightage[2]); //read and assign to weightages
	// fclose(weightage_file);
	float weightSum = 0;
	for(int i=0 ; i<3 ; i++)
	{
		weightSum += weightage[i];
		//printf("%f, ", weightage[i]);
	}
	// Check if weight != 100 and modify weightage in same ratio
	if(weightSum != 100)
		for(int i=0 ; i<3 ; i++)
			weightage[i] /= weightSum/100;
	// Calculate weighted loads from three provided methods
	return returnWeightedLoads(w,weightage);
}

// TO DO complete function to fetch data from map
float getOuterWheelTorque(float TPS, float load, float slip, float turningRadius, float wheelSpeed,struct arrayDivider a[5])
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
float getInnerWheelTorque(float TPS, float load, float slip, float turningRadius, float wheelSpeed,struct arrayDivider a[5])
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
outputTorque* getStraightLineTorque(float TPS, float load, float slip, float wheelSpeed,struct arrayDivider a[5])
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	output->RR = 100;
	output->RL = 100;
	return output;
}

// strip required parameter from incoming data and call getTorque function to get R and L wheel data
outputTorque* getDataFromTorqueMap(loggedData* data, wheelLoad* load,float wheelbase,struct arrayDivider a[5])
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	// Get values from different sensors
	float TPS = getAvgTPS(data->throttle);
	float Rslip = 100 * ( (data->wheelSpeed.FR/data->wheelSpeed.RR) - 1 );
	float Lslip = 100 * ( (data->wheelSpeed.FL/data->wheelSpeed.RL) - 1 );
	float turningRadius = calculateTurningRadius(data->steeredAngle,wheelbase);
	// TO DO create fethcer for fetching data from map Outer, Inner or Straight
	// TO DO See, if 5 is appropriate value for not being straigth line, this is being doublechecked here.
	if(data->steeredAngle > 3)
	{
		output->RL = getOuterWheelTorque(TPS,load->RL,Lslip,turningRadius,data->wheelSpeed.RL,a);	// Outer Wheel - from Outer Wheel torque Map
		output->RR = getInnerWheelTorque(TPS,load->RR,Rslip,turningRadius,data->wheelSpeed.RR,a);	// Inner Wheel - from Inner Wheel torque Map
	}
	else if(data->steeredAngle < -3)
	{
		output->RR = getOuterWheelTorque(TPS,load->RR,Rslip,turningRadius,data->wheelSpeed.RR,a);	// Outer Wheel - from Outer Wheel torque Map
		output->RL = getInnerWheelTorque(TPS,load->RL,Lslip,turningRadius,data->wheelSpeed.RL,a);	// Inner Wheel - from Inner Wheel torque Map
	}
	else
	{
		// only average wheel speeds considered as straight line will not require Torque Vectoring
		float avgWheelSpeed = (data->wheelSpeed.RR + data->wheelSpeed.RL)/2;
		float avgWheelLoad= (load->RR + load->RL)/2;
		output = getStraightLineTorque(TPS,avgWheelLoad,(Rslip+Lslip)/2,avgWheelSpeed,a);
	}
	return output;
}

// Fetches data from the torque map and informs the ML map modifier to modify map

outputTorque* preventSlip(loggedData* prevData, loggedData* data, carData* cData, double elapsed, wheelLoad* wLoad,struct arrayDivider a[5])
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	// Calculate average front Wheel and rear Wheel speeds for slip calculations
	float avgF = (data->wheelSpeed.FL + data->wheelSpeed.FR) / 2;
	float avgR = (data->wheelSpeed.RL + data->wheelSpeed.RR) / 2;
	// TO DO Replace maxOutOfRange with a slip tracker feature so that algo can learn
	// This is the maximum value that the wheel loads can be off 
	// Eg: if it is 5. rear wheel speed = 100 and front wheel speed = 93 continuous slip evaluation is 
	// 		informed about the complete misallignment in wheel speeds thus allowing it to sent an arbitrary 
	// 		high slip value torque, whish is decreased via a fractional multiplier.
	float maxOutOfRange = 5;
	// 
	if(!inRange(avgR,avgF,maxOutOfRange))	// TO DO replace this 10 with feature which is modifiable/mappable
	{
		float Rslip = 100 * ( (data->wheelSpeed.FR/data->wheelSpeed.RR) - 1 );
		float Lslip = 100 * ( (data->wheelSpeed.FL/data->wheelSpeed.RL) - 1 );
		// int group = slipCluster((Rslip+Lslip)/2);
		// TO DO : Add a learner which keeps track of slip to modify MAP
		// float fractionalMultiplier = 1 - group*0.1;
		float fractionalMultiplier = 0.9;
		//printf("Slip\n");
		// fractionalMultiplier = sendToLearner(Rslip,Lslip);
		output = getDataFromTorqueMap(data,wLoad,cData->wheelbase,a);
		output->RR *= fractionalMultiplier; 
		output->RL *= fractionalMultiplier; 
	}
	else
		output = getDataFromTorqueMap(data,wLoad,cData->wheelbase,a);
	// calculateWheelLoad(prevData,data,cData,elapsed)
	float batteryMultiplier = returnBatteryMultipler(data,cData,elapsed);
	float brakeMultiplier = returnBrakeMultiplier(data, cData, elapsed);
	return output;
}
