#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TrabalhoED1.h"

// Tipo de cada nó na árvore
struct NO{
    struct usuario dados;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz=(ArvAVL*)malloc(sizeof(ArvAVL));
    if(raiz!=NULL)
        *raiz=NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no==NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no=NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz==NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

// Funções auxiliares Árvore AVL

int altura_NO(struct NO* no){
    if(no==NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq)-altura_NO(no->dir));
}

int maior(int x,int y){
    if(x>y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz==NULL)
        return 1;
    if(*raiz==NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz==NULL)
        return 0;
    if (*raiz==NULL)
        return 0;
    int alt_esq=totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir=totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq+alt_dir+1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz==NULL)
        return 0;
    if (*raiz==NULL)
        return 0;
    int alt_esq=altura_ArvAVL(&((*raiz)->esq));
    int alt_dir=altura_ArvAVL(&((*raiz)->dir));

    if (alt_esq>alt_dir)
        return (alt_esq+1);
    else
        return(alt_dir+1);
}

// Verifica se um número recebido está contido na árvore
int consulta_ArvAVL(ArvAVL *raiz, int numero){
    if(raiz==NULL)
        return 0;
    struct NO* atual= *raiz;
    while(atual!=NULL){
        if(numero==atual->dados.numero){
            return 1;
        }
        if(numero>atual->dados.numero)
            atual=atual->dir;
        else
            atual=atual->esq;
    }
    return 0;
}

// Verifica se o número está na árvore e devolve a Struct com informações correspondentes ao número
int consulta_ArvAVL_devolveStruct(ArvAVL *raiz,int numero,struct usuario* us){
    if(raiz==NULL)
        return 0;
    struct NO* atual= *raiz;
    while(atual!=NULL){
        if(numero==atual->dados.numero){
            *us=atual->dados;
            return 1;
        }
        if(numero>atual->dados.numero)
            atual=atual->dir;
        else
            atual=atual->esq;
    }
    return 0;
}

// Consulta a árvore ordenada por nome utilizando strcasecmp() para comparações
int consulta_ArvAVL_porNome(ArvAVL *raiz,char *nome){
    if(raiz==NULL)
        return 0;
    struct NO* atual= *raiz;
    while(atual!=NULL){
        if(strcasecmp(nome,atual->dados.nome)==0){
            return 1;
        }
        if(strcasecmp(nome,atual->dados.nome)>0)
            atual=atual->dir;
        else
            atual=atual->esq;
    }
    return 0;
}

// Imprimir as árvores nos 3 percursos

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        printf("Nome: %s\n",(*raiz)->dados.nome);
        printf("Endereco: %s\n",(*raiz)->dados.endereco);
        printf("Numero: %d\n",(*raiz)->dados.numero);
        printf("\n");
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("Nome: %s\n",(*raiz)->dados.nome);
        printf("Endereco: %s\n",(*raiz)->dados.endereco);
        printf("Numero: %d\n",(*raiz)->dados.numero);
        printf("\n");
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("Nome: %s\n",(*raiz)->dados.nome);
        printf("Endereco: %s\n",(*raiz)->dados.endereco);
        printf("Numero: %d\n",(*raiz)->dados.numero);
        printf("\n");
    }
}

void RotacaoLL(ArvAVL *A){
    struct NO *B;
    B=(*A)->esq;
    (*A)->esq=B->dir;
    B->dir= *A;
    (*A)->altura=maior(altura_NO((*A)->esq),altura_NO((*A)->dir))+1;
    B->altura=maior(altura_NO(B->esq),(*A)->altura)+1;
    *A=B;
}

void RotacaoRR(ArvAVL *A){
    struct NO *B;
    B=(*A)->dir;
    (*A)->dir=B->esq;
    B->esq=(*A);
    (*A)->altura=maior(altura_NO((*A)->esq),altura_NO((*A)->dir))+1;
    B->altura=maior(altura_NO(B->dir),(*A)->altura)+1;
    (*A)=B;
}

