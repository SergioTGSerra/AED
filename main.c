////////////////////////////////////////////////////////////////////////////////////
//Bibliotecas
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>
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
void esperaApaga(char msg[100], int time){
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

//Função para aceitar apenas valores inteiros

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
    int nif;
    int nCarta;
    int ativo;
    
    MORADA morada;
    DATANASCIMENTO dataNascimento;
    DATACONCLUSAOCARTA dataConclusaoCarta;
} ALUNOS;

ALUNOS alunos[30];

int existeNoArray(int dado_i, char dado_c[20], char tipo){
    int i;
    for(i = 0; i < nAlunos; i++){
        switch (tipo){
            case 1:
                if(alunos[i].nAluno == dado_i){
                    printf ("\n\n\tJá existe um aluno com esse numero! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 2:
                if(strcmp(alunos[i].email, dado_c) == 0){
                    printf ("\n\n\tJá existe um aluno com esse email! Por favor insira outro.");
                    return 1; 
                }
            case 3:
                if(strcmp(alunos[i].cartaoCidadao, dado_c) == 0){
                    printf ("\n\n\tJá existe um aluno com esse cartão de cidadão! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 4:
                if(alunos[i].nif == dado_i){
                    printf ("\n\n\tJá existe um aluno com esse nif! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 5:
                if(alunos[i].nCarta == dado_i){
                    printf ("\n\n\tJá existe um aluno com esse numero de carta! Por favor insira outro.");
                    return 1; 
                }
            break;
        }
    }
    return 0;
}

//insere um aluno
void inserirAluno(){
    int i, j, flag  = 0;
    char msg[100];

    printf ("\n\n< < < Inserção de Aluno > > >");

    if(nAlunos > 30){
        strcpy(msg, "\n\n\tNumero máximo de alunos (30) excedido! A redirecionar ....");
        esperaApaga(msg, 3);
    }else{

        do{
            printf ("\n\n\tInsira o Nº do aluno: ");
            scanf ("%d", &alunos[nAlunos].nAluno);
            fflush(stdin);
            if(alunos[nAlunos].nAluno <= 0) do{
                printf ("\n\n\tPor favor insira um nº do aluno válido: ");
                scanf ("%d", &alunos[nAlunos].nAluno);
                fflush(stdin);
            }while(alunos[nAlunos].nAluno <= 0);
        }while(existeNoArray(alunos[nAlunos].nAluno, 0, 1) == 1);

        printf ("\n\n\tInsira o nome do aluno: ");
        scanf (" %50[^\n]s", &alunos[nAlunos].nome);

        printf("\n\n\tInsira a rua:");
        scanf (" %50[^\n]s", &alunos[nAlunos].morada.rua);

        printf("\n\n\tInsira a código de postal:");
        scanf (" %50[^\n]s", &alunos[nAlunos].morada.cpostal);

        printf("\n\n\tInsira a localidade:");
        scanf (" %50[^\n]s", &alunos[nAlunos].morada.localidade);

        do{
            printf ("\n\n\tInsira o email do aluno: ");
            scanf (" %50[^\n]s", &alunos[nAlunos].email);
        }while(existeNoArray(0, alunos[nAlunos].email, 2) == 1);
        
        printf ("\n\n\tInsira a data de nascimento (dia/mês/ano): ");
        scanf ("%d/%d/%d", &alunos[nAlunos].dataNascimento.dia, &alunos[nAlunos].dataNascimento.mes, &alunos[nAlunos].dataNascimento.ano);

        do{
            printf ("\n\n\tInsira o cartão de cidadão: ");
            scanf (" %20[^\n]s", &alunos[nAlunos].cartaoCidadao);
        }while(existeNoArray(0, alunos[nAlunos].cartaoCidadao, 3) == 1);

        do{
            printf ("\n\n\tInsira o NIF: ");
            scanf ("%d", &alunos[nAlunos].nif);
            fflush(stdin);
            if(alunos[nAlunos].nif <= 0) do{
                printf ("\n\n\tPor favor insira um nif válido: ");
                scanf ("%d", &alunos[nAlunos].nif);
                fflush(stdin);
            }while(alunos[nAlunos].nif <= 0);
        }while(existeNoArray(alunos[nAlunos].nif, 0, 4) == 1);

        printf ("\n\n\tInsira a data de conclusão da carta (dia/mês/ano): ");
        scanf ("%d/%d/%d", &alunos[nAlunos].dataConclusaoCarta.dia, &alunos[nAlunos].dataConclusaoCarta.mes, &alunos[nAlunos].dataConclusaoCarta.ano);

        do{
            printf ("\n\n\tInsira o número da carta: ");
            scanf ("%d", &alunos[nAlunos].nCarta);
            fflush(stdin);
            if(alunos[nAlunos].nCarta <= 0) do{
                printf ("\n\n\tPor favor insira um número da carta válido: ");
                scanf ("%d", &alunos[nAlunos].nCarta);
                fflush(stdin);
            }while(alunos[nAlunos].nCarta <= 0);
        }while(existeNoArray(alunos[nAlunos].nCarta, 0, 5) == 1);

        printf ("\n\n\tInsira a situação do aluno (1 - ATIVO / 0 - NÃO ATIVO): ");
        scanf ("%d", &alunos[nAlunos].ativo);
        fflush(stdin);
        if(alunos[nAlunos].ativo != 0 || alunos[nAlunos].ativo != 1) do{
            printf ("\n\n\tPor favor insira uma situação válida: ");
            scanf ("%d", &alunos[nAlunos].ativo);
            fflush(stdin);
        }while(alunos[nAlunos].ativo != 0 && alunos[nAlunos].ativo != 1);

        nAlunos++;
        strcpy(msg, "\n\n\tAluno inserido com sucesso! A redirecionar ....");
        esperaApaga(msg, 3);
    }
}

//listar dados de um aluno
void dadosAluno(int aluno){
    printf ("\n\n< < < Dados do aluno %s > > >", alunos[aluno].nome);
    printf ("\n\n\tNumero: %d", alunos[aluno].nAluno);
    printf ("\n\n\tNome: %s", alunos[aluno].nome);
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
    int op;
    char msg[100];
    printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
    printf ("\n\n\t1 - Numero: %d", alunos[aluno].nAluno);
    printf ("\n\n\t2 - Nome: %s", alunos[aluno].nome);
    printf ("\n\n\t3 - Email: %s", alunos[aluno].email);
    printf ("\n\n\t4 - Cartão de cidadão: %s", alunos[aluno].cartaoCidadao);
    printf ("\n\n\t5 - NIF: %d", alunos[aluno].nif);
    printf ("\n\n\t6 - Nº da carta: %d", alunos[aluno].nCarta);
    printf ("\n\n\t7 - Rua: %s", alunos[aluno].morada.rua);
    printf ("\n\n\t8 - Código-postal: %s", alunos[aluno].morada.cpostal);
    printf ("\n\n\t9 - Localidade: %s", alunos[aluno].morada.localidade);
    printf ("\n\n\t10 - Data de nascimento: %d/%d/%d", alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano);
    printf ("\n\n\t11 - Data da conclusão da carta: %d/%d/%d", alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano);
    printf ("\n\n\t12 - Situação: %d", alunos[aluno].ativo);
    printf ("\n\n\t0 - Voltar");

    printf("\n\nInsira a opção que deseja alterar: ");
    scanf("%d", &op);

    switch(op){
        case 1:
            system("clear||cls");
            strcpy(msg, "\n\n\tNão é possivel alerar o número do aluno! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 2:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o nome do aluno: ");
            scanf (" %50[^\n]s", &alunos[aluno].nome);
            strcpy(msg, "\n\n\tNome alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 3:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o email do aluno: ");
            scanf (" %50[^\n]s", &alunos[aluno].email);
            strcpy(msg, "\n\n\tE-mail alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 4:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Cartão de cidadão do aluno: ");
            scanf (" %50[^\n]s", &alunos[aluno].cartaoCidadao);
            strcpy(msg, "\n\n\tCartão de cidadão alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 5:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o NIF do aluno: ");
            scanf (" %d", &alunos[aluno].nif);
            strcpy(msg, "\n\n\tNIF alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 6:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Nº da carta do aluno: ");
            scanf (" %d", &alunos[aluno].nCarta);
            strcpy(msg, "\n\n\tNº da carta alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 7:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Rua do aluno: ");
            scanf (" %50[^\n]s", &alunos[aluno].morada.rua);
            strcpy(msg, "\n\n\tRua alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 8:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Código-postal do aluno: ");
            scanf (" %50[^\n]s", &alunos[aluno].morada.cpostal);
            strcpy(msg, "\n\n\tCódigo-postal alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 9:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Localidade do aluno: ");
            scanf (" %50[^\n]s", &alunos[aluno].morada.localidade);
            strcpy(msg, "\n\n\tLocalidade alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 10:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Data de nascimento do aluno: ");
            scanf (" %d/%d/%d", &alunos[aluno].dataNascimento.dia, &alunos[aluno].dataNascimento.mes, &alunos[aluno].dataNascimento.ano );
            strcpy(msg, "\n\n\tData de nascimento alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 11:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Data da conclusão da carta do aluno: ");
            scanf ("%d/%d/%d", &alunos[aluno].dataConclusaoCarta.dia, &alunos[aluno].dataConclusaoCarta.mes, &alunos[aluno].dataConclusaoCarta.ano);
            strcpy(msg, "\n\n\tData da conclusão da carta alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
        case 12:
            system("clear||cls");
            printf ("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
            printf ("\n\n\tAltere o Situação do aluno: ");
            scanf (" %d", &alunos[aluno].ativo);
            strcpy(msg, "\n\n\tSituação alterado com sucesso! A redirecionar ....");
            esperaApaga(msg, 3);
            alteraAluno(aluno);
        break;
    }
    system("clear||cls");
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
        if(op2 == 'Y' || op2 == 'y'){
            alteraAluno(op);
        }
    }
}

//Lista para procurar aluno por nome
void listarNome(){
    int i;
    char nome[50];
    printf ("Insira o nome do aluno que pretende consultar: ");
    scanf (" %50[^\n]s", &nome);
    for(i = 0; i < nAlunos; i++){
        if((alunos[i].nome == nome || alunos[i].nome[0] == nome[0])){
            printf("\n%d - %s", i +1, alunos[i].nome);
        }
    }
}

//menu consultar/alterar
void menuConsutarAlterarAlunos(){
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
                listarNome();
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
                menuConsutarAlterarAlunos();
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
        char msg[100];
        strcpy(msg, "\n\n\tInstrutor inserido com sucesso! A redirecionar ....");
        esperaApaga(msg, 3);
}

//listar dados de um instrutor
void dadosInstrutor(int instrutor){
    printf ("\n\n< < < Dados do instrutor %s > > >", instrutores[instrutor].nome);
    printf ("\n\n\tEmail: %s", instrutores[instrutor].email);
    printf ("\n\n\tCartão de cidadão: %s", instrutores[instrutor].cartaoCidadao);
    printf ("\n\n\tAno de entrada na escola: %d/%d/%d", instrutores[instrutor].anoEntradaEscola.dia, instrutores[instrutor].anoEntradaEscola.mes, instrutores[instrutor].anoEntradaEscola.ano);
    printf ("\n\n\tSituação: %d", instrutores[instrutor].ativo);
}

//Funcção para alterar dados de um instrutor
void alteraInstrutor(int instrutor){
    printf ("\n\n< < < Dados do instrutor %s > > >", instrutores[instrutor].nome);
    printf ("\n\n\tEmail: %s", instrutores[instrutor].email);
    printf ("\n\n\tCartão de cidadão: %s", instrutores[instrutor].cartaoCidadao);
    printf ("\n\n\tAno de entrada na escola: %d/%d/%d", instrutores[instrutor].anoEntradaEscola.dia, instrutores[instrutor].anoEntradaEscola.mes, instrutores[instrutor].anoEntradaEscola.ano);
    printf ("\n\n\tSituação: %d", instrutores[instrutor].ativo); 
}

//Lista para consultar alterar todos os instrutores
void listaTodosIns(){
    int op, i;
    char op2;
    printf ("\n\n< < < Listagem de instrutores > > >");
    for(i = 0; i<nInstrutores; i++){
        printf("\n\n\t %d - %s", i+1, instrutores[i].nome);
    }
    printf("\n\n\t 0 - Voltar");
    printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
    scanf("%d", &op);
    if(op != 0){
        system("clear||cls");
        op--;
        dadosInstrutor(op);
        printf("\n\n Pretende alterar este instrutor? (y/N): ");
        scanf(" %c", &op2);
        system("clear||cls");
        if(op2 == 'Y' || op2 == 'y'){
            alteraInstrutor(op);
        }
    }
}

void gerirDadosInstrutores(){
	int op;
    do{
        printf ("\n\n< < < Consultar/Alterar dados dos alunos > > >");
        printf ("\n\n\t1 - Todos");
        printf ("\n\n\t2 - Nome");
        printf ("\n\n\t4 - Email");
        printf ("\n\n\t5 - Ano de entrada");
        printf ("\n\n\t6 - Cartão de cidadão");
        printf ("\n\n\t7 - Situação do instrutor");
        printf ("\n\n\t0 - Voltar");
        printf ("\n\nInsira a sua opção: ");
        scanf ("%d", &op);
        system("clear||cls");
        switch (op) {
            case 1:
                listaTodosIns();
            break;
            case 2:
            break;
        }
    }while (op != 0);
}

//menu de gestão dos instrutores
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
            gerirDadosInstrutores();
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
