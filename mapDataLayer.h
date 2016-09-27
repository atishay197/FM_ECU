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

struct arrayDivider
{
	int divisions;
	float range[2];
	float rangeDivision[100];
	arrayDivider(int divisions,float range[2])
	{
		this.divisions = divisions;
		this.range = range;
	}
}

struct arrayDivider createLinearCluster(struct arrayDivider a)
{
	float diff = (a.range[1] -  a.range[0]) / a.divisions;
	for(int i=0  ; i<a.divisions ; i++)
	{
		if(i>0)
			a.rangeDivision[i] = a.rangeDivision[i-1] + diff;
		else
			a.rangeDivision[i] = a.range[0];
	}
	return a;
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
	arrayDivider wheelLoad = arrayDivider(WHEELLOAD_DIVISIONS,wheelLoadRange);
	wheelLoad = createLinearCluster(wheelLoad);
	for(int i=WHEELLOAD_DIVISIONS; i>=0 ; i--)
	{
		printf("%f\n",wheelLoad.rangeDivision[i]);	
		if(load < wheelLoad.rangeDivision[i])
			return i;
	}
	return -1;
}

// logarithmic division
int getTurningRadiusDivision(float turnRadius)
{
	return 4;
}

// divide logarithmically / polynomially
int getWheelSpeedDivision(float wheelSpeed)
{
	return 5;
}
