

//Define batteryMultiplierArray
float batteryMultiplierArray[] = {0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 1};


//TO-DO In the calling function for initAndReturnMultiplier, determine the index. 
//Change condition to battery <= 60%. And when calling, set i=soc/10
//UPDATE: calling function is returnBatteryMultiplier
float returnMultiplierFromArray(int i)
{
	return batteryMultiplierArray[6-i];
}

double stoppageTime = 0.0;

void stoppageTimeKeeper(loggedData* currentData)
{
	//TO-DO These are dummy values.Change the values.
	if( ((currentData->wheelSpeed.FL < 5) || (currentData->wheelSpeed.FL < 5) || (currentData->wheelSpeed.FL < 5) || (currentData->wheelSpeed.FL < 5)) )
	{
		stoppageTime+=0.01;				//TO-DO Replace with loop timing of the main loop in simpleVectoring_V2.cpp
	}
}


bool determineDriverChangeCompletion()
{
	if( stoppageTime > 180.0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}


//Call this function in preventSlip
float returnBatteryMultipler(loggedData* currentData, carData* carData, double elapsed)
{
	float batteryMultiplier = 1;				//If any of the following conditions aren't true, this makes sure 
												//that this module 
												//doesnt affect the value fetched from the map. 
												//Multiply the multipliers from the battery and brake modues
	stoppageTimeKeeper(currentData);
	if( determineDriverChangeCompletion() )		//To be executed after driver change
	{
		//Get aimed autoX Lap timings and specific competition's number  of laps in endurance 
		float lapTime = carData->autoXLapTime;
		int eventLapNumber = carData->eventLapNumber;	
	
		//Get current SOC and current elapsed time
		float SOC = currentData->batterySOC;
		float timeElapsed = elapsed;
			
		//for now, torque increasing part is not being considered. Instead, some sort of indication to the driver 
		//can be given, as according to the rules, driver requested torque cannot be increased by the ECU. 
		//So if elapsed >autox*laps let the driver know that he should go faster,using an indicator. Or better, 
		//TO-DO show him the estimated lap number he should be in.
	
		int currentlap = currentData->currentLapNumber;
	
		if(timeElapsed > lapTime*currentlap)
		{
		
			bool pressHarder = 1;
			//printf("\n%d\n", pressHarder);
			//TO-DO Add code to turn on a latching indicator to tell the driver to drive faster
		}	
		else
		{
			bool pressHarder = 0;
			//printf("\n%d\n", pressHarder);
		}
	
		//calculate torque increase in the map
		if(timeElapsed > lapTime*eventLapNumber)	
		{
	
		}
	
		if((SOC <= 60) && (timeElapsed > lapTime*eventLapNumber))
		{
			batteryMultiplier = returnMultiplierFromArray((int)SOC/10);
		}
		//printf("\n%f\n", batteryMultiplier);
		//TO-DO Add modification to the torque map to increase torque based on elapsed>autoXLapTime*eventLapNumber
		return batteryMultiplier;
	}
	return batteryMultiplier;
}
	
	
