// All map related calculations and map data transfer

# define TPS_DIVISIONS 100
# define SLIP_DIVISIONS 100
# define WHEELLOAD_DIVISIONS 10
# define RADIUS_DIVISIONS 10
# define WHEELSPEED_DIVISIONS 10
float tpsRange[2] = {0,100};
float slipRange[2] = {-5,5};
float wheelLoadRange[2] = {0,150};
float radiusRange[2] = {0,FLT_MAX};
float wheelSpeedRange[2] = {0,150};

float* createLinearCluster(int divNo, float Range[2])
{
	float *finalDiv;
	float diff = (Range[1] -  Range[0]) / divNo;
	for(int i=0  ; i<WHEELLOAD_DIVISIONS ; i++)
	{
		if(i>0)
			finalDiv[i] = finalDiv[i-1] + diff;
		else
			finalDiv[i] = Range[0];
	}
	return finalDiv;
} 


// cluster logrithmically / polynomially
int getTPSDivision(float TPS)
{
	return 1;
}

// cluster logrithmically 
int getSlipDivision(float slip)
{
	return 2;
}

// cluster linear - divisions of 15kgs each
int getWheelLoadDivision(float load)
{
	float* a;
	a = createLinearCluster(WHEELLOAD_DIVISIONS,wheelLoadRange);
	for(int i=WHEELLOAD_DIVISIONS; i>=0 ; i--)
	{
		if(load < a[i])
			return i;
	}
	return -1;
}

// logarithmic division
int getTurningRaduisDivision(float turnRadius)
{
	return 4;
}

// divide logarithmically / polynomially
int getWheelSpeedDivision(float wheelSpeed)
{
	return 5;
}
