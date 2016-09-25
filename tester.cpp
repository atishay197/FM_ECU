#include <bits/stdc++.h>


bool inRange(float value1, float value2 , float percentage)
{
	float maxval2 = value2 * 0.01 * (100 + percentage);
	float minval2 = value2 * 0.01 * (100 - percentage);
	if(value1 <= minval2 || value1 >= maxval2)
		return false;
	return true;
}

float bringInRange(float value1, float value2, float percentage)
{
	return value1>value2?value2*(100+percentage)*0.01:value2*(100-percentage)*0.01;
}

int main()
{
	float x = 100;
	float y = 109;
	float z = 112;
	float a = 91;
	float b = 80;
	printf("inRange : %d\n",inRange(y,x,10)?1:0);
	printf("inRange : %d\n",inRange(z,x,10)?1:0);
	printf("inRange : %d\n",inRange(a,x,10)?1:0);
	printf("inRange : %d\n",inRange(b,x,10)?1:0);
	printf("bringInRange : %f\n",bringInRange(y,x,10));
	printf("bringInRange : %f\n",bringInRange(z,x,10));
	printf("bringInRange : %f\n",bringInRange(a,x,10));
	printf("bringInRange : %f\n",bringInRange(b,x,10));
}
