#include <bits/stdc++.h>

int b[243][5];

// TO DO : Convert to recusive or maybe not
void permute(int a[5][3])
{
	int i,j,k,l,m,n=0;
	for(i=0 ; i<3 ; i++)
		for(j=0 ; j<3 ; j++)
			for(k=0 ; k<3 ; k++)
				for(l=0 ; l<3 ; l++)
					for(m=0 ; m<3 ; m++)
					{
						b[n][0] = a[0][i];
						b[n][1] = a[1][j];
						b[n][2] = a[2][k];
						b[n][3] = a[3][l];
						b[n][4] = a[4][m];
						for(int p=0 ; p<5 ; p++)
							printf("%d\t",b[n][p]);
						printf("\n");
						n++;						
					}
}

float getFromMap(int dest[5])
{
	float val = 0;
	for(int i=0 ; i<5 ; i++)
		val += dest[i];
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
	printf("Map : %f\n",getFromMap(dest));
	int calcDiff[5][3] = {0};
	for(i=0 ; i<5 ; i++)
	{
		calcDiff[i][0] = dest[i]-2;
		calcDiff[i][1] = dest[i];
		calcDiff[i][2] = dest[i]+2;
	}
	// for(i=0 ; i<5 ; i++)
	// 	printf("%d %d %d\n",calcDiff[0][i],calcDiff[1][i],calcDiff[2][i]);
	permute(calcDiff);
	// To be used when advanced usage with bigger map and sinosoudal map increment is required
	// float scaleMultiplier[5][2] = {0};
	// for(i=0 ; i<5 ; i++)
	// {
	//  	scaleMultiplier[i][0] = 0.1*(getFromMap(dest) - getFromMap(calcDiff[i][0]));
	//  	scaleMultiplier[i][1] = 0.1*(getFromMap(dest) - getFromMap(calcDiff[i][1]));
	// }
	// Use linear equations as number of points are reduced
	for(i=0 ; i<5 ; i++)
	{
		if(inRange(calcDiff[i][0]))
			lRange[0] = getFromMap(calcDiff[0]);
		// else if(inRange(calcDiff[i][0]-1))
		// 	lRange[i] = getFromMap(calcDiff[i][0]-1);
		else
			lRange[0] = 102;
		if(inRange(calcDiff[i][1]))
			rRange[0] = getFromMap(calcDiff[1]);
		// if(inRange(calcDiff[i][1]-1))
		// 	rRange[i] = getFromMap(calcDiff[i][1]-1);
		else
			rRange[0] = 102;
	}
	float finalIncrease;
	for(i=0 ; i<5 ; i++)
	{
		printf("L : %f\tR : %f\n",lRange[i],rRange[i]);
		float curFinal = lRange[i]<rRange[i]?lRange[i]:rRange[i];
		if(curFinal < finalIncrease)
			finalIncrease = curFinal;
	}
	printf("Final : %f\n",finalIncrease);
	if(increase < finalIncrease)
		finalIncrease = increase;
	return 0;
}

int main()
{
	int dest[5] = {3,4,5,6,7};
	mapModifier5D(dest,3);
}