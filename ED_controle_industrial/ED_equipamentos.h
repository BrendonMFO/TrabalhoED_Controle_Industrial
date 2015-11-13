#include <string.h>
#include "ED_botao.h"

//============================================
// Constantes
//============================================
enum ESTADOS_EQUIPAMENTOS {DESLIGADO, LIGADO, OCUPADO, PREPARANDO, PROBLEMA};
//============================================

//============================================
// Estrutura de horarios para os equipamentos
//============================================
typedef struct{
    time_t Tempo_de_espera;
    time_t Hora_inicial;
    time_t Hora_final;
}data;
//============================================

//============================================
// Criar nova data
//============================================
data criar_data(){
    data temp;
    time(&temp.Hora_inicial);
    temp.Hora_final = 0;
    temp.Tempo_de_espera = 0;
    return temp;
}
//============================================

//============================================
// Estrutura de atributos dos equipamentos
//============================================
/*
    N�o ser� utilizado todos os atributos em
    todos os equipamentos, por exemplo o forno
    n�o possui velocidade.
*/
//============================================
typedef struct{
    float Gasto;
    float Temperatura;
    float Velocidade;
}dados;
//============================================

//============================================
// Criar novo dados
//============================================
dados criar_dados(float _gasto, float _temperatura, float _velocidade){
    dados temp = {_gasto, _temperatura, _velocidade};
    return temp;
}
//============================================

//============================================
// Estrutura de dados para a propor��o das imagens
//============================================
typedef struct{
    int X;
    int Y;
    int Largura;
    int Altura;
}dimensao;
//============================================

//============================================
// Estrutura dos equipamentos
//============================================
/*
    Triturador -    Estado & Velocidade
    Modelador  -    Estado & Velocidade
    Forno      -    Estado & Temperatura
    Resfriador -    Estado & Temperatura
*/
//============================================
typedef struct s_equipamento{
    char                        *Nome;
    Ed_imagens               	 Imagem;
    dimensao                     Dimensao;
    dados                        Atributos;
    data                         Horarios;
    int                          Estado;
    chapa                       *chapa;
    botao                        botao_de_controle;
    struct s_equipamento        *Prox;
}equipamento;
//============================================

//============================================
// Criar pilha de equipamentos
//============================================
typedef struct{
    equipamento *topo;
}pilha_equipamento;
//============================================

//============================================
// Iniciar pilha de equipamento
//============================================
void iniciar_pilha_de_equipamento(pilha_equipamento *_e){
    _e->topo = NULL;
}
//============================================

//============================================
// Criar novo equipamento
equipamento *criar_novo_equipamento(enum ESTADOS_EQUIPAMENTOS _index_da_imagem, char *_n, dados _d, data _dh){
//============================================
    equipamento *aux = (equipamento*)calloc(1, sizeof(equipamento));
    if(!aux)return NULL;
    aux->Atributos  = _d;
    aux->Imagem     = Imagens_do_sistema[_index_da_imagem];
    aux->chapa      = NULL;
    aux->Estado     = DESLIGADO;
    aux->Horarios   = _dh;
    aux->Nome       = _n;
    aux->botao_de_controle = criar_botao_de_controle(BOTAO);
    return aux;
}
//============================================

//============================================
// Associar chapa ao equipamento
//============================================
void associar_equipamento_chapa(equipamento *_e, chapa *_c){
    _e->chapa = _c;
    _e->chapa->tempo_passar_equipamento = obter_tempo_atual() + ( 60 / (_e->Atributos.Temperatura + (_e->Atributos.Velocidade * 2)));
}
//============================================

//=======================================
// Mudar estado do equipamento
//=======================================
void mudar_estado_equipamento(equipamento *_equipamento, int _estado){
    _equipamento->Estado = _estado;
}
//=======================================

//========================================
// Calcular tempo de espera
//========================================
void calcular_tempo_preparando(equipamento *_equipamento){
    _equipamento->Horarios.Tempo_de_espera = obter_tempo_atual() + 2;
}
//========================================

//========================================
// Checar se o tempo de espera passou
//========================================
int equipamento_esta_disponivel_novamente(equipamento *_equipamento){
    if((_equipamento->Horarios.Tempo_de_espera - obter_tempo_atual()) <= 0){
        mudar_estado_equipamento(_equipamento, LIGADO);
        return TRUE;
    }return FALSE;
}
//========================================

