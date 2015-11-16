#include "ED_texto.h"

//===========================================
// Globais para o socket
//===========================================
WSADATA data;
SOCKET winsock;
SOCKADDR_IN sock;
//===========================================

//===========================================
// Iniciar configurações do socket
//===========================================
int Iniciar_Configuracao_Socket(){
    if(WSAStartup(MAKEWORD(1,1),&data)==SOCKET_ERROR){
        printf("Erro ao inicializar o winsock\n");
        return ERRO;
    }
    if((winsock = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR){
        printf("Erro ao criar socket\n");
        return ERRO;
    }
    sock.sin_family      = AF_INET;
    sock.sin_port        = htons(1234);
    sock.sin_addr.s_addr = inet_addr("192.168.0.102");
    if(connect(winsock,(SOCKADDR*)&sock,sizeof(sock))==SOCKET_ERROR){
        printf("Erro ao se conectar\n");
        return ERRO;
    }
    return SUCESSO;
}
//===========================================

//===========================================
// Comunicacao do servidor
//===========================================
int Comunicao_servidor(fila_textos_t *_textos){
    char buffer[1024]; int bytes;
    char *texto_split;
    memset(buffer, 0, 1024);
    bytes = recv(winsock, buffer, 1024, 0);
    ALLEGRO_COLOR cor = buffer[0] == '0' ? Definir_Cor(255,255,255) : Definir_Cor(140,23,23);
    buffer[0] = ' ';
    if(bytes == -1){
        printf("Conexão perdida\n");
        return ERRO;
    }
    if(bytes > 0){
        texto_split = strtok(buffer, "\n");
        Adicionar_novo_texto(_textos, Criar_Texto(texto_split, (75 * ALTURA_DA_TELA) / 1080, (200 * ALTURA_DA_TELA) / 1080 ,  cor, 0));
        Renderizar_texto(_textos->fim);
        texto_split = strtok(NULL, "\n");
        al_flip_display();
        if(quantidade_de_textos >= (17 * ALTURA_DA_TELA) / 1080) return RESET;
    }
    return SUCESSO;
}
//===========================================

//===========================================
// Função para enviar uma resposta ao cliente
//===========================================
void enviar_resposta_ao_servidor(char *_resposta){
    send(winsock, _resposta, strlen(_resposta), 0);
}
//===========================================

//===========================================
// Conexao socket
//===========================================
void Fechar_Conexao_Socket(){
    closesocket(winsock);
    WSACleanup();
}
//===========================================
