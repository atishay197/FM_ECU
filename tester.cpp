#include <bits/stdc++.h>
using namespace std;

# define SLIP_DIVISIONS 100
float slipRange[2] = {-5,5};

struct arrayDivider
{
	int divisions;
	float range[2];
	float rangeDivision[101];
	arrayDivider(int divisions,float range[2])
	{
		this->divisions = divisions;
		this->range[0] = range[0];
		this->range[1] = range[1];
	}
};

// create logrithmic Division/range creator
struct arrayDivider createLogrithmicDivision(struct arrayDivider a,float logBase)
{
	float x;int i;
	float max = ((-1*log(-1*(0.49-1))))/log(logBase);
	float multiplier = a.range[1]/max;
	for(i=50,x = 0 ; x < 0.5,i<100 ; x+=0.01,i++)
	{
		a.rangeDivision[i] = multiplier*((-1*log(-1*(x-1))))/log(logBase);
		printf("%f\n",x);
	}
	for(i=0 ; i<50 ; i++)
		a.rangeDivision[50-i] = -1*a.rangeDivision[50+i];
	a.rangeDivision[100] = FLT_MAX;
	a.rangeDivision[0] = -1*FLT_MAX;
	return a;
}

int main()
{
	arrayDivider slip = arrayDivider(SLIP_DIVISIONS,slipRange);
	slip = createLogrithmicDivision(slip,120);
	for(int i=0 ; i<101 ; i++)
	{
		printf("%f\n",slip.rangeDivision[i]);
	}
	printf("MAX = %f",FLT_MAX);

	// for(int i=0 ; i<100 ; i++)
	// {
	// 	float k = i/2;
	// }
}
