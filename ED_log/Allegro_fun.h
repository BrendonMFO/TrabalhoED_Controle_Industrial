#include <winsock.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

//============================================
// Contantes
//============================================
enum DIMENSAO_TELA   {LARGURA_DA_TELA = 1920, ALTURA_DA_TELA = 1080};
enum VALORES_LOGICOS {ERRO, SUCESSO, RESET};
ALLEGRO_FONT     *fonte_principal = NULL;
ALLEGRO_BITMAP   *fundo           = NULL;
int quantidade_de_textos = 0;
//============================================

//============================================
// Iniciar ALLEGRO
//============================================
int Iniciar_Allegro(){
    if(!al_init()) return ERRO;
    al_init_font_addon();
    if(!al_init_ttf_addon()) return ERRO;
    if(!al_init_image_addon()) return ERRO;
    return SUCESSO;
}
//============================================

//============================================
// Iniciar janela
//============================================
int Iniciar_Janela_Allegro(ALLEGRO_DISPLAY *_janela){
    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
    al_set_window_position(_janela, 0, 0);
    _janela = al_create_display(LARGURA_DA_TELA, ALTURA_DA_TELA);
    al_set_window_title(_janela, "ED - LOG");
    if(!_janela) return ERRO;
    return SUCESSO;
}
//============================================

//============================================
// Fun��o - Carregar imagem teste
//============================================
ALLEGRO_BITMAP *carregar_imagem(char *img_path){
    ALLEGRO_BITMAP *img = al_load_bitmap(img_path);
    if(!img) return NULL;
    return img;
}
//============================================

//============================================
// Carregar fonte
//============================================
ALLEGRO_FONT *Carregar_Fonte_Allegro(const char *_nome_fonte, int _tamanho_da_fonte, int _flag){
    ALLEGRO_FONT *_fonte = (ALLEGRO_FONT*)calloc(1, sizeof(ALLEGRO_FONT));
    _fonte = al_load_font(_nome_fonte, _tamanho_da_fonte, _flag);
    if(!_fonte) return ERRO;
    return _fonte;
}
//============================================

//============================================
// Definir cor ALLEGRO
//============================================
ALLEGRO_COLOR Definir_Cor(int R, int G, int B){
    ALLEGRO_COLOR variavel_de_retorno = al_map_rgb(R, G, B);
    return variavel_de_retorno;
}
//============================================

//============================================
// Renderizar fundo - Limpar tela
//============================================
void Limpar_Tela(){
    al_draw_scaled_bitmap(fundo, 0, 0, al_get_bitmap_width(fundo), al_get_bitmap_height(fundo), 0, 0, LARGURA_DA_TELA, ALTURA_DA_TELA, 0);
}
//============================================
