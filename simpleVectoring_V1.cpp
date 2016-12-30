#include <bits/stdc++.h>
using namespace std;

FILE* file = fopen("Sample.csv","r");
FILE* fcar = fopen("CarData.csv","r");
FILE* outp = fopen("outputTorque.csv","w");
FILE* wout = fopen("wheel.csv","w");

#include "dataLoggingStructures.h"
#include "outputTorque.h"
#include "wheelLoads.h"
#include "carData.h"
#include "clustering.h"
#include "torqueVectoring.h"
#include "arrayDivisionFetcher.h"


loggedData* readnextcsv(char buffer[10000])
{
    // Simple read from file and assign in structure
	loggedData* prevdata;
    prevdata = (LoggedData *)malloc(sizeof(struct LoggedData));
    prevdata->exists = true;
    prevdata->currentTime = atof(strtok(buffer, ","));
    prevdata->distance = atoi(strtok(NULL, ","));
    prevdata->brakePressure.front = atoi(strtok(NULL, ","));
    prevdata->brakePressure.rear = atoi(strtok(NULL, ","));
    prevdata->drivespeed = atof(strtok(NULL, ","));
    prevdata->wheelSpeed.FL = atof(strtok(NULL, ","));
    prevdata->wheelSpeed.FR = atof(strtok(NULL, ","));
    prevdata->wheelSpeed.RL = atof(strtok(NULL, ","));
    prevdata->wheelSpeed.RR = atof(strtok(NULL, ","));
    prevdata->gForce.longitudnal = atof(strtok(NULL, ","));
    prevdata->gForce.lateral = atof(strtok(NULL, ","));
    prevdata->gForce.vertical = atof(strtok(NULL, ","));
    prevdata->gyroYawVelocity = atof(strtok(NULL, ","));
    prevdata->steeredAngle = atof(strtok(NULL, ","));
    prevdata->throttle.TPS1 = atof(strtok(NULL, ","));
    prevdata->throttle.TPS2 = prevdata->throttle.TPS1+prevdata->throttle.TPS1*(((float)(rand()%30)-15)/1000);
	prevdata->susPot.FL = atof(strtok(NULL, ","));
    prevdata->susPot.FR = atof(strtok(NULL, ","));
    prevdata->susPot.RL = atof(strtok(NULL, ","));
    prevdata->susPot.RR = atof(strtok(NULL, ","));
	return prevdata;
}

carData* readCarData()
{
    // read first line from file and update structure in program
    char buffer[1000];
    if(fgets(buffer, 1000, fcar) != NULL)
    {
        carData* cardata = (carData *)malloc(sizeof(struct CarData));
        cardata->carWeight = atof(strtok(buffer, ","));
        cardata->driverWeight = atof(strtok(NULL, ","));
        cardata->cg.x = atof(strtok(NULL, ","));
        cardata->cg.y = atof(strtok(NULL, ","));
        cardata->cg.z = atof(strtok(NULL, ","));
        cardata->wheelbase = atof(strtok(NULL, ","));
        cardata->track.front = atof(strtok(NULL, ","));
        cardata->track.rear = atof(strtok(NULL, ","));
        cardata->wheelDiameter = atof(strtok(NULL, ","));
        cardata->tirePressure.front = atof(strtok(NULL, ","));
        cardata->tirePressure.rear = atof(strtok(NULL, ","));
        cardata->camber.front = atof(strtok(NULL, ","));
        cardata->camber.rear = atof(strtok(NULL, ","));
        cardata->frontDistribution = atof(strtok(NULL, ","));
		cardata->suspension.dampingCoeff = atof(strtok(NULL, ","));
		cardata->suspension.springConstant = atof(strtok(NULL, ","));
		cardata->suspension.pRodAngle = atof(strtok(NULL, ","));
        fclose(fcar);
        return cardata;
    }
}

int main()
{
    // Write FL FR RL RR to output file : wheelLoad.csv for readbility
    fprintf(wout,"FL,FR,RL,RR\n");
    // initiate timer
	double timer = 0;
    // initialize array divider to read divisions for map from file
    struct arrayDivider sensorDivisions[5];
    // arrayDivider[0] = 
    // TO DO remove in finla code read from sensors directly
    // buffer to read each line in CSV
	char buffer[10000];
    // initialize minimum frequency and count to keep track of torquevectoring() iterations
    float minfreq = 9999999,count = 0, avgFreq = 0;
    // read carData like weight, CG coordinates, wheelbase, track etc.
    carData* carData = readCarData();
    // printCarData(carData);
    // Initialize prevData to e=be used in case of difference btw prev and current values are required
    // Eg : used in case of calculation of wheel loads via gyro
	loggedData* prevData = (LoggedData *)malloc(sizeof(struct LoggedData));
    // initialize begin clock
    clock_t b = clock();
    // While sensor is still providing data
	while(fgets(buffer, 1000, file) != NULL)
	{
        // TO DO: increase timer based on actual timer in actual code
		timer += 0.01;
        // End clock value assigned
		clock_t e = clock();
        // calculate time difference to calculate code frequency
  		double elapsed = double(e - b)/CLOCKS_PER_SEC;	
        // reassign begin to variable b
		b = clock();
        // read logged data from sensors in case of real code
		loggedData* currentData = readnextcsv(buffer);
		// printData(currentData);
        // called until current data exists, 
        // currentData->exists = false in case of data logging error
		if(currentData->exists)
        {   
            // EXECUTE TORQUE VECTORING ALGORITHM FOR EACH INPUT DATA.
			torqueVectoring(prevData,currentData,carData,elapsed, sensorDivisions);
        }
		else
			break;	
        // assign current data values to current Data to be used in the next loop	
		prevData = currentData;		
        // frequency calculation
		float curfreq = 1/(elapsed*1000);
        avgFreq = (((count)*avgFreq + curfreq)/(count+1));
        count++;
        // assign minimum frequency if current frequency is lower than it
        if(curfreq<minfreq) 
            minfreq = curfreq;
        printf("%f : %f :: %f kHz\n",timer,elapsed,curfreq);
	}
    printf("Minimum frequency : %f KHz\nAverage frequency : %f KHz\n",minfreq,avgFreq);
    // TO DO close all files, including extra files that are added in the beggining
    fclose(outp);
    fclose(file);
	fclose(wout);
}
