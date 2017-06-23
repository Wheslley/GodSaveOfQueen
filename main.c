#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int contadorFilhos=0;

typedef struct tagmembro{
    char nome[64];
    int idade;
    char antecessor_nome[64];
    int vivo_ou_morto;
    int antecessor_indice;
    int primeiro_filho;
    int segundo_filho;
    int terceiro_filho;
} membro;

void init_vet_membros (membro* membroQueen, int qtdArvoreGenetica)
{
    int i=0;

    for(i=0 ; i < qtdArvoreGenetica; i++){

        fflush(stdin);
        scanf("%[^;];%d;%[^;];%d\n", membroQueen[i].nome
                                   , &membroQueen[i].idade
                                   , membroQueen[i].antecessor_nome
                                   , &membroQueen[i].vivo_ou_morto);

        membroQueen[i].antecessor_indice = -1;
        membroQueen[i].primeiro_filho = -1;
        membroQueen[i].segundo_filho = -1;
        membroQueen[i].terceiro_filho = -1;

    }

}

void get_filhos (membro* membroQueen, int qtdArvoreGenetica){

    int i=0, j=0, contador=0;

    for(i=0; i<qtdArvoreGenetica; i++){
        for(j=0; j<qtdArvoreGenetica; j++){
            if(strcmp(membroQueen[i].nome, membroQueen[j].antecessor_nome) == 0){
                membroQueen[i].antecessor_indice = j;
                if(contador==0){
                    membroQueen[i].primeiro_filho = j;
                }else if (contador==1){
                    membroQueen[i].segundo_filho = j;
                }else{
                    membroQueen[i].terceiro_filho = j;
                }
                ++contador;
            }
        }
        contador=0;
    }
}

void ordenar_filhos_idade (membro* membroQueen, int qtdArvoreGenetica){

    int i=0, aux=0;

    system("cls");

    for(i=0; i<qtdArvoreGenetica; i++){

        if((membroQueen[i].primeiro_filho > -1) && (membroQueen[i].segundo_filho > -1)){
            if(membroQueen[membroQueen[i].primeiro_filho].idade < membroQueen[membroQueen[i].segundo_filho].idade){
                aux = membroQueen[i].primeiro_filho;
                membroQueen[i].primeiro_filho = membroQueen[i].segundo_filho;
                membroQueen[i].segundo_filho = aux;
            }
        }

        if((membroQueen[i].terceiro_filho > -1) && (membroQueen[i].primeiro_filho > -1)){
            if(membroQueen[membroQueen[i].primeiro_filho].idade < membroQueen[membroQueen[i].terceiro_filho].idade){
                aux = membroQueen[i].primeiro_filho;
                membroQueen[i].primeiro_filho = membroQueen[i].terceiro_filho;
                membroQueen[i].terceiro_filho = aux;
            }
        }

        if((membroQueen[i].terceiro_filho > -1) && (membroQueen[i].segundo_filho > -1)){
            if(membroQueen[membroQueen[i].segundo_filho].idade < membroQueen[membroQueen[i].terceiro_filho].idade){
                aux = membroQueen[i].segundo_filho;
                membroQueen[i].segundo_filho = membroQueen[i].terceiro_filho;
                membroQueen[i].terceiro_filho = aux;
            }
        }

    }

}

int exibir_filhos(membro* membroQueen, int indice ){

    if (membroQueen[indice].primeiro_filho > -1){
        if(membroQueen[membroQueen[indice].primeiro_filho].vivo_ou_morto==0){
            ++contadorFilhos;
            printf("%d) %s\n", contadorFilhos, membroQueen[membroQueen[indice].primeiro_filho].nome);
        }
        exibir_filhos(membroQueen, membroQueen[indice].primeiro_filho);
    }

    if (membroQueen[indice].segundo_filho > -1){
        if(membroQueen[membroQueen[indice].segundo_filho].vivo_ou_morto==0){
           ++contadorFilhos;
            printf("%d) %s\n", contadorFilhos, membroQueen[membroQueen[indice].segundo_filho].nome);
        }
        exibir_filhos(membroQueen, membroQueen[indice].segundo_filho);
    }

    if (membroQueen[indice].terceiro_filho > -1){
        if(membroQueen[membroQueen[indice].terceiro_filho].vivo_ou_morto==0){
            ++contadorFilhos;
            printf("%d) %s\n", contadorFilhos, membroQueen[membroQueen[indice].terceiro_filho].nome);
        }
        exibir_filhos(membroQueen, membroQueen[indice].terceiro_filho);
    }

}

int main()
{
    int j=0, qtdArvoreGenetica = 0;

    //printf("Total de membros na arvore genealogica (\"God Save of Queen!!\")");
    scanf("%d",&qtdArvoreGenetica);

    membro membroQueen[qtdArvoreGenetica];

    init_vet_membros(&membroQueen, qtdArvoreGenetica);

    get_filhos(&membroQueen, qtdArvoreGenetica);

    ordenar_filhos_idade(&membroQueen, qtdArvoreGenetica);

    exibir_filhos(&membroQueen, 0);

    return 0;
}
