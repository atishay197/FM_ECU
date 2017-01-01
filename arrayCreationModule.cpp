#include <bits/stdc++.h>

FILE* outp = fopen("arrayDivider.csv","w");
# define SLIP_LOGRITHMIC_SCALE 12
# define DIVISIONS 10
float tpsRange[2] = {0,100};
float slipRange[2] = {-5,5};
float wheelLoadRange[2] = {0,150};
float radiusRange[2] = {0,FLT_MAX};
float wheelSpeedRange[2] = {0,150};

struct arrayDivider
{	
	int divisions;
	int curDiv;
	float range[2];
	float rangeDivision[11];
	arrayDivider(int divisions,float range[2])
	{
		this->divisions = divisions;
		this->range[0] = range[0];
		this->range[1] = range[1];
	}
	arrayDivider()
	{
		this->divisions = 0;
		this->range[0] = 0;
		this->range[1] = 0;
	}
};

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
	float max = ((-1*log(-1*(0.49-1))))/log(logBase);
	float multiplier = a.range[1]/max;
	int midDiv = DIVISIONS/2;
	for(i=midDiv,x = 0 ; x < 0.5,i<DIVISIONS ; x+=0.01,i++)
	{
		a.rangeDivision[i] = multiplier*((-1*log(-1*(x-1))))/log(logBase);
	}
	for(i=0 ; i<midDiv ; i++)
		a.rangeDivision[midDiv-i] = -1*a.rangeDivision[midDiv+i];
	a.rangeDivision[DIVISIONS] = FLT_MAX;
	a.rangeDivision[0] = -1*FLT_MAX;
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
		fprintf(outp,a.rangeDivision[i]);
		fprintf(outp,",");
	}
	fprintf(outp,"\n");
}

int main()
{
	// Initialize all array dividers...
	arrayDivider tps = arrayDivider(DIVISIONS,tpsRange);
	arrayDivider slip = arrayDivider(DIVISIONS,slipRange);
	arrayDivider wheelLoad = arrayDivider(DIVISIONS,wheelLoadRange);
	arrayDivider radius = arrayDivider(DIVISIONS,radiusRange);
	arrayDivider wheelSpeed = arrayDivider(DIVISIONS,wheelSpeedRange);

	// Create array divider divisions and write them to file
	tps = createLinearDivision(tps);
	slip = createLogrithmicDivision(slip);
	wheelLoad = createLinearDivision(wheelLoad);
	radius = createLinearDivision(radius);
	wheelSpeed = createLinearDivision(wheelSpeed);

	writeToFile(tps);

	fclose(outp);
}