void RotacaoLR(ArvAVL *A){
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

// Inserção por ordenação numérica
int insere_ArvAVL(ArvAVL *raiz, struct usuario us){
    int res;
    if(*raiz==NULL){
        struct NO *novo;
        novo=(struct NO*)malloc(sizeof(struct NO));
        if(novo==NULL)
            return 0;
        novo->dados=us;
        novo->altura=0;
        novo->esq=NULL;
        novo->dir=NULL;
        *raiz=novo;
        return 1;
    }
    struct NO *atual = *raiz;
    if(us.numero<atual->dados.numero){
        if((res = insere_ArvAVL(&(atual->esq), us)) == 1){
            if(fatorBalanceamento_NO(atual)>=2){
                if(us.numero<(*raiz)->esq->dados.numero ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(us.numero>atual->dados.numero){
            if((res=insere_ArvAVL(&(atual->dir),us)) == 1){
                if(fatorBalanceamento_NO(atual)>=2){
                    if((*raiz)->dir->dados.numero<us.numero){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }
    atual->altura=maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;
    return res;
}

// Inserção por ordem alfabética com strcasecmp()
int insere_ArvAVL_porNome(ArvAVL *raiz, struct usuario us){
    int res;
    if(*raiz==NULL){
        struct NO *novo;
        novo=(struct NO*)malloc(sizeof(struct NO));
        if(novo==NULL)
            return 0;
        novo->dados=us;
        novo->altura=0;
        novo->esq=NULL;
        novo->dir=NULL;
        *raiz=novo;
        return 1;
    }
    struct NO *atual = *raiz;
    if(strcasecmp(us.nome,atual->dados.nome)<0){
        if((res = insere_ArvAVL_porNome(&(atual->esq), us)) == 1){
            if(fatorBalanceamento_NO(atual)>=2){
                if(strcasecmp(us.nome,(*raiz)->esq->dados.nome)<0){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(strcasecmp(us.nome,atual->dados.nome)>0){
            if((res=insere_ArvAVL_porNome(&(atual->dir),us)) == 1){
                if(fatorBalanceamento_NO(atual)>=2){
                    if(strcasecmp((*raiz)->dir->dados.nome,us.nome)<0){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }
    atual->altura=maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;
    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1=atual;
    struct NO *no2=atual->esq;
    while(no2!=NULL){
        no1=no2;
        no2=no2->esq;
    }
    return no1;
}

// Remoção por comparação numérica
int remove_ArvAVL(ArvAVL *raiz, struct usuario us){
	if(*raiz==NULL){
	    return 0;
	}
    int res=0;
	if(us.numero<(*raiz)->dados.numero){
	    if((res=remove_ArvAVL(&(*raiz)->esq,us)) == 1){
            if(fatorBalanceamento_NO(*raiz)>=2){
                if(altura_NO((*raiz)->dir->esq)<=altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}
	if((*raiz)->dados.numero<us.numero){
	    if((res=remove_ArvAVL(&(*raiz)->dir,us)) == 1){
            if(fatorBalanceamento_NO(*raiz)>=2){
                if(altura_NO((*raiz)->esq->dir)<= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}
	if((*raiz)->dados.numero==us.numero){
	    if(((*raiz)->esq==NULL||(*raiz)->dir==NULL)){
			struct NO *oldNode=(*raiz);
			if((*raiz)->esq!=NULL)
                *raiz=(*raiz)->esq;
            else
                *raiz=(*raiz)->dir;
			free(oldNode);
		}else {
			struct NO* temp=procuraMenor((*raiz)->dir);
			(*raiz)->dados.numero=temp->dados.numero;
			remove_ArvAVL(&(*raiz)->dir,(*raiz)->dados);
            if(fatorBalanceamento_NO(*raiz)>=2){
				if(altura_NO((*raiz)->esq->dir)< altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz!=NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}
	(*raiz)->altura=maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
	return res;
}

// Remoção por comparação de nomes
int remove_ArvAVL_porNome(ArvAVL *raiz,struct usuario us){
if(*raiz==NULL){
	    return 0;
	}
    int res=0;
	if(strcasecmp(us.nome,(*raiz)->dados.nome)<0){
	    if((res=remove_ArvAVL_porNome(&(*raiz)->esq,us)) == 1){
            if(fatorBalanceamento_NO(*raiz)>=2){
                if(altura_NO((*raiz)->dir->esq)<=altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}
	if(strcasecmp((*raiz)->dados.nome,us.nome)<0){
	    if((res=remove_ArvAVL_porNome(&(*raiz)->dir,us)) == 1){
            if(fatorBalanceamento_NO(*raiz)>=2){
                if(altura_NO((*raiz)->esq->dir)<= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}
	if(strcasecmp((*raiz)->dados.nome,us.nome)==0){
	    if(((*raiz)->esq==NULL||(*raiz)->dir==NULL)){
			struct NO *oldNode=(*raiz);
			if((*raiz)->esq!=NULL)
                *raiz=(*raiz)->esq;
            else
                *raiz=(*raiz)->dir;
			free(oldNode);
		}else {
			struct NO* temp=procuraMenor((*raiz)->dir);
			strcpy((*raiz)->dados.nome,temp->dados.nome);
			remove_ArvAVL_porNome(&(*raiz)->dir,(*raiz)->dados);
            if(fatorBalanceamento_NO(*raiz)>=2){
				if(altura_NO((*raiz)->esq->dir)< altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz!=NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}
	(*raiz)->altura=maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
	return res;
}

// Insere o DDD nas árvores ordenadas por nome e número
int insere_ArvAVL_DDD(ArvAVL *raiz, ArvAVL *raiz2,int ddd){
    // Compara o DDD recebido com todos os DDDs do Brasil
    // Insere uma Struct contendo a sua macroregião e estado nas árvores
	switch(ddd){
        case 11:
            {
            struct usuario dddDados={11,"Sao Paulo","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 12:
            {
            struct usuario dddDados={12,"Sao Jose dos Campos","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 13:
            {
            struct usuario dddDados={13,"Santos","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 14:
            {
            struct usuario dddDados={14,"Bauru","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 15:
            {
            struct usuario dddDados={15,"Sorocaba","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 16:
            {
            struct usuario dddDados={16,"Ribeirao Preto","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 17:
            {
            struct usuario dddDados={17,"Sao Jose do Rio Preto","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 18:
            {
            struct usuario dddDados={18,"Presidente Prudente","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 19:
            {
            struct usuario dddDados={19,"Campinas","Sao Paulo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 21:
            {
            struct usuario dddDados={21,"Rio de Janeiro","Rio de Janeiro"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 22:
            {
            struct usuario dddDados={22,"Campos dos Goytacazes","Rio de Janeiro"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 24:
            {
            struct usuario dddDados={24,"Volta Redonda","Rio de Janeiro"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 27:
            {
            struct usuario dddDados={27,"Vitoria / Vila Velha","Espirito Santo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 28:
            {
            struct usuario dddDados={28,"Cachoeiro de Itapemirim","Espirito Santo"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 31:
            {
            struct usuario dddDados={31,"Belo Horizonte","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 32:
            {
            struct usuario dddDados={32,"Juiz de Fora","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 33:
            {
            struct usuario dddDados={33,"Governador Valadares","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 34:
            {
            struct usuario dddDados={34,"Uberlandia","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 35:
            {
            struct usuario dddDados={35,"Pocos de Caldas","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 37:
            {
            struct usuario dddDados={37,"Divinopolis","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
         case 38:
            {
            struct usuario dddDados={38,"Montes Claros","Minas Gerais"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 41:
            {
            struct usuario dddDados={41,"Curitiba","Parana"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 42:
            {
            struct usuario dddDados={42,"Ponta Grossa","Parana"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 43:
            {
            struct usuario dddDados={43,"Londrina","Parana"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 44:
            {
            struct usuario dddDados={44,"Maringa","Parana"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 45:
            {
            struct usuario dddDados={45,"Foz do Iguacu","Parana"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 46:
            {
            struct usuario dddDados={46,"Pato Branco / Francisco Beltrao ","Parana"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 47:
            {
            struct usuario dddDados={47,"Joinville","Santa Catarina"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 48:
            {
            struct usuario dddDados={48,"Florianopolis","Santa Catarina"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 49:
            {
            struct usuario dddDados={49,"Chapeco","Santa Catarina"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 51:
            {
            struct usuario dddDados={51,"Porto Alegre","Rio Grande do Sul"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 53:
            {
            struct usuario dddDados={53,"Pelotas","Rio Grande do Sul"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 54:
            {
            struct usuario dddDados={54,"Caxias do Sul","Rio Grande do Sul"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 55:
            {
            struct usuario dddDados={55,"Santa Maria","Rio Grande do Sul"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 61:
            {
            struct usuario dddDados={61,"Brasilia","Distrito Federal"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 62:
            {
            struct usuario dddDados={62,"Goiania","Goias"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 63:
            {
            struct usuario dddDados={63,"Palmas","Tocantins"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 64:
            {
            struct usuario dddDados={64,"Rio Verde","Goias"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 65:
            {
            struct usuario dddDados={65,"Cuiaba","Mato Grosso"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 66:
            {
            struct usuario dddDados={66,"Rondonopolis","Mato Grosso"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 67:
            {
            struct usuario dddDados={67,"Campo Grande","Mato Grosso do Sul"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 68:
            {
            struct usuario dddDados={68,"Rio Branco","Acre"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 69:
            {
            struct usuario dddDados={69,"Porto Velho","Rondonia"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 71:
            {
            struct usuario dddDados={71,"Salvador","Bahia"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 73:
            {
            struct usuario dddDados={73,"Ilheus","Bahia"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 74:
            {
            struct usuario dddDados={74,"Juazeiro","Bahia"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 75:
            {
            struct usuario dddDados={75,"Feira de Santana","Bahia"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 77:
            {
            struct usuario dddDados={77,"Barreiras","Bahia"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 79:
            {
            struct usuario dddDados={79,"Aracaju","Sergipe"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 81:
            {
            struct usuario dddDados={81,"Recife","Pernambuco"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 82:
            {
            struct usuario dddDados={82,"Maceio","Alagoas"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 83:
            {
            struct usuario dddDados={83,"Joao Pessoa","Paraiba"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 84:
            {
            struct usuario dddDados={84,"Natal","Rio Grande do Norte"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 85:
            {
            struct usuario dddDados={85,"Fortaleza","Ceara"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 86:
            {
            struct usuario dddDados={86,"Teresina","Piaui"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 87:
            {
            struct usuario dddDados={87,"Petrolina","Pernambuco"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 88:
            {
            struct usuario dddDados={88,"Juazeiro do Norte","Ceara"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 89:
            {
            struct usuario dddDados={89,"Picos","Piaui"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 91:
            {
            struct usuario dddDados={91,"Belem","Para"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 92:
            {
            struct usuario dddDados={92,"Manaus","Amazonas"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 93:
            {
            struct usuario dddDados={93,"Santarem","Para"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 94:
            {
            struct usuario dddDados={94,"Maraba","Para"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 95:
            {
            struct usuario dddDados={95,"Boa Vista","Roraima"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 96:
            {
            struct usuario dddDados={96,"Macapa","Amapa"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 97:
            {
            struct usuario dddDados={97,"Coari","Amazonas"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 98:
            {
            struct usuario dddDados={98,"Sao Luis","Maranhao"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        case 99:
            {
            struct usuario dddDados={99,"Imperatriz","Maranhao"};
            insere_ArvAVL(raiz,dddDados);
            insere_ArvAVL_porNome(raiz2,dddDados);
            return 1;
            }
        default:
            printf("\nDDD inexistente no Brasil! \n");
            return 0;
            }
}

// Retorna um número gerado aleatoriamente
// A segunda parte do número será igual a primeira
int geradorNumero8Digitos(){
    int parte1= 1000+(rand()%9000);
    int parte2= 1000+(rand()%9000);
    char parte1string[4];
    char parte2string[4];
    sprintf(parte1string, "%i", parte1);
    sprintf(parte2string, "%i", parte2);
    strcat(parte1string,parte2string);
    int numero=atoi(parte1string);
    return numero;
}

// Insere o usuário nas árvores ordenadas por nome e número
int insere_ArvAVL_semRepeticao(ArvAVL *raiz, ArvAVL *raiz2,int numero){
    char nome[200], endereco[200];
    if(!consulta_ArvAVL(raiz,numero)){
            struct usuario novo;
            novo.numero=numero;
            printf("\nInsira o nome:\n");
            fflush(stdin);
            gets(nome);
            while(consulta_ArvAVL_porNome(raiz2,nome)){
                printf("\nEsse nome ja foi utilizado! Insira outro:\n");
                gets(nome);
            }
            strcpy(novo.nome,nome);
            printf("\nInsira o endereco:\n");
            fflush(stdin);
            gets(endereco);
            strcpy(novo.endereco,endereco);
            insere_ArvAVL(raiz,novo);
            insere_ArvAVL_porNome(raiz2,novo);
            printf("\nNumero inserido com sucesso!\n");
            return 1;
    }
    else{
        // Imprime 3 opções de números aleatórios em caso de repetição
        printf("\nEsse numero ja existe! Escolha um desses 3:\n");
        int opcao,opcao1, opcao2, opcao3;
        do
        {
            opcao1=geradorNumero8Digitos();
        } while (opcao1==numero);
        do
        {
            opcao2=geradorNumero8Digitos();
        } while (opcao2==numero&&opcao2==opcao1);
        do
        {
            opcao3=geradorNumero8Digitos();
        } while (opcao3==numero&&opcao3==opcao1&&opcao3==opcao2);
        printf("(1) - %d\n",opcao1);
        printf("\n(2) - %d\n",opcao2);
        printf("\n(3) - %d\n",opcao3);
        printf("\nInsira a opcao referente ao numero desejado:\n");
        scanf("%d",&opcao);
        while(opcao!=1&&opcao!=2&&opcao!=3){
            printf("\nAs opcoes validas sao 1, 2 ou 3.\n");
            scanf("%d",&opcao);
        }
        if(opcao==1){
            struct usuario novo;
            novo.numero=opcao1;
            printf("\nInsira o nome:\n");
            fflush(stdin);
            gets(nome);
            while(consulta_ArvAVL_porNome(raiz2,nome)){
                printf("\nEsse nome ja foi utilizado! Insira outro:\n");
                gets(nome);
            }
            strcpy(novo.nome,nome);
            printf("\nInsira o endereco:\n");
            fflush(stdin);
            gets(endereco);
            strcpy(novo.endereco,endereco);
            insere_ArvAVL(raiz,novo);
            insere_ArvAVL_porNome(raiz2,novo);
            printf("\nNumero inserido com sucesso!\n");
            return 1;
        }
        else if(opcao==2){
            struct usuario novo;
            novo.numero=opcao2;
            printf("\nInsira o nome:\n");
            fflush(stdin);
            gets(nome);
            while(consulta_ArvAVL_porNome(raiz2,nome)){
                printf("\nEsse nome ja foi utilizado! Insira outro:\n");
                gets(nome);
            }
            strcpy(novo.nome,nome);
            printf("\nInsira o endereco:\n");
            fflush(stdin);
            gets(endereco);
            strcpy(novo.endereco,endereco);
            insere_ArvAVL(raiz,novo);
            insere_ArvAVL_porNome(raiz2,novo);
            printf("\nNumero inserido com sucesso!\n");
            return 1;
        }
        else if(opcao==3){
            struct usuario novo;
            novo.numero=opcao3;
            printf("\nInsira o nome:\n");
            fflush(stdin);
            gets(nome);
            while(consulta_ArvAVL_porNome(raiz2,nome)){
                printf("\nEsse nome ja foi utilizado! Insira outro:\n");
                gets(nome);
            }
            strcpy(novo.nome,nome);
            printf("\nInsira o endereco:\n");
            fflush(stdin);
            gets(endereco);
            strcpy(novo.endereco,endereco);
            insere_ArvAVL(raiz,novo);
            insere_ArvAVL_porNome(raiz2,novo);
            printf("\nNumero inserido com sucesso!\n");
            return 1;
        }
    }
    return 0;
}

int remove_mostraAltura_ArvAVL(ArvAVL *raiz, ArvAVL *raiz2,int numero){
    struct usuario remocao;
    int consulta=consulta_ArvAVL_devolveStruct(raiz,numero,&remocao);
    if(consulta){
        printf("\nAltura da arvore ordenada por numero antes: %i\n",altura_ArvAVL(raiz));
        printf("\nAltura da arvore ordenada por nome antes: %i\n",altura_ArvAVL(raiz2));
        remove_ArvAVL(raiz,remocao);
        remove_ArvAVL_porNome(raiz2,remocao);
        printf("\n----------------------------------------------------------\n");
        printf("\n              Numero removido com sucesso!\n");
        printf("\n----------------------------------------------------------\n");
        printf("\nAltura da arvore ordenada por numero depois: %i\n",altura_ArvAVL(raiz));
        printf("\nAltura da arvore ordenada por nome depois: %i\n",altura_ArvAVL(raiz2));
        return 1;
    }
    else{
        printf("\nAltura da arvore ordenada por numero antes: %i\n",altura_ArvAVL(raiz));
        printf("\nAltura da arvore ordenada por nome antes: %i\n",altura_ArvAVL(raiz2));
        printf("\n----------------------------------------------------------\n");
        printf("\n              Esse numero nao existe na arvore!\n");
        printf("\n----------------------------------------------------------\n");
        printf("\nAltura da arvore ordenada por numero depois: %i\n",altura_ArvAVL(raiz));
        printf("\nAltura da arvore ordenada por nome depois: %i\n",altura_ArvAVL(raiz2));
        return 1;
    }
    return 0;
}

//Funções Lista

struct elemento{
    int ddd;
    ArvAVL *raiz;
    struct elemento *prox;
};

typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li=(Lista*)malloc(sizeof(Lista));
    if(li!=NULL)
        *li=NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li!=NULL){
        Elem* no;
        while((*li)!=NULL){
            no=*li;
            *li=(*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, ArvAVL *raiz){
    if(li==NULL)
        return 0;
    Elem *no=(Elem*)malloc(sizeof(Elem));
    if(no==NULL)
        return 0;
    no->ddd=(*raiz)->dados.numero;
    no->raiz=raiz;
    no->prox=NULL;
    // Insere a árvore no começo da lista caso esteja vazia
    if((*li)==NULL){
        *li=no;
    }
    // Caso contrário, insere no final
    else{
        Elem *aux=*li;
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        aux->prox=no;
    }
    return 1;
}

int consulta_lista_posicao(Lista* li,int pos,ArvAVL **raiz){
    if(li==NULL||pos<=0)
        return 0;
    Elem *no=*li;
    int i=1;
    while(no!=NULL&&i<pos){
        no=no->prox;
        i++;
    }
    if(no==NULL)
        return 0;
    else{
        *raiz=no->raiz;
        return 1;
    }
}

int consulta_lista_numero(Lista* li, int numero, ArvAVL **raiz){
    if(li==NULL)
        return 0;
    Elem *no=*li;
    while(no!=NULL&&no->ddd!=numero){
        no=no->prox;
    }
    if(no==NULL)
        return 0;
    else{
        *raiz=no->raiz;
        return 1;
    }
}

int tamanho_lista(Lista* li){
    if(li==NULL)
        return 0;
    int cont=0;
    Elem* no=*li;
    while(no!=NULL){
        cont++;
        no=no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li==NULL)
        return 1;
    if(*li==NULL)
        return 1;
    return 0;
}

// Funções Tabela Hash

struct hash{
    int qtd,TABLE_SIZE;
    Lista **lista; // Cada posição da tabela é uma lista
};

Hash* criaHash(int TABLE_SIZE){
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha!=NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->lista= (Lista**)malloc(TABLE_SIZE * (sizeof(Lista*)));
        if(ha->lista==NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(i=0;i<ha->TABLE_SIZE;i++)
            ha->lista[i]=cria_lista();
    }
    return ha;
}

void liberaHash(Hash* ha){
    if(ha!=NULL){
        int i;
        for(i=0;i<ha->TABLE_SIZE; i++){
            if(ha->lista[i] != NULL)
                free(ha->lista[i]);
        }
        free(ha->lista);
        free(ha);
    }
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF)%TABLE_SIZE;
}

int insereHash_EncadSeparado(Hash* ha, ArvAVL *raiz){
    if(ha==NULL||ha->qtd>ha->TABLE_SIZE)
        return 0;
    int ddd=(*raiz)->dados.numero; // Cálculo da chave a partir do DDD
    int pos=chaveDivisao(ddd,ha->TABLE_SIZE);
    //Insere a Árvore na Lista correspondente à posição da Tabela
    if(lista_vazia(ha->lista[pos])){
        insere_lista_final(ha->lista[pos],raiz);
        ha->qtd++;
        return 1;
    }
    else{
        insere_lista_final(ha->lista[pos],raiz);
        return 1;
    }
    return 0;
}

int buscaHash_EncadSeparado(Hash* ha, int ddd, ArvAVL **raiz){
    if(ha==NULL)
        return 0;
    int pos=chaveDivisao(ddd,ha->TABLE_SIZE);
        if(lista_vazia(ha->lista[pos])){
            return 0;
        }
        else{
            int teste=consulta_lista_numero(ha->lista[pos],ddd,raiz);
            if(teste)
                return 1;
            }
    return 0;
}

// Funções Conjuntas

void imprimirMenu(){
    printf("\nO que voce deseja fazer?\n");
    printf("\n|---------------------------------------------------------|\n");
    printf("|                                                         |\n");
    printf("|            ( 1 ) Inserir numero de telefone             |\n");
    printf("|                                                         |\n");
    printf("|            ( 2 ) Remover numero de telefone             |\n");
    printf("|                                                         |\n");
    printf("|            ( 3 ) Buscar numero de telefone              |\n");
    printf("|                                                         |\n");
    printf("|            ( 4 ) Mostrar numeros por DDD                |\n");
    printf("|                                                         |\n");
    printf("|            ( 5 ) Mostrar lista telefonica completa      |\n");
    printf("|                                                         |\n");
    printf("|            ( 0 ) Sair                                   |\n");
    printf("|                                                         |\n");
    printf("|---------------------------------------------------------|\n");
    printf("\nInsira a opcao:\n");
}

void imprimirMenu2(){
    printf("\nImprimir menu novamente?\n");
    printf("\n|---------------------------|\n");
    printf("|                           |\n");
    printf("|        ( 1 ) Sim          |\n");
    printf("|                           |\n");
    printf("|        ( 0 ) Nao          |\n");
    printf("|                           |\n");
    printf("|---------------------------|\n");
    printf("\nInsira a opcao:\n");
}

void opcao1Menu(Hash *hashAVLNumero, Hash *hashAVLNome, int ddd){
    int numeroTelefone;
    ArvAVL *numero,*nome;
    numero=cria_ArvAVL();
    nome=cria_ArvAVL();
    int teste=buscaHash_EncadSeparado(hashAVLNumero,ddd,&numero);
    int teste2=buscaHash_EncadSeparado(hashAVLNome,ddd,&nome);
    if(teste&&teste2){
        printf("\nInsira o numero de 8 digitos:\n");
        char numeroTelefoneString[10];
        do
        {
            scanf("%10s", numeroTelefoneString);
            if(strnlen(numeroTelefoneString, 10) != 8)
            {
                printf("\nEsse numero nao possui 8 digitos!\n");
                printf("\nInsira o numero de 8 digitos:\n");
            }
        }while(strlen(numeroTelefoneString)!= 8);
        numeroTelefone=atoi(numeroTelefoneString);
        insere_ArvAVL_semRepeticao(numero,nome,numeroTelefone);
    }
    else{
        printf("\nEsse DDD nao foi inserido previamente!\n");
    }
}

void opcao2Menu(Hash *hashAVLNumero, Hash *hashAVLNome, int ddd){
    int numeroTelefone;
    ArvAVL *numero;
    ArvAVL *nome;
    numero=cria_ArvAVL();
    nome=cria_ArvAVL();
    int teste=buscaHash_EncadSeparado(hashAVLNumero,ddd,&numero);
    int teste2=buscaHash_EncadSeparado(hashAVLNome,ddd,&nome);
    if(teste&&teste2){
        printf("\nInsira o numero:\n");
        scanf("%i",&numeroTelefone);
        remove_mostraAltura_ArvAVL(numero,nome,numeroTelefone);
    }
    else{
        printf("\nEsse DDD nao foi inserido previamente!\n");
    }
}

void opcao3Menu(Hash *hashAVLNumero, int ddd){
    int numeroTelefone;
    ArvAVL *numero;
    numero=cria_ArvAVL();
    int teste=buscaHash_EncadSeparado(hashAVLNumero,ddd,&numero);
    if(teste){
        printf("\nInsira o numero:\n");
        scanf("%d",&numeroTelefone);
        struct usuario dados;
        int teste2=consulta_ArvAVL_devolveStruct(numero,numeroTelefone,&dados);
        if(teste2){
            printf("\nAqui esta o usuario buscado:\n\n");
            printf("Nome: %s\n",dados.nome);
            printf("Endereco: %s\n",dados.endereco);
            printf("Numero: %d\n",dados.numero);
        }
        else{
            printf("\nNao ha nenhum usuario com esse numero!\n");
        }
    }
    else{
        printf("\nEsse DDD nao foi inserido previamente!\n");
    }
}

void opcao4Menu(Hash *hashAVLNumero, int ddd){
    ArvAVL *numero;
    numero=cria_ArvAVL();
    int teste=buscaHash_EncadSeparado(hashAVLNumero,ddd,&numero);
    if(teste){
    printf("\n==========================================================\n");
    printf("    Percurso Pre-Ordem   ");
    printf("\n==========================================================\n");
    printf("\n----------------------------------------------------------\n");
    preOrdem_ArvAVL(numero);
    printf("----------------------------------------------------------\n");

    printf("\n==========================================================\n");
    printf("    Percurso Em-Ordem   ");
    printf("\n==========================================================\n");
    printf("\n----------------------------------------------------------\n");
    emOrdem_ArvAVL(numero);
    printf("----------------------------------------------------------\n");

    printf("\n==========================================================\n");
    printf("    Percurso Pos-Ordem   ");
    printf("\n==========================================================\n");
    printf("\n----------------------------------------------------------\n");
    posOrdem_ArvAVL(numero);
    printf("----------------------------------------------------------\n");
    }
    else{
        printf("\nEsse DDD nao foi inserido previamente!\n");
    }
}

void opcao5Menu(ArvAVL *raiz[], ArvAVL *raiz2[], int quantidade){
    printf("\n==========================================================\n");
    printf("    Lista telefonica ordenada por numero de telefone");
    printf("\n==========================================================\n");
    for(int i=0;i<quantidade;i++){
        printf("\n----------------------------------------------------------\n");
        emOrdem_ArvAVL(raiz[i]);
        printf("----------------------------------------------------------\n");
    }
    printf("\n==========================================================\n");
    printf("    Lista telefonica ordenada por nome do usuario");
    printf("\n==========================================================\n");
    for(int i=0;i<quantidade;i++){
        printf("\n----------------------------------------------------------\n");
        emOrdem_ArvAVL(raiz2[i]);
        printf("----------------------------------------------------------\n");
    }
}
