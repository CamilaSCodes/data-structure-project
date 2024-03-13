
// Prot�tipos das fun��es

// Tamanho m�ximo da Tabela Hash, o maior DDD do Brasil � 99
#define MAX 101 // Maior numero primo mais pr�ximo de 99

// Informa��es do usu�rio guardadas em cada n� da �rvore
struct usuario{
    int numero;
    char nome[200];
    char endereco[200];
};

// Fun��es �rvore AVL
// raiz: �rvore ordenada por n�mero
// raiz 2: �rvore ordenada por nome

typedef struct NO* ArvAVL;
ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int estaVazia_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
int totalNO_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz,int numero);
int consulta_ArvAVL_devolveStruct(ArvAVL *raiz,int numero,struct usuario *us);
int consulta_ArvAVL_porNome(ArvAVL *raiz,char *nome);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz,struct usuario us);
int insere_ArvAVL_porNome(ArvAVL *raiz,struct usuario us);
int remove_ArvAVL(ArvAVL *raiz,struct usuario us);
int remove_ArvAVL_porNome(ArvAVL *raiz,struct usuario us);
int insere_ArvAVL_DDD(ArvAVL *raiz, ArvAVL *raiz2,int ddd);
int insere_ArvAVL_semRepeticao(ArvAVL *raiz, ArvAVL *raiz2,int numero);
int remove_mostraAltura_ArvAVL(ArvAVL *raiz, ArvAVL *raiz2,int numero);

// Fun��es Lista Din�mica

typedef struct elemento* Lista;
Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
int insere_lista_final(Lista* li, ArvAVL *raiz);
int consulta_lista_posicao(Lista* li,int pos,ArvAVL **raiz);
int consulta_lista_numero(Lista* li, int numero,ArvAVL **raiz);

// Fun��es Tabela Hash

typedef struct hash Hash;
Hash* criaHash(int TABLE_SIZE);
void liberaHash(Hash* ha);
int insereHash_EncadSeparado(Hash* ha, ArvAVL *raiz);
int buscaHash_EncadSeparado(Hash* ha, int ddd, ArvAVL **raiz);

// Fun��es Conjuntas

void imprimirMenu();
void imprimirMenu2();
void opcao1Menu(Hash *hashAVLNumero, Hash *hashAVLNome,int ddd);
void opcao2Menu(Hash *hashAVLNumero, Hash *hashAVLNome,int ddd);
void opcao3Menu(Hash *hashAVLNumero, int ddd);
void opcao4Menu(Hash *hashAVLNumero, int ddd);
void opcao5Menu(ArvAVL *raiz[], ArvAVL *raiz2[], int quantidade);

