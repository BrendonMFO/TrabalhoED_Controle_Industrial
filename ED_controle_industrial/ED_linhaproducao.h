#include "ED_equipamentos.h"

//=====================================================
// Globais de controle
//=====================================================
int Quantidade_de_Linhas = 0;
//=====================================================

//=================================================
// Estrutura de dados da linha de produção
//=================================================
typedef struct s_linha{
    char              *nome;
    pilha_equipamento  equipamentos;
    fila_chapa         chapas;
    struct s_linha    *prox;
}linha;
//=================================================

//=================================================
//Pilha de linhas de produção
//=================================================
typedef struct lista_linha_de_producao{
    linha *topo
}linha_producao;
//=================================================

//=================================================
// Iniciar pilha de produção
//=================================================
void iniciar_pilha_producao(linha_producao *_producao){
    _producao->topo = NULL;
}
//=================================================

//=================================================
// Adicionar nova linha de produção
//=================================================
int criar_nova_linha(linha_producao *_producao, char *_nome, int _n_equipamentos, ...){
    linha *aux = (linha*)calloc(1, sizeof(linha));
    if(!aux) return FALSE;
    iniciar_pilha_de_equipamento(&aux->equipamentos);
    iniciar_fila_chapa(&aux->chapas);
    if(_n_equipamentos > 0){
        va_list lista_de_equipamentos;
        int contador;
        va_start(lista_de_equipamentos, _n_equipamentos);
        for(contador = 0; contador < _n_equipamentos; contador++){
            equipamento *temp = va_arg(lista_de_equipamentos, equipamento*);
            if(temp == NULL) return FALSE;
            temp->Prox = aux->equipamentos.topo;
            aux->equipamentos.topo = temp;
        }
        va_end(lista_de_equipamentos);
    }
    aux->prox       = _producao->topo;
    _producao->topo = aux;
    aux->nome       = _nome;
    Quantidade_de_Linhas++;
    return TRUE;
}
//=================================================
