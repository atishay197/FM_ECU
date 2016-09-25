// All calculative functions

float decreaseBy(float value, float percentage)
{
	return value*percentage/100;
}

bool inRange(float value1, float value2 , float percentage)
{
	float maxval2 = value2 * 0.01 * (100 + percentage);
	float minval2 = value2 * 0.01 * (100 - percentage);
	if(value1 <= minval2 || value1 >= maxval2)
		return false;
	return true;
}

float bringInRange(float value1, float value2, float percentage)
{
	if(!inRange(value1,value2,percentage))
		return value1>value2?value2*(100+percentage)*0.01:value2*(100-percentage)*0.01;
}

float getAvgTPS(struct Throttle t)
{
	return ( t.TPS1 + t.TPS2 ) / 2;
}

//TO DO: Write code for calculation
float calculateTurningRadius(float steeredAngle)
{
	return 5;
}

wheelLoad* returnWeightedLoads(wheelLoad* w[3], float weightage[3])
{
	wheelLoad* wFinal = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	wFinal->FL = 0;
	wFinal->FR = 0;
	wFinal->RL = 0;
	wFinal->RR = 0;
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
	float ef = (cData->track.front)/1000;						// m
	float er = (cData->track.rear)/1000;						// m
	float mv = cData->carWeight + cData->driverWeight; 			// kgs
	float l = (cData->wheelbase)/1000;							// m
	float h = (cData->cg.z)/1000;								// m
	float lf = (cData->cg.x)/1000;								// m
	float lr = l - lf;											// m
	float ax = data->gForce.longitudnal;						// m/sec^2
	float ay = data->gForce.lateral;							// m/sec^2
	w->FL = mv*((lr-h*ax)/l)*(0.5-((h*ay)/(ef)));
	w->FR = mv*((lr-h*ax)/l)*(0.5+((h*ay)/(ef)));
	w->RL = mv*((lf+h*ax)/l)*(0.5-((h*ay)/(ef)));
	w->RR = mv*((lf+h*ax)/l)*(0.5+((h*ay)/(ef)));
	// Formula from : http://www.gipsa-lab.grenoble-inp.fr/~moustapha.doumiati/VSD09.pdf
	return w;
}

// TO DO : complete this function
wheelLoad* calculateWheelLoadYaw(loggedData* data, carData* cData)
{
	wheelLoad* w = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	return w;
}

// TO DO : complete this function
wheelLoad* calculateWheelLoadSusPot(loggedData* data, carData* cData)
{
	wheelLoad* w = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	return w;
}

wheelLoad* calculateWheelLoad(loggedData* data, carData* cData)
{
	wheelLoad* w[3];	// wheelLoad from acceleration, yaw, SusPot
	// TO DO : Write function for calculating loads via Yaw and susPot
	w[0] = calculateWheelLoadAcceletarion(data,cData);
	w[1] = calculateWheelLoadYaw(data,cData);
	w[2] = calculateWheelLoadSusPot(data,cData);
	// TO DO : make weightage parameter modifiable
	// sum should always be 100
	float weightage[3] = {100,0,0};		// {Acceleration,Yaw,Suspot}
	float weightSum = 0;
	for(int i=0 ; i<3 ; i++)
		weightSum += weightage[i];
	if(weightSum != 100)				// check if weight != 100 and modify weightage in same ratio
		for(int i=0 ; i<3 ; i++)
			weightage[i] /= weightSum/100;
	return returnWeightedLoads(w,weightage);
}

// complete function to fetch data from map
float getOuterWheelTorque(float TPS, wheelLoad* load, float slip, float turningRadius)
{
	return 100;
}

// complete function to fetch data from map
float getInnerWheelTorque(float TPS, wheelLoad* load, float slip, float turningRadius)
{
	return 90;
}

// complete function to fetch data from map
outputTorque* getStraightLineTorque(float TPS, wheelLoad* load, float slip)
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	output->RR = 100;
	output->RL = 100;
	return output;
}

// strip required parameter from incoming data and call getTorque function to get R and L wheel data
outputTorque* getDataFromTorqueMap(loggedData* data, wheelLoad* load)
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	float TPS = getAvgTPS(data->throttle);
	float Rslip = 100 * ( (data->wheelSpeed.FR/data->wheelSpeed.RR) - 1 );
	float Lslip = 100 * ( (data->wheelSpeed.FL/data->wheelSpeed.RL) - 1 );
	float turningRadius = calculateTurningRadius(data->steeredAngle);
	// TO DO create fethcer for fetching data from map Outer, Inner or Straight
	// TO DO See, if 5 is appropriate value for not being straigth line, this is being doublechecked here.
	if(data->steeredAngle > 5)
	{
		output->RL = getOuterWheelTorque(TPS,load,Lslip,turningRadius);	// Outer Wheel - from Outer Wheel torque Map
		output->RR = getInnerWheelTorque(TPS,load,Rslip,turningRadius);	// Inner Wheel - from Inner Wheel torque Map
	}
	else if(data->steeredAngle > 5)
	{

		output->RR = getOuterWheelTorque(TPS,load,Rslip,turningRadius);	// Outer Wheel - from Outer Wheel torque Map
		output->RL = getInnerWheelTorque(TPS,load,Lslip,turningRadius);	// Inner Wheel - from Inner Wheel torque Map
	}
	else
		output = getStraightLineTorque(TPS,load,(Rslip+Lslip)/2);
	return output;
}

// Fetches data from the torque map and informs the ML map modifier to modify map
outputTorque* preventSlip(loggedData* data, carData* cData)
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	float avgTPS =  getAvgTPS(data->throttle);
	float avgF = (data->wheelSpeed.FL + data->wheelSpeed.FR) / 2;
	float avgR = (data->wheelSpeed.RL + data->wheelSpeed.RR) / 2;
	if(!inRange(avgR,avgF,10))	// TO DO replace this 10 with feature which is modifiable/mappable
	{
		float Rslip = 100 * ( (data->wheelSpeed.FR/data->wheelSpeed.RR) - 1 );
		float Lslip = 100 * ( (data->wheelSpeed.FL/data->wheelSpeed.RL) - 1 );
		// TO DO : Add a learner which keeps track of slip to modify MAP
		// sendToLearner(Rslip,Lslip)
	}
	output = getDataFromTorqueMap(data,calculateWheelLoad(data,cData));
	return output;
}


