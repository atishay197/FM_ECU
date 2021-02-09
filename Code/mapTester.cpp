#include <bits/stdc++.h>
using namespace std;

struct mapWriter
{
	float b[243][6];
	int total;
};

int writeToMap(float percentage)
{
	char writeVal[5];
	writeVal[2] = '.';
	if(percentage < 0)
		percentage = 0;
	if(percentage > 99.99)
	{
		for(int i=0 ; i<5 ; i++)
			if(i != 2)
				writeVal[i] = '9';
	}
	else
	{
		if(percentage<10)
		{
			writeVal[0] = '0';
		}
		else
		{
			writeVal[0] = (char)(((int)(percentage/10)%10)) + '0'; 
		}
		writeVal[1] = (char)(((int)percentage%10)) + '0';
		writeVal[3] = (char)(((int)(percentage*10)%10)) + '0';
		writeVal[4] = (char)(((int)(percentage*100)%10)) + '0';
	}
	printf("%f : %s\n",percentage,writeVal);
}

void printMapWriter(mapWriter m)
{
	int i,j;
	for(i=0 ; i<m.total ; i++)
	{
		for(j=0 ; j<6 ; j++)
			writeToMap(m.b[i][j]);
		printf("\n");
	}
}


// TO DO : Convert to recusive or maybe not
// a is the indexes that have to be fetched for comparison
mapWriter permute(int a[5][3], bool increaserMode, mapWriter mw)
{
	int i,j,k,l,m,n=0;
	for(i=0 ; i<3 ; i++)
		for(j=0 ; j<3 ; j++)
			for(k=0 ; k<3 ; k++)
				for(l=0 ; l<3 ; l++)
					for(m=0 ; m<3 ; m++)
					{
						if(i==1 && j==1 && k==1 && l==1 && m==1)
							continue;
						mw.b[n][0] = a[0][i];
						mw.b[n][1] = a[1][j];
						mw.b[n][2] = a[2][k];
						mw.b[n][3] = a[3][l];
						mw.b[n][4] = a[4][m];
						mw.b[n][5] = 1;
						// for(int p=0 ; p<5 ; p++)
						// 	printf("%d\t",b[n][p]);
						// printf("\n");
						if(increaserMode)
						{
							if(i != 1)
								mw.b[n][5] /= 2;
							if(j != 1)
								mw.b[n][5] /= 2;
							if(k != 1)
								mw.b[n][5] /= 2;
							if(l != 1)
								mw.b[n][5] /= 2;
							if(m != 1)
								mw.b[n][5] /= 2;
						}
						n++;						
					}
	return mw;
}

float getFromMap(float dest[5])
{
	float val = 80;
	for(int i=0 ; i<5 ; i++)
		val -= 0.1*dest[i];
	return val;
}

bool inRange(float x[5])
{
	for(int i=0 ; i<5 ; i++)
		if(x[i] < 0 || x[i] > 9)
			return false;
	return true;
}

/**
	Filters out the index values which are out of range
	While calculations in the previous steps, no write operations were performed.
	But after this some write operations are performed in the array
	if we write to a[9][0][0][0][0] it is ok, but if we do the same to a[9][0][0][0][0].
	It might trhow out an illegalAccess exception. Filtering prevents writing to those indexes.
**/
mapWriter filterMapWriter(mapWriter m)
{
	m.total = 0;
	int i,j,k=0;
	// Determine which indexes are correct using an array of flags...
	bool correctValues[243] = {0};
	for(i=0 ; i<243 ; i++)
	{
		if(inRange(m.b[i]))
		{
			correctValues[i] = 1;
			// Increment m.total so that the writer know the exact amount of indexes to write.
			m.total++;
		}
	}
	for(i=0 ; i<243 ; i++)
	{
		if(correctValues[i])
		{
			for(j=0 ; j<6 ; j++)
			{
				m.b[k][j] = m.b[i][j];
			}
			k++;
		}
	}
	return m;
}

mapWriter mapincementer5D(float dest[5],float increase, mapWriter m)
{
	int i,j;
	int calcDiff[5][3] = {0};
	for(i=0 ; i<5 ; i++)
	{
		calcDiff[i][0] = dest[i]-1;
		calcDiff[i][1] = dest[i];
		calcDiff[i][2] = dest[i]+1;
	}
	for(i=0 ; i<243 ; i++)
		for(j=0 ; j<5 ; j++)
			m.b[i][j] = 10;
	m = permute(calcDiff,1,m);
	for(i=0 ; i<5 ; i++)
		m.b[242][i] = dest[i];
	m.b[242][5] = increase;
	for(i=0 ; i<242 ; i++)
		m.b[i][5] *= increase;
	m = filterMapWriter(m);
	// printMapWriter(m);
	return m;
}

/** 
	Function to find the increase limit in the map. 
	A value in the map cannot be increased to whatever we like
 	To ensure smooth transition hapens between states and adjacent values in the map,
 	values are compared to adjacent cells and only a percentage of that increase or decrease
 	in change is allowed.
**/ 
float findincreaseLimit5D(float dest[5],float increase, mapWriter m)
{
	int i,j;
	// printf("Map : %f\n",getFromMap(dest));
	// array for calculating different indexes from where map values are fetched
	int calcDiff[5][3] = {0};
	// find all indexes for map value comparison for finding change value
	for(i=0 ; i<5 ; i++)
	{
		calcDiff[i][0] = dest[i]-2;
		calcDiff[i][1] = dest[i];
		calcDiff[i][2] = dest[i]+2;
	}
	for(i=0 ; i<243 ; i++)
		for(j=0 ; j<6 ; j++)
			m.b[i][j] = 10;
	// for(i=0 ; i<5 ; i++)
		// printf("%d %d %d\n",calcDiff[0][i],calcDiff[1][i],calcDiff[2][i]);
	m = permute(calcDiff,0,m);
	bool mode = increase>0?1:0;
	float finalMax = 101, finalMin = -1;
	float curMapValue = getFromMap(dest);
	float increaseedValue = curMapValue + increase;
	for(i=0 ; i<242 ; i++)
	{
		if(inRange(m.b[i]))
		{
			float range = getFromMap(m.b[i]);
			// find the maximum value that is present in it's surroundings
			if(range<finalMax)
				finalMax = range;
			// find the miniimum value that is present in it's surroundings
			if(range>finalMin)
				finalMin = range;
		}
	}
	printf("Cur : %f\tMax : %f\tMin : %f\n",curMapValue,finalMax,finalMin);
	float percentageInRange = 0.05; // TO DO 5% is arbitrary vary value of you want to 
	finalMax *= 1+percentageInRange ;
	finalMin /= 1+percentageInRange ;
	if(finalMin < 0)
		finalMin = 0;
	if(finalMax > 99.99)
		finalMax = 99.99;
	printf("Inc : %f\tMax : %f\tMin : %f\n", increaseedValue,finalMax,finalMin);
	if(!(increaseedValue < finalMax && increaseedValue > finalMin))
		if(mode)
			increase = finalMax - curMapValue;
		else
			increase = finalMin - curMapValue;
	printf("Final : %f\n",increase);
	return increase;
}

int main()
{
	float dest[5] = {0,1,2,3,9};
	float increase = -34;
	mapWriter m;
	increase = findincreaseLimit5D(dest,increase,m);
	m = mapincementer5D(dest,increase,m);

	printf("\n\n");
	for(float i=0; i<102; i+=0.1)
		writeToMap(i);
}
