int numbers = 0, nums[100];

int slipCluster(int slip)
{
  int k = 10;
  int kvals[25], prevKvals[25], steps = 1, addition[25][100], count = 0, groups[25][100];
  int retval, min, groupnum, value, sum, ok = 1, curval = numbers%100;
  nums[numbers%100] = slip;
  numbers++;
  // set values of Centers
  for(int i = 0; i < 3; i++)
  {
    kvals[i] = nums[i];
  }
  //while(steps < 10)
  while(ok == 1)
  {
    //make calculations (C - bla bla bla)
    for(int i = 0; i < k; i++)
    {
      for(int j = 0; j < numbers; j++)
      {
        addition[i][j] = abs(kvals[i] - nums[j]);
      }
    }
    //make groups of number(C)
    for(int i = 0; i < numbers; i++)
    {
      min = 100000;
      for(int j = 0; j < k; j++)
      {
        if(addition[j][i] < min)
        {
          min = addition[j][i];
          value = nums[i];
          groupnum = j;
          if(i == curval)
            retval = groupnum;
        }
      }
      groups[groupnum][i] = value;
    }
    for(int i = 0; i < k; i++)
    {
      sum = 0;
      count = 0;
      for(int j = 0; j < numbers; j++)
      {
        if(groups[i][j] != 0)
        {
         sum += groups[i][j];
         count++;
        }
      }
      prevKvals[i] = kvals[i];
      kvals[i] = sum/count;
    }

    //make empty array of groups
    for(int i = 0; i < 25; i++)
    {
      for(int j = 0; j < 100; j++)
      {
        groups[i][j] = 0;
      }
    }
    //check condition of termination
    ok = 0;
    for(int i = 0; i < k; i++)
    {
      if(prevKvals[i] != kvals[i])
      {
        ok = 1;
      }
    }
    steps++;
  }
  return retval;
}