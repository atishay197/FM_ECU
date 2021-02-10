
#include "calculationModule.h"
/*
	Reduce a value to its percentage%.
*/
float decreaseBy(float value, float percentage)
{
	return value*percentage/100;
}

/* 
	Check if value1 is within +/- percentage of value 2
*/
bool inRange(float value1, float value2 , float percentage)
{
	float maxval2 = value2 * 0.01 * (100 + percentage);
	float minval2 = value2 * 0.01 * (100 - percentage);
	// if value less than ninimum permitted value
	// or
	// greater than maximum possible value
	// then return false
	if(value1 <= minval2 || value1 >= maxval2)
		return false;
	return true;
}

/* 
	Bring value 1 within some percantage of value 2 
*/
float bringInRange(float value1, float value2, float percentage)
{
	// Eg: percentage = 5
	// if 1st value is greater than second value
	// return ((100 + 5)/100)*value2 = 1.05*value2
	// else if second is greater than 1st
	// return ((100-5)/100)*value2 = 0.95*value2
	if(!inRange(value1,value2,percentage))
		return value1>value2?value2*(100+percentage)*0.01:value2*(100-percentage)*0.01;
}

/*
	Calculate turning radious given the steeredAngle
*/
float calculateTurningRadius(float steeredAngle,float wheelbase)
{
	float turnRadius;
	if (steeredAngle != 0)
		turnRadius = (wheelbase/tan((3.1415*steeredAngle)/180));  
	//tan function from math.h, will give negative radius for left turn
	else if (steeredAngle == 0)
		turnRadius = 99999;
	// printf("%f \n",turnRadius);	
	return turnRadius;
}
