#include "ED_chapaFinal.h"

//===========================================================
// Estrutura dos botões da sistema
//===========================================================
typedef struct s_botao{
    Ed_imagens             imagem_do_botao;
    int                    posicao_X;
    int                    posicao_Y;
    int                    altura;
    int                    largura;
    int                    estado;
}botao;
//===========================================================

//===========================================================
// Organizar os botoes
//===========================================================
botao criar_botao_de_controle(int _index_da_imagem){
    botao variavel_de_retorno;
	variavel_de_retorno.imagem_do_botao = Imagens_do_sistema[_index_da_imagem];
	variavel_de_retorno.estado          = 0;
    return variavel_de_retorno;
}
//===========================================================

//===========================================================
// Mudar estado botao
//===========================================================
void mudar_estado_botao(botao *_botao, int _estado){
    _botao->estado = _estado;
}
//===========================================================

//===========================================================
// Calcular proporção das imagens dos botões
//===========================================================
void calcular_proporcao_do_botao(botao *_botao, int _quantidade_de_linhas, int _ordem_do_botao_X, int _ordem_do_botao_Y){
    if(_botao && _botao->imagem_do_botao.imagem){
        _botao->largura     = ((LARGURA_DA_JANELA - ((_quantidade_de_linhas - 1) * 60)) / _quantidade_de_linhas);
        _botao->altura      = ((ALTURA_DA_JANELA * (altura_da_imagem(_botao->imagem_do_botao.imagem) / _botao->imagem_do_botao.frames) / 1080));
        _botao->posicao_X   = (_botao->largura * _ordem_do_botao_X) + (60 * _ordem_do_botao_X);
        _botao->posicao_Y   = (((ALTURA_DA_JANELA * 820) / 1080) + (_botao->altura * _ordem_do_botao_Y));
    }
}
//===========================================================

//===========================================================
// Render botao
//===========================================================
void renderizar_botao(botao *_botao, int _frame){
   if(_botao)
        al_draw_scaled_bitmap(_botao->imagem_do_botao.imagem, 0,
                              (_frame == 1 ? 0 : altura_da_imagem(_botao->imagem_do_botao.imagem) / _frame),
                              largura_da_imagem(_botao->imagem_do_botao.imagem),
                              altura_da_imagem(_botao->imagem_do_botao.imagem) / _botao->imagem_do_botao.frames,
                              _botao->posicao_X,
                              _botao->posicao_Y,
                              _botao->largura,
                              _botao->altura, 0);
}
//===========================================================
