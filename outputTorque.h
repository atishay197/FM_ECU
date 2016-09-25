struct OutputTorque
{
	float torqueRL;
	float torqueRR;
};
typedef struct OutputTorque outputTorque;

void printoutput(outputTorque* o)
{
	printf("Output Torque :: RL : %f :: RR : %f\n",o->torqueRL,o->torqueRL);
}

outputTorque* writeAndReturn(outputTorque* output,FILE* outfile)
{
	fprintf(outfile,"%f,%f\n",output->torqueRL,output->torqueRR);
	return output;
}
