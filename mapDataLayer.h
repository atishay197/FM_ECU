// All map related calculations and map data transfer

# define TPS_DIVISIONS 10
# define SLIP_DIVISIONS 10
# define SLIP_LOGRITHMIC_SCALE 120
# define WHEELLOAD_DIVISIONS 10
# define RADIUS_DIVISIONS 10
# define WHEELSPEED_DIVISIONS 10
float tpsRange[2] = {0,100};
float slipRange[2] = {-5,5};
float wheelLoadRange[2] = {0,150};
float radiusRange[2] = {0,FLT_MAX};
float wheelSpeedRange[2] = {0,150};

struct mapData
{
	int dimensions;
	float data[5];
	float finalData;
};

struct mapFetcherStruct{
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

struct arrayDivider createLinearDivision(struct arrayDivider a)
{
	float diff = (a.range[1] -  a.range[0]) / a.divisions;
	for(int i=0  ; i<a.divisions ; i++)
	{
		if(i>0)
			a.rangeDivision[i] = a.rangeDivision[i-1] + diff;
		else
			a.rangeDivision[i] = a.range[0];
	}
	a.rangeDivision[a.divisions] = a.range[1];
	return a;
} 

// create logrithmic Division/range creator
struct arrayDivider createLogrithmicDivision(struct arrayDivider a,float logBase)
{
	float x;int i;
	float max = ((-1*log(-1*(0.49-1))))/log(logBase);
	float multiplier = a.range[1]/max;
	for(i=50,x = 0 ; x < 0.5,i<100 ; x+=0.01,i++)
	{
		a.rangeDivision[i] = multiplier*((-1*log(-1*(x-1))))/log(logBase);
		// printf("%f\n",x);
	}
	for(i=0 ; i<50 ; i++)
		a.rangeDivision[50-i] = -1*a.rangeDivision[50+i];
	a.rangeDivision[100] = FLT_MAX;
	a.rangeDivision[0] = -1*FLT_MAX;
	return a;
}


// create polynomial Division/range creator
struct arrayDivider createPolynomialDivision(struct arrayDivider a, float polynomialEquation[10])
{
	return a;
}

// Division logrithmically / polynomially
arrayDivider getTPSDivision(float TPS)
{
	arrayDivider tps = arrayDivider(TPS_DIVISIONS,tpsRange);
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	tps = createLinearDivision(tps);
	for(int i=0 ; i<TPS_DIVISIONS ; i++)
	{
		if(TPS > tps.rangeDivision[i] && TPS <= tps.rangeDivision[i+1])
		{
			tps.curDiv = i;
			return tps;
		}
	}
	return NULL;
}

// Division logrithmically 
arrayDivider getSlipDivision(float slip)
{
	arrayDivider slipDiv = arrayDivider(SLIP_DIVISIONS,slipRange);
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	slipDiv = createLogrithmicDivision(slipDiv,SLIP_LOGRITHMIC_SCALE);
	for(int i=0 ; i<SLIP_DIVISIONS ; i++)
	{
		if(slip > slipDiv.rangeDivision[i] && slip <= slipDiv.rangeDivision[i+1])
		{
			slipDiv.curDiv = i;
			return slipDiv;
		}
	}
	return NULL;
}

// Division linear - divisions of 15kgs each
arrayDivider getWheelLoadDivision(float load)
{
	arrayDivider wheelLoad = arrayDivider(WHEELLOAD_DIVISIONS,wheelLoadRange);
	// DO NOT initialize evertime, initialize in the beginning og torqueVectoring();
	wheelLoad = createLinearDivision(wheelLoad);
	// for(int i=WHEELLOAD_DIVISIONS; i>=0 ; i--)
	// 	printf("%f, ",wheelLoad.rangeDivision[i]);
	// printf("\n");
	for(int i=0 ; i<WHEELLOAD_DIVISIONS ; i++)
	{
		if(load > wheelLoad.rangeDivision[i] && load <= wheelLoad.rangeDivision[i+1])
		{
			wheelLoad.curDiv = i;
			return wheelLoad;
		}
	}
	return NULL;
}

// logarithmic division
arrayDivider getTurningRadiusDivision(float turnRadius)
{
	arrayDivider radius = arrayDivider(RADIUS_DIVISIONS,radiusRange);
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	radius = createLinearDivision(radius);
	for(int i=0 ; i<RADIUS_DIVISIONS ; i++)
	{
		if(turnRadius > radius.rangeDivision[i] && turnRadius <= radius.rangeDivision[i+1])
		{
			radius.curDiv = i;
			return radius;
		}
	}
	return NULL;
}

// TO DO Divide polynomially not linearly
// divide polynomially
arrayDivider getWheelSpeedDivision(float wheelSpeed)
{
	arrayDivider speed = arrayDivider(WHEELSPEED_DIVISIONS,wheelSpeedRange);
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	speed = createLinearDivision(speed);
	for(int i=0 ; i<WHEELSPEED_DIVISIONS ; i++)
	{
		if(wheelSpeed > speed.rangeDivision[i] && wheelSpeed <= speed.rangeDivision[i+1])
		{
			speed.curDiv = i;
			return speed;
		}
	}
	return NULL;
}

float interpolateFromMap(struct mapData m,struct mapFetcherStruct mfs,struct arrayDivider a[4],int dimensions)
{
	float otherVal,thisVal,diff,diffCur,perOther,finalMapOutput[5],fullOutput=0;
	for(int i=0 ; i<dimensions ; i++)
	{
		otherVal = a[i].rangeDivision[curDiv];
		thisVal = a[i].rangeDivision[curDiv+1];
		diff = otherVal-thisVal;
		diffCur = otherVal - mfs.data[i];
		perOther = diffCur/diff;
		finalMapOutput[i] = (perOther)*mapData.finalMapOutput + (1-perOther)*mapData.finalMapOutput;
	}
	for(int i=0 ; i<dimensions ; i++)
		fullOutput += finalMapOutput[i];
	return fullOutput;
}