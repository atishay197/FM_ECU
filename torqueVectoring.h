#include "calculations.h"

outputTorque* torqueVectoring(loggedData* prevData, loggedData* data, struct CarData* cData, double elapsed,struct arrayDivider sensorDivisions[5])
{
	// TO DO Neural networks to be used here
	// Assign steergin angles for case detemination
	float maxStraightAngle = 5; // Changed for testing purposes only
	float minhairpinAngle = 20;

	int mode;
	// Calculate wheel load for current sensor data
	wheelLoad* wLoad = calculateWheelLoad(prevData,data,cData,elapsed);

	// write wheel load to file
	writeWheelLoad(wLoad,wout);
	// mode determination
	if(abs(data->steeredAngle) < maxStraightAngle) mode = 1; 		//straight
	else if(abs(data->steeredAngle) > minhairpinAngle) mode = 2;		//hairpin

	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	// prevent slip gets data from map and calculates output torque
	output = preventSlip(prevData,data,cData,elapsed,wLoad,sensorDivisions);
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
			return writeAndReturn(output,outp);
		}
		case 2 :		// hairpin
		{

		}
		default:
		{

		}
	}

	return NULL;
}
