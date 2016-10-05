#include <bits/stdc++.h>

float getFromMap(int dest[5])
{
	float val = 0;
	for(int i=0 ; i<5 ; i++)
		val += i;
	return val;
}

bool inRange(int x)
{
	if(x < 0 || x > 9)
		return false;
	return true;
}

float mapModifier5D(int dest[5],float increase)
{
	int i;
	float calcDiff[5][2] = {0};
	for(i=0 ; i<5 ; i++)
	{
		calcDiff[i][0] = dest[i] - 2;
		calcDiff[i][1] = dest[i] + 2;
	}
	for(i=0 ; i<5 ; i++)
		printf("%f %f\n",calcDiff[i][0],calcDiff[i][1]);
	float scaleMultiplier[5][2] = {0};
	// To be used when advanced usage with bigger map and sinosoudal map increment is required
	// for(i=0 ; i<5 ; i++)
	// {
	//  	scaleMultiplier[i][0] = 0.1*(getFromMap(dest) - getFromMap(calcDiff[i][0]));
	//  	scaleMultiplier[i][1] = 0.1*(getFromMap(dest) - getFromMap(calcDiff[i][1]));
	// }
	// Use linear equations as number of points are reduced
	// if(inRange((dest[i] + mapfield[i]),i))
	float lRange[5],rRange[5];
	for(i=0 ; i<5 ; i++)
	{
		lRange[i] = getFromMap(calcDiff[i][0]);
		rRange[i] = getFromMap(calcDiff[i][1]);
	}
	
	return 0;
}

int main()
{
	int dest[5] = {5,5,5,5,5};
	mapModifier5D(dest,3);
}