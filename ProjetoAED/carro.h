typedef struct data{
    int dia;
    int mes; 
    int ano; 
    int hora; 
    int minuto;
    int segundo;
}*DATA;

typedef struct carro{
    char matricula[9];
    int piso;
    int lugar;
    struct data data; 
}*CARRO;

