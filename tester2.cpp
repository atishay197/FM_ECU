#include <bits/stdc++.h>

struct mapWriter
{
	float b[243][6];
	int total;
};

void printMapWriter(mapWriter m)
{
	int i,j;
	for(i=0 ; i<m.total ; i++)
	{
		for(j=0 ; j<6 ; j++)
			printf("%f ",m.b[i][j]);
		printf("\n");
	}
}

// TO DO : Convert to recusive or maybe not
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

mapWriter filterMapWriter(mapWriter m)
{
	m.total = 0;
	int i,j,k=0;
	bool correctValues[243] = {0};
	for(i=0 ; i<243 ; i++)
	{
		if(inRange(m.b[i]))
		{
			correctValues[i] = 1;
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
	for(i=0 ; i<242 ; i++)
		for(j=0 ; j<5 ; j++)
			m.b[i][j] = 10;
	m = permute(calcDiff,1,m);
	for(i=0 ; i<5 ; i++)
		m.b[242][i] = dest[i];
	m.b[242][5] = increase;
	for(i=0 ; i<242 ; i++)
		m.b[i][5] *= increase;
	m = filterMapWriter(m);
	printMapWriter(m);
	return m;
}

float findincreaseLimit5D(float dest[5],float increase, mapWriter m)
{
	int i,j;
	// printf("Map : %f\n",getFromMap(dest));
	int calcDiff[5][3] = {0};
	for(i=0 ; i<5 ; i++)
	{
		calcDiff[i][0] = dest[i]-2;
		calcDiff[i][1] = dest[i];
		calcDiff[i][2] = dest[i]+2;
	}
	for(i=0 ; i<242 ; i++)
		for(j=0 ; j<242 ; j++)
			m.b[i][j] = 10;
	// for(i=0 ; i<5 ; i++)
	// 	printf("%d %d %d\n",calcDiff[0][i],calcDiff[1][i],calcDiff[2][i]);
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
			if(range<finalMax)
				finalMax = range;
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
	float dest[5] = {0,0,0,0,1};
	float increase = -34;
	mapWriter m;
	increase = findincreaseLimit5D(dest,increase,m);
	m = mapincementer5D(dest,increase,m);
}