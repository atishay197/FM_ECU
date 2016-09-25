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

wheelLoad* calculateWheelLoad(loggedData* data, carData* cData)
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

outputTorque* preventSlip(loggedData* data, carData* cData)
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	float avgTPS =  ( data->throttle.TPS1 + data->throttle.TPS2 ) / 2;
	float requiredChange = 0;
	float FL = data->wheelSpeed.FL;
	float FR = data->wheelSpeed.FR;
	float RL = data->wheelSpeed.RL;
	float RR = data->wheelSpeed.RR;
	float avgF = (FL + FR) / 2;
	float avgR = (RL + RR) / 2;
	if(!inRange(avgR,avgF,10))
		requiredChange = bringInRange(avgR,avgF,10)
	output = getDataFromTorqueMap(data,requiredChange,calculateWheelLoad(data,cData));
	return output;
}

outputTorque* getDataFromTorqueMap(data,requiredChange,wheelLoad* load)
{
	return 5;
}
