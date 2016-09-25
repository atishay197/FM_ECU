#include "wheelLoads.h"
#include "calculations.h"

outputTorque* torqueVectoring(loggedData* data, struct CarData* cData, FILE* outp, FILE* wout)
{
	float maxStraightAngle = 5;
	float minhairpinAngle = 20;

	int mode;

	wheelLoad* wLoad = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	wLoad = calculateWheelLoad(data,cData);
	writeWheelLoad(wLoad,wout);

	// mode determination
	if(data->steeredAngle < maxStraightAngle) mode = 1; 		//straight
	else if(data->steeredAngle > minhairpinAngle) mode = 2;		//hairpin

	switch (mode)
	{
		case 1 :		// straight
		{
			outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
			output = preventSlip(data);
			// TO DO : 0.9 and 1.1 in terms of % via machine learning algorithm
			if(output->torqueRL/output->torqueRR < 0.9)
				output->torqueRR=0.9*output->torqueRL;
			else if(output->torqueRL/output->torqueRR > 1.1)
				output->torqueRR=output->torqueRL/1.1;
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
