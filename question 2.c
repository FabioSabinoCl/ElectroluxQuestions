
#include xxx

#define Btn pin1
#define ON 0
#define OFF 1
#define PROTECTED 2 
#define TimeInProtected_ms 10000

short status = OFF;
short LastStatus = OFF;
bool flagProtected = false;
configure_input(Btn, pulldown);
uint TimePressed = 0;
int ProtectedTime_ms = 0; 


void main(void)
{
	
	while()
	{
		if (Btn) // suposing bounce effect was aready filtered by the hardware
		{
			TimePressed = 0;
			switch (status)
			{
				case ON:
					while (Btn)
					{
						TimePressed++;
						delay_ms(1);
					}
					LastStatus = ON;
					status = PROTECTED;
					ProtectedTime_ms = TimeInProtected_ms;
					// the button was pressed during approx. %d millisseconds, TimePressed.
					//the status will be switched from ON to OFF and protected time was activated.
				break;
				
				case OFF:
					while (Btn)
					{
						TimePressed++;
						delay_ms(1);
					}
					LastStatus = OFF;
					status = PROTECTED;
					ProtectedTime_ms = TimeInProtected_ms;
					// the button was pressed during approx. %d millisseconds, TimePressed.
					//the status will be switched from OFF to ON and protected time was activated.
				break;
				
				case else:
					while (Btn)
					{
						TimePressed++;
						ProtectedTime_ms--;
						delay_ms(1);
					}
					// the button was pressed during approx. %d millisseconds with protected status activated, TimePressed.
				break;
			}
		}
		if (status == PROTECTED)
		{
			ProtectedTime_ms--;
			delay_ms(1);
			if (ProtectedTime_ms <= 0)
			{
				if (LastStatus == ON)
				{
					status = OFF;
				}	
				else
				{
					status = ON;
				}	
			}	
		}
	}
}