struct WheelSpeed
{
	float FL;
	float FR;
	float RL;
	float RR;
};
struct GForce
{
	float longitudnal;
	float lateral;
	float vertical;
};
struct BrakePressure
{
	int front;
	int rear;
};
struct Throttle
{
	float TPS1;
	float TPS2;
};
struct Suspot
{
	float FL;
	float FR;
	float RL;
	float RR;
};	
struct LoggedData
{
	bool exists;						// true/false
	float currentTime; 					// s
	int distance;						// m
	struct BrakePressure brakePressure;	// kPa
	float drivespeed;					// km/h
	struct WheelSpeed wheelSpeed;		// km/h
	struct GForce gForce;				// G
	float gyroYawVelocity;				// deg/s
	float steeredAngle;					// deg
	struct Throttle throttle;			// %
	struct Suspot susPot;				//mm
	
	//Copy Constructor
	LoggedData(LoggedData* prev)
	{
		this->exists = prev->exists;
		this->currentTime = prev->currentTime;
		this->distance = prev->distance;
		this->brakePressure = prev->brakePressure;
		this->drivespeed = prev->drivespeed;
		this->wheelSpeed = prev->wheelSpeed;
		this->gForce = prev->gForce;
		this->gyroYawVelocity = prev->gyroYawVelocity;
		this->steeredAngle = prev->steeredAngle;
		this->throttle = prev->throttle;
		this->susPot = prev->susPot;
	}
	
	//Default Constructor
	LoggedData()
	{
		this->exists = 0;
		this->currentTime = 0.0;
		this->distance = 0;
		this->brakePressure.front = 0;
		this->brakePressure.rear = 0;
		this->drivespeed = 0.0;
		this->wheelSpeed.FL = 0.0;
		this->wheelSpeed.FR = 0.0;
		this->wheelSpeed.RL = 0.0;
		this->wheelSpeed.RR = 0.0;
		this->gForce.longitudnal = 0.0;
		this->gForce.lateral = 0.0;
		this->gForce.vertical = 0.0;
		this->gyroYawVelocity = 0.0;
		this->steeredAngle = 0.0;
		this->throttle.TPS1 = 0.0;
		this->throttle.TPS2 = 0.0;
		this->susPot.FL = 0.0;
		this->susPot.FR = 0.0;
		this->susPot.RL = 0.0;
		this->susPot.RR = 0.0;
	}
};
typedef struct LoggedData loggedData;

void printData(loggedData* r)
{
	printf("Exists : ");
	r->exists?printf("True\n"):printf("False\n");
	printf("Time : %f :: Distance : %d DriveSpeed : %f\n",r->currentTime,r->distance,r->drivespeed);
	printf("Brake Pressure :: Front : %d :: Rear : %d\n",r->brakePressure.front,r->brakePressure.rear);
	printf("Wheel Speed :: FR : %f :: FL : %f :: RR : %f :: RL : %f\n",r->wheelSpeed.FR,r->wheelSpeed.FL,r->wheelSpeed.RR,r->wheelSpeed.RL);
	printf("GForce :: Longitudnal : %f :: Lateral : %f :: Vertical : %f\n",r->gForce.longitudnal,r->gForce.lateral,r->gForce.vertical);
	printf("Gyro Yaw :: %f\n",r->gyroYawVelocity);
	printf("Steered Angle :: %f\n",r->steeredAngle);
	printf("Throttle :: TPS1 : %f :: TPS2 : %f\n",r->throttle.TPS1,r->throttle.TPS2);
	return;
}
