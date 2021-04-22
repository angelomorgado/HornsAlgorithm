#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Expressao{
    char *Positivos;
    int tamPositivos;
    char *Negativos;
    int tamNegativos;
}Expressao;

//
int DesfragmentarLinha(char *linha, Expressao **lista)
{
    //indice que vamos utilizar para percorrer a lista
    int i=0;

    //Variáveis auxiliares de cada expressao
    int tamLista=0;

    while (linha[i] != '\0')
    {
        //Se encontrar o inicio de uma expressão ou seja o caracter '('
        if(linha[i] == '(')
        {
            tamLista++;
            (*lista) = realloc((*lista), tamLista * sizeof(Expressao));
            //Inicializa a (*lista) de inteiros ou negativos dessa expressão
            (*lista)[tamLista-1].Negativos = malloc(1);
            (*lista)[tamLista-1].Positivos = malloc(1);
            (*lista)[tamLista-1].tamPositivos=0; 
            (*lista)[tamLista-1].tamNegativos=0;
        }

        //Se encontrar um '~' significa que o próximo caracter é um literal negativo
        if(linha[i] == '~')
        {
            //Atualiza a (*lista) de negativos e adiciona o caracter negativo
            (*lista)[tamLista-1].tamNegativos++;
            (*lista)[tamLista-1].Negativos = realloc((*lista)[tamLista-1].Negativos, (*lista)[tamLista-1].tamNegativos * sizeof(char));
            (*lista)[tamLista-1].Negativos[(*lista)[tamLista-1].tamNegativos-1] = linha[i+1];
            //Avança na (*lista) para não repetir o caracter
            i++;
        }

        //Se for uma letra, adicionar aos positivos
        if(((linha[i] >= 65 && linha[i] <=90) || (linha[i] >= 97 && linha[i] <=122)) && linha[i-1] != '~')
        {
            //Atualiza a (*lista) de positivos e adiciona o caracter positivo
            (*lista)[tamLista-1].tamPositivos++;
            (*lista)[tamLista-1].Positivos = realloc((*lista)[tamLista-1].Positivos, (*lista)[tamLista-1].tamPositivos * sizeof(char));
            (*lista)[tamLista-1].Positivos[(*lista)[tamLista-1].tamPositivos-1] = linha[i];
        }

        //Avançar na linha
        i++;
    }
    return tamLista;
}

void debugLinha(Expressao *lista, int tamLista)
{
    for(int i=0; i< tamLista; i++)
    {
        printf("\n============================ EXPRESSAO %d =========================\n\n", i+1);
        printf("Elementos positivos:\n");
        for(int f = 0; f< lista[i].tamPositivos; f++)
        {
            printf("%c ", lista[i].Positivos[f]);
        }
        printf("\n\n");
        printf("Elementos negativos:\n");
        for(int f = 0; f< lista[i].tamNegativos; f++)
        {
            printf("%c ", lista[i].Negativos[f]);
        }
        printf("\n");
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
    Expressao *lista = malloc(1);
    int tamLista;
    //Este while irá ler linha a linha
    while((read = getline(&linha, &tam, f)) != -1)
    {
        printf("%s\n", linha);
        tamLista = DesfragmentarLinha(linha,&lista); 
        debugLinha(lista, tamLista);
        
        /*for(int f = 0; f< lista[3].tamPositivos; f++)
            {
                printf("%c \n", lista[3].Positivos[f]);
            }
        printf("%d\n",lista[3].tamPositivos);*/
    }

    return 0;
}