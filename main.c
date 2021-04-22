#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


//Versão simplificada da função do split que funciona
//de forma eficaz para o problema em questão
void split(char * str, char *delim, char **lista)
{
    int tam = strlen(delim);
    int listaTam=0;
    int inicio=0,fim=inicio+tam-1;
    char *substr = malloc(1);
    while(str[fim] != '\0')
    {
        strncpy(substr, str + inicio, tam);
        if(strcmp(delim, substr) == 0)
        {
            //Juntar a primeira parte á lista 
            strncpy(substr, str, inicio);
            listaTam++;
            *lista = realloc(*lista, listaTam * sizeof(char **));
            lista[listaTam-1] = substr;

            //Atualizar a string
            strncpy(substr, str + fim + 1, tam -1);
            str = substr;

            printf("Lista: %s --||-- string: %s\n", lista[listaTam-1], str);
        }

        inicio++;
        fim++;
    }
}

int main()
{
    //Abre o ficheira
    FILE *f = fopen("teste.txt", "r");
    if(f == NULL)
    {
        printf("Falha na abertura do ficheiro\n");
        return 1;
    }

    char *linha = NULL;
    size_t read, tam;
    char **lista = malloc(1);
    //Este while irá ler linha a linha
    while((read = getline(&linha, &tam, f)) != -1)
    {
        printf("%s\n", linha);
        split(linha, ") & (",lista);
    }

    return 0;
}