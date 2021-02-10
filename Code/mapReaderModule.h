#include <stdlib.h>
#include <stdio.h>
#include <string.h>
# define SLIP_LOGRITHMIC_SCALE 12
# define DIVISIONS 10

// TO-DO Use some other opening mode for the maps 
FILE* outerWheelMap = fopen("../Build/Input/OuterWheelTorqueMap.csv", "r");
FILE* innerWheelMap = fopen("../Build/Input/InnerWheelTorqueMap.csv", "r");
FILE* arrayDivisionFile = fopen("../Build/Input/arrayDivider.csv","r");

/*
	Ranges for sensor values for division detection from map
*/
float tpsRange[2] = {0,100};
float slipRange[2] = {-5,5};
float wheelLoadRange[2] = {0,150};
float radiusRange[2] = {0,200};
float wheelSpeedRange[2] = {0,150};

/*
	To get division values and current division to act as 
	index for map.
*/
class arrayDivider
{
	public:
			int divisions;
			int curDiv;
			float range[2];
			float rangeDivision[11];
	public:
			arrayDivider(int, float*);
			arrayDivider();
			
			void setArrayDivider_divisions(int);
			void setArrayDivider_curDiv(int);
			void setArrayDivider_range(float*);
			void setArrayDivider_rangeDivision(float*);
			
			int getArrayDivider_divisions();
			int getArrayDivider_curDiv();
			void getArrayDivider_range(float*);
			void getArrayDivider_rangeDivision(float*);
			
			
			arrayDivider getTPSDivision(float, arrayDivider);
			arrayDivider getSlipDivision(float, arrayDivider);
			arrayDivider getWheelLoadDivision(float, arrayDivider);
			arrayDivider getTurningRadiusDivision(float, arrayDivider);
			arrayDivider getWheelSpeedDivision(float, arrayDivider);
			/*
			void getTPSDivision(float);
			void getSlipDivision(float);
			void getWheelLoadDivision(float);
			void getTurningRadiusDivision(float);
			void getWheelSpeedDivision(float);			
			*/
			void arrayDividerReader(int, FILE*);
};

/*
	Holds the values read from the map
*/
class mapData
{
	private:
			int dimensions;
			float data[5];
			float finalData;
	public:
			int getMapData_dimensions();
			void getMapData_data(float*);
			float getMapData_finalData();
			
			void setMapData_dimensions(int);
			void setMapData_data(float*);
			void setmapData_finalData(float);
			
			mapData(int, float*, float);
};

/*
	Gets all division values in one go.
*/
class arrayValueStruct
{
	private:
			arrayDivider a[5];
			float values[5];
			int dimensions;
	public:
			void getArrayValueStruct_a(arrayDivider*);
			void getArrayValueStruct_values(float*);
			int getArrayValueStruct_dimensions();
			
			void setArrayValueStruct_a(arrayDivider*);
			void setArrayValueStruct_values(float*);
			void setArrayValueStruct_dimensions(int);
			
			arrayValueStruct(float, float, float, float, float, int, arrayDivider*);
};

class mapFetcherStruct
{
	private:
			/*
				The divisions according to current value
			*/
			int divisions[5];
			
			/*
				To determine if closer to right division or left, for
				interpolation.
			*/
			bool fetchLeftRight[5];
			int dimensions;
	public:
			void getMapFetcherStruct_divisions(int*);
			void getMapFetcherStruct_fetchLeftRight(bool*);
			int getMapFetcherStruct_dimensions();
			
			void setMapFetcherStruct_divisions(int*);
			void setMapFetcherStruct_fetchLeftRight(bool*);
			void setMapFetcherStruct_dimensions(int);
			
			
			mapFetcherStruct(arrayValueStruct);
			void printMapFetcherStruct();
};

float interpolateFromMap(mapData, mapFetcherStruct, arrayValueStruct);
mapData getDataFromInnerWheelMap(mapFetcherStruct);
mapData getDataFromOuterWheelMap(mapFetcherStruct);
float getFromOuterMap(int*, float**);
float getFromInnerMap(int*, float**);

// Constructor will be called to assign zeros to divisions, and ranges.
extern arrayDivider tpsAD;						
extern arrayDivider slipAD;					
extern arrayDivider wheelLoadAD;				
extern arrayDivider radiusAD;					
extern arrayDivider wheelSpeedAD;

void initializeAllArrayDivider();

	
	
