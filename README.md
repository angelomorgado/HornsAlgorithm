# Trabalho prático lógica computacional - Algoritmo de Horn 
## Trabalho realizado por: 
- Ângelo Morgado, a43855
- Manuel Carvalho, a43760


# Problema:

Aplicar o algoritmo de Horn como foi dado nas aulas. Para isso foi utilizado C (standart C99) e 
para compilar foi utilizado gcc -o main main.c -Wall -std=c99 -lm.

# Algoritmo:
## Introdução ao problema

O algoritmo de Horn consiste em pegar numa fórmula na forma FNC e verificar se essa fórmula é satisfazivel, para ver isso, é criada uma lista auxiliar que se vai completando até chegar ao bottom, se não for satisfazivel, e, se não chegar ao bottom, é satisfazivel.

## 1ºpasso -  Tratar do input dado

Para tratar do input que foi recebido como argumento utilizou-se um ciclo while que lê linha a linha, ou seja, fórmula a fórmula (já que foi desta forma que o input foi dado).Após termos a linha, é necessário tratar de cada um dos conjuntos de disjunções, e, para saber isso, verificamos que cada um dos conjuntos de disjunções começa pelo caracter '(', essa é chave para saber em qual estamos. após isso, verificamos quais os literais negativos e positivos e colocamos numa estrutura do tipo Expressão juntamente com o número de literais positivos e negativos nessa estrutura. Após isso adiciona-se todas as expressões organizadas num array de expressões.

## 2ºpasso - Verificar se a formula é NA ou válida

Verificamos se alguma expressão da fórmula tem mais do que um literal, se tiver, é NA e salta a iteração com um continue, senão prossegue-se com o algoritmo.

## 3ºpasso - Aplicar o algoritmo

Para aplicar um algoritmo é criada uma lista vazia que vai ser a lista que vamos completar para saber se  fórmula é SAT ou UNSAT. NOTA: a lista contém inicialmente o TOP, porém não é necessário este ser existente pois tê-lo na lista não é obrigatório no código.
Num primeiro ciclo vamos preencher a lista com aqueles que são implicados por TOP, ou seja, aqueles que só tinha um positivo e adicionava-se.
Após isso vai se precorrer a lista quantas vezes forem necessárias verificar quais fórmulas eram implicadas por elementos da lista. Para isso foi utilizado um while inteligente, que verifica o tamanho da lista e se no final dessa iteração, o tamanho não mexeu, significa que não é possivel fazer mais nada e sai do while, porém se encontrar o bottom (representado pelo caracter '_') sai logo do while, ele encontra quando uma expressao só tem literais negativos.
Assim que temos a nossa lista completa, verificamos se o ultimo elemento é um bottom (representado pelo caracter '_'), se for, é UNSAT, senão é SAT.