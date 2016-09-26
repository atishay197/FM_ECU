#include <bits/stdc++.h>
#include "dataLoggingStructures.h"
#include "outputTorque.h"
#include "wheelLoads.h"
#include "carData.h"
#include "torqueVectoring.h"

using namespace std;

FILE* file = fopen("Sample.csv","r");
FILE* fcar = fopen("CarData.csv","r");
FILE* outp = fopen("outputTorque.csv","w");
FILE* wout = fopen("wheel.csv","w");


loggedData* readnextcsv(char buffer[1000])
{
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
	return prevdata;
}

carData* readCarData()
{
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
        return cardata;
    }
}

int main()
{
    fprintf(wout,"FL,FR,RL,RR\n");
  	clock_t b = clock();
	double timer = 0;
	char buffer[1000];
    float minfreq = 9999999;
    carData* carData = readCarData();
    printCarData(carData);
    float avgFreq = 0;
	while(fgets(buffer, 1000, file) != NULL)
	{
		timer += 0.01;
		loggedData* currentData = readnextcsv(buffer);
		printData(currentData);
		if(currentData->exists)
        {
			torqueVectoring(currentData,carData,outp,wout);	// EXECUTE TORQUE VECTORING ALGORITHM FOR EACH INPUT DATA.
        }
		else
			break;
		clock_t e = clock();
  		double elapsed = double(e - b)/CLOCKS_PER_SEC;
        float curfreq = 1/(elapsed*1000);
  		//printf("Time : %f :: Frequency : %f kHz\n",elapsed,curfreq);
        avgFreq = (((timer*100)-1)*avgFreq + curfreq)/(timer*100);
        if(curfreq<minfreq) 
            minfreq = curfreq;
  		b = clock();
	}
    printf("Minimum frequency : %f\nAverage frequency : %f\n",minfreq,avgFreq);
    fclose(outp);
	fclose(wout);
}
