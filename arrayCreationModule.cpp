#include <bits/stdc++.h>
#include "mapDataLayer.h"
FILE* arrayDivisionFile = fopen("arrayDivider.csv","w");	

arrayDivider tpsAD;
arrayDivider slipAD;
arrayDivider wheelLoadAD;
arrayDivider radiusAD;
arrayDivider wheelSpeedAD;

#include "arrayDivisionFetcher.h"

struct arrayDivider createLinearDivision(struct arrayDivider a)
{
	float diff = (a.range[1] -  a.range[0]) / a.divisions;
	for(int i=0  ; i<a.divisions ; i++)
	{
		if(i>0)
			a.rangeDivision[i] = a.rangeDivision[i-1] + diff;
		else
			a.rangeDivision[i] = a.range[0];
	}
	a.rangeDivision[a.divisions] = a.range[1];
	return a;
} 

// create logrithmic Division/range creator
struct arrayDivider createLogrithmicDivision(struct arrayDivider a,float logBase)
{
	float x;int i;
	float max = ((-1*log(-1*(0.45-1))))/log(logBase);
	float multiplier = a.range[1]/max;
	int midDiv = DIVISIONS/2;
	for(i=midDiv,x = 0 ; x < 0.5,i<DIVISIONS ; x+=0.01,i++)
	{
		a.rangeDivision[i] = multiplier*((-1*log(-1*(x-1))))/log(logBase);
	}
	for(i=0 ; i<midDiv ; i++)
		a.rangeDivision[midDiv-i] = -1*a.rangeDivision[midDiv+i];
	a.rangeDivision[DIVISIONS] = a.range[1];
	a.rangeDivision[0] = a.range[0];
	// for(i=0 ; i<DIVISIONS ; i++)
	// 	printf("%f\n",a.rangeDivision[i]);
	return a;
}


// create polynomial Division/range creator
struct arrayDivider createPolynomialDivision(struct arrayDivider a, float polynomialEquation[10])
{
	int i,j;
	float max = 0;
	for (j=0;j<10;j++)
	{
		max = max + (polynomialEquation[9-j]*pow(50,9-j));
	}
	float multiplier = a.range[1]/max;
	for(i = 50,j = 0 ; j < 50,i < 100;i++,j++)
	{
		for (int k=0; k < 10 ; k++)
		{
			a.rangeDivision[i] = a.rangeDivision[i] + (polynomialEquation[9-k]*pow(j,9-k));
		}
		a.rangeDivision[i] = multiplier * a.rangeDivision[i];
	}
	for(i = 0 ; i < 50 ; i++)
	{
		a.rangeDivision[50 - i] = -1 * a.rangeDivision[50+i];
	}
	a.rangeDivision[100] = a.range[1];
	a.rangeDivision[0] = a.range[0];
	//for ( i=0;i<100;i++)
	//{
		//printf("%d", a.rangeDivision[i]);
	//}	
	return a;
}

void writeToFile(arrayDivider a)
{
	for(int i=0 ; i<DIVISIONS ; i++)
	{
		char array[100];
		sprintf(array, "%f", a.rangeDivision[i]);
		fprintf(arrayDivisionFile,array);
		if(i != DIVISIONS-1)
			fprintf(arrayDivisionFile,",");
	}
	fprintf(arrayDivisionFile,"\n");
}

int main()
{
	// Initialize all array dividers...
	tpsAD = arrayDivider(DIVISIONS,tpsRange);
	slipAD = arrayDivider(DIVISIONS,slipRange);
	wheelLoadAD = arrayDivider(DIVISIONS,wheelLoadRange);
	radiusAD = arrayDivider(DIVISIONS,radiusRange);
	wheelSpeedAD = arrayDivider(DIVISIONS,wheelSpeedRange);

	// Create array divider divisions and write them to file
	tpsAD = createLinearDivision(tpsAD);
	slipAD = createLogrithmicDivision(slipAD,SLIP_LOGRITHMIC_SCALE);
	wheelLoadAD = createLinearDivision(wheelLoadAD);
	radiusAD = createLinearDivision(radiusAD);
	wheelSpeedAD = createLinearDivision(wheelSpeedAD);

	writeToFile(tpsAD);
	writeToFile(slipAD);
	writeToFile(wheelLoadAD);
	writeToFile(radiusAD);
	writeToFile(wheelSpeedAD);


	arrayDivider b = arrayDividerReader(tpsAD,0);
	for(int i=0 ; i<=DIVISIONS ; i++)
		printf("%f ",b.rangeDivision[i]);
	printf("\n");

	b = arrayDividerReader(slipAD,1);
	for(int i=0 ; i<=DIVISIONS ; i++)
		printf("%f ",b.rangeDivision[i]);
	printf("\n");

	fclose(arrayDivisionFile);
}

