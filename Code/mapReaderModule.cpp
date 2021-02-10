#include "mapReaderModule.h"

/*
	Parameterized constructor to initialize arrayDividers with number of 
	division (since it was to be a variable before, but now it's 10 for 
	all dimension) and range of values.	
*/
arrayDivider::arrayDivider(int divisions, float range[2])
{
	this->divisions = divisions;
	this->range[0] = range[0];
	this->range[1] = range[1];
}

/*
	Default constructor to initialize arrayDividers.
*/
arrayDivider::arrayDivider()
{
	this->divisions = 0;
	this->range[0] = 0;
	this->range[1] = 0;
}

/*
	Setters for members of arrayDivider.
*/
void arrayDivider::setArrayDivider_divisions(int num)
{
	divisions = num;
}

void arrayDivider::setArrayDivider_curDiv(int num)
{
	curDiv = num;
}

void arrayDivider::setArrayDivider_range(float r[2])
{
	range[0] = r[0];
	range[1] = r[1];
}

void arrayDivider::setArrayDivider_rangeDivision(float rd[11])
{
	for(int i = 0; i < 11; i++)
	{
		rangeDivision[i] = rd[i];	
	}
}

/*
	Getters for members of arrayDivider.
*/
int arrayDivider::getArrayDivider_divisions()
{
	return divisions;
}

int arrayDivider::getArrayDivider_curDiv()
{
	return curDiv;
}

void arrayDivider::getArrayDivider_range(float rg[2])
{
	for(int i = 0; i < 2; i++)
	{
		rg[i] = range[i];
	}	
}

void arrayDivider::getArrayDivider_rangeDivision(float rd[11])
{
	for(int i = 0; i < 11; i++)
	{
		rd[i] = rangeDivision[i];
	}
}


/*
	To get index for the dimension TPS	
*/
arrayDivider arrayDivider::getTPSDivision(float TPS, arrayDivider tps)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (TPS > tps.rangeDivision[i] && TPS <= tps.rangeDivision[i+1])
		{
			tps.curDiv = i;
			return tps;
		}
	}
	tps.curDiv = 0;
	return tps ;
}
/*
void arrayDivider::getTPSDivision(float TPS)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (TPS > rangeDivision[i] && TPS <= rangeDivision[i+1])
		{
			curDiv = i;
			return;			
		}
	}
}
*/
/*
	To get index for the dimension slip	
*/
arrayDivider arrayDivider::getSlipDivision(float slip, arrayDivider slipDiv)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (slip > slipDiv.rangeDivision[i] && slip <= slipDiv.rangeDivision[i+1])
		{
			slipDiv.curDiv = i;
			return slipDiv;
		}
	}
	return slipDiv;
}
/*
void arrayDivider::getSlipDivision(float slip)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (slip > rangeDivision[i] && slip <= rangeDivision[i+1])
		{
			curDiv = i;
			return;			
		}
	}
}
*/
/*
	To get index for the dimension wheel load	
*/
arrayDivider arrayDivider::getWheelLoadDivision(float load, arrayDivider wheelLoad)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (load > wheelLoad.rangeDivision[i] && load <= wheelLoad.rangeDivision[i+1])
		{
			wheelLoad.curDiv = i;
			return wheelLoad;
		}
	}
	return wheelLoad;
}
/*
void arrayDivider::getWheelLoadDivision(float load)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (load > rangeDivision[i] && load <= rangeDivision[i+1])
		{
			curDiv = i;
			return;
		}
	}
}
*/

/*
	To get index for the dimension Turning radius	
*/
arrayDivider arrayDivider::getTurningRadiusDivision(float turnRadius, arrayDivider radius)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (turnRadius > radius.rangeDivision[i] && turnRadius <= radius.rangeDivision[i+1])
		{
			radius.curDiv = i;
			return radius;
		}
	}
	radius.curDiv = 0;
	return radius;
}
/*
void arrayDivider::getTurningRadiusDivision(float turnRadius)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (turnRadius > rangeDivision[i] && turnRadius <= rangeDivision[i+1])
		{
			curDiv = i;
			return;
		}
	}
}
*/
/*
	To get index for the dimension wheel speed	
*/
arrayDivider arrayDivider::getWheelSpeedDivision(float wheelSpeed, arrayDivider wheels)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (wheelSpeed > wheels.rangeDivision[i] && wheelSpeed <= wheels.rangeDivision[i+1])
		{
			curDiv = i;
			return wheels;
		}
	}
	curDiv = 0;
	return wheels;
}
/*
arrayDivider arrayDivider::getWheelSpeedDivision(float wheelSpeed)
{
	for(int i = 0; i <= DIVISIONS; i++)
	{
		if (wheelSpeed > rangeDivision[i] && wheelSpeed <= rangeDivision[i+1])
		{
			curDiv = i;
			return;
		}
	}
}
*/

