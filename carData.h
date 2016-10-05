struct CGData
{
	float x;
	float y;
	float z;
};

struct Camber
{
	float front;
	float rear;
};

struct Track
{
	float front;
	float rear;
};

struct TirePressure
{
	float front;
	float rear;
};

struct Suspension
{
	float dampingCoeff;					//random data entered in cardata.csv. change when necessary. Also, each wheel's damper has its own damping coeff
	float springConstant;				//random data entered in cardata.csv. change when necessary
	float pRodAngle;					//Push/Pull rod angle with the vertical in degrees. Random data entered in cardata.csv. change when necessary
};

struct CarData
{
	float carWeight;					// kgs
	float driverWeight;					// kgs
	struct CGData cg;					// mm
	float wheelbase;					// mm
	struct Track track;					// mm
	float wheelDiameter;				// mm
	struct TirePressure tirePressure;	// psi
	struct Camber camber;				// degrees
	float frontDistribution;			// fraction : (%/100)
	struct Suspension suspension;
};
typedef struct CarData carData;

void printCarData(carData* c)
{
	float total = c->carWeight + c->driverWeight;
	float fweight = total * c->frontDistribution;
	float rweight = total - fweight;
	printf("Car Data:\nCar Weight : %f , Driver Weight : %f, Total : %f\n",c->carWeight,c->driverWeight,total);
	printf("CG :: X : %f :: Y : %f :: Z : %f\n",c->cg.x,c->cg.y,c->cg.z);
	printf("Wheelbase : %f :: Track:: Front: %f :: Rear : %f\n",c->wheelbase,c->track.front,c->track.rear);
	printf("Wheel Dia : %f :: TirePressure : F : %f : R : %f\n",c->wheelDiameter,c->tirePressure.front,c->tirePressure.rear);
	printf("Camber : F : %f R : %f\n",c->camber.front,c->camber.rear);
	printf("Front: %f :: Rear: %f :: Weight :: F : %f : R : %f\n",c->frontDistribution,(1 - c->frontDistribution),fweight,rweight);
	return;
}
