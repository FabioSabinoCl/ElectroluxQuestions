void paserSerial(char packReceived[], int packSize);
void USARTx_interrupt(void);

int j=0;
char receiveSerial[257];
int tamVector = 0;
bool FlagSerial = false;
int TimeOutSerial = -1;

void main()
{
	while()
	{
		if (flagserial)
		{
		 flagserial = false;	
		 paserSerial(receiveSerial, tamVector);
		}
		if (timeoutSerial > 0)
		{
			timeoutSerial--;
			delay_ms(1);
			if (timeoutSerial == 0)
			{	
				flagserial = false;
				timeoutSerial = -1;
				j = 0;
				//send in serial TIME_OUT exception
			}	
		}
		
	}	
}




	//*******************************************************************************//
	// Pack structure
	// SIZE;COMMAND;PAYLOAD1;PAYLOAD2;PAYLOADn;CRC
	//where:
	//SIZE-> hex value  (FF), it will determine the size of pack, including crc
	//COMMAND-> hex value (FF)
	//PAYLOADS-> int value
	//CRC-> hex value(FFFF) 
	//*******************************************************************************//

void USARTx_interrupt(void) // no timeout was implemented in this function
{	
	/*************************INTERUPÇÃO SERIAL 1***********************************/
	if ((interrupt)	        
	{			
		flagserial = false;
		timeoutSerial = 200; //aprox. 200 miliseconds to timeout in the serial data.
		receiveSerial[j++] = USART_ReceiveData(USARTx);	
		if (j == 2)
		{	
			//compare if is hexadecimal value
			if (((receiveSerial[0] >= 0x30 &&  receiveSerial[0] <= 0x39) && (receiveSerial[0] >= 0x41 &&  receiveSerial[0] <= 0x46)) && ((receiveSerial[1] >= 0x30 &&  receiveSerial[1] <= 0x39) && (receiveSerial[1] >= 0x41 &&  receiveSerial[1] <= 0x46)))
			{	
				tamVector = strtol(receiveSerial, NULL, 16);//get the command size in hexadecimal.   
			}
			else // if not, abort the pack
			{
				timeoutSerial = -1;
				j = 0;
				tamVector = 0;
			}
		}
		if (j == tamVector)// when the information is fully received
		{ 
			timeoutSerial = -1;
			j = 0;
			flagserial = true;
		}
	}
}



void paserSerial(char packReceived[], int packSize)
{
	
	bool CrcConfirm = false;
	char *crcCalc[];
	char CRCRec[4];
	char temp_crcData[255] = {'\0'}; 
	char serialSplit[25][25] = {'\0'};
	int contSplit = 0;
	char chatacter;
	int contLine = 0;
	int EndOfPack = 0;
	
	//clean flag serial
	flagserial = false;
	 
	//add received crc to var CRCRec
	CRCRec[0] = packReceived[packSize - 4];
	CRCRec[1] = packReceived[packSize - 3];
	CRCRec[2] = packReceived[packSize - 2];
	CRCRec[3] = packReceived[packSize - 1];
	//clean temp_crcData
	memset(temp_crcData, '\0',sizeof(temp_crcData));
	// get values for crc calc.	
	for (int i = 2; i < (packSize - 4); i++) 
	temp_crcData[i-2] = packReceived[i]; 
	//checkCRC
	CrcConfirm = calculate_crc(temp_crcData, CRCRec);// only a sample function to represents a CRC check , returns true or false


	if (CrcConfirm)
	{			
		//Split the pack by ";"		
		contSplit = 0;
		contChatacter = 0;
		contLine = 0;
		EndOfPack = strlen(temp_crcData);
		//clean serial split
		memset(serialSplit, '\0',sizeof(serialSplit));
		do {
			chatacter = temp_crcData[contSplit];		
			if (chatacter == ';') 
			{
				contLine += 1;
				contCaracter = 0;
			}
			else 
			{
				serialSplit[contLine][contCaracter] = chatacter;
				contCaracter += 1;
			}
			contSplit += 1;			
		} while(contSplit <= EndOfPack);			
	}
	else
	{
		//send in serial BAD_CRC exception
		return;		
	}
	//check the command
	//**************************************************************************//
		if(strcmp(serialSplit[0],"00")==0) // check the command stored in serialsplit[0] if command is 00 run the action
		{
			int payload1 = atoi(serialSplit[1]);
			int payload2 = atoi(serialSplit[2]);
			//use the payload values stored int serialsplit[1], serialsplit[2]... serialsplit[n].
			//send in serial any data.
			return;
		}
		else if(strcmp(serialSplit[0],"FF")==0) // check the command stored in serialsplit[0] if commando is FF run the action
		{
			int payload1 = atoi(serialSplit[1]);
			int payload2 = atoi(serialSplit[2]);
			//use the payload values stored int serialsplit[1], serialsplit[2]... serialsplit[n].
			//send in serial any data.
			return;
		}
		else
		{
			//send in serial BAD_CMD exception
			return;		
		}	
}