/*
	Reads the array divisions from the file.
*/
void arrayDivider::arrayDividerReader(int read, FILE* arrayDivisionFile)
{
    char buffer[1000];
    int j=0;				//Acts as a label to select which line to read. 
    						//0: TPS	1: slip		2: wheelLoad	3: turnRadius	4: wheelSpeed
    
    //Read Array Divisions. DIVISIONS = 10
    while(fgets(buffer, 1000, arrayDivisionFile) != NULL)		
    {
    	if(j == read)				
    	{
			for(int i=0 ; i<DIVISIONS ; i++)
				rangeDivision[i] = atof(strtok(buffer, ","));
		}
		j++;						
	}
}

/*
	Parameterized Constructor
*/
mapData::mapData(int dim, float da[5], float fData)
{
	dimensions = dim;
	for(int i = 0; i < dim; i++)
	{
		data[i] = da[i];
	}
	finalData = fData;
}

/*
	Getters for mapData members.
*/
int mapData::getMapData_dimensions()
{
	return dimensions;
}

void mapData::getMapData_data(float arr[5])
{
	for(int i = 0; i < 5; i++)
	{
		arr[i] = data[i];
	}
}

float mapData::getMapData_finalData()
{
	return finalData;
}

/*
	Setters for mapData members
*/
void mapData::setMapData_dimensions(int dim)
{
	dimensions = dim;
}

void mapData::setMapData_data(float arr[5])
{
	for(int i = 0; i < 5; i++)
	{
		data[i] = arr[i];
	}
}
void mapData::setmapData_finalData(float fData)
{
	finalData = fData;
}

/*
	Parameterized Constructor
*/
arrayValueStruct::arrayValueStruct(float TPS, float load, float slip, float turningRadius, float wheelSpeed, int dim, struct arrayDivider b[5])
{
	dimensions = dim;
	values[0] = TPS;
	a[0] = a[0].getTPSDivision(TPS,b[0]);
	values[1] = load;
	a[1] = a[1].getWheelLoadDivision(load,b[1]);
	values[2] = slip;
	a[2] = a[2].getSlipDivision(slip,b[2]);
	values[3] = turningRadius;
	a[3] = a[3].getTurningRadiusDivision(turningRadius,b[3]);
	values[4] = wheelSpeed;
	a[4] = a[4].getWheelSpeedDivision(wheelSpeed,b[4]);
}

/*
	Setters for arrayValueStruct
*/
void arrayValueStruct::setArrayValueStruct_a(arrayDivider b[5])
{
	for(int i = 0; i < 5; i++)
	{
		a[i].divisions = b[i].divisions;
		a[i].curDiv = b[i].curDiv;
		for(int j = 0; j < 2; j++)
		{
			a[i].range[j] = b[i].range[j];
		}
		for(int j = 0; j < 11; j++)
		{
			a[i].rangeDivision[j] = b[i].rangeDivision[j];
		}
	}
}

void arrayValueStruct::setArrayValueStruct_values(float values[5])
{
	for(int i = 0; i < 5; i++)
	{
		this->values[i] = values[i];
	}
}

void arrayValueStruct::setArrayValueStruct_dimensions(int dimensions)
{
	this->dimensions = dimensions;
}

/*
	Getters for arrayValueStruct
*/
void arrayValueStruct::getArrayValueStruct_a(arrayDivider b[5])
{
	for(int i = 0; i < 5; i++)
	{
		b[i].divisions = a[i].divisions;
		b[i].curDiv = a[i].curDiv;
		for(int j = 0; j < 2; j++)
		{
			b[i].range[j] = a[i].range[j];
		}
		for(int j = 0; j < 11; j++)
		{
			b[i].rangeDivision[j] = a[i].rangeDivision[j];
		}
	}
}

void arrayValueStruct::getArrayValueStruct_values(float values[5])
{
	for(int i = 0; i < 5; i++)
	{
		values[i] = this->values[i];
	}
}

int arrayValueStruct::getArrayValueStruct_dimensions()
{
	return dimensions;
}



/*
	Parameterized Constructor to determine left division to take
	or right
*/
mapFetcherStruct::mapFetcherStruct(arrayValueStruct a)
{
	dimensions = a.getArrayValueStruct_dimensions();
	arrayDivider b[5];
	a.getArrayValueStruct_a(b);
	float values[5];
	a.getArrayValueStruct_values(values);
	
	for(int i = 0; i < dimensions; i++)
	{
		float rangeDivision[11];
		b[i].getArrayDivider_rangeDivision(rangeDivision);
		this->divisions[i] = b[i].getArrayDivider_curDiv();
		int curDiv = b[i].getArrayDivider_curDiv();
		float leftRange=999999,rightRange=999999;
		if(curDiv>=0 && curDiv<10)
			leftRange = rangeDivision[curDiv];
		if((curDiv+1)>=0 && (curDiv+1)<10)
			rightRange = rangeDivision[curDiv+1];
		float diffLeft = abs(values[i] - leftRange);
		float diffRight = abs(values[i] - rightRange);
		fetchLeftRight[i] = diffRight>diffLeft?1:0;
	}
}

