#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "funcoes.h"

int main(int argc, char *argv[]) {
    int pisos, lugares, opcao;
    printf("CRIACAO DO PARQUE\n\n");
    printf("Introduza o numero de pisos: ");
    scanf("%d", &pisos);
    printf("Introduza o numero de lugares de cada piso: ");
    scanf("%d", &lugares);
    char** parque;
    parque = criarParque(pisos, lugares);
    printf("\n- Parque Criado - \n");
    mostrarParque(parque, pisos, lugares);
    
    CARRO carros = malloc(sizeof(struct carro));
    int *contador = malloc(sizeof(int));
    *contador = 0; 
    while(1){
        printf("1. Estacionar carro\n");
        printf("2. Remover carro\n");
        printf("3. Mostrar informacao da viatura\n");
        printf("4. Visualizar o parque\n");
        printf("5. Sair\n");
        printf("\nSelecione uma opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                if(disponivel(parque, pisos, lugares)){
                    printf("\nIntroduza a matricula (##-##-##): ");
                    char* matricula = malloc(sizeof(char)*9);
                    fflush(stdin);
                    gets(matricula);
                    if(strlen(matricula) < 8 || strlen(matricula) > 8){
                        printf("Introduza uma matricula valida\n");
                    }else{
                        if(verificarMatricula(carros, contador, matricula)){
                            printf("\nA matricula ja se encontra no parque\n\n");  
                        }else{
                            carros = adicionarCarro(carros, contador, parque, pisos, lugares, matricula);
                            mostrarParque(parque, pisos, lugares);
                        }
                    }
                }else{
                    printf("\nO parque esta cheio\n"); 
                }
                break;
            case 2: 
                printf("\nIntroduza a matricula do carro que pretende remover (##-##-##): ");
                char* matricula = malloc(sizeof(char)*9);
                fflush(stdin);
                gets(matricula);
                if(verificarMatricula(carros, contador, matricula)){
                    retirarCarro(carros, contador, parque, matricula);
                    mostrarParque(parque, pisos, lugares);  
                }else{
                    printf("\nA matricula nao se encontra no parque\n\n");
                }
                break; 
            case 3:
                printf("\nIntroduza a matricula do carro que pretende ver informacoes: ");
                char* mat = malloc(sizeof(char)*9);
                fflush(stdin);
                gets(mat);
                verInformacoes(carros, contador, parque, mat);
                break; 
            case 4:
                mostrarParque(parque, pisos, lugares);
                break; 
            case 5:
                system("cls");
                printf("Programa Terminado!\n");
                printf("\nTrabalho realizado por:\n");
                printf(" - Goncalo Fernandes Pereira, n96550\n");
                printf(" - Jose Pedro Costa Vilaca, n97992\n");
                printf(" - Mariana Magalhaes Araujo, n97245\n");
                exit(0);
                break; 
            default: 
                printf("\nOpcao Invalida\n");
                break; 
        }  
    }
	return 0;
}
