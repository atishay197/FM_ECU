#include "mapInitializerModule.h"

/*
	
*/
int mapInitializer::calculateDataPoints(int dimensions)
{
	return pow(dimensions, 3) - 1;
}

/*
	Converts float value to string.
*/
char* mapInitializer::returnMapValue(float percentage, char writeValue[5])
{
	writeValue[2] = '.';
	if(percentage < 0)
		percentage = 0;
	if(percentage > 99.99)
	{
		for(int i=0 ; i<5 ; i++)
			if(i != 2)
				writeValue[i] = '9';
	}
	else
	{
		if(percentage<10)
		{
			writeValue[0] = '0';
		}
		else
		{
			writeValue[0] = (char)(((int)(percentage/10)%10)) + '0'; 
		}
		writeValue[1] = (char)(((int)percentage%10)) + '0';
		writeValue[3] = (char)(((int)(percentage*10)%10)) + '0';
		writeValue[4] = (char)(((int)(percentage*100)%10)) + '0';
	}
	return writeValue;
}

/*
	Creates dummy map. Each 10x10 array is the same. only used in testers
*/
void mapInitializer::createOuterWheelMap(FILE* outerWheelMap)
{
	float v[10][10];
	float k = 0.00;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			v[i][j] = k;
			k = k + 1.02;
		}
	}
	for(int z = 0; z < 1000; z++)
	{
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				char a[5];
				fprintf(outerWheelMap, "%s,", returnMapValue(v[i][j], a));
			}
			fprintf(outerWheelMap, "\n");
		}
	}
}

/*
	Creates dummy map. Each 10x10 array is the same. Only used in testers
*/
void mapInitializer::createInnerWheelMap(FILE* innerWheelMap)
{
	float v[10][10];
	float k = 0.00;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			v[i][j] = k;
			k = k + 1.01;
		}
	}
	for(int z = 0; z < 1000; z++)
	{	
		for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				char a[5];
				fprintf(innerWheelMap, "%s,", returnMapValue(v[i][j], a));
			}
			fprintf(innerWheelMap, "\n");
		}	
	}
}
/*
-------------------------END-------------------------
*/
