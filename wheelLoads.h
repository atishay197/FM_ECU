struct WheelLoad
{
	float FL;	// kgs
	float FR;	// kgs
	float RL;	// kgs
	float RR;	// kgs
};
typedef struct WheelLoad wheelLoad;

void printWheelLoad(wheelLoad* w)
{
	printf("Wheel Loads :: FL : %f :: FR %f :: RL : %f :: RR : %f\n",w->FL,w->FR,w->RL,w->RR);
}

void writeWheelLoad(wheelLoad* w, FILE* wout)
{
	fprintf(wout,"%f,%f,%f,%f\n",w->FL,w->FR,w->RL,w->RR);
}