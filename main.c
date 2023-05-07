/**********************
**Rantses Vinse
**AM:2022201900196
**dit19196@go.uop.gr
**
**Alexandropoulos Ilias
**AM:2022201900007
**dit19007@go.uop.gr
***********************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define IpMaxLength 21

typedef char treeItem;

typedef struct treenode *treelink;

struct treenode
{
	
	treeItem data;
	treelink left, right;
	
};

int ipInsert_flag = 0;

treelink createleaf(treeItem data);
void treeInsert(treelink root, char *prefix);

char** load(char* str,int* arr_length);

char* StringToBinary(char *str);
int string_se_int( char *str, int max);
char* IpToBinary(char *str,int* prefix_int);
char* treeSearch(char *prefix_str, treelink temproot);

int main(void)
{
	char** arr;
	int arr_length, prefix_int, i, x;
	treelink root;
	root = createleaf(-1);	
	char file[50] = {'\0'};
	do{
		do
		{
			printf("\n1. Eisagwgh arxeiou\n2. Eisagwgh ip gia anazhthsh prothematos\n3. Creators\n4. Exit\nEpileje ena apo ta parapanw ~");
			scanf("%d", &x);
		}while(x < 1 || x > 4);
		if(x == 3)
		{
			printf("Made by ");
			printf("\033[1;36m");
			printf("L0uSg3");
			printf("\033[0m");
			printf(" and ");
			printf("\033[1;31m");
			printf("TheHueMaster");
			printf("\033[0m");	
			printf("!!\n");		
		}
		else if( x == 1)
		{
			ipInsert_flag = 0;
			printf("Dwse onoma arxeiou: ");
			scanf("%s",file);
			arr = load(file, &arr_length);
			if( arr == NULL)
				return 1;
			char **prefix_str = (char **)malloc(sizeof(char *)*arr_length);
			char *temp;	
			for(i = 0; i < arr_length; i++)
			{
				temp = IpToBinary(arr[i],&prefix_int);
				prefix_str[i] = (char *)malloc(sizeof(char)*(prefix_int));
				strncpy(prefix_str[i],temp,prefix_int);
				free(temp);
				
				treeInsert(root,prefix_str[i]);
			}
						
			for(i = 0; i < arr_length; i++)
				free(arr[i]);
			free(arr);
		}
		else if( x == 2)
		{
			ipInsert_flag = 1;
			char ip[19] = {'\0'};
			printf("Dwse ip: ");
			scanf("%s",ip);
			ip[18] = '\0';
			
			char *temp;
			int prefix_int;
			temp = IpToBinary(ip,&prefix_int);
		
			if( root->left == NULL  && root->right == NULL)
				printf("Den yparxei dendro.\n");
			else
			{
				treelink temproot = root;
				char *str = treeSearch(temp,temproot);
				if( str != NULL )
					printf("Vrethike tairiasma prothematos %s.\n",str);
				else
					printf("Den vrethike tairiasma prothematos.\n");
			}
		}	
	}while(x != 4);
	
	return 0;
}
treelink createleaf(treeItem data)
{
	
	treelink tmproot = (treelink)malloc(sizeof *tmproot);
	
	tmproot->data = data;
							
	tmproot->left = NULL;
					
	tmproot->right = NULL;	
	
	return tmproot;
}

void treeInsert(treelink root, char *prefix)
{
	treelink temproot = root;
	
	int i, size = strlen(prefix);

	for(i = 0; i < size; i++)
	{
		if( temproot->left != NULL &&  prefix[i] == temproot->left->data )
			temproot = temproot->left;
		else if( temproot->right != NULL && prefix[i] == temproot->right->data )
			temproot = temproot->right;
		else
		{
			if( prefix[i] == '0' )
			{
				temproot->left = createleaf('0');
				temproot = temproot->left;
			}
			else if( prefix[i] =='1')
			{
				temproot->right = createleaf('1');
				temproot = temproot->right;
			}
		}
	}	
}

char** load(char* str,int* arr_length)
{
	FILE *myFile;
	myFile = fopen(str,"r");
	
	if( myFile == NULL)
	{
		printf("Sfalma anoigmatos tou arxeiou!\n");
		return NULL;
	}	
  	else
    	printf("To arxeio anoije epituxws\n");
	int i = 0, count = 0, c = 0;
	

	count++;
	while(!feof(myFile))
	{
  		c = fgetc(myFile);
  		if(c == '\n')
  			count++;
  
	}
        *arr_length = count;
        fclose(myFile);
       	myFile = fopen(str, "r");
       	char **STR;
       	STR = (char **)malloc(sizeof(char*)*count);
	for(i = 0; i < count; i++)
		STR[i] = (char *)malloc(sizeof(char)*IpMaxLength);   
	i = 0;
	while(i < count )
	{
		fgets(STR[i], IpMaxLength, myFile);
		i++;	
	}
	int j;
	for( i = 0; i < count; i++)
		for(j = 0; j < strlen(STR[i]); j++)
			if( (STR[i][j] < '0' || STR[i][j] > '9')  && STR[i][j] != '.' && STR[i][j] != '/')
				STR[i][j] = '\0'; 
  	fclose(myFile);
	return STR;
}

char* StringToBinary(char *str)
{
	int i, j;
	int n = string_se_int(str, strlen(str));
	char* strTobinary;
	strTobinary = (char *)malloc(sizeof(char)*9);
	for(i = 0; i < 9; i++)
		strTobinary[i] = '\0';
	for ( i = 7; i >= 0; i--) 
	{ 
        	int k = n >> i; 
        	if (k & 1) 
            		strTobinary[7-i]='1'; 
       	 	else
            		strTobinary[7-i]='0'; 
    	}	
    	return strTobinary;
}

int string_se_int( char *str, int max)
{
	int i, div = 1, x = 0;
	for(i = 0; i < max-1; i++)
		div *= 10;
	for( i = 0; i <= max-1; i++)
	{
		x += (str[i] - '0')*div;
		div /= 10;
	}
	return x;
}

char* IpToBinary(char *str, int* prefix_int)
{
	char ip[5][4] = {'\0'};
	int i, rows = 0, col = 0;
	for(i = 0 ; i < strlen(str); i++)
	{
		if( str[i] != '.' && str[i] != '/' )
		{
			ip[rows][col] = str[i];
			col++;
		}
		else
		{
			col = 0;
			rows++;
		}	
	
	}
	if( ipInsert_flag == 0)
		*prefix_int = string_se_int(ip[4], strlen(ip[4]));
	char* ip_split[4];

	for( i = 0; i < 4; i++)
		ip_split[i] = StringToBinary(ip[i]);
		
	char* IpString = (char *)malloc(sizeof(char)*32);
	strcpy(IpString,ip_split[0]);
	strcpy(IpString+8,ip_split[1]);
	strcpy(IpString+16,ip_split[2]);
	strcpy(IpString+24,ip_split[3]);
	
	return IpString;
}


char* treeSearch(char* prefix_str, treelink temproot)
{
	int i, size = strlen(prefix_str), counter = 0;
	for(i = 0; i < size; i++)
	{
		if( temproot->left != NULL &&  prefix_str[i] == temproot->left->data )
		{
			temproot = temproot->left;
			counter++;
		}
		else if( temproot->right != NULL && prefix_str[i] == temproot->right->data )
		{	
			temproot = temproot->right;
			counter++;
		}
		else
			break;
	}
	char* str = (char *)malloc(sizeof(char)*(counter+1));
	str[counter] = '\0';
	if( counter == 0 )
		return NULL;
	else
	{
		strncpy(str,prefix_str,counter);
		return str;
	}
}
