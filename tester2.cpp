#include <bits/stdc++.h>

float getFromMap(int dest[5])
{
	float val = 0;
	for(int i=0 ; i<5 ; i++)
		val += i;
	return val;
}

bool inRange(int x,int i)
{
	if(x < 0)
		return false;
	if(i == 0 && x > 99)
		return false;
	if(i != 0 && x > 9)
		return false;
	return true;
}

float mapModifier5D(int dest[5],float increase)
{
	int mapfield[5] = {8,2,2,2,2},i;
	float calcDiff[5][2] = {0};
	for(i=0 ; i<5 ; i++)
	{
		if(inRange((dest[i]-mapfield[i]),i))
			calcDiff[i][0] = dest[i]-mapfield[i];
		if(inRange((dest[i] + mapfield[i]),i))
			calcDiff[i][1] = dest[i] + mapfield[i];
	}
	for(i=0 ; i<5 ; i++)
		printf("%f %f\n",calcDiff[i][0],calcDiff[i][1]);
	return 0;
}

int main()
{
	int dest[5] = {50,5,5,5,5};
	mapModifier5D(dest,3);
}