////////////////////////////////////////////////////////////////////////////////////
//Bibliotecas
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

////////////////////////////////////////////////////////////////////////////////////
//Variaveis Globais
////////////////////////////////////////////////////////////////////////////////////
int nAlunos = 0;
int nInstrutores = 0;
int nAulas = 0;

////////////////////////////////////////////////////////////////////////////////////
//Funções
////////////////////////////////////////////////////////////////////////////////////

//ecra grande só funciona em windows
void fullscreen(){
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

//espera algum tempo delay(tempo_em_segundos)
void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

//apaga espera algum tempo em segundos enquanto apresenta uma frase e apaga de novo esperaApaga("texto_a_apresentar", tempo_em_segundos)
void esperaApaga(char msg[255], int time){
    system("clear||cls");
    printf("%s", msg);
    delay(time);
    system("clear||cls");
}

//mensagem quando se inicializa o programa
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
    delay(1);
    system("clear||cls");
}

////////////////////////////////////////////////////////////////////////////////////
//Alunos
////////////////////////////////////////////////////////////////////////////////////

//Estrutura de dados definida para os aulnos
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
    char cartaoCidadao[20];
    char nif[50];
    int nCarta;
    int ativo;
    
    MORADA morada;
    DATANASCIMENTO dataNascimento;
    DATACONCLUSAOCARTA dataConclusaoCarta;
} ALUNOS;

ALUNOS alunos[30];

//insere um aluno
void inserirAluno(){
        printf ("\n\n< < < Inserção de Aluno > > >");
		printf ("\n\n\tInsira o Nº do aluno: ");
		scanf ("%d", &alunos[nAlunos].nAluno);

		printf ("\n\n\tInsira o nome do aluno: ");
		scanf (" %50[^\n]s", &alunos[nAlunos].nome);

        printf("\n\n\tInsira a rua:");
        scanf (" %50[^\n]s", &alunos[nAlunos].morada.rua);

        printf("\n\n\tInsira a código de postal:");
        scanf (" %50[^\n]s", &alunos[nAlunos].morada.cpostal);

        printf("\n\n\tInsira a localidade:");
        scanf (" %50[^\n]s", &alunos[nAlunos].morada.localidade);
        
        printf ("\n\n\tInsira o email do aluno: ");
        scanf (" %50[^\n]s", &alunos[nAlunos].email); 
        
		printf ("\n\n\tInsira a data de nascimento (dia/mês/ano): ");
		scanf ("%d/%d/%d", &alunos[nAlunos].dataNascimento.dia, &alunos[nAlunos].dataNascimento.mes, &alunos[nAlunos].dataNascimento.ano);

		printf ("\n\n\tInsira o cartão de cidadão: ");
		scanf (" %20[^\n]s", &alunos[nAlunos].cartaoCidadao);

		printf ("\n\n\tInsira o NIF: ");
		scanf ("%d", &alunos[nAlunos].nif);

		printf ("\n\n\tInsira a data de conclusão da carta (dia/mês/ano): ");
		scanf ("%d/%d/%d", &alunos[nAlunos].dataConclusaoCarta.dia, &alunos[nAlunos].dataConclusaoCarta.mes, &alunos[nAlunos].dataConclusaoCarta.ano);

		printf ("\n\n\tInsira o número da carta: ");
		scanf ("%d", &alunos[nAlunos].nCarta);

		printf ("\n\n\tInsira a situação do aluno (ATIVO / NÃO ATIVO): ");
		scanf (" %50[^\n]s", &alunos[nAlunos].ativo);
        nAlunos++;
        esperaApaga("\n\n\tAluno inserido com sucesso! A redirecionar ....", 3);
}

