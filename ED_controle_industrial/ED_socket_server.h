#include <winsock.h>
#include <windows.h>

//====================================================
// Globais de acesso socket
//====================================================
/*
    -WSADATA e SOCKET guardam informações de inicialização
     dos sockets para a futura comunicação entre o cliente
     e o servidor
    -SOCKADDR_IN contem a configuração do socket como o ip
     a porta e a familia
*/
//====================================================
WSADATA data_socket;
SOCKET winsock;
SOCKADDR_IN sock;
//====================================================

//====================================================
// Função para iniciar configurações sockets
//====================================================
int configurar_sockets(){
    if(WSAStartup(MAKEWORD(1,1), &data_socket)==SOCKET_ERROR){
        printf("Erro ao inicializar o winsock");
        return 0;
    }
    if((winsock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR){
        printf("Erro ao criar socket");
        return 0;
    }
    sock.sin_family = AF_INET;
    sock.sin_port   = htons(1234);
    if(bind(winsock, (SOCKADDR*)&sock, sizeof(sock)) == SOCKET_ERROR){
        printf("Erro colocar utilizar a funcao BIND");
        return 0;
    }
    return 1;
}
//====================================================

//====================================================
// Função para escuta do servidor
//====================================================
void iniciar_escuta_servidor(){
    listen(winsock,1);
    while((winsock = accept(winsock, 0, 0)) == SOCKET_ERROR)
    {
        Sleep(1);
    }
    printf("Cliente conectado!\n");
}
//====================================================

//====================================================
// Função para enviar uma resposta ao cliente
//====================================================
void enviar_resposta_ao_cliente(char *_resposta){
    send(winsock, _resposta, strlen(_resposta), 0);
}
//====================================================

//====================================================
// Função para obter a requisição do cliente
//====================================================
char requisicao_cliente(){
    char buffer2[1024]; int bytes;
    while(1){
        Sleep(1);
        memset(buffer2, 0, 1024);
        bytes = recv(winsock, buffer2, 1024, 0);
        if(bytes == -1){
            printf("Conexão perdida");
            getch();
        return 0;
        }
        printf(buffer2);
    }
}
//====================================================

//====================================================
// Finalizar socket
//====================================================
void finalizar_comunicacao(){
    getch();
    closesocket(winsock);
    WSACleanup();
}
//====================================================
