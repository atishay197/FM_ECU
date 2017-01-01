arrayDivider arrayDividerReader(arrayDivider a, int read)
{
    char buffer[1000];
    int j=0;
    while(fgets(buffer, 1000, arrayDivisionFile) != NULL)
    {
    	if(j == read)
    	{
			for(int i=0 ; i<DIVISIONS ; i++)
				a.rangeDivision[i] = atof(strtok(buffer, ","));
		}
		j++;
	}
	return a;
}

void initializeAllArrayDivider()
{
	tpsAD = arrayDivider(DIVISIONS,tpsRange);
	slipAD = arrayDivider(DIVISIONS,slipRange);
	wheelLoadAD = arrayDivider(DIVISIONS,wheelLoadRange);
	radiusAD = arrayDivider(DIVISIONS,radiusRange);
	wheelSpeedAD = arrayDivider(DIVISIONS,wheelSpeedRange);
	tpsAD = arrayDividerReader(tpsAD,0);
	slipAD = arrayDividerReader(slipAD,1);
	wheelLoadAD = arrayDividerReader(wheelLoadAD,2);
	radiusAD = arrayDividerReader(radiusAD,3);
	wheelSpeedAD = arrayDividerReader(wheelSpeedAD,4);
	return;
}