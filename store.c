#include <stdio.h>
#include <stdlib.h>

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
      numProd++;
    }
   fclose(fp);

   return(numProd);
}

int newProd()
{
	return(1);
}

int checkout()
{

}

int main()
{
	int i;

	numProd = readProd();

   printf("Num of Products: %d\n", numProd);
   

   for(i = 0; i < numProd; i++)
	    printf("Product: %2d Code:%13s Price: %8.2f\n", i,    p[i].code, p[i].price);

   return(0);
}
