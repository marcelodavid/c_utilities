#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prototypes declarations
char** split(char *str, char *delimitators);

int main(void)
{
	char** result;
	char str[] = "1-0:0.0.1(132412515)\n1-0:0.2.3.4(654236517)\n";

	result = split(str, "()\n");

	for(size_t index = 0; *(result + index); index++) 
	{
		printf("%s\n",*(result + index));
	}
	free(result);
	return 0;
}

char** split(char *str, char* delimitators)
{
	int count = 0;
	size_t index = 0;
	char **parse;
	char *tmp = str;
	char *token;
	char *last_delimitator;

	while(*tmp)
	{
		/******************************************
		si *tmp contiene uno de los deliitadores
		strchr devolvera la direcccion de este sino
		devolvera una direccion nula
		*******************************************/
		if(strchr(delimitators, *tmp) != NULL)
		{
			count++;
			last_delimitator = tmp;

		}
		tmp++;
	}

	//Espacio para datos ubicados luego del ultimo delimitador
	count += last_delimitator < (str + strlen(str) - 1);

	//Espacio para el caracter nulo del arreglo de punteros
	count++;

	parse = malloc(sizeof(char*) * count);
	token = strtok(str, delimitators);

	while(token != NULL)
	{
		*(parse + index++) = token;
		token = strtok(NULL, delimitators);
	}

	*(parse + index) = 0;

	return parse; 
}
