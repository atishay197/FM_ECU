// All map related calculations and map data transfer

// Everything has 10 divisions now :(
# define SLIP_LOGRITHMIC_SCALE 12
# define DIVISIONS 10
// Ranges for sensor values for division detection from map
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
		this->range[1] = 0;
	}
};


arrayDivider getTPSDivision(float,arrayDivider);
arrayDivider getSlipDivision(float,arrayDivider);
arrayDivider getWheelLoadDivision(float,arrayDivider);
arrayDivider getTurningRadiusDivision(float,arrayDivider);
arrayDivider getWheelSpeedDivision(float,arrayDivider);

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
	arrayValueStruct(float TPS, float load, float slip, float turningRadius, float wheelSpeed, int dim, struct arrayDivider b[5])
	{
		dimensions = dim;
		values[0] = TPS;
		a[0] = getTPSDivision(TPS,b[0]);
		values[1] = load;
		a[1] = getWheelLoadDivision(load,b[1]);
		values[2] = slip;
		a[2] = getSlipDivision(slip,b[2]);
		values[3] = turningRadius;
		a[3] = getTurningRadiusDivision(turningRadius,b[3]);
		values[4] = wheelSpeed;
		a[4] = getWheelSpeedDivision(wheelSpeed,b[4]);
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
			this->divisions[i] = a.a[i].curDiv;
			int curDiv = a.a[i].curDiv;
			//arbitrary values to give correct division.
			float leftRange=999999,rightRange=999999;
			if(curDiv>=0 && curDiv<10)
				leftRange = a.a[i].rangeDivision[curDiv];
			if((curDiv+1)>=0 && (curDiv+1)<10)
				rightRange = a.a[i].rangeDivision[curDiv+1];
			float diffLeft = abs(a.values[i] - leftRange);
			float diffRight = abs(a.values[i] - rightRange);
			fetchLeftRight[i] = diffRight>diffLeft?1:0;
			// printf("%d %f %f %d\n",i,diffLeft,diffRight,fetchLeftRight[i]);
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
	printf("\n");
	printf("Dim : %d\n",m.dimensions);
}


// Division logrithmically / polynomially
arrayDivider getTPSDivision(float TPS, arrayDivider tps)
{
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	// arrayDivider tps = arrayDivider(TPS_DIVISIONS,tpsRange);
	// tps = createLinearDivision(tps);
	for(int i=0 ; i<=DIVISIONS ; i++)
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
	// arrayDivider tpsDiv = arrayDivider(TPS_DIVISIONS,tpsRange);
	// FILE *polynomial_file  = fopen("polynomialTPS.txt", "r"); //open polynomialTPS file having editable weights
	// float polynomial[10];
	// fscanf(polynomial_file, "%f %f %f %f %f %f %f %f %f %f", &polynomial[0], &polynomial[1], &polynomial[2], &polynomial[3], &polynomial[4], &polynomial[5], &polynomial[6], &polynomial[7], &polynomial[8], &polynomial[9]); 
	// fclose(polynomial_file);
	// tpsDiv = createPolynomialDivision(tpsDiv,polynomial);
	// /*
	// for(int i=0;i<TPS_DIVISIONS;i++)
	// {
		
	// 	tpsDiv.rangeDivision[i] += tpsRange[1]; 
	// 	printf("%f ", tpsDiv.rangeDivision[i]);
		
	// }
	// */
	// for(int i = 0 ; i<TPS_DIVISIONS+1 ; i++)
	// {
	// 	if (TPS> tpsDiv.rangeDivision[i] && TPS<=tpsDiv.rangeDivision[i+1])
	// 		return i;
	// }
	// return 1;
}

// Division logrithmically 
arrayDivider getSlipDivision(float slip, arrayDivider slipDiv)
{
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	// arrayDivider slipDiv = arrayDivider(SLIP_DIVISIONS,slipRange);
	// slipDiv = createLogrithmicDivision(slipDiv,SLIP_LOGRITHMIC_SCALE);
	for(int i=0 ; i<DIVISIONS ; i++)
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
arrayDivider getWheelLoadDivision(float load, arrayDivider wheelLoad)
{
	// DO NOT initialize evertime, initialize in the beginning og torqueVectoring();
	// arrayDivider wheelLoad = arrayDivider(WHEELLOAD_DIVISIONS,wheelLoadRange);
	// wheelLoad = createLinearDivision(wheelLoad);
	// for(int i=WHEELLOAD_DIVISIONS; i>=0 ; i--)
	// 	printf("%f, ",wheelLoad.rangeDivision[i]);
	// printf("\n");
	for(int i=0 ; i<DIVISIONS+1 ; i++)
	{
		if(load > wheelLoad.rangeDivision[i] && load <= wheelLoad.rangeDivision[i+1])
		{
			wheelLoad.curDiv = i;
			return wheelLoad;
		}
	}
}

// logarithmic division
arrayDivider getTurningRadiusDivision(float turnRadius, arrayDivider radius)
{
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	// arrayDivider radius = arrayDivider(RADIUS_DIVISIONS,radiusRange);
	// radius = createLinearDivision(radius);
	for(int i=0 ; i<DIVISIONS ; i++)
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
arrayDivider getWheelSpeedDivision(float wheelSpeed, arrayDivider speed)
{
	// DO NOT initialize evertime, initialize in the beginning of torqueVectoring();
	// arrayDivider speed = arrayDivider(WHEELSPEED_DIVISIONS,wheelSpeedRange);
	// speed = createLinearDivision(speed);
	for(int i=0 ; i<DIVISIONS ; i++)
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
	for(i=1 ; i<m.dimensions+1 ; i++)
	{
		for(j=0 ; j<m.dimensions ; j++)
		{
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
	// TO DO replace get from map by respective Maps
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
	// TO DO replace get from map by respective Maps
	float final = getFromMap(divisions[0]);
	float data[5];
	for(i=1 ; i<m.dimensions+1 ; i++)
		data[i] = getFromMap(divisions[i]);
	return mapData(m.dimensions,data,final);
}

float interpolateFromMap(struct mapData m,struct mapFetcherStruct mfs,struct arrayValueStruct avs)
{
	float otherVal=-99999,thisVal=99999,diff,diffCur,perOther,finalMapOutput[5],fullOutput=0;
	for(int i=0 ; i<m.dimensions ; i++)
	{
		// printf("div : %d\n",avs.a[i].curDiv);
		if((avs.a[i].curDiv)+1>-1)
			otherVal = avs.a[i].rangeDivision[(avs.a[i].curDiv)-1];
		// printf("seg3\n");
		if((avs.a[i].curDiv)+1<11)
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