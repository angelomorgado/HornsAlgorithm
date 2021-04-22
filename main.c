#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Expressao{
    char *Positivos;
    char *Negativos;
}Expressao;

//Versão simplificada da função do split que funciona
//de forma eficaz para o problema em questão
void DesfragmentarLinha(char * linha, Expressao *lista)
{
    //indice que vamos utilizar para percorrer a lista
    int i=0;

    //Variáveis auxiliares de cada expressao
    int tamLista=0, tamPositivos=0, tamNegativos=0;

    while (linha[i] != '\0')
    {
        //Se encontrar o inicio de uma expressão ou seja o caracter '('
        if(linha[i] == '(')
        {
            tamLista++;
            lista = realloc(lista, tamLista * sizeof(Expressao));
            //Inicializa a lista de inteiros ou negativos dessa expressão
            lista[tamLista-1].Negativos = malloc(1);
            lista[tamLista-1].Positivos = malloc(1);
            tamPositivos=0; 
            tamNegativos=0;
        }

        //Se encontrar um '~' significa que o próximo caracter é um literal negativo
        if(linha[i] == '~')
        {
            //Atualiza a lista de negativos e adiciona o caracter negativo
            tamNegativos++;
            lista[tamLista-1].Negativos = realloc(lista[tamLista-1].Negativos, tamNegativos * sizeof(char));
            lista[tamLista-1].Negativos[tamNegativos-1] = linha[i+1];
            //Avança na lista para não repetir o caracter
            i++;
        }

        //Se for uma letra, adicionar aos positivos
        if(((linha[i] >= 65 && linha[i] <=90) || (linha[i] >= 97 && linha[i] <=122)) && linha[i-1] != '~')
        {
            //Atualiza a lista de positivos e adiciona o caracter positivo
            tamPositivos++;
            lista[tamLista-1].Positivos = realloc(lista[tamLista-1].Positivos, tamPositivos * sizeof(char));
            lista[tamLista-1].Positivos[tamPositivos-1] = linha[i];
        }

        //Avançar na linha
        i++;
    }


    printf("\nPOSITIVOS DO ULTIMO\n");
    for(int f=0;f<tamPositivos; f++)
    {
        printf("%c ", lista[1].Positivos[f]);
    }
    printf("\n\nNEGATIVOS DO ULTIMO\n");
    for(int f=0;f<21; f++)
    {
        printf("%c ", lista[1].Negativos[f]);
    }

    //Printa a linha como forma de debug, não apagar!
    /*for(int i=0; i<tamLista;i++)
    {
        //Printa os positivos da expressao
        printf("Positivos da expressao %d:\n", i);
        int f=0;
        while (lista[i].Positivos[f] != '\0')
        {
            printf("%d ", lista[i].Positivos[f]);
        }
        printf("\n\n");
        //Printa os negativos da expressao
        printf("Negativos da expressao %d:\n", i);
        f=0;
        while (lista[i].Negativos[f] != '\0')
        {
            printf("%d ", lista[i].Negativos[f]);
        }

        printf("\n\n\n");
    }*/
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
    //Este while irá ler linha a linha
    while((read = getline(&linha, &tam, f)) != -1)
    {
        printf("%s\n", linha);
        DesfragmentarLinha(linha,lista);
    }

    return 0;
}