//listar dados de um aluno
void dadosAluno(int aluno){
    printf ("\n\n< < < Dados do aluno %s > > >", alunos[aluno].nome);
    printf ("\n\n\tNumero: %s", alunos[aluno].nome);
    printf ("\n\n\tEmail: %s", alunos[aluno].email);
    printf ("\n\n\tCartão de cidadão: %s", alunos[aluno].cartaoCidadao);
    printf ("\n\n\tNIF: %d", alunos[aluno].nif);
    printf ("\n\n\tNº da carta: %d", alunos[aluno].nCarta);
    printf ("\n\n\tRua: %s", alunos[aluno].morada.rua);
    printf ("\n\n\tCódigo-postal: %s", alunos[aluno].morada.cpostal);
    printf ("\n\n\tLocalidae: %s", alunos[aluno].morada.localidade);
    printf ("\n\n\tData de nascimento: %d/%d/%d", alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano);
    printf ("\n\n\tData da conclusão da carta: %d/%d/%d", alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano);
    printf ("\n\n\tSituação: %d", alunos[aluno].ativo);
}

//Funcção para alterar dados de um aluno
void alteraAluno(int aluno){
    printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
    printf ("\n\n\tNumero: %s", alunos[aluno].nome);
    printf ("\n\n\tEmail: %s", alunos[aluno].email);
    printf ("\n\n\tCartão de cidadão: %s", alunos[aluno].cartaoCidadao);
    printf ("\n\n\tNIF: %d", alunos[aluno].nif);
    printf ("\n\n\tNº da carta: %d", alunos[aluno].nCarta);
    printf ("\n\n\tRua: %s", alunos[aluno].morada.rua);
    printf ("\n\n\tCódigo-postal: %s", alunos[aluno].morada.cpostal);
    printf ("\n\n\tLocalidae: %s", alunos[aluno].morada.localidade);
    printf ("\n\n\tData de nascimento: %d/%d/%d", alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano);
    printf ("\n\n\tData da conclusão da carta: %d/%d/%d", alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano);
    printf ("\n\n\tSituação: %d", alunos[aluno].ativo);
}

//Lista para consultar alterar todos os alunos
void listaTodos(){
    int op, i;
    char op2;
    printf ("\n\n< < < Listagem de alunos > > >");
    for(i = 0; i<nAlunos; i++){
        printf("\n\n\t %d - %s", i+1, alunos[i].nome);
    }
    printf("\n\n\t 0 - Voltar");
    printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
    scanf("%d", &op);
    if(op != 0){
        system("clear||cls");
        op--;
        dadosAluno(op);
        printf("\n\n Pretende alterar este aluno? (y/N): ");
        scanf(" %c", &op2);
        system("clear||cls");
        if(op2 == "Y" || op2 == "y"){
            alteraAluno(op);
        }
    }
}

//Lista para procurar aluno por nome
void listaNome(){
    int op;
    printf("\n Insira o numero do aluno que deseja consultar/alterar: ");
    scanf("%d", &op);
    system("clear||cls");
    op--;
    dadosAluno(op);
}

void gerirDadosAlunos(){
	int op;
    do{
        printf ("\n\n< < < Consultar/Alterar dados dos alunos > > >");
        printf ("\n\n\t1 - Todos");
        printf ("\n\n\t2 - Nome");
        printf ("\n\n\t3 - Nº do aluno");
        printf ("\n\n\t4 - Email");
        printf ("\n\n\t5 - Cartão de cidadão");
        printf ("\n\n\t6 - NIF");
        printf ("\n\n\t7 - Nº da Carta");
        printf ("\n\n\t8 - Situação do aluno");
        printf ("\n\n\t0 - Voltar");
        printf ("\n\nInsira a sua opção: ");
        scanf ("%d", &op);
        system("clear||cls");
        switch (op) {
            case 1:
                listaTodos();
            break;
            case 2:
                listaNome();
            break;
        }
    }while (op != 0);
}

//menu de gestão dos alunos
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
                gerirDadosAlunos();
            break;
        }
    }while (op != 0);
} 

////////////////////////////////////////////////////////////////////////////////////
//Instrutores
////////////////////////////////////////////////////////////////////////////////////

//Estrutura de dados definida para os instrutores
typedef struct {
    int dia;
    int mes;
    int ano;
} ANOENTRADAESCOLA;

