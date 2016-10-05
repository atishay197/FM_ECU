// All map related calculations and map data transfer

# define TPS_DIVISIONS 100
# define SLIP_DIVISIONS 100
# define SLIP_LOGRITHMIC_SCALE 120
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
	float rangeDivision[101];
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
	int i,j;
	float max = 0;
	for (j=0;j<10;j++)
	{
		max = max + (polynomialEquation[9-j]*pow(50,9-j));
	}
	float multiplier = a.range[1]/max;
	for(i = 50,j = 0 ; j < 50,i < 100;i++,j++)
	{
		for (int k=0; k < 10 ; k++)
		{
			a.rangeDivision[i] = a.rangeDivision[i] + (polynomialEquation[9-k]*pow(j,9-k));
		}
		a.rangeDivision[i] = multiplier * a.rangeDivision[i];
	}
	for(i = 0 ; i < 50 ; i++)
	{
		a.rangeDivision[50 - i] = -1 * a.rangeDivision[50+i];
	}
	a.rangeDivision[100] = a.range[1];
	a.rangeDivision[0] = a.range[0];
	//for ( i=0;i<100;i++)
	//{
		//printf("%d", a.rangeDivision[i]);
	//}
	
	
	return a;
}

// Division logrithmically / polynomially
int getTPSDivision(float TPS)
{
	arrayDivider tpsDiv = arrayDivider(TPS_DIVISIONS,tpsRange);
	FILE *polynomial_file  = fopen("polynomialTPS.txt", "r"); //open polynomialTPS file having editable weights
	float polynomial[10];
	fscanf(polynomial_file, "%f %f %f %f %f %f %f %f %f %f", &polynomial[0], &polynomial[1], &polynomial[2], &polynomial[3], &polynomial[4], &polynomial[5], &polynomial[6], &polynomial[7], &polynomial[8], &polynomial[9]); 
	fclose(polynomial_file);
	tpsDiv = createPolynomialDivision(tpsDiv,polynomial);
	/*
	for(int i=0;i<TPS_DIVISIONS;i++)
	{
		
		tpsDiv.rangeDivision[i] += tpsRange[1]; 
		printf("%f ", tpsDiv.rangeDivision[i]);
		
	}
	*/
	for(int i = 0 ; i<TPS_DIVISIONS+1 ; i++)
	{
		if (TPS> tpsDiv.rangeDivision[i] && TPS<=tpsDiv.rangeDivision[i+1])
			return i;
	}
	return 1;
}

// Division logrithmically 
int getSlipDivision(float slip)
{
	arrayDivider slipDiv = arrayDivider(SLIP_DIVISIONS,slipRange);
	// DO NOT initialize evertime, initialize in the beginning og torqueVectoring();
	slipDiv = createLogrithmicDivision(slipDiv,SLIP_LOGRITHMIC_SCALE);
	for(int i=0 ; i<SLIP_DIVISIONS ; i++)
	{
		if(slip > slipDiv.rangeDivision[i] && slip <= slipDiv.rangeDivision[i+1])
			return i;
	}
}

// Division linear - divisions of 15kgs each
int getWheelLoadDivision(float load)
{
	arrayDivider wheelLoad = arrayDivider(WHEELLOAD_DIVISIONS,wheelLoadRange);
	// DO NOT initialize evertime, initialize in the beginning og torqueVectoring();
	wheelLoad = createLinearDivision(wheelLoad);
	// for(int i=WHEELLOAD_DIVISIONS; i>=0 ; i--)
	// 	printf("%f, ",wheelLoad.rangeDivision[i]);
	// printf("\n");
	for(int i=0 ; i<WHEELLOAD_DIVISIONS+1 ; i++)
	{
		if(load > wheelLoad.rangeDivision[i] && load <= wheelLoad.rangeDivision[i+1])
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
