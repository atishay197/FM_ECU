#include <bits/stdc++.h>

struct mapData
{
	int dimensions;
	float data[5];
	float finalData;
};

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
};

struct mapFetcherStruct
{
	int divisions[5];
	bool fetchLeftRight[5];
	mapFetcherStruct (int divisions[5], float values[5], float leftRange[5],float rightRange[5])
	{
		for(int i=0 ; i<5 ; i++)
		{
			this->divisions[i] = divisions[i];
			float diffLeft = values[i] - leftRange[i];
			float diffRight = values[i] - rightRange[i];
			fetchLeftRight[i] = diffRight>diffLeft?1:0;
		}

	}
};


float interpolateFromMap(struct mapData m,struct mapFetcherStruct mfs,struct arrayDivider a[5],int dimensions)
{
	float otherVal,thisVal,diff,diffCur,perOther,finalMapOutput[5],fullOutput=0;
	// for(int i=0 ; i<dimensions ; i++)
	// {
	// 	otherVal = a[i].rangeDivision[curDiv];
	// 	thisVal = a[i].rangeDivision[curDiv+1];
	// 	diff = otherVal-thisVal;
	// 	diffCur = otherVal - mfs.data[i];
	// 	perOther = diffCur/diff;
	// 	finalMapOutput[i] = (perOther)*mapData.finalMapOutput + (1-perOther)*mapData.finalMapOutput;
	// }
	for(int i=0 ; i<dimensions ; i++)
		fullOutput += finalMapOutput[i];
	return fullOutput;
}

int calculateDataPoints(int dimensions)
{
	return pow(dimensions,3)-1;
}

int main()
{
	int divisions[5] = {4,5,6,4,5};
	float values[5] = {};
	float a[10][10][10][10][10] = {0};
	float b[10][10][10][10][10] = {0};
	float c[10][10][10][10] = {0};
}
