#include <bits/stdc++.h>
using namespace std;

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

struct mapKey
{
	int a,b,c,d,e;
	mapKey(int a,int b,int c,int d,int e)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
	}	
};

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
	float f1[20][20][20][10][10] = {1};
	float f2[20][20][20][10][10] = {1};
	// float f3[20][20][20][10][10] = {1};
	// float f4[20][20][20][10][10] = {1};
	// float f5[20][20][20][10][10] = {1};
	// float f6[20][20][20][10][10] = {1};
	// float f7[20][20][20][10][10] = {1};
	// float f8[20][20][20][10][10] = {1};
	// float f9[20][20][20][10][10] = {1};
	// float f0[20][20][20][10][10] = {1}; // gives segmentation fault
	printf("f : %d\n",sizeof(f1));
	// map<mapKey,float> outerWheelMap;
	// mapKey m = mapKey(1,2,3,4,5);
	// outerWheelMap.insert(pair<mapKey,float>(m,1));

}
