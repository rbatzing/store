#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"

#define MAXPROD 30
#
Product p[MAXPROD];

int numProd = 0;

int readProd()
{
	FILE * fp;
	char buffer[DESCLEN];
	
	numProd = 0;
    fp = fopen ("sample.dat", "r");
    while (!feof(fp))
    {
		fscanf(fp, "%s", p[numProd].code);
		
		do
		{
			fscanf(fp, "%s", buffer);
			
			if ((strlen(buffer) != 1) && ( buffer[0] != '@'))
			{
				strcat(p[numProd].desc, buffer);
				strcat(p[numProd].desc, " ");
			}
			
		} while ((strlen(buffer) != 1) || ( buffer[0] != '@'));
			
		fscanf(fp, "%f", &p[numProd].price);
			
		if (strlen(p[numProd].code) > 1)
		   numProd++;
    }
   fclose(fp);

   return(numProd);
}

int writeProd()
{
    FILE * fp;
	int i;
	
	rename("sample.dat","sample.bak");
	
    fp = fopen("sample.dat","a");
	for (i=0; i < numProd; i++)
		fprintf(fp,"%s %s @ %.2f\n",p[i].code, p[i].desc, p[i].price);
	fclose(fp);
    return(-1);
}

int addProd()
{ 
    if (numProd < MAXPROD)
	{
		printf("Scan barcode:");
		gets(p[numProd].code);
	
		printf("Enter description:");
		gets(p[numProd].desc);
		
		printf("Enter price:");
		scanf("%f",&p[numProd].price);
		numProd++;
		getchar();
		return(TRUE);
	}
	return(FALSE);
}

void drawLine(char c,int num)
{
	int i;
	for (i=0; i< num; i++ )
	   putchar(c);
	printf("\n");
}

int checkout()
{	
	int i;
	SalesItem invoice[20];
	int numItem = 0;
	float cost,totalCost;
	
	char buffer[20];
	do {
		printf("Enter code or [ENTER] to end :");
		gets(buffer);
		if (strlen(buffer) > 0)
		{
			i =0;
			while (i < numProd)
			{
				if (strcmp(buffer, p[i].code) == 0)
				{
					invoice[numItem].prod = &p[i];
					printf("How many? (0 to Cancel): ");
					scanf("%d", &invoice[numItem].quantity);
					getchar();
					if (invoice[numItem].quantity > 0)
						numItem++;
						
					break;
				}
				i++;
			}
			
			if (i == numProd)
				printf(">>>> Product %s not found\n",buffer);			
					
		}	
	} while (strlen(buffer) > 0);
	
	totalCost = 0;
	printf("\n%-30s **** Invoice : %d item(s) ****\n\n",
		"PYU CS110 MiniStore",numItem);
	drawLine('=',60);
	printf("%-13s %-20s %-3s @ %8s %10s\n",
		"Product code","Description","Qty","Price", "Cost");
	drawLine('-',60);
	for (i = 0; i < numItem; i++)
	{
		cost = invoice[i].quantity * ((*invoice[i].prod).price);
		printf("%13s %-20s %3d @ %8.2f %10.2f\n",
			(*invoice[i].prod).code, (*invoice[i].prod).desc,
			invoice[i].quantity, (*invoice[i].prod).price, 
			cost);
		totalCost += cost;
	}
	drawLine('=',60);
	printf(" %45s:   %10.2f\n\n","Total cost",totalCost);
   return(1);
}


int editProd()
{
	char c;
	int chg = FALSE;
	
	do 
	{
	   printf("Product Menu: [A]dd [D]elete [U]pdate [Q]uit (Please Choose):");
	   
	   c = getchar();
	   switch(c)
	   {
	   case 'A':
	   case 'a': getchar(); chg = addProd(); break;
		
	   case 'D':
	   case 'd': getchar(); deleteProd(); break;
	     
	   case 'U':
	   case 'u': getchar(); updateProd(); break;
		  
	   case 'Q':
	   case 'q': getchar();
	   case '\n': break;
	   
	   default: getchar();
	        printf("\n>>>> Unknown command: %c\n\n", c);
	   
	   }
    } while ((c != 'Q') && (c != 'q'));
	
	if (chg)
		writeProd();

   return(1);
}

int updateProd()
{
   return(1);
}

int deleteProd()
{
   return(1);
}

int searchProd()
{
	char searchbuf[20];
        int i;
        
        printf("Product code:");
        scanf("%s", searchbuf);
        getchar();
        
        for(i=0; i < numProd;i++)
        	if(strcmp(searchbuf,p[i].code) == 0)
          	{
          		printf("\ncode:\t %-13s\ndesc:\t %-35s\nprice:\t %8.2f\n\n",
          			p[i].code, p[i].desc, p[i].price);
          		return();
          	}
        printf("\n>>>>Product not found\n");  
    	return(1);
}


int displayProd()
{
	int i;

	printf("\nNum of Products: %d\n", numProd);
	drawLine('=',48);
	puts("Num  Product code       Description       Price");

    drawLine('-',48);
    for(i = 0; i < numProd; i++)
	    printf("%3d %13s %-20s %8.2f\n", 
			i+1, p[i].code, p[i].desc, p[i].price);
	drawLine('=',48);
	return(1);
}
			
int main()
{
	int i;
	char c;
	
	puts("\nWelcome to the PYU CS110 MiniStore\n");
	
	numProd = readProd();
	do 
	{
	   printf("Store Menu: [A]dmin [D]isplay [S]earch [C]heckout [Q]uit (Please Choose):");
	   
	   c = getchar();
	   switch(c)
	   {
	   case 'A':
	   case 'a': getchar(); editProd(); break;
		
	   case 'D':
	   case 'd': getchar(); displayProd(); break;
	     
       case 'S':
		case 's': getchar(); searchProd(); break;
			
	   case 'C':
	   case 'c': getchar(); checkout(); break;
	   
	   case 'Q':
	   case 'q': getchar();
	   case '\n': break;

	   default: getchar();
	            printf("\n>>>> Unknown command: %c\n\n", c);
	   }
    } while ((c != 'Q') && (c != 'q'));

    printf("Good-bye\n");

   return(0);
}
