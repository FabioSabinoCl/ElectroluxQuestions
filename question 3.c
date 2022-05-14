
void ManyReturns(int InputArray[], int* EvenArray, int* EvenCount, float* Average, int* max, int* min)
{
	int length = 0;
	int temp;
	int newsize;
	long long int SumAverage;

	lenght = sizeof(InputArray);
	EvenArray = NULL;
	EvenCount = 0;
	
	//sort and check even numbers
	for (int i = 0; i < length; i++) 
	{   
      for (int j = i+1; j < length; j++) 
	  {     
        if(InputArray[i] > InputArray[j]) 
		{    
          temp = InputArray[i];    
		  InputArray[i] = InputArray[j];    
		  InputArray[j] = temp; 
		}  
      }
	  if(InputArray[i] % 2 == 0)
	  {
		EvenCount++;
		newsize = EvenCount * sizeof(int);
		EvenArray = realloc(EvenArray, newsize); 
		EvebArray[EvenCount-1] = InputArray[i];
	  } 
	  SumAverage += InputArray[i];
    } 
	// get other parameters
	temp = sizeof(InputArray);
	max = InputArray[temp-1];
	min = InputArray[0];
	Average = (float)SumAverage/(float)temp;
	return;
}