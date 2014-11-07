#define CODELEN 15
#define DESCLEN 35

#define TRUE 1
#define FALSE 0

typedef struct product
{
	char code[CODELEN];
	char desc[DESCLEN];
	float price;
} Product;

typedef struct salesItem
{
	Product *prod;
	int quantity;
} SalesItem;


