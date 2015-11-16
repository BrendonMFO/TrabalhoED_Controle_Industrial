#include "ED_eventos.h"

//================================================================
// Carregar botoes
//================================================================
void carregar_equipamentos(equipamento *_equipamentos, int posicao_X, int posicao_Y){
    if(_equipamentos != NULL){
        calcular_proporcao_do_botao(&_equipamentos->botao_de_controle, Quantidade_de_Linhas, posicao_X, posicao_Y);
        calcular_proporcao_do_equipamento(_equipamentos, Quantidade_de_Linhas, posicao_X, posicao_Y);
        if(_equipamentos->Prox)
            carregar_equipamentos(_equipamentos->Prox, posicao_X, posicao_Y + 1);
    }
}
//================================================================

//================================================================
// Checar necessidade de novos botoes
//================================================================
int iniciar_equipamentos(linha_producao *_linha_de_producao){
    linha *aux = _linha_de_producao->topo;
    int i = 0;
    while(aux != NULL){
        carregar_equipamentos(aux->equipamentos.topo, i++, 0);
        aux = aux->prox;
    }
    return TRUE;
}
//================================================================

//================================================================
// Criar linhas de produção
//================================================================
int criar_linha_de_producao(linha_producao *_linha_de_producao){
     if(
       !criar_nova_linha(_linha_de_producao, "Linha de producao - Esquerda", 3,
                         criar_novo_equipamento(MODELADOR,  "MODELADOR - Esquerda",  criar_dados(125, 0, 400),  criar_data()),
                         criar_novo_equipamento(FORNO,      "FORNO - Esquerda",      criar_dados(125, 1110, 0), criar_data()),
                         criar_novo_equipamento(TRITURADOR, "TRITURADOR - Esquerda", criar_dados(125, 0, 500),  criar_data())) ||
       !criar_nova_linha(_linha_de_producao, "Linha de producao - Centro", 3,
                         criar_novo_equipamento(MODELADOR,  "MODELADOR - Centro",    criar_dados(125, 0, 700),  criar_data()),
                         criar_novo_equipamento(FORNO,      "FORNO - Centro",        criar_dados(125, 1250, 0), criar_data()),
                         criar_novo_equipamento(TRITURADOR, "TRITURADOR - Centro",   criar_dados(125, 0, 600),  criar_data())) ||
       !criar_nova_linha(_linha_de_producao, "Linha de producao - Direita", 3,
                         criar_novo_equipamento(MODELADOR,  "MODELADOR - Direita",   criar_dados(125, 0, 550),  criar_data()),
                         criar_novo_equipamento(FORNO,      "FORNO - Direita",       criar_dados(125, 1500, 0), criar_data()),
                         criar_novo_equipamento(TRITURADOR, "TRITURADOR - Direita",  criar_dados(125, 0, 600),  criar_data())) ||
        !criar_nova_linha(_linha_de_producao, "Linha de producao - NOVA", 3,
                         criar_novo_equipamento(MODELADOR,  "MODELADOR - NOVA",   criar_dados(125, 0, 550),  criar_data()),
                         criar_novo_equipamento(FORNO,      "FORNO - NOVA",       criar_dados(125, 1500, 0), criar_data()),
                         criar_novo_equipamento(TRITURADOR, "TRITURADOR - NOVA",  criar_dados(125, 0, 600),  criar_data()))
       ) return FALSE;
    return TRUE;
}
//================================================================

//================================================================
// Iniciar eventos de controle do sistema
//================================================================
int iniciar_operacoes_do_sistema(ALLEGRO_DISPLAY *_janela, ALLEGRO_EVENT_QUEUE *_eventos, linha_producao *_linha_de_producao){
    configurar_sockets();
    iniciar_escuta_servidor();
    if(!iniciar_ALLEGRO() ||
       !criar_janela(&_janela, LARGURA_DA_JANELA, ALTURA_DA_JANELA) ||
       !iniciar_mouse_ALLEGRO(&_janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) return -1;
    srand(clock());
    carregar_imagens_do_sistema();
    iniciar_pilha_producao(_linha_de_producao);
    criar_linha_de_producao(_linha_de_producao);
    return iniciar_equipamentos(_linha_de_producao);
}
//================================================================
