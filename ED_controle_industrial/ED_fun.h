#include <time.h>
#include <stdarg.h>
#include "ED_socket_server.h"

//=====================================================
// Fun��o para retornar o tempo atual do sistema
//=====================================================
int obter_tempo_atual(){
    time_t tempo_atual; time(&tempo_atual);
    return tempo_atual;
}
//=====================================================

//=====================================================
// Fun��o para converter celsius para fahrenheit
//=====================================================
float converter_temperatura(float temperatura){
    return (((9 * temperatura) / 5) + 32);
}
//=====================================================

//=====================================================
// Calcular tempo necessario
//=====================================================
int calcular_tempo_necessario(float _temperatura, float _velocidade){

}
//=====================================================
