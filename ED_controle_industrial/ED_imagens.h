#include "Allegro_Fun.h"

//========================================================
// Enumeração das imagens disponiveis
//========================================================
enum IMAGENS_DISPONIVEIS {FORNO, TRITURADOR, MODELADOR, BOTAO};
//========================================================

//========================================================
// Estrutura de dados das imagens
//========================================================
typedef struct {
    ALLEGRO_BITMAP *imagem;
    int             frames;
}Ed_imagens; Ed_imagens Imagens_do_sistema[4];
//========================================================

//========================================================
// Carregar imagens
//========================================================
Ed_imagens popular_imagens_do_sistema(char *_caminho_da_imagem, int _frames){
    Ed_imagens variavel_de_retorno;
    variavel_de_retorno.imagem = carregar_imagem(_caminho_da_imagem);
    variavel_de_retorno.frames = _frames;
    return variavel_de_retorno;
}

//========================================================
// Carregar imagens
//========================================================
void carregar_imagens_do_sistema(){
    Imagens_do_sistema[0] = popular_imagens_do_sistema("Forno.fw.png", 5);
    Imagens_do_sistema[1] = popular_imagens_do_sistema("Triturador.fw.png", 5);
    Imagens_do_sistema[2] = popular_imagens_do_sistema("Modelador.fw.png", 5);
    Imagens_do_sistema[3] = popular_imagens_do_sistema("Botoes.fw.png", 2);
}
//========================================================