typedef struct {
    int nInstrutor;
    char nome[50];
    char email[50];
    char cartaoCidadao[20];
    int ativo;
    ANOENTRADAESCOLA anoEntradaEscola; 
} INSTRUTORES;

INSTRUTORES instrutores[10];

//insere um instrutor
void inserirInstrutor() {
        
        printf ("\n\n< < < Inserção de Instrutor > > >");
        printf ("\n\n\tInsira o NOME do instrutor: ");
	    scanf (" %30[^\n]s", &instrutores[nInstrutores].nome);

        printf ("\n\n\tInsira o CARTÃO DE CIDADÃO: ");
	    scanf (" %30[^\n]s", &instrutores[nInstrutores].cartaoCidadao);
    
        printf ("\n\n\tInsira o EMAIL do instrutor: ");
        scanf (" %50[^\n]s", &instrutores[nInstrutores].email); 
    
        printf ("\n\n\tInsira o ANO DE ENTRADA NA ESCOLA: ");
        scanf ("%d/%d/%d", &instrutores[nInstrutores].anoEntradaEscola.dia, &instrutores[nInstrutores].anoEntradaEscola.mes, &instrutores[nInstrutores].anoEntradaEscola.ano);
    
        printf ("\n\n\tInsira a SITUAÇÃO do instrutor (1 - Ativo / 0 - Não Ativo): ");
	    scanf (" %50[^\n]s", &instrutores[nInstrutores].ativo);
        nInstrutores++;
        esperaApaga("Instrutor inserido com sucesso! A redirecionar ....", 3);
}

//menu de destão dos instrutores
void menuInstrutores(){
    int op;
    do {
        printf ("\n\n< < < MENU GESTÃO DE INSTRUTORES > > >");
        printf ("\n\n\t1 - Inserir novos instrutores");
        printf ("\n\n\t2 - Consultar/Alterar dados do instrutor");
        printf ("\n\n\t0 - Voltar");
        printf ("\n\nInsira a sua opção: ");
        scanf ("%d", &op);
        system("clear||cls");
        switch (op) {
            case 1:
                inserirInstrutor();
            break;
            case 2:
            break;
            case 3:
            break;
        }
    }while (op != 0);
}

////////////////////////////////////////////////////////////////////////////////////
//Aulas
////////////////////////////////////////////////////////////////////////////////////

//Estrutura de dados definida para as aulas

typedef struct{
    int dia;
    int mes;
    int ano;
} DATAAULA;

typedef struct {
    int aluno;
    int instrutor;
    DATAAULA dataAula;
} AULAS;

AULAS aulas[100];

//marcar Aula
void marcarAula(){
    printf("--- Listagem de alunos ---");
    printf("\n\n Insira o Aluno que deseja marcar a aula: ");
    scanf("%d", &aulas[nAulas].aluno);
    do{
        printf("\nPor favor insira um aluno válido:");
    }while(aulas[nAulas].aluno <= 0 && aulas[nAulas].aluno >= nAlunos + 1);
    scanf("%d/%d/%d", &aulas[nAlunos].dataAula.dia, &aulas[nAlunos].dataAula.mes, &aulas[nAlunos].dataAula.ano);
}

//consultarAula
void consultarAulas(){
}

//menu de gestão de aulas
void menuAulas(){
    int op;
    do{
        printf ("\n\n< < < MENU MARCAÇÃO/CONSULTA DE AULAS > > >");
        printf("\n\n\t1 - Marcar aulas");
        printf ("\n\n\t2 - Consultar aulas");
        printf ("\n\n\t0 - Voltar");
        printf ("\n\nInsira a sua opção: ");
        scanf ("%d", &op);

        switch(op){
            case 1:
                marcarAula();
            break;
            case 2:
                consultarAulas();
            break;
        }
    }while(op != 0);
}

////////////////////////////////////////////////////////////////////////////////////
//Função Main e Menu Principal
////////////////////////////////////////////////////////////////////////////////////

//Menu principal
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

//função principal onde o programa é inicializado
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