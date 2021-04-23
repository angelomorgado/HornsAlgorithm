#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Estrutura que vamos utilizar para conter os literais positivos e negativos de uma expressão
typedef struct Expressao{
    char *Positivos;
    int tamPositivos;
    char *Negativos;
    int tamNegativos;
}Expressao;

//=============================================== FUNÇÕES AUXILIARES =================================================================


/**
 * Verifica se um char c existe num qualquer array de chars lista
 * @param lista string que queremos usar
 * @param c caracter que queremos verificar se existe na string
 * @param tam tamanho da lista
 * @return retorna 1 se o caracter tiver contido e 0 se não
*/
int existeNaLista(char *lista, char c, int tam)
{
    for(int i=0; i<tam; i++)
    {
        if(lista[i] == c)
            return 1;
    }
    return 0;
}


/**
 * Verifica se um determinado Array de chars está contido noutro, return 1 se está senão return 0
 * @param big string que vamos verificar se contém a small
 * @param tamBig tamanho da string big
 * @param small conjunto de caracteres que vamos verificar se estão contidos na string big
 * @param tamSmall tamanho do buffer small
 * @return retorna 1 se os caracteres de small estão contidos na string big e 0 senão
*/
int estaContido(char *big, int tamBig, char *small, int tamSmall)
{
    int count=0;
    //percorrer small e verificar se cada caracter dele existe no big
    for(int i=0; i<tamSmall; i++)
    {
        if(existeNaLista(big, small[i], tamBig) == 1)
            count++;
    }

    if(count == tamSmall)
        return 1;
    else
        return 0;
}


/**
 * Dá reset á lista de expressões para que possa ser utilizada novamente devolve o valor do tamanho da lista como 0
 * @param lista lista de todas as expressões
 * @return retorna o tamanho da lista a 0
*/
int reset(Expressao **lista)
{
    //Liberta a memória em heap da lista
    free(*lista);
    //Volta a inicializar a lista
    *lista = malloc(1);

    return 0;
}

/**
 * Verifica se existe mais do que um literal positivo numa expressa, se sim retornar 1 senão retornar 0
 * @param lista lista de todas as expressões
 * @param tamLista tamanho da lista
 * @return 1 se existir mais do que um, 0 se não
*/
int verificarPositivos(Expressao *lista, int tamLista)
{
    for(int i = 0; i<tamLista; i++)
    {
        if(lista[i].tamPositivos > 1)
        {
            return 1;
        }
    }
    return 0;
}

//================================================================================================================================================
//============================================================== FUNÇOES PRINCIPAIS ==============================================================

//Divide a linha em expressoes e separa os valores negativos e positivos na estrutura Expressao

/**
 *  Esta função tem como objetivo pegar na linha obtida do ficheiro dado como input e, não só dividir as expressões, mas como também dividir cada
 *  literal atómico delas em positivo e negativo, para isso foi utilizada a estrutura Expressão
 * 
 *  @param linha Buffer que contém a linha do ficheiro dado para que se possa desfragmentar-se em forma da estrutura Expressao
 *  @param lista Lista vazia do tipo Expressao que vai ser preenchida pelas expressoes contidas no buffer linha
 *  @return Retorna o tamanho dessa lista para que possa ser utilizado noutras operações e assim ser mais otimizado
*/
int DesfragmentarLinha(char *linha, Expressao **lista)
{
    //indice que vamos utilizar para percorrer o buffer linha
    int i=0;

    //Variavel que vai conter o tamanho da lista e assim poder ser retornado
    int tamLista=0;

    //Vai percorrer o buffer linha, caracter a caracter
    while (linha[i] != '\0')
    {
        //Se encontrar o inicio de uma expressão ou seja o caracter '(' cria uma nova instância na lista e inicializa as suas variáveis
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

        //Se encontrar um '~' significa que o próximo caracter é um literal negativo, portanto adiciona o caracter imediatamente a seguir 
        //na lista de literais negativos
        if(linha[i] == '~')
        {
            //Atualiza a (*lista) de negativos e adiciona o caracter negativo
            if(existeNaLista((*lista)[tamLista-1].Negativos, linha[i+1], (*lista)[tamLista-1].tamNegativos) == 0)
            {
                (*lista)[tamLista-1].tamNegativos++;
                (*lista)[tamLista-1].Negativos = realloc((*lista)[tamLista-1].Negativos, (*lista)[tamLista-1].tamNegativos * sizeof(char));
                (*lista)[tamLista-1].Negativos[(*lista)[tamLista-1].tamNegativos-1] = linha[i+1];
            }
            //Avança na (*lista) para não repetir o caracter
            i++;
        }

        //Se for uma letra, adicionar ao grupo de literais positivos, porém é preciso verificar se esse literal não se encontra na lista
        //Para evitar caracteres repetidos
        if(((linha[i] >= 65 && linha[i] <=90) || (linha[i] >= 97 && linha[i] <=122)) && linha[i-1] != '~')
        {
            if(existeNaLista((*lista)[tamLista-1].Positivos, linha[i], (*lista)[tamLista-1].tamPositivos) == 0)
            {
                //Atualiza a (*lista) de positivos e adiciona o caracter positivo
                (*lista)[tamLista-1].tamPositivos++;
                (*lista)[tamLista-1].Positivos = realloc((*lista)[tamLista-1].Positivos, (*lista)[tamLista-1].tamPositivos * sizeof(char));
                (*lista)[tamLista-1].Positivos[(*lista)[tamLista-1].tamPositivos-1] = linha[i];
            }
        }

        //Avançar na linha
        i++;
    }
    return tamLista;
}