/*
	Prints the members of the class.
*/
void mapFetcherStruct::printMapFetcherStruct()
{
	int i;
	for(i = 0; i < 5; i++)
		printf("%d", divisions[i]);
	printf("\n");
	for(i = 0; i < 5; i++)
		printf("%d", fetchLeftRight[i]);
	printf("\n");
	printf("Dim : %d\n",dimensions);
}

/*
	Getters for mapFetcherStruct.
*/
void mapFetcherStruct::getMapFetcherStruct_divisions(int divisions[5])
{
	for(int i = 0; i < 5; i++)
	{
		divisions[i] = this->divisions[i];
	}
}

void mapFetcherStruct::getMapFetcherStruct_fetchLeftRight(bool fetchLeftRight[5])
{
	for(int i = 0; i < 5; i++)
	{
		fetchLeftRight[i] = this->fetchLeftRight[i];
	}
}

int mapFetcherStruct::getMapFetcherStruct_dimensions()
{
	return dimensions;
}
			
/*
	Setters for mapFetcherStruct.
*/
void mapFetcherStruct::setMapFetcherStruct_divisions(int divisions[5])
{
	for(int i = 0; i < 5; i++)
	{
		this->divisions[i] = divisions[i];
	}
}

void mapFetcherStruct::setMapFetcherStruct_fetchLeftRight(bool fetchLeftRight[5])
{
	for(int i = 0; i < 5; i++)
	{
		this->fetchLeftRight[i] = fetchLeftRight[i];
	}
}
void mapFetcherStruct::setMapFetcherStruct_dimensions(int dimensions)
{
	this->dimensions = dimensions;
}

/*
	Fetch data from the file
*/
float getFromOuterMap(int dest[5], float map[10][10])
{
	int value = 571;		//This value is based on increments of file pointer
							//found using ftell when reading and printing
	fseek(outerWheelMap, (dest[0]*100 + dest[1]*10 + dest[2])*value, SEEK_SET);
	int i = 0;
	char buffer[1000];
	while ( i < 10 )
	{
		fgets(buffer, 1000, outerWheelMap);
		for(int j = 0; j < 10; j++)
		{
			if( j == 0)
				map[i][j] = atof(strtok(buffer, ","));
			else
				map[i][j] = atof(strtok(NULL, ","));
		}
		i++;
	}
	return map[dest[3]][dest[4]];
}

/*
	Fetch data from the file
*/
float getFromInnerMap(int dest[5], float map[10][10])
{
	int value = 571;		//This value is based on increments of file pointer
							//found using ftell when reading and printing
	//printf("%d\n", dest[0]);
	fseek(innerWheelMap, (dest[0]*100 + dest[1]*10 + dest[2])*value, SEEK_SET);
	int i = 0;
	char buffer[1000];
	//printf("%s\n", buffer);
	while ( i < 10 )
	{
		fgets(buffer, 1000, innerWheelMap);
		for(int j = 0; j < 10; j++)
		{
			if( j == 0)
				map[i][j] = atof(strtok(buffer, ","));
			else
				map[i][j] = atof(strtok(NULL, ","));
		}
		i++;
	}
	return map[dest[3]][dest[4]];
}

/*
	Get the actual value and other 5 values for interpolation
	from the map
*/
mapData getDataFromOuterWheelMap(mapFetcherStruct m)
{
	int divisions[6][5],i,j;
	int div[5];
	m.getMapFetcherStruct_divisions(div);
	for(j=0 ; j<m.getMapFetcherStruct_dimensions() ; j++)
		divisions[0][j] = div[j];
	bool fetchLeftRight[5];
	m.getMapFetcherStruct_fetchLeftRight(fetchLeftRight);
	for(i=1 ; i<m.getMapFetcherStruct_dimensions()+1 ; i++)
	{
		for(j=0 ; j<m.getMapFetcherStruct_dimensions() ; j++)
		{
			divisions[i][j] = div[i-1];
			if((i-1) == j)
			{
				if(!fetchLeftRight[i-1])
					divisions[i][j] -= 1;
				else
					divisions[i][j] += 1;
			}
		}
	}
	
	float map[10][10];
	float final = getFromOuterMap(divisions[0], map);
	float data[5];
	for(i=1 ; i<m.getMapFetcherStruct_dimensions()+1 ; i++)
		data[i] = getFromOuterMap(divisions[i], map);
	return mapData(m.getMapFetcherStruct_dimensions(),data,final);
}

