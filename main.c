#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TrabalhoED1.h"

int main()
{
    srand(time(NULL)); // Gera seeds diferentes para a função rand() na função de inserção

    int i,j,quantidade,opcao,ddd;

    printf("\nQual a quantidade de DDDs que voce deseja inserir?\n");
    scanf("%i",&quantidade);

    ArvAVL *ordenadaNumero[quantidade];
    ArvAVL *ordenadaNome[quantidade];

    Hash* hashOrdenadoNumero=criaHash(MAX);
    Hash* hashOrdenadoNome=criaHash(MAX);

    for(i=0;i<quantidade;i++){
        // Cria as árvores AVL
        ordenadaNumero[i]=cria_ArvAVL();
        ordenadaNome[i]=cria_ArvAVL();
        printf("\nInsira o DDD: \n");
        scanf("%i",&ddd); // DDD inserido na raiz
        // Impede DDD duplicado
        for(j=0;j<i;j++){
            if(consulta_ArvAVL(ordenadaNumero[j],ddd)||consulta_ArvAVL(ordenadaNome[j],ddd)){
                printf("\nEsse DDD ja foi inserido!");
                return 0;
            }
        }
        int teste=insere_ArvAVL_DDD(ordenadaNumero[i],ordenadaNome[i],ddd);
        // Impede DDD inexistente
        if(!teste){
            return 0;
        }
        // Insere as árvores na Tabela Hash
        insereHash_EncadSeparado(hashOrdenadoNumero,ordenadaNumero[i]);
        insereHash_EncadSeparado(hashOrdenadoNome,ordenadaNome[i]);
    }

    printf("\nDDDs inseridos com sucesso.\n");

    imprimirMenu();
    scanf("%d",&opcao);
    while(opcao!=0){
        if(opcao==1){
            system("cls");
            printf("\nInsira o DDD:\n");
            scanf("%d",&ddd);
            // Insere o número ou imprime 3 opções de números não usados em caso de repetição
            opcao1Menu(hashOrdenadoNumero,hashOrdenadoNome,ddd);
        }
        else if(opcao==2){
            system("cls");
            printf("\nInsira o DDD:\n");
            scanf("%d",&ddd);
            // Remove o número das árvores e imprime as alturas de antes e depois da remoção
            opcao2Menu(hashOrdenadoNumero,hashOrdenadoNome,ddd);
        }
        else if(opcao==3){
            system("cls");
            printf("\nInsira o DDD:\n");
            scanf("%d",&ddd);
            // Devolve o nome e endereço do usuário a partir do número de telefone
            opcao3Menu(hashOrdenadoNumero,ddd);
        }
        else if(opcao==4){
            system("cls");
            printf("\nInsira o DDD:\n");
            scanf("%d",&ddd);
            // Lista todos os números de um DDD por 3 percursos
            opcao4Menu(hashOrdenadoNumero,ddd);
        }
        else if(opcao==5){
            system("cls");
            // Gera uma lista telefônica por DDD
            opcao5Menu(ordenadaNumero,ordenadaNome,quantidade);
        }
        else{
            printf("\nOpcao Invalida!\n");
        }
        imprimirMenu2();
        int opcao2;
        scanf("%d",&opcao2);
        if(opcao2){
            system("cls");
            imprimirMenu();
            scanf("%d",&opcao);
        }
        else if(!opcao2){
            break;
        }
    }

    // Libera a memória
    for(i=0;i<quantidade;i++){
        libera_ArvAVL(ordenadaNome[i]);
        libera_ArvAVL(ordenadaNumero[i]);
    }
    liberaHash(hashOrdenadoNumero);
    liberaHash(hashOrdenadoNome);
    return 0;
}
