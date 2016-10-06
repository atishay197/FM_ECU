// All map related calculations and map data transfer

// Everything has 10 divisions now :(
# define TPS_DIVISIONS 10
# define SLIP_DIVISIONS 10
# define SLIP_LOGRITHMIC_SCALE 12
# define WHEELLOAD_DIVISIONS 10
# define RADIUS_DIVISIONS 10
# define WHEELSPEED_DIVISIONS 10
# define DIVISIONS 10
float tpsRange[2] = {0,100};
float slipRange[2] = {-5,5};
float wheelLoadRange[2] = {0,150};
float radiusRange[2] = {0,FLT_MAX};
float wheelSpeedRange[2] = {0,150};

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
	arrayDivider()
	{
		this->divisions = 0;
		this->range[0] = 0;
		this->range[1] = 999;
	}
};


arrayDivider getTPSDivision(float);
arrayDivider getSlipDivision(float);
arrayDivider getWheelLoadDivision(float);
arrayDivider getTurningRadiusDivision(float);
arrayDivider getWheelSpeedDivision(float);

// TO DO file/array input
float getFromMap(int dest[5])
{
	float val = 80;
	for(int i=0 ; i<5 ; i++)
		val -= 0.1*dest[i];
	return val;
}


struct mapData
{
	int dimensions;
	float data[5];
	float finalData;
	mapData(int dim, float da[5],float fData)
	{
		dimensions = dim;
		for(int i=0 ; i<dim ; i++)
			data[i] = da[i];
		finalData = fData;
	}
};


struct arrayValueStruct
{
	struct arrayDivider a[5];
	float values[5];
	int dimensions;
	arrayValueStruct(float TPS, float load, float slip, float turningRadius, float wheelSpeed, int dim)
	{
		dimensions = dim;
		values[0] = TPS;
		a[0] = getTPSDivision(TPS);
		values[1] = load;
		a[1] = getWheelLoadDivision(load);
		values[2] = slip;
		a[2] = getSlipDivision(slip);
		values[3] = turningRadius;
		a[3] = getTurningRadiusDivision(turningRadius);
		values[4] = wheelSpeed;
		a[4] = getWheelSpeedDivision(wheelSpeed);
	}
};


struct mapFetcherStruct
{
	int divisions[5];
	bool fetchLeftRight[5];
	int dimensions;
	mapFetcherStruct(arrayValueStruct a)
	{
		dimensions = a.dimensions;
		for(int i=0 ; i<a.dimensions ; i++)
		{
			this->divisions[i] = a.a[i].divisions;
			int curDiv = a.a[i].curDiv;
			//arbitrary values to give correct division.
			float leftRange=999999,rightRange=999999;
			if(curDiv>=0 && curDiv<10)
				leftRange = a.a[i].rangeDivision[curDiv];
			if((curDiv+1)>=0 && (curDiv+1)<10)
				float rightRange = a.a[i].rangeDivision[curDiv+1];
			float diffLeft = a.values[i] - leftRange;
			float diffRight = a.values[i] - rightRange;
			fetchLeftRight[i] = diffRight>diffLeft?1:0;
		}

	}
};

void printMapFetcherStruct(mapFetcherStruct m)
{
	int i;
	for(i=0 ; i<5 ; i++)
		printf("%d ",m.divisions[i]);
	printf("\n");
	for(i=0 ; i<5 ; i++)
		printf("%d ",m.fetchLeftRight[i]);
	printf("\nDim : %d\n",m.dimensions);
}


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
	int midDiv = DIVISIONS/2;
	for(i=midDiv,x = 0 ; x < 0.5,i<DIVISIONS ; x+=0.01,i++)
	{
		a.rangeDivision[i] = multiplier*((-1*log(-1*(x-1))))/log(logBase);
	}
	for(i=0 ; i<midDiv ; i++)
		a.rangeDivision[midDiv-i] = -1*a.rangeDivision[midDiv+i];
	a.rangeDivision[DIVISIONS] = FLT_MAX;
	a.rangeDivision[0] = -1*FLT_MAX;
	// for(i=0 ; i<DIVISIONS ; i++)
	// 	printf("%f\n",a.rangeDivision[i]);
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
	for(int i=0 ; i<=TPS_DIVISIONS ; i++)
	{
		// printf("T :%f %f\n",TPS,tps.rangeDivision[i]);
		if(TPS > tps.rangeDivision[i] && TPS <= tps.rangeDivision[i+1])
		{
			// printf("Here : %d\n",i);
			tps.curDiv = i;
			return tps;
		}
	}
	tps.curDiv = 0;
	return tps;
}

