#include "calculations.h"

outputTorque* torqueVectoring(loggedData* prevData, loggedData* data, struct CarData* cData, FILE* outp, FILE* wout , double elapsed)
{
	float maxStraightAngle = 10; // Changed for testing purposes only
	float minhairpinAngle = 20;

	int mode;

	wheelLoad* wLoad = calculateWheelLoad(prevData,data,cData,elapsed);
	writeWheelLoad(wLoad,wout);
	// mode determination
	if(abs(data->steeredAngle) < maxStraightAngle) mode = 1; 		//straight
	else if(abs(data->steeredAngle) > minhairpinAngle) mode = 2;		//hairpin

	switch (mode)
	{
		case 1 :		// straight
		{
			outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));

			output = preventSlip(prevData,data,cData,elapsed);
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
