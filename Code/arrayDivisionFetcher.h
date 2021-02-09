arrayDivider arrayDividerReader(arrayDivider a, int read)
{
    char buffer[1000];
    int j=0;				//Acts as a label to select which line to read. 
    						//0: TPS	1: slip		2: wheelLoad	3: turnRadius	4: wheelSpeed
    
    //Read Array Divisions. DIVISIONS = 10
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
	tpsAD = arrayDivider(DIVISIONS,tpsRange);				//Assign TPS range
	slipAD = arrayDivider(DIVISIONS,slipRange);				//Assign slip range
	wheelLoadAD = arrayDivider(DIVISIONS,wheelLoadRange);	//Assign wheelLoad range
	radiusAD = arrayDivider(DIVISIONS,radiusRange);			//Assign turnRadius range
	wheelSpeedAD = arrayDivider(DIVISIONS,wheelSpeedRange);	//Assign wheelSpeed range
	
	tpsAD = arrayDividerReader(tpsAD,0);					//Assign TPS divisions from arrayDivisionFile
	slipAD = arrayDividerReader(slipAD,1);					//Assign slip divisions from arrayDivisionFile
	wheelLoadAD = arrayDividerReader(wheelLoadAD,2);		//Assign wheelLoad divisions from arrayDivisionFile
	radiusAD = arrayDividerReader(radiusAD,3);				//Assign divisions from arrayDivisionFile
	wheelSpeedAD = arrayDividerReader(wheelSpeedAD,4);		//Assign divisions from arrayDivisionFile
	
	return;
}