//========================================
// Checar se o primeiro equipamento esta disponivel
//========================================
void equipamento_processar_chapa(equipamento *_equipamento, chapa *_chapa){
    associar_equipamento_chapa(_equipamento, _chapa);
    mudar_estado_equipamento(_equipamento, OCUPADO);
}
//========================================

//========================================
// Checar se a chapa j� passou pelo equipamento
//========================================
int chapa_esta_pronta(equipamento *_equipamento){
    if(_equipamento->chapa)
        if((_equipamento->chapa->tempo_passar_equipamento - obter_tempo_atual()) <= -2) return FINALIZADO;
    return PROCESSANDO;
}
//========================================

//========================================
// Equipamento com problema
//========================================
void checar_se_equipamento_esta_com_defeito(equipamento *_equipamento){
    if((_equipamento->Atributos.Temperatura < 900 || _equipamento->Atributos.Temperatura > 2000) ||
       (_equipamento->Atributos.Velocidade  < 150 || _equipamento->Atributos.Velocidade  > 1000)){
        mudar_estado_equipamento(_equipamento, PROBLEMA);
        renderizar_equipamento(_equipamento,   PROBLEMA);
        renderizar_botao(&_equipamento->botao_de_controle, 2);
        calcular_tempo_preparando(_equipamento);
        printf("PROBLEMA\n");
    }
}
//========================================

//========================================
// Evento aleatorio de mudan�a de estado dos equipamentos
//========================================
void evento_aleatorio_de_mudanca_de_estado(equipamento *_equipamento){
    srand(time(NULL));
    int probabilidade = rand() % 100 + 1;
    _equipamento->Atributos.Temperatura += probabilidade > 90 ? ((_equipamento->Atributos.Temperatura / 100) * 20) : 0;
    _equipamento->Atributos.Velocidade  += probabilidade > 90 ? ((_equipamento->Atributos.Velocidade  / 100) * 20) : 0;
    _equipamento->Atributos.Temperatura += probabilidade > 85 ? ((_equipamento->Atributos.Temperatura / 100) * 10) : 0;
    _equipamento->Atributos.Velocidade  += probabilidade > 85 ? ((_equipamento->Atributos.Velocidade  / 100) * 10) : 0;
    _equipamento->Atributos.Temperatura -= probabilidade < 10 ? ((_equipamento->Atributos.Temperatura / 100) * 30) : 0;
    _equipamento->Atributos.Velocidade  -= probabilidade < 10 ? ((_equipamento->Atributos.Velocidade  / 100) * 35) : 0;
    _equipamento->Atributos.Temperatura -= probabilidade < 15 ? ((_equipamento->Atributos.Temperatura / 100) * 25) : 0;
    _equipamento->Atributos.Velocidade  -= probabilidade < 15 ? ((_equipamento->Atributos.Velocidade  / 100) * 25) : 0;
}
//========================================

//========================================
// Ajustar propor��o das imagens dos equipamentos
//========================================
void calcular_proporcao_do_equipamento(equipamento *_equipamento, int _quantidade_de_linhas, int _ordem_do_equipamento_X, int _ordem_do_equipamento_Y){
    if(_equipamento){
        _equipamento->Dimensao.Largura = ((LARGURA_DA_JANELA - ((_quantidade_de_linhas - 1) * 60)) / _quantidade_de_linhas);
		_equipamento->Dimensao.Altura  = ((ALTURA_DA_JANELA * (altura_da_imagem(_equipamento->Imagem.imagem) / _equipamento->Imagem.frames) / 1080));
        _equipamento->Dimensao.X       = (_equipamento->Dimensao.Largura * _ordem_do_equipamento_X) + (60 * _ordem_do_equipamento_X);
        _equipamento->Dimensao.Y       = (((ALTURA_DA_JANELA * 60) / 1080) + (_equipamento->Dimensao.Altura * _ordem_do_equipamento_Y));
    }
}
//========================================

//========================================
// Renderizar equipamento
//========================================
void renderizar_equipamento(equipamento *_equipamento, int _frames){
    if(_equipamento)
        al_draw_scaled_bitmap(_equipamento->Imagem.imagem, 0,
                              (altura_da_imagem(_equipamento->Imagem.imagem) / _equipamento->Imagem.frames) * _frames,
                              largura_da_imagem(_equipamento->Imagem.imagem),
                              altura_da_imagem(_equipamento->Imagem.imagem) / _equipamento->Imagem.frames,
                              _equipamento->Dimensao.X,
                              _equipamento->Dimensao.Y,
                              _equipamento->Dimensao.Largura,
                              _equipamento->Dimensao.Altura, 0);
}
//========================================
