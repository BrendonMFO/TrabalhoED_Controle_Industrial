#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdarg.h>
#include <string.h>
#include "ED_fun.h"

//=====================================================
// Constantes
//=====================================================
enum PROPORCAO_DA_JANELA {LARGURA_DA_JANELA = 1366, ALTURA_DA_JANELA = 768};
#define TRUE 1
#define FALSE 0
//=====================================================

//=====================================================
// Função - Iniciar Allegro
//=====================================================
int iniciar_ALLEGRO(){
    if(!al_init()){
        printf("Falha ao iniciar modo grafico Allegro\n");
        return FALSE;
    }
    if(!al_install_mouse()){
        printf("Falha ao iniciar mouse Allegro\n");
        return FALSE;
    }
    if(!al_init_image_addon()){
        printf("Falha ao iniciar Addon de imagem Allegro\n");
        return FALSE;
    }
    if(!al_init_ttf_addon()){
        printf("Falha ao iniciar Addon de fonte ttf\n");
        return FALSE;
    }
    al_init_font_addon();
    return TRUE;
}
//=====================================================

//=====================================================
// Função - Iniciar janela
//=====================================================
int criar_janela(ALLEGRO_DISPLAY **window, int x, int y){
    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
    *window = al_create_display(x, y);
    if(!*window){
        printf("Erro ao criar janela");
        return FALSE;
    }
    return TRUE;
}
//=====================================================

//=====================================================
// Função - Instanciar mouse do sistema na aplicação
//=====================================================
int iniciar_mouse_ALLEGRO(ALLEGRO_DISPLAY **janela, int flags){
    if(!al_set_system_mouse_cursor(*janela, flags)){
        printf("Falha ao instanciar mouse do sistema Allegro\n");
        return FALSE;
    }
    return TRUE;
}
//=====================================================

//=====================================================
// Função - Iniciar evento
//=====================================================
int criar_lista_de_eventos(ALLEGRO_EVENT_QUEUE **evento){
    *evento = al_create_event_queue();
    if(!*evento){
        printf("Falha ao criar lista de eventos\n");
        return FALSE;
    }
    return TRUE;
}
//=====================================================

//=====================================================
// Função - Carregar imagem teste
//=====================================================
ALLEGRO_BITMAP *carregar_imagem(char *img_path){
    ALLEGRO_BITMAP *img = al_load_bitmap(img_path);
    if(!img) return NULL;
    return img;
}
//=====================================================

//=====================================================
// Função - Carregar font
//=====================================================
int carregar_font(ALLEGRO_FONT **font, char *fonte, int tamanho, int flags){
    *font = al_load_ttf_font(fonte, tamanho, flags);
    if(!*font){
        printf("Erro ao carregar fonte - %s\n", fonte);
        return FALSE;
    }
    return TRUE;
}
//=====================================================

//=====================================================
// Função - Retornar largura ou altura de um bitmap
//=====================================================
int largura_da_imagem(ALLEGRO_BITMAP *_imagem){
    return al_get_bitmap_width(_imagem);
}
int altura_da_imagem(ALLEGRO_BITMAP *_imagem){
    return al_get_bitmap_height(_imagem);
}
//=====================================================
