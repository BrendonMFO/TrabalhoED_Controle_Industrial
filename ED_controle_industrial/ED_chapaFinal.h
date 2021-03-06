#include "ED_imagens.h"

//============================================
// Constantes
//============================================
#define PROCESSANDO 0
#define FINALIZADO  1
//============================================

//============================================
// Estrutura da chapa final de a�o
//============================================
typedef struct s_chapa{
    time_t          tempo_passar_equipamento;
    time_t          horario_de_inicio;
    int             chapa_finalizada;
    struct s_chapa *prox;
}chapa;
//============================================

//============================================
// Estrutura da fila da chapa
//============================================
typedef struct{
    chapa *inicio;
    chapa *fim;
}fila_chapa;
//============================================

//============================================
// Iniciar fila de chapas
//============================================
void iniciar_fila_chapa(fila_chapa *_fila){
    _fila->inicio   = NULL;
    _fila->fim      = NULL;
}
//============================================

//============================================
// Criar chapa
//============================================
chapa *criar_nova_chapa(fila_chapa *_fila){
    chapa *aux = (chapa*)calloc(1, sizeof(chapa));
    if(aux == NULL) return NULL;
    aux->prox = NULL;
    aux->horario_de_inicio = obter_tempo_atual();
    if(!_fila->fim){
        _fila->fim = aux;
        _fila->inicio = aux;
        return aux;
    }
    _fila->fim->prox = aux;
    _fila->fim = aux;
    return aux;
}
//============================================

//============================================
// Transferir chapa para a pilha de chapas concluidas
//============================================
void obter_endereco_para_tranferencia_chapa(chapa *_chapa){
    _chapa->chapa_finalizada = TRUE;
}
//============================================
