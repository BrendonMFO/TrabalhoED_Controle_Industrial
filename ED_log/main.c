#include "ED_dado_cliente.h"

int main()
{
    //============================================
    // Variaveis
    //============================================
    ALLEGRO_DISPLAY *janela_principal = NULL;
    fila_textos_t    textos;
    //============================================

    //============================================
    // Iniciar configurações
    //============================================
    if(!Iniciar_Allegro() || !Iniciar_Configuracao_Socket());
    Iniciar_fila_textos(&textos);
    Iniciar_Janela_Allegro(janela_principal);
    fonte_principal = Carregar_Fonte_Allegro("arial.ttf", (LARGURA_DA_TELA * 56) / 1920, 0);
    //============================================

    //============================================
    // Carrregar e renderizar fundo
    //============================================
    fundo = carregar_imagem("Fundo.fw.png");
    al_draw_scaled_bitmap(fundo, 0, 0, al_get_bitmap_width(fundo), al_get_bitmap_height(fundo), 0, 0, LARGURA_DA_TELA, ALTURA_DA_TELA, 0);
    //============================================

    al_flip_display();

    while(1){
        Sleep(1);
        if((Comunicao_servidor(&textos) == ERRO)) return 0;
    }

    return 0;
}