/*
	Get the actual value and other 5 values for interpolation
	from the map
*/
mapData getDataFromInnerWheelMap(mapFetcherStruct m)
{
	// First read "fetchLeftRightExplanation" <- search for term....
	// divisions[6][5] is the 6 map values that will be fetched from the 5D map.
	// divisions[0] represents the actual map value that is required.
	// divisions[1-5] represents the 5 values that are fetched only for interpolation purposes
	// divisions[x][5] is 5 dimensional because the map is 5D so 5 indexes correspond to 1 value
	int divisions[6][5],i,j;
	int div[5];
	m.getMapFetcherStruct_divisions(div);
	for(j=0 ; j<m.getMapFetcherStruct_dimensions() ; j++)
		divisions[0][j] = div[j];
	bool fetchLeftRight[5];
	m.getMapFetcherStruct_fetchLeftRight(fetchLeftRight);
	// orignal division values stored in divisions[0]
	for(i=1 ; i<m.getMapFetcherStruct_dimensions()+1 ; i++)
	{
		for(j=0 ; j<m.getMapFetcherStruct_dimensions() ; j++)
		{
			// printf("Seg1 %d %d\n",i,j);
			// divisions[1-5] are being filled
			// it is first set equal to the actual indexes of the map value to be fetched
			divisions[i][j] = div[i-1];
			// value of 1 index per dimension is changed for interpolation values
			if((i-1) == j)
			{
				// change index value of dimension if left or right fetching has to be done
				if(!fetchLeftRight[i-1])
					divisions[i][j] -= 1;
				else
					divisions[i][j] += 1;
			}
		}
	}
	float map[10][10];
	float final = getFromInnerMap(divisions[0], map);
	float data[5];
	for(i=1 ; i<m.getMapFetcherStruct_dimensions()+1 ; i++)
		data[i-1] = getFromInnerMap(divisions[i], map);
	return mapData(m.getMapFetcherStruct_dimensions(),data,final);
}

float interpolateFromMap(mapData m, mapFetcherStruct mfs, arrayValueStruct avs, FILE* )
{
	float leftVal=-99999,rightVal=99999,diff,diffCur,perLeft,finalMapOutput[5],fullOutput=0;
	arrayDivider a[5];
	avs.getArrayValueStruct_a(a);
	float data[5];
	m.getMapData_data(data);
	for(int i = 0; i < m.getMapData_dimensions(); i++)
	{ 
		float rangeDivision[11];
		a[i].getArrayDivider_rangeDivision(rangeDivision);
		// printf("div : %d\n",avs.a[i].curDiv);
		// check if division value is valid
		if((a[i].getArrayDivider_curDiv())+1>-1)
		{
			// find left boundary value of division
			leftVal = rangeDivision[a[i].getArrayDivider_curDiv()-1];
		}
		if((a[i].getArrayDivider_curDiv())+1<11)
		{
			// find right boundary value of division
			rightVal = rangeDivision[a[i].getArrayDivider_curDiv()+1];
		}
		// difference between  and right division values for denominator
		diff = leftVal-rightVal;
		// difference between  and right division values for numerator
		diffCur = leftVal - data[i];
		// find what fraction the left value should be multiplied with
		// based on the distance from it's boundary
		perLeft = diffCur/diff;
		// final = leftfraction * actual value + rightfraction * actual value
		finalMapOutput[i] = (perLeft)*m.getMapData_finalData() + (1-perLeft)*m.getMapData_finalData();
	}
	// average out all the interpolation data...
	for(int i=0 ; i<m.getMapData_dimensions() ; i++)
		fullOutput += finalMapOutput[i];
	return fullOutput/m.getMapData_dimensions();
}

	

/*
	Gets the arrayDivisions from a file into the objects of class arrayDivider
*/
void initializeAllArrayDivider()
{
	/*
		The following calls assign the respective ranges to the objects
		declared globally.
	*/
	tpsAD = arrayDivider(DIVISIONS,tpsRange);				
	slipAD = arrayDivider(DIVISIONS,slipRange);				
	wheelLoadAD = arrayDivider(DIVISIONS,wheelLoadRange);	
	radiusAD = arrayDivider(DIVISIONS,radiusRange);			
	wheelSpeedAD = arrayDivider(DIVISIONS,wheelSpeedRange);	
	
	tpsAD.arrayDividerReader(0, arrayDivisionFile);					
	slipAD.arrayDividerReader(1, arrayDivisionFile);					
	wheelLoadAD.arrayDividerReader(2, arrayDivisionFile);		
	radiusAD.arrayDividerReader(3, arrayDivisionFile);				
	wheelSpeedAD.arrayDividerReader(4, arrayDivisionFile);		
}


