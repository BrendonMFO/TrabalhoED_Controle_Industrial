#include "ED_linhaproducao.h"
#include <windows.h>

//========================================
// Montar string de comunicacao
//========================================
char *string_de_tranferencia(equipamento *_equipamento, char *_nome_linha){
    char string_de_comunicacao[1024];
    memset(string_de_comunicacao, 0, 1024);
    time_t tempo = obter_tempo_atual();
    struct tm *tempo_formato = localtime(&tempo);
    sprintf(string_de_comunicacao, "%s - Horario - %s ", _nome_linha, asctime(tempo_formato));
    return string_de_comunicacao;
}
//========================================

//========================================
// Transferir chapa entre os equipamentos
//========================================
void transferir_chapa(equipamento *_equipamento, char *_nome_linha){
    mudar_estado_equipamento(_equipamento, PREPARANDO);
    calcular_tempo_preparando(_equipamento);
    if(_equipamento->Prox == NULL){

    }
    else{
        if(_equipamento->Prox->Estado == LIGADO){
            associar_equipamento_chapa(_equipamento->Prox, _equipamento->chapa);
            mudar_estado_equipamento(_equipamento->Prox, OCUPADO);
            renderizar_equipamento(_equipamento->Prox, PREPARANDO);
        }
    }
    _equipamento->chapa = NULL;
    calcular_tempo_preparando(_equipamento);
    renderizar_equipamento(_equipamento, PREPARANDO);
    enviar_resposta_ao_cliente(string_de_tranferencia(_equipamento, _nome_linha));
}
//========================================

//========================================
// Click do mouse
//========================================
void click_do_mouse(equipamento *_equipamento, ALLEGRO_EVENT_QUEUE *_fila_eventos){
    if (!al_is_event_queue_empty(_fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(_fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if ((evento.mouse.x >= _equipamento->botao_de_controle.posicao_X &&
                     evento.mouse.x <= _equipamento->botao_de_controle.posicao_X + _equipamento->botao_de_controle.largura) &&
                    (evento.mouse.y >= _equipamento->botao_de_controle.posicao_Y &&
                     evento.mouse.y <= _equipamento->botao_de_controle.posicao_Y + _equipamento->botao_de_controle.altura))
                {
                    switch(_equipamento->botao_de_controle.estado){
                    case 0:
                        mudar_estado_botao(&_equipamento->botao_de_controle, 1);
                        mudar_estado_equipamento(_equipamento, LIGADO);
                        renderizar_botao(&_equipamento->botao_de_controle, 2);
                        renderizar_equipamento(_equipamento, LIGADO);
                        break;
                    case 1:
                        mudar_estado_botao(&_equipamento->botao_de_controle, 0);
                        mudar_estado_equipamento(_equipamento, DESLIGADO);
                        renderizar_botao(&_equipamento->botao_de_controle, 1);
                        renderizar_equipamento(_equipamento, DESLIGADO);
                        break;
                    }
                }
            }
        }
}
//========================================

//========================================
// Iniciar operação dos equipamentos
//========================================
void start_equipamentos(pilha_equipamento *_equipamento, fila_chapa *_chapas, ALLEGRO_EVENT_QUEUE *_fila_eventos, char *_nome_linha){
    equipamento *aux = _equipamento->topo; int contador_equipamento;
    for(contador_equipamento = 0; aux; contador_equipamento++, aux = aux->Prox){
        click_do_mouse(aux, _fila_eventos);
        //evento_aleatorio_de_mudanca_de_estado(aux);
        switch(aux->Estado){
            case DESLIGADO:
                mudar_estado_equipamento(aux, LIGADO);
                mudar_estado_botao(&aux->botao_de_controle, 1);
                renderizar_botao(&aux->botao_de_controle, 2);
                renderizar_equipamento(aux, LIGADO);
                break;
            case LIGADO:
                if(!contador_equipamento) equipamento_processar_chapa(aux, criar_nova_chapa(_chapas));
                break;
            case OCUPADO:
                if(chapa_esta_pronta(aux) == FINALIZADO) transferir_chapa(aux, _nome_linha);
                else renderizar_equipamento(aux, OCUPADO);
                break;
            case PREPARANDO:
                if(equipamento_esta_disponivel_novamente(aux)) renderizar_equipamento(aux, LIGADO);
                break;
            case PROBLEMA:
                if(equipamento_esta_disponivel_novamente(aux));
                break;
        }
    }
}
//========================================

//========================================
// Iniciar linha de produção
//========================================
void start(linha_producao *_linha, ALLEGRO_EVENT_QUEUE *_fila_eventos){
    linha *aux = _linha->topo;
    while(aux != NULL){
        click_do_mouse(aux->equipamentos.topo, _fila_eventos);
        start_equipamentos(&aux->equipamentos, &aux->chapas, _fila_eventos, aux->nome);
        aux = aux->prox;
    }
    al_flip_display();
}
//========================================
