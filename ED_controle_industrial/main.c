#include <stdio.h>
#include <stdlib.h>
#include "ED_iniciar.h"

int main()
{
    //================================================
    // Variaveis iniciais
    //================================================
    ALLEGRO_DISPLAY         *janela_principal;
    ALLEGRO_BITMAP          *fundo;
    ALLEGRO_EVENT_QUEUE     *eventos_do_sistema;
    linha_producao           fabrica;
    //================================================

    iniciar_operacoes_do_sistema(janela_principal, eventos_do_sistema, &fabrica);
    fundo = carregar_imagem("fundo.JPG");
    al_draw_scaled_bitmap(fundo,0,0,largura_da_imagem(fundo),altura_da_imagem(fundo),0,0,LARGURA_DA_JANELA,ALTURA_DA_JANELA,0);

    eventos_do_sistema = al_create_event_queue();
    al_register_event_source(eventos_do_sistema, al_get_mouse_event_source());

    while(1)
        start(&fabrica, eventos_do_sistema);

    return 0;
}
