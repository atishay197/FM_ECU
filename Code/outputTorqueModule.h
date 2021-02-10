#include "wheelLoadsModule.h"
#include "mapReaderModule.h"
#include "calculationModule.h"
/*
	a. 	This class simply provides a data structure and necessary functions to send out the calculated
		torque command to  the Motor Controllers
	b. 	The class contains data members whose values will be sent to the motor controllers.
		For now, the values ae stored in a file. But this class will contain functions to send PWM
		output to the motor controllers.
*/

class outputTorque
{
	private:
			float RL;
			float RR;
	public:
			void setOutputTorque_RL(float);
			void setOutputTorque_RR(float);	
			
			float getOutputTorque_RL();
			float getOutputTorque_RR();
			
			void initializePWM();
			//void setOutputTorque(float, float);
			void printOutputTorque();
			void writeOutputTorque(FILE*);
			
			float getOuterWheelTorque(float, float, float, float, float, arrayDivider*);
			float getInnerWheelTorque(float, float, float, float, float, arrayDivider*);
			void getStraightLineTorque(float, float, float, float, arrayDivider*);
			void getDataFromTorqueMap(sensorData*, wheelLoad*, float, arrayDivider*);
			void preventSlip(sensorData*, sensorData*, carData*, double, wheelLoad*, arrayDivider*);
			void torqueVectoring(sensorData*, sensorData*, carData*, double, arrayDivider*);
			
};
/*
-------------------------END-------------------------
*/	


