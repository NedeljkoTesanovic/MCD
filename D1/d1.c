//Nedeljko Tesanovic
//RA181-2017
//Domaci: Vjezba#1 - Zadatak#5

bit e_str2num = 0;	//Globalni flagovi za greske funkcija; Laksi debug
bit e_izracunaj = 0;

char str2num(char* str) //pretvori string u decimalni broj
{
	 char broj = 0;	//receno je da su promjenljive 8-bitne
	 unsigned char i = 0;
	 bit neg = 0;
	 
	 if(str[i] == '-') //u pitanju je negativni broj
	 {
	 	i++; //pomjeri se sa minusa
		neg = 1;
	 }
	 else
	 {
	 }

	 if(str[i] == 'b' || str[i] == 'B') //u pitanju je binarni sistem
	 {
	 	i++; //pomjeri se na cifre
	 	  while(str[i] != '\0')
		  {
		  	if(str[i] == '0' || str[i] == '1')
			{
				broj*=2; //Pomnozi sa bazom brojnog sistema - shiftovanje cifara u lijevo da bi napravili mjesta za
				broj+=(str[i++]-48); //trenutnu cifru na najnizoj poziciji
			}
			else
			{
				e_str2num = 1;
				return 1;
			}
		  }
	 }
	 else if(str[i] == 'H' || str[i] == 'h') //u pitanju je heksadecimalni sistem
	 {
		 i++; //pomjeri se na cifre
	 	  while(str[i] != '\0')
		  {
			if(str[i]>='0' && str[i]<='9')	//U pitanju je obicna cifra 0-9; '0' je po decimalnoj vrijednosti ASCII tabele 48
			{
				broj*=16;
				broj+=(str[i++]-48);
			}
			else if(str[i]>='A' && str[i]<='F')
			{
				broj*=16;
				broj+=(str[i++]-55); //U pitanju su heksadecimalne cifre ABCDEF; 'A' je po decimalnoj brijednosti ASCII tabele 65; -55 = -65 +10
			}
			else if(str[i]>='a' && str[i]<='f')
			{
				broj*=16;
				broj+=(str[i++]-87); //U pitanju su heksadecimalne cifre ABCDEF u lowercase-u; 'a' je po decimalnoj brijednosti ASCII tabele 97; -87 = -97 +10
			}
			else
			{
				e_str2num = 1;
				return 1;
			}
		  }
	 }
	 else //Ukoliko nije greska, u pitanju je dekadni sistem
	 {
	 	  while(str[i] != '\0')
		  {
				if(str[i]>='0' && str[i]<='9')
				{
			  		broj*=10;
					broj+=(str[i++]-48);
				}
				else //U pitanju je greska
				{
					e_str2num = 1;
					return 1;
				}
		  }
	 }
	 if(neg == 1)
	 {
	 	broj*= (-1);
	 }
	 else
	 {
	 }
	return broj;
}

void num2str(char broj, char* retval)	//pretvori decimalni broj u string
{
	char str[10];	 //pomocni string jer ce rezultat biti naopacke 
	unsigned char i = 0; //brojaci za indekse 
 	unsigned char j = 0;
	bit neg;
	if(broj<0)
	{
	neg = 1;
	broj*=(-1);
	retval[j++] = '-';
	}
	else
	{
	neg = 0;
	}
	while (broj)
	{
	 		str[i++] = (broj % 10)+48; //Izoluj cifru i pretvori je u ASCII ekvivalentu
			broj /= 10;	//Odbaci poslednju cifru
	}
	while(i>0)	//Invertuj string
	{
		retval[j++]=str[--i];
	}
	retval[j]='\0';
} 

void kopiraj(char* src, char* dst) //odredisni string "upija" izvorni; Samo korisceni biti ce biti prepisani
{
	unsigned char i=0;
	while(src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
}

void izracunaj(char* op1, char* op2, char* rez, char operant)
{
	char operand1;
	char operand2;
	char retval;
	char retstr[10];

	operand1 = str2num(op1);
	operand2 = str2num(op2);

	if(operant == '+')
	{
		retval = operand1 + operand2;
	}
	else if(operant == '-')
	{
		retval = operand1 - operand2;
	}
	else if(operant == '*')
	{
		retval = operand1 * operand2;
	}
	else if(operant == '/')
	{
		if(operand2 != 0)
		{
			retval = operand1 / operand2;
		}
		else
		{
			e_izracunaj = 1; //Greska: dijeljenje sa nulom
			return;
		}
	}
	else
	{
		e_izracunaj = 1;
		return;
	}
	num2str(retval, retstr); //za debugging; puni odredisni string sa '\0' radi preglednosti rezultata;							   
	kopiraj(retstr, rez);			  
}

void main()
{
	char rezultat[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	izracunaj("5","H1",rezultat,'*');
	izracunaj("b1000000", "-HF", rezultat, '/');
	izracunaj("HA","-HB",rezultat,'+');
	izracunaj("HB4","0",rezultat,'+');
	izracunaj("100","HAD", rezultat, '-');
	izracunaj("-b101","H4", rezultat, '*');
	izracunaj("2","H0", rezultat, '/');	 //e_izracunaj ce prijaviti gresku jer dijelimo sa nulom;
	return;
}