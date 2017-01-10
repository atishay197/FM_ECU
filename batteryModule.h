

//Define batteryMultiplierArray
float batteryMultiplierArray[] = {0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 1};


//TO-DO In the calling function for initAndReturnMultiplier, determine the index. Change condition to battery <= 60%. And when calling, set i=soc/10
//UPDATE: calling function is returnBatteryMultiplier
float returnMultiplierFromArray(int i)
{
	return batteryMultiplierArray[6-i];
}

//TO-DO Call this function in preventSlip
float returnBatteryMultipler(loggedData* currentData, carData* carData)
{
	//Get aimed autoX Lap timings and specific competition's number  of laps in endurance 
	float lapTime = carData->autoXLapTime;
	float eventLapNumber = carData->eventLapNumber;
	
	
	
	float SOC = currentData->batterySOC;
	int timeElapsed = currentData->currentTime;
	
	//for now, torque increasing part is not being considered. Instead, some sort of indication to the driver 
	//can be given, as according to the rules, driver requested torque cannot be increased by the ECU. 
	//So if elapsed >autox*laps let the driver know that he should go faster,using an indicator. Or better, 
	//show him the estimated lap number he should be in.
	
	//int currentlap = currentData->lap;
	/*
	if(timeElapsed > lapTime*currentlap)
	{
		
		bool pressHarder = TRUE;
		//TO-DO Add code to turn on a latching indicator to tell the driver to drive faster
	}
	else
	{
		bool pressHarder = FALSE;
	*/
	
	
	float batteryMultiplier = 1;				//If any of the following conditions aren't true, this makes sure that this module doesnt affect the value fetched from the map. Multiply the multipliers from the battery and brake modues
	if((SOC <= 60) && (timeElapsed > lapTime*eventLapNumber))
	{
		batteryMultiplier = returnMultiplierFromArray((int)SOC/10);
	}
	//TO-DO Add modification to the torque map to increase torque based on elapsed>autoXLapTime*eventLapNumber
	return batteryMultiplier;
}
	
	
