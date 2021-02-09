

//The power to the motors must be immediately shut down completely, if the mechanical brakes are
//actuated and the APPS signals more than 25% pedal travel at the same time.
//The motor power shut down must remain active until the APPS signals less than 5% pedal travel, no
//matter whether the brakes are still actuated or not.

//A standalone non-programmable circuit must be used on the car such that when braking hard (without
//locking the wheels) and when a positive current is delivered from the motor controller (a current to
//propel the vehicle forward), the AIRs will be opened. The current limit for triggering the circuit must
//be set at a level where 5kW of electrical power in the DC circuit is delivered to the motors at the
//nominal battery voltage. The action of opening the AIRs must occur if the implausibility is persistent
//for more than 0.5sec.

//TO-DO Add intial Bleed pressure

float brakeMultiplierArray[] = {1, 0.8, 0.6, 0.4, 0.2, 0.1};		//TO-DO change the array as required

float returnBrakeMultiplierFromArray(int i)
{
	return brakeMultiplierArray[5-i];
}

bool determineBrakeState(loggedData* currentData)
{
	if( currentData->brakePressure.rear > 5000 )			//If hard braking, return 1
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

int determineWheelState(loggedData* currentData)
{
	float averageRearSpeed = 0.5*(currentData->wheelSpeed.RL + currentData->wheelSpeed.RR);
	if ( averageRearSpeed < 60)	return -1;
	if ( averageRearSpeed > 1000)	return 1;
	return 0;
}


float returnBrakeMultiplier(loggedData* currentData, carData* carData, double elapsed)
{
	bool brakeState = determineBrakeState(currentData);
	static int flag = 0;
	float avgTPS = (currentData->throttle.TPS1 + currentData->throttle.TPS2)/2;
	if( (avgTPS > 25.0) && brakeState )
	{
		flag = 1;
	}
	
	if( flag != 1 && (brakeState))		//Redundancy to the above case	
	{									//Might need to remove this case
		return 0;
	}
	
	if( flag == 0 )
	{
		return returnBrakeMultiplierFromArray((int)currentData->brakePressure.rear/1000);
	}
	
	if(flag == 1)
	{
		if(avgTPS < 5)
		{
			flag = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}	
}
