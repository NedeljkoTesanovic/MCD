//Nedeljko Tesanovic RA181/2017
#include <at89c51rc2.h>

void delay() //trajanje od 1 sekunde (na mom racunaru ove vrijednosti daju 1s, a ne znam da li da mijenjam posto ne spustam na plocu; Ako treba na plocu onda samo umjesto 500, staviti 250)
{
	int i,j;
	for (i=0;i<500;i++)
	{	
		for (j=0;j<500;j++)
		{
		}
	}
	return;
}

void program1()	//treptanje dioda; radice iz bilo kog stanja P2;
{
	if(P2!=0xFF) //ako je ugaseno, upali sve;
	{
		P2 = 0xFF;
	}
	else //inace ugasi sve
	{
		P2 = 0x00;
	}
	return;
}


void program2() //pomjera svjetlo od desnog kraja ka lijevom svaku 1 sekundu
{
	if(P2 == 128) //polozaji su u sustini stepeni dvojke
	{
		P2 = 1; //skoci sa lijevog kraja na desni
	}
	else
	{
		P2<<=1; //pomjeri za 1 poziciju
	}
	return;
}

void program3(unsigned char* LED1, unsigned char* LED2) //pomjera dva svjetla sa krajeva do sredine
{
	if((*LED1) == 128) //ako je dosao na desni kraj, vrati se na lijevi; LED2 ce uvijek pratiti LED1 pa nema potrebe provjeravati i nju
	{
		(*LED1) = 2;
		(*LED2) = 64;
	}
	else if ((*LED1)==8) //ako je na sredini (8 i 16), preskoci jedan korak, inace bi na sredini bio dva puta zbog mimoilazenja svjetala
	{
		(*LED1)=32;
		(*LED2)=4;
	}
	else
	{
		(*LED1)<<=1;
		(*LED2)>>=1;
	}
	P2 = (*LED1)+(*LED2);  //saberi maske
	return;
}

void program4()	//puni diode sa lijeva na desno  / loading bar
{
	if(P2>=255)
	{
	P2 = 0;
	}
	else
	{
	P2*=2;
	P2++;
	}
	return;
}

void main()
{	
	unsigned char pos1 = 1;	//LED1 pozicija
	unsigned char pos2 = 128; //LED2 pozicija
	bit start = 1;	//receno mi je da radim po obrnutoj logici, tj da je pritisnut taster jednak nuli;
	bit stop = 1;
	bit brzina = 1;
	unsigned char program = 1;
	while(1)
	{  
		start = P0_0;
		if(!start) //zapocni program
		{
			stop = P0_1;
			while(stop)
			{
				stop = P0_1;
				switch(program)
				{
					case 2 : //1011
						program2();
						 break;
					case 3 : //1101
						program3(&pos1, &pos2);
						break;
					case 4 : //1110
						program4();
						break;
					default: //x111
						program1();
						break;
				}
				delay();//default prva brzina;
				if(!brzina) //+druga brzina
				{
					delay();
				}
				else
				{
				}
				//azuriraj izbor;
		
				if(!P0_2)  //program
				{
					program = 1;
				}
				else if(!P0_3)
				{
					program = 2;
					P2 = 1;
				}
				else if (!P0_4)
				{
					program = 3;
				}
				else if (!P0_5)
				{
					P2 = 0;
					program = 4;
				}
		
				if(!P0_6)  //brzina
				{
					brzina = 1;
				}
				else if(!P0_7)
				{
					brzina = 0;
				}
				else
				{
				}
			}
		}
		else
		{
			//azuriraj izbor;
			if(!P0_2)  //program
			{
				program = 1;
			}
			else if(!P0_3)
			{
				program = 2;
			}
			else if (!P0_4)
			{
				program = 3;
			}
			else if (!P0_5)
			{
				program = 4;
			}
	
			if(!P0_6)  //brzina
			{
				brzina = 1;
			}
			else if(!P0_7)
			{
				brzina = 0;
			}
			else
			{
			}
		}
	}
	return;
}