// Division logrithmically 
arrayDivider getSlipDivision(float slip)
{
	arrayDivider slipDiv = arrayDivider(SLIP_DIVISIONS,slipRange);
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	slipDiv = createLogrithmicDivision(slipDiv,SLIP_LOGRITHMIC_SCALE);
	for(int i=0 ; i<SLIP_DIVISIONS ; i++)
	{
		// printf("%f ",slipDiv.rangeDivision[i]);
		if(slip > slipDiv.rangeDivision[i] && slip <= slipDiv.rangeDivision[i+1])
		{
			slipDiv.curDiv = i;
			// printf("\n");
			return slipDiv;
		}
	}
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
}

mapData getDataFromOuterWheelMap(mapFetcherStruct m)
{
	int divisions[6][5],i,j;
	for(j=0 ; j<m.dimensions ; j++)
		divisions[0][j] = m.divisions[j];
	// printf("seg4\n");
	for(i=1 ; i<m.dimensions+1 ; i++)
	{
		for(j=0 ; j<m.dimensions ; j++)
		{
			// printf("Seg1 %d %d\n",i,j);
			divisions[i][j] = m.divisions[i-1];
			if((i-1) == j)
			{
				if(!m.fetchLeftRight)
					divisions[i][j] -= 1;
				else
					divisions[i][j] += 1;
			}
		}
	}
	float final = getFromMap(divisions[0]);
	float data[5];
	for(i=1 ; i<m.dimensions+1 ; i++)
		data[i] = getFromMap(divisions[i]);
	return mapData(m.dimensions,data,final);
}

mapData getDataFromInnerWheelMap(mapFetcherStruct m)
{
	int divisions[6][5],i,j;
	for(j=0 ; j<m.dimensions ; j++)
		divisions[0][j] = m.divisions[i];
	for(i=1 ; i<m.dimensions+1 ; i++)
	{
		for(j=0 ; j<m.dimensions ; j++)
		{
			divisions[i][j] = m.divisions[i];
			if((i-1) == j)
			{
				if(!m.fetchLeftRight)
					divisions[i][j] -= 1;
				else
					divisions[i][j] += 1;
			}
		}
	}
	float final = getFromMap(divisions[i]);
	float data[5];
	for(i=1 ; i<m.dimensions+1 ; i++)
		data[i] = getFromMap(divisions[i]);
	return mapData(m.dimensions,data,final);
}

float interpolateFromMap(struct mapData m,struct mapFetcherStruct mfs,struct arrayValueStruct avs)
{
	float otherVal,thisVal,diff,diffCur,perOther,finalMapOutput[5],fullOutput=0;
	for(int i=0 ; i<m.dimensions ; i++)
	{
		// printf("div : %d\n",avs.a[i].curDiv);
		otherVal = avs.a[i].rangeDivision[avs.a[i].curDiv];
		// printf("seg3\n");
		thisVal = avs.a[i].rangeDivision[(avs.a[i].curDiv)+1];
		diff = otherVal-thisVal;
		diffCur = otherVal - m.data[i];
		perOther = diffCur/diff;
		finalMapOutput[i] = (perOther)*m.finalData + (1-perOther)*m.finalData;
	}
	for(int i=0 ; i<m.dimensions ; i++)
		fullOutput += finalMapOutput[i];
	return fullOutput/m.dimensions;
}