/**
 * Esta é a função principal do algoritmo de horn, ela vai criar uma lista 'listaHorn' e vai preenchendo-a assim como foi feito nos exercícios da aula
 * Se no final dessa lista houver um bottom (representado pelo caracter '_' vai escrever no ecrã "UNSAT", caso contrário escreve "SAT")
 * NOTA->  Como o TOP (geralmente representado pela letra T) não é estritamente necessário estar na lista, tornando-se oculto, ele vai ser tratado na primeira
 *         parte do algoritmo, preenchendo a listaHorn com todas as expressões atómicas que este inplica, desta forma poupamos recursos
 * 
 * @param lista Recebe como argumento a lista de Expressões daquela linha
 * @param tamLista Tamanho da lista de expressões
*/
void AlgoritmoHorn(Expressao *lista, int tamLista)
{
    //Inicialização da lista utilizada para fazer o algoritmo de Horn, o TOP em código pode ser omitido
    //Desta forma ele já está imbutido na lista mesmo que esta esteja vazia
    char *listaHorn = malloc(1);
    int tamHorn = 0;

    //1º passo -> Colocar todos os que Top implica dentro da lista
    for(int i=0; i<tamLista; i++)
    {
        if(lista[i].tamNegativos == 0)
        {
            tamHorn++;
            listaHorn = realloc(listaHorn, tamHorn * sizeof(char));
            //Como só pode existir um positivo é seguro adicionar esse mesmo positivo
            listaHorn[tamHorn-1] = lista[i].Positivos[0];
        }
    }

    //2º passo -> Colocar todos aqueles que sejam implicados pelos elementos da listaHorn
    
    //A variável tomHornInicial vai ser comparada com o tamHorn para ver se houve alteração
    int tamHornInicial = 0;

    //Se não houver quaisquer alterações no tamamnho sair do while pois significa que já não
    //é possivel realizar mais nenhuma operação
    //Enquanto for diferente adiciona aqueles pela qual os elementos de listaHorn implicam
    while(tamHorn != tamHornInicial)
    {
        tamHornInicial = tamHorn;

        //Vai percorrer a lista para verificar se é possivel adicionar á listaHorn usando a função estaContido
        for(int i=0;i<tamLista; i++)
        {
            //Se está contido adicionar o positivo
            if(estaContido(listaHorn, tamHorn, lista[i].Negativos, lista[i].tamNegativos) == 1 && existeNaLista(listaHorn, lista[i].Positivos[0], tamHorn) == 0)
            {
                //Se tiver 1 positivo significa que se adiciona esse positivo à lista
                if(lista[i].tamPositivos == 1)
                {
                    tamHorn++;
                    listaHorn = realloc(listaHorn, tamHorn * sizeof(char));
                    //Como só pode existir um positivo é seguro adicionar esse mesmo positivo
                    listaHorn[tamHorn-1] = lista[i].Positivos[0];
                }
                //Se tiver 0 significa que esse negativo implica bottom, nesse caso deve-se adicionar o bottom á lista e sair 
                //imediatamente do loop e escrever no ecra "UNSAT"
                else
                {
                    tamHorn++;
                    listaHorn = realloc(listaHorn, tamHorn * sizeof(char));
                    //Como só pode existir um positivo é seguro adicionar esse mesmo positivo
                    listaHorn[tamHorn-1] = '_';
                    break;
                }
            }
        }  
        
        //Se o último for um bottom sair imediatamente do loop
        if(listaHorn[tamHorn-1] == '_')
            break;
    }

    //Se o último elemento da listaHorn for um bottom ('_') escrever UNSAT, senão escrever SAT
    if(listaHorn[tamHorn-1] == '_')
    {
        printf("UNSAT\n");
    }
    else
    {
        printf("SAT\n");
    }

    //Libertar a memória do listaHorn de forma que não hajam quaisquer memory leeks
    free(listaHorn);     
}

int main()
{
    /*Aqui são inicializados os buffers necessários para fazer o algoritmo
    linha -> Este buffer irá conter toda a informação da linha que lemos do input
    lista -> É um array do tipo Expressao que irá conter todas as expressões do tipo ( a | ~b | c) da linha
            divididas em literais negativos e positivos 
    */
    char *linha = malloc(60000); 
    Expressao *lista = malloc(1);

    //Esta variável contém o tamanho da lista, útil para no que as operações que envolvam a lista sejam otimizadas em número de iterações
    int tamLista;

    //Este while irá ler linha a linha do ficheiro dado como input
    while(fgets(linha, 60000, stdin))
    {
        //Organiza a linha recebida por input numa estrutura 
        tamLista = DesfragmentarLinha(linha,&lista); 

        //Se por acaso alguma das expressoes da lista tiver mais do que um positivo deve printar NA e saltar para a próxima iteração, não entrando no AlgoritmoHorn
        if(verificarPositivos(lista, tamLista) == 1)
        {
            printf("NA\n");
            tamLista = reset(&lista);
            continue;
        }
        
        //Aplica o algoritmo de Horn
        AlgoritmoHorn(lista, tamLista);
        
        //Dá reset na lista e no seu tamanho para ser reutilizado
        tamLista = reset(&lista);
    }

    //No final de tudo dá-se free à lista para precaver quaisquer memory leeks
    free(lista);
    return 0;
}