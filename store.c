#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"

Product p[20];
int numProd = 0;

/** readInv(): Read products from a file into the inventory*/
int readInv()
{
	FILE * fp;
	char c;
	
	numProd = 0;
    fp = fopen ("sample.dat", "r");
    while (!feof(fp))
    {
        
		fscanf(fp, "%s %s %f", p[numProd].code,
			p[numProd].desc,&p[numProd].price);
		if (strlen(p[numProd].code) > 1)
		   numProd++;
    }
   fclose(fp);

   return(numProd);
}

/** readInv(): Save the inventory into a products file */
int writeInv()
{
    FILE * fp;
	int i;
    fp = fopen("sample.dat","a");
    for(i=0; i < numProd; i++)
		fprintf(fp,"%s; &s; %.2f\n", p[i].code, p[i].desc, p[i].price );
	fclose(fp); 
	return(1);
}

/** Select products for sale and create the bill */

int checkout()
{
   return(1);
}

/** Display the products in the inventory */
int display()
{
    int i;
	char line[] = "-------------------------------------------------";
	printf("NUM  Product Code   Description             Price\n");
	puts(line);
	for(i = 0; i < numProd; i++)
	    printf("%3d  %13s  %-20s %8.2f\n", i+1, 
			p[i].code, p[i].desc, p[i].price);
	printf("Num of Products: %d\n", numProd);
	puts(line);
}

/** editProd: Edit the inventory list */
int editProd()
{
	char c;

	do 
	{
		/* Offer a command menu */
		printf("Inventory Menu: [A]dd, [D]elete, [U]pdate [Q]uit  Choose:");
	   
		c = getchar();
		switch(c)
		{
		case 'A':
		case 'a': newProd(); getchar(); putchar('\r'); break;
		
		case 'D':
		case 'd': deleteProd(); getchar(); putchar('\r'); break;
	     
		case 'U':
		case 'u': updateProd(); getchar(); putchar('\r');  break;

		case 'Q':
		case 'q': getchar();
		case '\n': putchar('\r'); break;
		
		default:
			printf(">>>> Unknown command: %c\n", c);
			c = getchar();
	   }
    } while ((c != 'Q') && (c != 'q'));
	return(1);
}

/** updateProd: Update the description and prices of a product */
int updateProd()
{
   return(1);
}

/** deleteProd: Remove a product from the inventory*/
int deleteProd()
{
   return(1);
}

/** newProd: Asd new product with description and price to the inventory */
int newProd()
{  Product x;
  
    printf("Scan barcode:");
    scanf("%s", x.code);
	printf("Enter description:");
    scanf("%f",x.desc);
    printf("Enter price");
    scanf("%f",&x.price);

	return(1);
}

/** Main: application structure */
int main()
{
	char c;
	
	/* Welcome */
	numProd = readInv();
    printf("WELCOME TO CS110 MINI STORE\n");
	printf("Selling %d product(s)\n\n", numProd);
	
	/* Work loop */
	do 
	{
		/* Offer a command menu */
		printf("Store Menu: [A]dmin, [D]isplay, [S]ale, [Q]uit Choose:");
	   
	    /* Get the command and execute the appropriate function */
		c = getchar();
		switch(c)
		{
		case 'A':
		case 'a': editProd(); getchar(); putchar('\r'); break;
				  
		case 'S':
		case 's': checkout(); getchar(); putchar('\r'); break;
		  
		case 'D':
		case 'd': display(); getchar(); putchar('\r'); break;

		case 'Q':
		case 'q': getchar();
		case '\n': putchar('\r'); break;
		
		default:
			printf(">>>> Unknown command: %c\n", c);
			getchar();
			putchar('\r'); break;
	   }
    } while ((c != 'Q') && (c != 'q'));

    printf("\nGood-bye\n");
	return(0);
}
