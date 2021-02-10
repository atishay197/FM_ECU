#include <bits/stdc++.h>
using namespace std;

// Open relevant header files

#include "outputTorqueModule.h"

arrayDivider tpsAD;						
arrayDivider slipAD;					
arrayDivider wheelLoadAD;				
arrayDivider radiusAD;					
arrayDivider wheelSpeedAD;


int main()
{
	double timer = 0;					// Initialize Timer
	
	initializeAllArrayDivider();
	fclose(arrayDivisionFile);
	arrayDivider sensorDivisions[5];	// Assign to array for ease of use
	sensorDivisions[0] = tpsAD;			
	sensorDivisions[1] = slipAD;
	sensorDivisions[2] = wheelLoadAD;
	sensorDivisions[3] = radiusAD;
	sensorDivisions[4] = wheelSpeedAD;
	
	carData* cardata = new carData;
	cardata->readCarDataFromCSV(carDataFile);
	
	char buffer[1000];					// Buffer to read lines from CSV
	
	// Initialize minimum frequency and count to keep track of torquevectoring() iterations
    float minfreq = 9999999,count = 0, avgFreq = 0;
    
	sensorData* prevData = new sensorData;
	
	sensorData prev;
	
	clock_t b = clock();
	
	while( fgets(buffer, 1000, sensorDataFile) != NULL )
	{
		timer += 0.01;
		
		clock_t e = clock();
		
		double elapsed = double(e-b)/CLOCKS_PER_SEC;
		
		b = clock();
		
		sensorData* currentData = new sensorData;
		currentData->readSensorDataFromCSV(buffer);
		
		outputTorque oT;
		if(currentData->getSensorData_exists())
		{	
			oT.torqueVectoring(prevData, currentData, cardata, elapsed, sensorDivisions);
		}
		else
		{
			break;
		}
		
		prev = sensorData(currentData);
		prevData  = &prev;
		
		float curfreq = 1/(elapsed*1000);
        avgFreq = ((count*avgFreq) + curfreq)/(count+1);
        count++;		
		
		if(curfreq < minfreq)
			minfreq = curfreq;
		cout<<timer<<" : "<<elapsed<<" : "<<curfreq<<" kHz"<<endl;
	}
	cout<<"Minimum frequency: "<<minfreq<<"kHz\t"<<"Averagre frequency: "<<avgFreq<<"kHz\t"<<endl;
	
	// Close all files, including extra files that are added in the beginning
	fclose(sensorDataFile);
	fclose(wout);
	fclose(weightageFile);
	fclose(outerWheelMap);
	fclose(innerWheelMap);


}

