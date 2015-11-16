#include "ED_linhaproducao.h"
#include <windows.h>

//========================================
// Montar string de comunicacao
//========================================
char *string_de_tranferencia(int _texto, equipamento *_equipamento, char *_nome_linha, int _cor){
    char string_de_comunicacao[1024];
    memset(string_de_comunicacao, 0, 1024);
    time_t tempo = obter_tempo_atual();
    struct tm *tempo_formato = localtime(&tempo);
    if(_texto == 0)
        sprintf(string_de_comunicacao, "%d%s  : Horario - %s", _cor, _nome_linha, asctime(tempo_formato));
    else
        sprintf(string_de_comunicacao, "%d%s  : Horario - %s DEFEITO", _cor, _equipamento->Nome, asctime(tempo_formato));
    return string_de_comunicacao;
}
//========================================

//========================================
// Transferir chapa entre os equipamentos
//========================================
void transferir_chapa(equipamento *_equipamento, char *_nome_linha){
    if(_equipamento->Prox == NULL){
        mudar_estado_equipamento(_equipamento, PREPARANDO);
        calcular_tempo_preparando(_equipamento);
        renderizar_equipamento(_equipamento, PREPARANDO);
        _equipamento->chapa = NULL;
        enviar_resposta_ao_cliente(string_de_tranferencia(0, _equipamento, _nome_linha, 0));
    }
    else{
        if(_equipamento->Prox->Estado == LIGADO){
            mudar_estado_equipamento(_equipamento, PREPARANDO);
            calcular_tempo_preparando(_equipamento);
            associar_equipamento_chapa(_equipamento->Prox, _equipamento->chapa);
            mudar_estado_equipamento(_equipamento->Prox, OCUPADO);
            renderizar_equipamento(_equipamento, PREPARANDO);
            _equipamento->chapa = NULL;
        }
    }
    if(evento_aleatorio_de_mudanca_de_estado(_equipamento))
        enviar_resposta_ao_cliente(string_de_tranferencia(1, _equipamento, _nome_linha, 1));
}
//========================================

//========================================
// Click do mouse
//========================================
void click_do_mouse(linha_producao *_linha, ALLEGRO_EVENT_QUEUE *_fila_eventos){
    if (!al_is_event_queue_empty(_fila_eventos))        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(_fila_eventos, &evento);
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                linha *aux = _linha->topo;
                equipamento *_equipamento = aux->equipamentos.topo;
                while(aux != NULL){
                    _equipamento = aux->equipamentos.topo;
                    while(_equipamento){
                        if ((evento.mouse.x >= _equipamento->botao_de_controle.posicao_X &&
                             evento.mouse.x <= _equipamento->botao_de_controle.posicao_X + _equipamento->botao_de_controle.largura) &&
                            (evento.mouse.y >= _equipamento->botao_de_controle.posicao_Y &&
                             evento.mouse.y <= _equipamento->botao_de_controle.posicao_Y + _equipamento->botao_de_controle.altura))
                        {
                            reiniciar_equipamento(_equipamento);
                            switch(_equipamento->botao_de_controle.estado){
                            case 0:
                                mudar_estado_botao(&_equipamento->botao_de_controle, 1);
                                mudar_estado_equipamento(_equipamento, LIGADO);
                                renderizar_botao(&_equipamento->botao_de_controle, 2);
                                renderizar_equipamento(_equipamento, LIGADO);
                                break;
                            case 1:
                                mudar_estado_botao(&_equipamento->botao_de_controle, 0);
                                mudar_estado_equipamento(_equipamento, 5);
                                renderizar_botao(&_equipamento->botao_de_controle, 1);
                                renderizar_equipamento(_equipamento, DESLIGADO);
                                break;
                            }
                        }
                        _equipamento = _equipamento->Prox;
                    }
                aux = aux->prox;
                }
            }
        }
}
//========================================

//========================================
// Iniciar opera��o dos equipamentos
//========================================
void start_equipamentos(pilha_equipamento *_equipamento, fila_chapa *_chapas, ALLEGRO_EVENT_QUEUE *_fila_eventos, char *_nome_linha){
    equipamento *aux = _equipamento->topo; int contador_equipamento;
    for(contador_equipamento = 0; aux; contador_equipamento++, aux = aux->Prox){
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
                if(equipamento_esta_disponivel_novamente(aux)){
                    mudar_estado_equipamento(aux, LIGADO);
                    renderizar_equipamento(aux, LIGADO);
                }
                break;
            case PROBLEMA:

                if(equipamento_esta_disponivel_novamente(aux));
                break;
        }
    }
}
//========================================

//========================================
// Iniciar linha de produ��o
//========================================
void start(linha_producao *_linha, ALLEGRO_EVENT_QUEUE *_fila_eventos){
    linha *aux = _linha->topo;
    while(aux != NULL){
        click_do_mouse(_linha, _fila_eventos);
        start_equipamentos(&aux->equipamentos, &aux->chapas, _fila_eventos, aux->nome);
        aux = aux->prox;
    }
    al_flip_display();
}
//========================================
