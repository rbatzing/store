#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product
{
	char code[15];
	float price;
} Product;

Product p[20];

int numProd = 0;

int readProd()
{
   FILE * fp;
   numProd = 0;
    fp = fopen ("sample.dat", "r");
    while (!feof(fp))
    {
       fscanf(fp, "%s %f", p[numProd].code, &p[numProd].price);
	   if (strlen(p[numProd].code) > 1)
		   numProd++;
    }
   fclose(fp);

   return(numProd);
}

int addProd()
{  Product x;
    FILE * fp;
   
    printf("Scan barcode:");
    scanf("%s", x.code);
    printf("Enter price");
    scanf("%f",&x.price);
    fp = fopen("sample.dat","a");
    fprintf(fp,"%s %.2f\n", x.code,x.price );
	fclose(fp);
	return(1);
}

int checkout()
{
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
int main()
{
	int i;
	char c;
	
	numProd = readProd();
	do 
	{
	   printf("Mini Store System Menu:\n");
	   printf("\t[A]dd\n\t[D]elete\n\t[U]pdate\n");
	   printf("\t[S]how\n\t[C]heckout\n\t[Q]uit\n");
	   printf("Please Choose:");
	   
	   c = getchar();
	   switch(c)
	   {
	   case 'A':
	   case 'a':
	   	addProd(); break;
		
	   case 'D':
	     deleteProd(); break;
	     
	   case 'U':
	      updateProd(); break;
		  
	   case 'C':
		  checkout(); break;
	   }
    } while ((c != 'Q') && (c != 'q'));

    printf("Good-bye\n");

  
   printf("Num of Products: %d\n", numProd);
   

   for(i = 0; i < numProd; i++)
	    printf("Product: %2d Code:%13s Price: %8.2f\n", i, p[i].code,
			p[i].price);

   return(0);
}
