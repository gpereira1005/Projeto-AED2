#include "carro.h"

/*Funçao que permite criar o array do Parque*/
char** criarParque(int pisos, int lugares){
    char** parque;
    int i, j;
    parque=malloc(sizeof(char)*pisos*100);
    for(i=0; i<pisos; i++){
        parque[i]=malloc(sizeof(char)*lugares);
    }
    for(i=0; i<pisos; i++){
        for(j=0; j<lugares; j++){
            parque[i][j]='L';
        }
    }
    return parque; 
}

/*Função que permite mostrar o Parque*/
void mostrarParque(char** parque, int pisos, int lugares){
    int i,j;
    printf("\n");
    for(i=0; i<pisos; i++){
        printf("| ");
        for(j=0; j<lugares; j++){
            printf("%c ", parque[i][j]);
        }
        printf("|");
        printf("\n");
    }
    printf("\n");
}

/*Função que permite determinar o proximo piso e lugar disponivel*/
int lugarDisponivel(char** parque, int pisos, int lugares, int *lugar){
    int i,j;
    for(i=0; i<pisos; i++){
        for(j=0; j<lugares; j++){
           if(parque[i][j]=='L'){
               *lugar=j;
               return i;
           }
        }
    }
}

/*Função que retorna o numero de lugares disponiveis no parque*/
int disponivel(char** parque, int pisos, int lugares){
    int i,j, livres=0;
    for(i=0; i<pisos; i++){
        for(j=0; j<lugares; j++){
           if(parque[i][j]=='L'){
               livres++;
           }
        }
    }
    return livres;
}

/*Função que permite estacionar um carro no Parque*/
CARRO adicionarCarro(CARRO carros, int *contador, char** parque, int pisos, int lugares, char* matricula){
    int lugar;
    int piso = lugarDisponivel(parque, pisos, lugares, &lugar);
    carros=realloc(carros, sizeof(struct carro)*(*contador+1));
    parque[piso][lugar]='O';
    strcpy(carros[*contador].matricula, matricula);
    carros[*contador].piso=piso;
    carros[*contador].lugar=lugar;
    
    struct data entrada;
	
	char buff[100];
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    strftime (buff, 100, "%d-%m-%Y %H:%M:%S", &now_t);
    
    entrada.ano = now_t.tm_year + 1900;
    entrada.mes = now_t.tm_mon + 1;  
    entrada.dia = now_t.tm_mday;  
    entrada.hora = now_t.tm_hour;
    entrada.minuto = now_t.tm_min;
    entrada.segundo =now_t.tm_sec;
    carros[*contador].data = entrada;
    printf("\nHORA DE ENTRADA: %dh:%dm:%ds\n", entrada.hora, entrada.minuto, entrada.segundo);
    (*contador)++;
    return carros;
}

/*Função que permite calcular o preço com base no tempo que esteve estacionado*/
float mostrarPreco(CARRO carros, int posicao){
    struct data saida;
    
    char buff[100];
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    strftime (buff, 100, "%d-%m-%Y %H:%M:%S", &now_t);
      
    saida.hora = now_t.tm_hour;
    saida.minuto = now_t.tm_min;
    saida.segundo =now_t.tm_sec;
    
    float hora_saida = saida.hora*3600+saida.minuto*60+saida.segundo;
    float hora_entrada = carros[posicao].data.hora*3600+carros[posicao].data.minuto*60+carros[posicao].data.segundo;
    float tempo = (hora_saida-hora_entrada)/3600;
    printf("\nEsteve %f horas no parque\n", tempo);
    return ceil(tempo)*2.5; /*Arredondar para o inteiro acima*/
    
}

/*Função que permite remover um carro do Parque*/
void retirarCarro(CARRO carros, int *contador, char** parque, char* matricula){
    int i, j;
    for(i=0; i<*contador; i++){
        if(strcmp(carros[i].matricula, matricula)==0){ /*strcmp retorna 0 se for verdade*/
            int piso = carros[i].piso;
            int lugar = carros[i].lugar;
            parque[piso][lugar]='L';
            printf("Carro removido");
            float preco = mostrarPreco(carros, i);
            printf("Hora de entrada %d:%d:%d\n", carros[i].data.hora, carros[i].data.minuto, carros[i].data.segundo);
            printf("Preco a pagar %.2f euros.\n", preco);
            for(j=i; j<*contador-1; j++){
                carros[j]=carros[j+1];
            }
            (*contador)--;
            carros = realloc(carros, sizeof(struct carro)*(*contador));
            return;
        }
    }
    printf("Esse carro nao esta no parque");
}

/*Função que permite ver as informações de um carro que está estacionado*/
void verInformacoes(CARRO carros, int *contador, char** parque, char* matricula){
    int i;
    for(i=0; i<*contador; i++){
        if(strcmp(carros[i].matricula, matricula)==0){
            printf("\n - Piso: %d \n", carros[i].piso);
            printf(" - Lugar: %d \n", carros[i].lugar);
            printf(" - Hora de entrada: %d/%d/%d - %d:%d:%d \n\n", carros[i].data.dia, carros[i].data.mes, carros[i].data.ano, carros[i].data.hora, carros[i].data.minuto, carros[i].data.segundo);
            return;
        }
    }
    printf("\nEsse carro nao esta no parque!\n"); 
}

/*Função que permite verificar se uma determinada matricula enontra-se estacionada no parque*/
int verificarMatricula(CARRO carros, int *contador, char* matricula){
    int i;
    for(i=0; i<*contador; i++){
        if(strcmp(carros[i].matricula, matricula)==0){
            return 1;
        }
    }
    return 0; 
}

