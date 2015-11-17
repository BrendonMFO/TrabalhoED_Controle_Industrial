#include "Allegro_fun.h"

//====================================
// Estrutura de dados para textos
//====================================
typedef struct s_texto_t{
    char              conteudo[1024];
    int               posicao_X;
    int               posicao_Y;
    ALLEGRO_COLOR     cor;
    int               flag_allegro;
    struct s_texto_t *proximo_texto;
}texto_t;
//====================================

//====================================
// Criar configurações do texto
//====================================
texto_t *Criar_Texto(char _conteudo[1024], int _posicao_X, int _posicao_Y, ALLEGRO_COLOR _cor, int _flag_allegro){
    texto_t *variavel_de_retorno = (texto_t*)calloc(1, sizeof(texto_t));
    if(!variavel_de_retorno) return ERRO;
    strcpy(variavel_de_retorno->conteudo, _conteudo);
    variavel_de_retorno->posicao_X     = _posicao_X;
    variavel_de_retorno->posicao_Y     = _posicao_Y;
    variavel_de_retorno->cor           = _cor;
    variavel_de_retorno->flag_allegro  = _flag_allegro;
    variavel_de_retorno->proximo_texto = NULL;
    return variavel_de_retorno;
}
//====================================

//====================================
// Fila dos textos
//====================================
typedef struct{
    int      total_de_textos;
    texto_t *inicio;
    texto_t *fim;
}fila_textos_t;
//====================================

//====================================
// Iniciar fila textos
//====================================
void Iniciar_fila_textos(fila_textos_t *_fila_textos){
    _fila_textos->total_de_textos   = 0;
    _fila_textos->inicio            = NULL;
    _fila_textos->fim               = NULL;
}
//====================================

//====================================
// Adicionar novo texto
//====================================
int Adicionar_novo_texto(fila_textos_t *_fila_textos, texto_t *_texto){
    if(!_texto) return ERRO;
    _fila_textos->inicio             = !_fila_textos->inicio ? _texto : _fila_textos->inicio;
    _fila_textos->fim                = !_fila_textos->fim    ? _texto : _fila_textos->fim;
    _fila_textos->fim->proximo_texto = _fila_textos->fim     ? _texto : NULL;
    _fila_textos->fim                = _texto;
    _fila_textos->total_de_textos++;
    return SUCESSO;
}
//====================================

//====================================
// Renderizar determinada quantidade de textos
//====================================
int Renderizar_quantidade_determinada_de_textos(fila_textos_t *_fila_textos, int _inicio){
    if(quantidade_de_textos <= 0) return ERRO;
    int contador;
    texto_t *aux = _fila_textos->inicio;
    Limpar_Tela();
    quantidade_de_textos = 0;
    for(contador = 0; aux && (contador <= (17 * ALTURA_DA_TELA) / 1080 && contador < _fila_textos->total_de_textos) ; contador++, aux = aux->proximo_texto){
        if(contador >= _inicio){
            Renderizar_texto(aux);
        }
    }
    return SUCESSO;
}
//====================================

//====================================
// Renderizar texto
//====================================
int Renderizar_texto(texto_t *_texto){
    if(!_texto) return ERRO;
    if(quantidade_de_textos >= (17 * ALTURA_DA_TELA) / 1080){
        quantidade_de_textos = 0;
        Limpar_Tela;
    }
    al_draw_text(fonte_principal, _texto->cor, _texto->posicao_X, _texto->posicao_Y + ((45 * ALTURA_DA_TELA) / 1080) * quantidade_de_textos, _texto->flag_allegro, _texto->conteudo);
    quantidade_de_textos++;
    return SUCESSO;
}
//====================================
