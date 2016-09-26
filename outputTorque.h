struct OutputTorque
{
	float RL;
	float RR;
};
typedef struct OutputTorque outputTorque;

void printoutput(outputTorque* o)
{
	//printf("Output Torque :: RL : %f :: RR : %f\n",o->RL,o->RR);
	return;
}

outputTorque* writeAndReturn(outputTorque* output,FILE* outfile)
{
	fprintf(outfile,"%f,%f\n",output->RL,output->RR);
	return output;
}
