#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

int nAlunos = 0;

typedef struct {
        char rua[50];
        char porta[50];
        char cpostal[50];
        char localidade[50];
} MORADA;

typedef struct {
    int dia;
    int mes;
    int ano;
} DATANASCIMENTO;

typedef struct {
    int dia;
    int mes;
    int ano;
} DATACONCLUSAOCARTA;

typedef struct {
    int nAluno;
    char nome[50];
    char email[50];
    char cartaoCidadao[50];
    char nif[50];
    int nCarta;
    int ativo;
    
    MORADA morada;
    DATANASCIMENTO dataNascimento;
    DATACONCLUSAOCARTA dataConclusaoCarta;
} ALUNOS;

ALUNOS alunos[30];


void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void esperaApaga(char msg[255], int time){
    system("clear||cls");
    printf("%s", msg);
    delay(time);
    system("clear||cls");
}

void mensagemBoasVindas(){
    printf("\n          .         .                                                                                                                          .         .                           ");
    printf("\n         ,8.       ,8.                   .8.          8 888888888o.                 ,o888888o.           .8.          8 8888                  ,8.       ,8.           ,o888888o.     ");
    printf("\n        ,888.     ,888.                 .888.         8 8888    `88.               8888     `88.        .888.         8 8888                 ,888.     ,888.       . 8888     `88.   ");
    printf("\n       .`8888.   .`8888.               :88888.        8 8888     `88            ,8 8888       `8.      :88888.        8 8888                .`8888.   .`8888.     ,8 8888       `8b  ");
    printf("\n      ,8.`8888. ,8.`8888.             . `88888.       8 8888     ,88            88 8888               . `88888.       8 8888               ,8.`8888. ,8.`8888.    88 8888        `8b ");
    printf("\n     ,8'8.`8888,8^8.`8888.           .8. `88888.      8 8888.   ,88'            88 8888              .8. `88888.      8 8888              ,8'8.`8888,8^8.`8888.   88 8888         88 ");
    printf("\n    ,8' `8.`8888' `8.`8888.         .8`8. `88888.     8 888888888P'             88 8888             .8`8. `88888.     8 8888             ,8' `8.`8888' `8.`8888.  88 8888         88 ");
    printf("\n   ,8'   `8.`88'   `8.`8888.       .8' `8. `88888.    8 8888`8b                 88 8888            .8' `8. `88888.    8 8888            ,8'   `8.`88'   `8.`8888. 88 8888        ,8P ");
    printf("\n  ,8'     `8.`'     `8.`8888.     .8'   `8. `88888.   8 8888 `8b.               `8 8888       .8' .8'   `8. `88888.   8 8888           ,8'     `8.`'     `8.`8888.`8 8888       ,8P  ");
    printf("\n ,8'       `8        `8.`8888.   .888888888. `88888.  8 8888   `8b.                8888     ,88' .888888888. `88888.  8 8888          ,8'       `8        `8.`8888.` 8888     ,88'   ");
    printf("\n,8'         `         `8.`8888. .8'       `8. `88888. 8 8888     `88.               `8888888P'  .8'       `8. `88888. 8 888888888888 ,8'         `         `8.`8888.  `8888888P'     ");
    delay(5);
    system("clear||cls");
}

void inserirAluno(){
		printf ("\nInsira o Nº do aluno: ");
		scanf ("%d", &alunos[nAlunos].nAluno);

		printf ("Insira o NOME do aluno: ");
		scanf (" %30[^\n]s", &alunos[nAlunos].nome);

        printf("Insira a rua:");
        scanf (" %30[^\n]s", &alunos[nAlunos].morada.rua);

        printf("Insira a código de postal:");
        scanf (" %30[^\n]s", &alunos[nAlunos].morada.cpostal);

        printf("Insira a localidade:");
        scanf (" %30[^\n]s", &alunos[nAlunos].morada.localidade);
        
		printf ("Insira a DATA DE NASCIMENTO (dia/mês/ano): ");
		scanf ("%d/%d/%d", &alunos[nAlunos].dataNascimento.dia, &alunos[nAlunos].dataNascimento.mes, &alunos[nAlunos].dataNascimento.ano);

		printf ("Insira o CARTÃO DE CIDADÃO: ");
		scanf (" %30[^\n]s", &alunos[nAlunos].cartaoCidadao);

		printf ("Insira o NIF: ");
		scanf ("%d", &alunos[nAlunos].nif);

		printf ("Insira a DATA DE CONCLUSÃO DA CARTA (dia/mês/ano): ");
		scanf ("%d/%d/%d", &alunos[nAlunos].dataNascimento.dia, &alunos[nAlunos].dataNascimento.mes, &alunos[nAlunos].dataNascimento.ano);

		printf ("Insira o NÚMERO DA CARTA:  ");
		scanf ("%d", &alunos[nAlunos].nCarta);

		printf ("Insira a SITUAÇÃO do aluno (ATIVO / NÃO ATIVO): ");
		scanf (" %30[^\n]s", &alunos[nAlunos].ativo);
        nAlunos++;
        esperaApaga("Aluno inserido com sucesso! A redirecionar ....", 3);
}

void menuAlunos(){
    int op;
    do{
        printf ("\n\n< < < MENU GESTÃO DE ALUNOS > > >");
        printf ("\n\n\t1 - Inserir novos alunos");
        printf ("\n\n\t2 - Consultar/Alterar dados do aluno");
        printf ("\n\n\t0 - Voltar");
        printf ("\n\nInsira a sua opção: ");
        scanf ("%d", &op);
        system("clear||cls");
        switch (op) {
            case 1:
                inserirAluno();
            break;
            case 2:
            break;
            case 3:
            break;
        }
    }while (op != 0);
} 

void menuInstrutores(){
    int op;
    printf ("\n\n< < < MENU GESTÃO DE INSTRUTORES > > >");
    printf ("\n\n\t1 - Inserir novos instrutores");
    printf ("\n\n\t2 - Consultar/Alterar dados do instrutor");
    printf ("\n\n\t0 - Voltar");
    printf ("\n\nInsira a sua opção: ");
    scanf ("%d", &op);
}

void menuAulas(){
    int op;
    printf ("\n\n< < < MENU MARCAÇÃO/CONSULTA DE AULAS > > >");
    printf("\n\n\t1 - Marcar aulas");
    printf ("\n\n\t2 - Consultar aulas");
    printf ("\n\n\t0 - Voltar");
    printf ("\n\nInsira a sua opção: ");
    scanf ("%d", &op);
}

int menuPrincipal(){
    int op;
    printf ("\n\n< < < MENU PRINCIPAL > > >");
    printf ("\n\n\t1 - Gestão de Alunos");
    printf ("\n\n\t2 - Gestão de Intrutores");
    printf ("\n\n\t3 - Marcação/Consultas de aulas");
    printf ("\n\n\t0 - Sair");
    printf ("\n\nInsira a sua opção: ");
    scanf ("%d", &op);
    system("clear||cls");
    switch (op){
        case 1:
            menuAlunos();
        break;
        case 2:
            menuInstrutores();
        break;
        case 3:
            menuAulas();
        break;
    }
    return op;
}

int main(void){
    fullscreen();
    setlocale(LC_ALL, "Portuguese");
    int op;
    mensagemBoasVindas();
    do{
        op = menuPrincipal();
    }while(op != 0);
    return 0;
}