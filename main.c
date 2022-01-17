 
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
//Estruturas Universais (Utilizado para outras estruturas)
////////////////////////////////////////////////////////////////////////////////////
typedef struct {
        char rua[50];
        int porta;
        char cpostal[50];
        char localidade[50];
} MORADA;

typedef struct {
    int dia;
    int mes;
    int ano;
} DATA;

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

//Função para validar uma data
int dataValida(int dia, int mes, int ano){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    //tm.tm_year ano atual
    //verifica intrevalo de datas
    if (ano > (tm.tm_year + 1900) || ano < 1900) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;
    return 1;
}

int calculaIdade(int dia, int mes, int ano){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int anoAtual = tm.tm_year + 1900;
    int mesAtual = tm.tm_mon + 1;
    int diaAtual = tm.tm_mday;
    // days of every month
    int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dia > diaAtual) {
        diaAtual = diaAtual + month[mes - 1];
        mesAtual = mesAtual - 1;
    }
    if (mes > mesAtual) {
        anoAtual = anoAtual - 1;
        mesAtual = mesAtual + 12;
    }
    int idade = anoAtual - ano;
    return idade;
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
    int nAluno;
    char nome[50];
    char email[50];
    char cartaoCidadao[50];
    int nif;
    int nCarta;
    int ativo;
    
    MORADA morada;
    DATA dataNascimento;
    DATA dataConclusaoCarta;
} ALUNOS;

ALUNOS alunos[30];

int existeNoArray(int dado_i, char dado_s[50], char tipo){
    int i;
    for(i = 0; i < nAlunos; i++){
        switch (tipo){
            case 1:
                if(alunos[i].nAluno == dado_i){
                    printf("\n\n\tJá existe um aluno com esse numero! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 2:
                if(strcmp(alunos[i].email, dado_s) == 0){
                    printf("\n\n\tJá existe um aluno com esse email! Por favor insira outro.");
                    return 1; 
                }
            case 3:
                if(strcmp(alunos[i].cartaoCidadao, dado_s) == 0){
                    printf("\n\n\tJá existe um aluno com esse cartão de cidadão! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 4:
                if(alunos[i].nif == dado_i){
                    printf("\n\n\tJá existe um aluno com esse nif! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 5:
                if(alunos[i].nCarta == dado_i){
                    printf("\n\n\tJá existe um aluno com esse numero de carta! Por favor insira outro.");
                    return 1; 
                }
            break;
        }
    }
    return 0;
}

//insere um aluno
void inserirAluno(){
    int i, j, flag  = 0, concluiCarta = 0;
    char msg[100];
    system("clear||cls");
    printf("\n\n< < < Inserção de Aluno > > >");

    if(nAlunos >= 30){
        strcpy(msg, "\n\n\tNumero máximo de alunos (30) excedido! A redirecionar ....");
        esperaApaga(msg, 3);
    }else{

        do{
            printf("\n\n\tInsira o Nº do aluno: ");
            scanf("%d", &alunos[nAlunos].nAluno);
            fflush(stdin);
            if(alunos[nAlunos].nAluno <= 0) do{
                printf("\n\n\tPor favor insira um nº do aluno válido: ");
                scanf("%d", &alunos[nAlunos].nAluno);
                fflush(stdin);
            }while(alunos[nAlunos].nAluno <= 0);
        }while(existeNoArray(alunos[nAlunos].nAluno, 0, 1) == 1);

        printf("\n\n\tInsira o nome do aluno: ");
        scanf(" %50[^\n]s", &alunos[nAlunos].nome);

        printf("\n\n\tInsira a localidade:");
        scanf(" %50[^\n]s", &alunos[nAlunos].morada.localidade);

        printf("\n\n\tInsira a rua:");
        scanf(" %50[^\n]s", &alunos[nAlunos].morada.rua);

        printf("\n\n\tInsira a porta:");
        scanf("%d", &alunos[nAlunos].morada.porta);
        fflush(stdin);

        printf("\n\n\tInsira o código de postal:");
        scanf(" %50[^\n]s", &alunos[nAlunos].morada.cpostal);

        do{
            printf("\n\n\tInsira o email do aluno: ");
            scanf(" %50[^\n]s", &alunos[nAlunos].email);
        }while(existeNoArray(0, alunos[nAlunos].email, 2) == 1);
        
        printf("\n\n\tInsira a data de nascimento (dia/mês/ano): ");
        scanf("%d/%d/%d", &alunos[nAlunos].dataNascimento.dia, &alunos[nAlunos].dataNascimento.mes, &alunos[nAlunos].dataNascimento.ano);
        fflush(stdin);
        if(dataValida(alunos[nAlunos].dataNascimento.dia, alunos[nAlunos].dataNascimento.mes, alunos[nAlunos].dataNascimento.ano) != 1) do{
            printf("\n\n\tPor favor insira a data de nascimento válida (dia/mês/ano): ");
            scanf("%d/%d/%d", &alunos[nAlunos].dataNascimento.dia, &alunos[nAlunos].dataNascimento.mes, &alunos[nAlunos].dataNascimento.ano);
            fflush(stdin);
        }while(dataValida(alunos[nAlunos].dataNascimento.dia, alunos[nAlunos].dataNascimento.mes, alunos[nAlunos].dataNascimento.ano) != 1);

        do{
            printf("\n\n\tInsira o cartão de cidadão: ");
            scanf(" %50[^\n]s", &alunos[nAlunos].cartaoCidadao);
        }while(existeNoArray(0, alunos[nAlunos].cartaoCidadao, 3) == 1);

        do{
            printf("\n\n\tInsira o NIF: ");
            scanf("%d", &alunos[nAlunos].nif);
            fflush(stdin);
            if(alunos[nAlunos].nif <= 0) do{
                printf("\n\n\tPor favor insira um nif válido: ");
                scanf("%d", &alunos[nAlunos].nif);
                fflush(stdin);
            }while(alunos[nAlunos].nif <= 0);
        }while(existeNoArray(alunos[nAlunos].nif, 0, 4) == 1);

        printf("\n\n\tO aluno(a) já concluiu a carta? (1 - Sim / 0 - Não): ");
        scanf("%d", &concluiCarta);
        fflush(stdin);

        if(concluiCarta == 1){
            do{
                printf("\n\n\tInsira o número da carta: ");
                scanf("%d", &alunos[nAlunos].nCarta);
                fflush(stdin);
                if(alunos[nAlunos].nCarta <= 0) do{
                    printf("\n\n\tPor favor insira um número da carta válido: ");
                    scanf("%d", &alunos[nAlunos].nCarta);
                    fflush(stdin);
                }while(alunos[nAlunos].nCarta <= 0);
            }while(existeNoArray(alunos[nAlunos].nCarta, 0, 5) == 1);

            printf("\n\n\tInsira a data de conclusão da carta (dia/mês/ano): ");
            scanf("%d/%d/%d", &alunos[nAlunos].dataConclusaoCarta.dia, &alunos[nAlunos].dataConclusaoCarta.mes, &alunos[nAlunos].dataConclusaoCarta.ano);
            fflush(stdin);
            if(dataValida(alunos[nAlunos].dataConclusaoCarta.dia, alunos[nAlunos].dataConclusaoCarta.mes, alunos[nAlunos].dataConclusaoCarta.ano) != 1) do{
                printf("\n\n\tPor favor insira a data de conclusão da carta válida (dia/mês/ano): ");
                scanf("%d/%d/%d", &alunos[nAlunos].dataConclusaoCarta.dia, &alunos[nAlunos].dataConclusaoCarta.mes, &alunos[nAlunos].dataConclusaoCarta.ano);
                fflush(stdin);
            }while(dataValida(alunos[nAlunos].dataConclusaoCarta.dia, alunos[nAlunos].dataConclusaoCarta.mes, alunos[nAlunos].dataConclusaoCarta.ano) != 1);
        }        

        printf("\n\n\tInsira a situação do aluno (1 - ATIVO / 0 - NÃO ATIVO): ");
        scanf("%d", &alunos[nAlunos].ativo);
        fflush(stdin);
        if(alunos[nAlunos].ativo != 0 && alunos[nAlunos].ativo != 1) do{
            printf("\n\n\tPor favor insira uma situação válida: ");
            scanf("%d", &alunos[nAlunos].ativo);
            fflush(stdin);
        }while(alunos[nAlunos].ativo != 0 && alunos[nAlunos].ativo != 1);

        nAlunos++;
        strcpy(msg, "\n\n\tAluno inserido com sucesso! A redirecionar ....");
        esperaApaga(msg, 3);
    }
}

//consultar dados de um aluno
int dadosAluno(int aluno){
    if (alunos[aluno].nAluno == 0) return 0;
    system("clear||cls");
    printf("\n\n< < < Dados do aluno %s > > >", alunos[aluno].nome);
    printf("\n\n\tNumero: %d", alunos[aluno].nAluno);
    printf("\n\n\tNome: %s", alunos[aluno].nome);
    printf("\n\n\tLocalidae: %s", alunos[aluno].morada.localidade);
    printf("\n\n\tRua: %s", alunos[aluno].morada.rua);
    printf("\n\n\tPorta: %d", alunos[aluno].morada.porta);
    printf("\n\n\tCódigo-postal: %s", alunos[aluno].morada.cpostal);
    printf("\n\n\tEmail: %s", alunos[aluno].email);
    printf("\n\n\tData de nascimento: %d/%d/%d", alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano);
    printf("\n\n\tCartão de cidadão: %s", alunos[aluno].cartaoCidadao);
    printf("\n\n\tNIF: %d", alunos[aluno].nif);
    printf("\n\n\tNº da carta: %d", alunos[aluno].nCarta);
    printf("\n\n\tData da conclusão da carta: %d/%d/%d", alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano);
    printf("\n\n\tSituação: %d", alunos[aluno].ativo);
}

//Funcção para alterar dados de um aluno
int alteraAluno(int aluno){
    if (alunos[aluno].nAluno == 0) return 0;
    /* temp_d -> dado temporario inteiro
       temp_s -> dado temporario string
       Nota: Estes dados temporarios estão aqui presentes para que os dados apenas fiquem
             guardados em um variavel local da funcao para que ao procurar no array (função existeNoArray)
             não encontre os dados que estamos a alterar.
    */
    int op, temp_d;
    char temp_s[30];
    char msg[100];
    do{
        system("clear||cls");
        printf("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);
        printf("\n\n\t1 - Número: %d", alunos[aluno].nAluno);
        printf("\n\n\t2 - Nome: %s", alunos[aluno].nome);
        printf("\n\n\t3 - Localidade: %s", alunos[aluno].morada.localidade);
        printf("\n\n\t4 - Rua: %s", alunos[aluno].morada.rua);
        printf("\n\n\t5 - Porta: %d", alunos[aluno].morada.porta);
        printf("\n\n\t6 - Código-postal: %s", alunos[aluno].morada.cpostal);
        printf("\n\n\t7 - Email: %s", alunos[aluno].email);
        printf("\n\n\t8 - Data de nascimento: %d/%d/%d", alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano);
        printf("\n\n\t9 - Cartão de cidadão: %s", alunos[aluno].cartaoCidadao);
        printf("\n\n\t10 - NIF: %d", alunos[aluno].nif);
        printf("\n\n\t11 - Nº da carta: %d", alunos[aluno].nCarta);
        printf("\n\n\t12 - Data da conclusão da carta: %d/%d/%d", alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano);
        printf("\n\n\t13 - Situação: %d", alunos[aluno].ativo);
        printf("\n\n\t0 - Voltar");

        printf("\n\nInsira a opção que deseja alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        system("clear||cls");
        printf("\n\n< < < Alterar dados do aluno %s > > >", alunos[aluno].nome);

        switch(op){
            case 1:
                strcpy(msg, "\n\n\tNão é possivel alerar o número do aluno! A redirecionar ....");
            break;
            case 2:
                printf("\n\n\tAltere o nome do aluno: ");
                scanf(" %50[^\n]s", &alunos[aluno].nome);
                strcpy(msg, "\n\n\tNome alterado com sucesso! A redirecionar ....");
            break;
            case 3:
                printf("\n\n\tAltere a localidade do aluno: ");
                scanf(" %50[^\n]s", &alunos[aluno].morada.localidade);
                strcpy(msg, "\n\n\tLocalidade alterada com sucesso! A redirecionar ....");
            break;
            case 4:
                printf("\n\n\tAltere a rua do aluno: ");
                scanf(" %50[^\n]s", &alunos[aluno].morada.rua);
                strcpy(msg, "\n\n\tRua alterado com sucesso! A redirecionar ....");
            break;
            case 5:
                printf("\n\n\tAltere a porta do aluno: ");
                scanf("%d", &alunos[aluno].morada.porta);
                fflush(stdin);
                strcpy(msg, "\n\n\tPorta alterada com sucesso! A redirecionar ....");
            break;
            case 6:
                printf("\n\n\tAltere o código de postal do aluno: ");
                scanf(" %50[^\n]s", &alunos[aluno].morada.cpostal);
                strcpy(msg, "\n\n\tCódigo de postal alterado com sucesso! A redirecionar ....");
            break;
            case 7:
                do{
                    //limpa string do array
                    memset(alunos[aluno].email, 0, 30);
                    printf("\n\n\tAltere o email do aluno: ");
                    scanf(" %30[^\n]s", &temp_s);
                }while(existeNoArray(0, temp_s, 2) == 1);
                strcpy(alunos[aluno].email, temp_s);
                strcpy(msg, "\n\n\tE-mail alterado com sucesso! A redirecionar ....");
            break;
            case 8:
                printf("\n\n\tAltere a data de nascimento (dia/mês/ano): ");
                scanf("%d/%d/%d", &alunos[aluno].dataNascimento.dia, &alunos[aluno].dataNascimento.mes, &alunos[aluno].dataNascimento.ano);
                fflush(stdin);
                if(dataValida(alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano) != 1) do{
                    printf("\n\n\tPor favor insira a data de nascimento válida (dia/mês/ano): ");
                    scanf("%d/%d/%d", &alunos[aluno].dataNascimento.dia, &alunos[aluno].dataNascimento.mes, &alunos[aluno].dataNascimento.ano);
                    fflush(stdin);
                }while(dataValida(alunos[aluno].dataNascimento.dia, alunos[aluno].dataNascimento.mes, alunos[aluno].dataNascimento.ano) != 1);
                strcpy(msg, "\n\n\tData de nascimento alterada com sucesso! A redirecionar ....");
            break;
            case 9:
                do{
                    //limpa string do array
                    memset(alunos[aluno].cartaoCidadao, 0, 30);
                    printf("\n\n\tAltere o cartão de cidadão do aluno: ");
                    scanf(" %30[^\n]s", &temp_s);
                }while(existeNoArray(0, temp_s, 3) == 1);
                strcpy(alunos[aluno].cartaoCidadao, temp_s);
                strcpy(msg, "\n\n\tCartão de cidadão alterado com sucesso! A redirecionar ....");
            break;
            case 10:
                do{
                    //"limpa" inteiro do array 
                    alunos[aluno].nif = -1;
                    printf("\n\n\tAltere o NIF do aluno: ");
                    scanf("%d", &temp_d);
                    fflush(stdin);
                    if(temp_d <= 0) do{
                        printf("\n\n\tPor favor insira um nif válido: ");
                        scanf("%d", &temp_d);
                        fflush(stdin);
                    }while(temp_d <= 0);
                }while(existeNoArray(temp_d, 0, 4) == 1);
                alunos[aluno].nif = temp_d;
                strcpy(msg, "\n\n\tNIF alterado com sucesso! A redirecionar ....");
            break;
            case 11:
                do{
                    //"limpa" inteiro do array 
                    alunos[aluno].nCarta = -1;
                    printf("\n\n\tAltere o número da carta do aluno: ");
                    scanf("%d", &temp_d);
                    fflush(stdin);
                    if(temp_d <= 0) do{
                        printf("\n\n\tPor favor insira um número da carta válido: ");
                        scanf("%d", &temp_d);
                        fflush(stdin);
                    }while(temp_d <= 0);
                }while(existeNoArray(temp_d, 0, 5) == 1);
                alunos[aluno].nCarta = temp_d;
                strcpy(msg, "\n\n\tNúmero da carta alterado com sucesso! A redirecionar ....");
            break;
            case 12:
                printf("\n\n\tAltere a data de conclusão da carta (dia/mês/ano): ");
                scanf("%d/%d/%d", &alunos[aluno].dataConclusaoCarta.dia, &alunos[aluno].dataConclusaoCarta.mes, &alunos[aluno].dataConclusaoCarta.ano);
                fflush(stdin);
                if(dataValida(alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano) != 1) do{
                    printf("\n\n\tPor favor insira a data de conclusão da carta válida (dia/mês/ano): ");
                    scanf("%d/%d/%d", &alunos[aluno].dataConclusaoCarta.dia, &alunos[aluno].dataConclusaoCarta.mes, &alunos[aluno].dataConclusaoCarta.ano);
                    fflush(stdin);
                }while(dataValida(alunos[aluno].dataConclusaoCarta.dia, alunos[aluno].dataConclusaoCarta.mes, alunos[aluno].dataConclusaoCarta.ano) != 1);
                strcpy(msg, "\n\n\tData da conclusão da carta alterado com sucesso! A redirecionar ....");
            break;
            case 13:
                printf("\n\n\tAltere a situação do aluno (1 - ATIVO / 0 - NÃO ATIVO): ");
                scanf("%d", &alunos[aluno].ativo);
                fflush(stdin);
                if(alunos[aluno].ativo != 0 && alunos[aluno].ativo != 1) do{
                    printf("\n\n\tPor favor insira uma situação válida: ");
                    scanf("%d", &alunos[aluno].ativo);
                    fflush(stdin);
                }while(alunos[aluno].ativo != 0 && alunos[aluno].ativo != 1);
                strcpy(msg, "\n\n\tSituação alterado com sucesso! A redirecionar ....");
            break;
        }
        if(op != 0) esperaApaga(msg, 3);
    }while(op != 0);
}

//consultar para consultar/alterar todos os alunos
void consultarTodos(){
    int op, i;
    char op2;
    system("clear||cls");
    printf("\n\n< < < Listagem de alunos > > >");
    for(i = 0; i<nAlunos; i++){
        printf("\n\n\t %d - %s", i+1, alunos[i].nome);
    }
    printf("\n\n\t 0 - Voltar");
    printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
    scanf("%d", &op);
    fflush(stdin);
    if(op != 0 && alunos[op-1].nAluno != 0){
        op--;
        dadosAluno(op);
        printf("\n\n Pretende alterar este aluno? (y/N): ");
        scanf(" %c", &op2);
        if(op2 == 'Y' || op2 == 'y'){
            alteraAluno(op);
        }
    }
}

//Procurar aluno por nome
void consultarPorNome(){
    int i, op, cont = 1, ids[30], flag = 0;
    char nome[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o nome do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &nome);
    if(strlen(nome) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo nome: ");
        scanf(" %50[^\n]s", &nome);
    }while(strlen(nome) < 3);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (strstr(alunos[i].nome, nome)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' no nome > > >", nome);
        for(i = 0; i < nAlunos; i++){
            if (strstr(alunos[i].nome, nome)){
                printf("\n\n\t %d - %s", cont, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i; 
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com esse numero encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por numero
void consultarPorNumero(){
    int i, numero, op, flag = 0;
    char op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o numero do aluno que pretende consultar: ");
    scanf("%d", &numero);
    fflush(stdin);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (alunos[i].nAluno == numero){
            flag = 1;
            dadosAluno(i);
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(i);
            }
        }
    }
    if(flag == 0){
        strcpy(msg, "\n\n\tNenhum aluno com esse numero encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por E-mail
void consultarPorEmail(){
    int i, op, cont = 1, ids[30], flag = 0;
    char email[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o email do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &email);
    if(strlen(email) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo email: ");
        scanf(" %50[^\n]s", &email);
    }while(strlen(email) < 3);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (strstr(alunos[i].email, email)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' no email > > >", email);
        for(i = 0; i < nAlunos; i++){
            if (strstr(alunos[i].email, email)){
                printf("\n\n\t %d - %s - %s", cont, alunos[i].email, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com esse email encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por Cartão de Cidadão
void consultarPorCc(){
    int i, op, cont = 1, ids[30], flag = 0;
    char cc[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o Cartão de Cidadão do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &cc);
    if(strlen(cc) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo Cartão de Cidadão: ");
        scanf(" %50[^\n]s", &cc);
    }while(strlen(cc) < 3);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (strstr(alunos[i].cartaoCidadao, cc)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' no Cartão de Cidadão > > >", cc);
        for(i = 0; i < nAlunos; i++){
            if (strstr(alunos[i].cartaoCidadao, cc)){
                printf("\n\n\t %d - %s - %s", cont, alunos[i].cartaoCidadao, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com esse Cartão de Cidadão encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por NIF
void consultarPorNif(){
    int i, op, cont = 1, ids[30], flag = 0;
    //str vai converter o inteiro para caracter para procurar uma parte do nif
    char nif[50], op2, msg[100], str[30];
    system("clear||cls");
    printf("\n\n\tInsira o NIF do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &nif);
    if(strlen(nif) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo NIF: ");
        scanf(" %50[^\n]s", &nif);
    }while(strlen(nif) < 3);
    system("clear||cls");
    //verifica se existe no array
    for(i = 0; i < nAlunos; i++){
        //str vai converter o inteiro para caracter para procurar uma parte do nif
        sprintf(str, "%d", alunos[i].nif);
        if (strstr(str, nif)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' no NIF > > >", nif);
        for(i = 0; i < nAlunos; i++){
            //str vai converter o inteiro para caracter para procurar uma parte do nif
            sprintf(str, "%d", alunos[i].nif);
            if (strstr(str, nif)){
                printf("\n\n\t %d - %d - %s", cont, alunos[i].nif, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com esse NIF encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por nCarta
void consultarPorNcarta(){
    int i, op, cont = 1, ids[30], flag = 0;
    //str vai converter o inteiro para caracter para procurar uma parte do nCarta
    char nCarta[50], op2, msg[100], str[30];
    system("clear||cls");
    printf("\n\n\tInsira o Numero de Carta do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &nCarta);
    if(strlen(nCarta) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo NIF: ");
        scanf(" %50[^\n]s", &nCarta);
    }while(strlen(nCarta) < 3);
    system("clear||cls");
    //verifica se existe no array
    for(i = 0; i < nAlunos; i++){
        //str vai converter o inteiro para caracter para procurar uma parte do nCarta
        sprintf(str, "%d", alunos[i].nCarta);
        if (strstr(str, nCarta)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' no Nº de Carta > > >", nCarta);
        for(i = 0; i < nAlunos; i++){
            //str vai converter o inteiro para caracter para procurar uma parte do nCarta
            sprintf(str, "%d", alunos[i].nCarta);
            if (strstr(str, nCarta)){
                printf("\n\n\t %d - %d - %s", cont, alunos[i].nCarta, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com esse Nº de carta foi encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por situação
void consultarPorSituacao(){
    int i, situacao, op, cont = 1, flag = 0;
    char msg[100], ids[30], op2;
    system("clear||cls");
    printf("\n\n\tInsira a Situação que pretende consultar (1 - Ativo / 0 - Inativo): ");
    scanf("%d", &situacao);
    fflush(stdin);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if(alunos[i].ativo == situacao){
            flag = 1;
            break;
        }
    }
    if((situacao == 1 || situacao == 0) && (flag = 1)){
        if(situacao == 1) printf("\n\n< < < Listagem de alunos Ativos > > >");
        if(situacao == 0) printf("\n\n< < < Listagem de alunos Inativos > > >");
        for(i = 0; i < nAlunos; i++){
            if(alunos[i].ativo == situacao){
               printf("\n\n\t %d - %s", cont, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;                 
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com essa Situação foi encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por cpostal
void consultarPorCpostal(){
    int i, op, cont = 1, ids[30], flag = 0;
    char cpostal[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o Código de Postal do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &cpostal);
    if(strlen(cpostal) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo Código de Postal: ");
        scanf(" %50[^\n]s", &cpostal);
    }while(strlen(cpostal) < 3);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (strstr(alunos[i].morada.cpostal, cpostal)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' no Código de Postal > > >", cpostal);
        for(i = 0; i < nAlunos; i++){
            if (strstr(alunos[i].morada.cpostal, cpostal)){
                printf("\n\n\t %d - %s - %s", cont, alunos[i].morada.cpostal, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com esse Código postal encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar aluno por Localidade
void consultarPorLocalidade(){
    int i, op, cont = 1, ids[30], flag = 0;
    char localidade[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira a localidade do aluno que pretende consultar: ");
    scanf(" %50[^\n]s", &localidade);
    if(strlen(localidade) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pela localidade: ");
        scanf(" %50[^\n]s", &localidade);
    }while(strlen(localidade) < 3);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (strstr(alunos[i].morada.localidade, localidade)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que contem '%s' na localidade > > >", localidade);
        for(i = 0; i < nAlunos; i++){
            if (strstr(alunos[i].morada.localidade, localidade)){
                printf("\n\n\t %d - %s - %s", cont, alunos[i].morada.localidade, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com essa localidade encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar por data de nascimento
void ConsultarPorDNascimento(){
    int i, op, cont = 1, ids[30], flag = 0, dia, mes, ano;
    char op2, msg[100];
    system("clear||cls");
    
    printf("\n\n\tInsira a data de nascimento do aluno que pretende consultar (dia/mês/ano): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    fflush(stdin);
    if(dataValida(dia, mes, ano) != 1)do{
        printf("\n\n\tPor favor insira a data de nascimento válida (dia/mês/ano): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
    }while(dataValida(dia, mes, ano) != 1);
    
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (alunos[i].dataNascimento.dia == dia && alunos[i].dataNascimento.mes == mes && alunos[i].dataNascimento.ano == ano){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que nasceram em %d/%d/%d ! > > >", dia, mes, ano);
        for(i = 0; i < nAlunos; i++){
            if (alunos[i].dataNascimento.dia == dia && alunos[i].dataNascimento.mes == mes && alunos[i].dataNascimento.ano == ano){
                printf("\n\n\t %d - %d/%d/%d - %s", cont, dia, mes, ano, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com essa data de nascimento encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar por data de conclusão da carta
void ConsultarPorDConclusaoCarta(){
    int i, op, cont = 1, ids[30], flag = 0, dia, mes, ano;
    char op2, msg[100];
    system("clear||cls");
    
    printf("\n\n\tInsira a data de conclusão da carta do aluno que pretende consultar (dia/mês/ano): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    fflush(stdin);
    if(dataValida(dia, mes, ano) != 1)do{
        printf("\n\n\tPor favor insira a data de conclusão da carta válida (dia/mês/ano): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
    }while(dataValida(dia, mes, ano) != 1);
    
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (alunos[i].dataConclusaoCarta.dia == dia && alunos[i].dataConclusaoCarta.mes == mes && alunos[i].dataConclusaoCarta.ano == ano){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de alunos que concluiram a carta em %d/%d/%d ! > > >", dia, mes, ano);
        for(i = 0; i < nAlunos; i++){
            if (alunos[i].dataConclusaoCarta.dia == dia && alunos[i].dataConclusaoCarta.mes == mes && alunos[i].dataConclusaoCarta.ano == ano){
                printf("\n\n\t %d - %d/%d/%d - %s", cont, dia, mes, ano, alunos[i].nome);
                //posicao de cada aluno no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno com essa data de conclusão de carta encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar Aluno Por Idades
void consultarPorIdade(){
    int i, op, cont = 1, ids[30], flag = 0, idade, mensagemAtiva1 = 0, mensagemAtiva2 = 0, idadeCalculada;
    char op2, msg[100];
    system("clear||cls");
    
    printf("\n\n\tInsira a idade que pretende consultar : ");
    scanf("%d", &idade);
    fflush(stdin);
    
    if(idade < 1 || idade > 150)do{
        printf("\n\n\tPor favor insira uma idade válida : ");
        scanf("%d", &idade);
        fflush(stdin);
    }while(idade < 1 || idade > 150);
    
    system("clear||cls");

    for(i = 0; i < nAlunos; i++){
        idadeCalculada = calculaIdade(alunos[i].dataNascimento.dia, alunos[i].dataNascimento.mes, alunos[i].dataNascimento.ano);
        if(idadeCalculada > idade){
            flag = 1;
            break;
        }else{
            flag = 1;
            break;
        }
    }

    if(flag == 1){
        
        for(i = 0; i < nAlunos; i++){
            idadeCalculada = calculaIdade(alunos[i].dataNascimento.dia, alunos[i].dataNascimento.mes, alunos[i].dataNascimento.ano);
            if(idadeCalculada > idade){
                if(mensagemAtiva1 == 0) printf("\n\n< < < Listagem de alunos com idade igual ou superior a %d ! > > >", idade);
                mensagemAtiva1 = 1;
                printf("\n\n\t %d - %d - %s", cont, idadeCalculada, alunos[i].nome);
                ids[cont] = i;
                cont++;
            }else{
                if(mensagemAtiva2 == 0) printf("\n\n< < < Listagem de alunos com inferior a %d ! > > >", idade);
                mensagemAtiva2 = 1;
                printf("\n\n\t %d - %d - %s", cont, idadeCalculada, alunos[i].nome);
                ids[cont] = i;
                cont++;
            }
        }

        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o aluno que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && alunos[op-1].nAluno != 0){
            dadosAluno(ids[op]); //posição do aluno no array
            printf("\n\n Pretende alterar este aluno? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraAluno(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum aluno encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

// Listar por nº da aluno
void listarNAluno () {
    int i, j, temp, numeroAlunos[30];
    system("clear||cls");
    //copiar array para outro array para alterar array copiado do array original
    for(i = 0; i < nAlunos; i++){
        numeroAlunos[i] = alunos[i].nAluno;
    }
    for(i = 0; i < nAlunos; i++){
        for(j = i + 1; j < nAlunos; j++){
            if(numeroAlunos[i] > numeroAlunos[j]){
                temp = numeroAlunos[i];
                numeroAlunos[i] = numeroAlunos[j];
                numeroAlunos[j] = temp;
            }
        }
    }
    printf("\n\n< < < Listagem de alunos pelo número > > >");
    for(i = 0; i < nAlunos; i++){
        for(j = 0; j < nAlunos; j++){
            if(numeroAlunos[i] == alunos[j].nAluno){
                printf("\n %d - %s", numeroAlunos[i], alunos[j].nome);
            }
        }
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();    
}

// Listar por nome
void listarNome(){
    int i, j;
    char temp[50];
    system("clear||cls");
    for(i=0;i<nAlunos;i++){
        for(j=i+1;j<nAlunos;j++){
            if(strcmp(alunos[i].nome,alunos[j].nome)>0){
                strcpy(temp,alunos[i].nome);
                strcpy(alunos[i].nome,alunos[j].nome);
                strcpy(alunos[j].nome,temp);
            }
        }
    }
    printf("\n\n< < < Listagem de alunos pelo nome > > >");
    for(i = 0; i<nAlunos; i++){
        printf("\n\n\t %d - %s", i+1, alunos[i].nome);
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

// Listar por localidade
void listarLocalidade() {
    int i, j;
    char localAlunos[30][50], nomeAlunos[30][50], temp1[50], temp2[50];
    system("clear||cls");
    //Copia da estrutura para o array dentro da funcao
    for(i = 0; i < nAlunos; i++){
        strcpy(localAlunos[i],alunos[i].morada.localidade);
        strcpy(nomeAlunos[i],alunos[i].nome);
    }
    for(i=0;i<nAlunos - 1;i++){
        for(j=0;j<nAlunos - i -1;j++){
            if(strcmp(localAlunos[j],localAlunos[j +1])>0){
                strcpy(temp1,localAlunos[j]);
                strcpy(localAlunos[j],localAlunos[j +1]);
                strcpy(localAlunos[j +1],temp1);
                strcpy(temp2,nomeAlunos[j]);
                strcpy(nomeAlunos[j],nomeAlunos[j + 1]);
                strcpy(nomeAlunos[j],temp2);
            }
        }
    }
    printf("\n\n< < < Listagem de alunos pela localidade > > >");
    for(i = 0; i<nAlunos; i++){
        for(j=0;j<nAlunos;j++){
            if (strcmp(alunos[j].morada.localidade,localAlunos[i])==0){
                printf("\n\n\t %s - %s", localAlunos[i], alunos[j].nome);
            }
        }
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

// Listar por código postal
void listarCpostal() {
    int i, j;
    char cpostalAlunos[30][50], nomeAlunos[30][50], temp1[50], temp2[50];
    system("clear||cls");
    //Copia da estrutura para o array dentro da funcao
    for(i = 0; i < nAlunos; i++){
        strcpy(cpostalAlunos[i],alunos[i].morada.cpostal);
        strcpy(nomeAlunos[i],alunos[i].nome);
    }
    for(i=0;i<nAlunos - 1;i++){
        for(j=0;j<nAlunos - i - 1;j++){
            if(strcmp(cpostalAlunos[j],cpostalAlunos[j + 1])>0){
                strcpy(temp1,cpostalAlunos[j]);
                strcpy(cpostalAlunos[j],cpostalAlunos[j + 1]);
                strcpy(cpostalAlunos[j+1],temp1);
                strcpy(temp2,nomeAlunos[j]);
                strcpy(nomeAlunos[j],nomeAlunos[j + 1]);
                strcpy(nomeAlunos[j],temp2);
            }
        }
    }
    printf("\n\n< < < Listagem de alunos pelo Código de Postal > > >");
    for(i = 0; i<nAlunos; i++){
        for(j=0;j<nAlunos;j++){
            if (strcmp(alunos[j].morada.cpostal,cpostalAlunos[i])==0){
                printf("\n\n\t %s - %s", cpostalAlunos[i], alunos[j].nome);
            }
        }
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

//Listar por conclusão da carta
void listarAlunosConclusaoCarta(){
    int i, j, anoCCarta[30], temp2;
    char temp[50], nomeAlunos[30][50];
    system("clear||cls");
    //Copia da estrutura para o array dentro da funcao
    for(i = 0; i < nAlunos; i++){
        anoCCarta[i] = alunos[i].dataConclusaoCarta.ano;
        strcpy(nomeAlunos[i],alunos[i].nome);
    }
    printf ("\n\n< < < Listagem de alunos que concluiram a carta > > >");
    for(i=0;i<nAlunos;i++){
        for(j=i;j<nAlunos;j++){
            if(strcmp(alunos[i].nome,alunos[j].nome)>0){
            	strcpy(temp,alunos[i].nome);
                strcpy(alunos[i].nome,alunos[j].nome);
                strcpy(alunos[j].nome,temp);
                temp2 = anoCCarta[i];
                anoCCarta[i] = anoCCarta[j];
                anoCCarta[j] = temp2;
        	}
        }
    }
    for(i=0;i<nAlunos;i++){
        if (anoCCarta[i] != 0){
            printf("\n\n\t%s - %d", alunos[i].nome, anoCCarta[i]);
        }
    }
    printf ("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

//menu consultar/alterar
void menuConsutarAlterarAlunos(){
	int op;
    do{
        /*
            Nº,Nome,Locali,Rua,Porta,CPostal,Email,DN,CC,Nif,NºCarta,DCC,Situa.
        */
        system("clear||cls");
        printf("\n\n< < < Consultar/Alterar dados dos alunos > > >");
        printf("\n\n\t1 - Todos");
        printf("\n\n\t2 - Nº do aluno");
        printf("\n\n\t3 - Nome");
        printf("\n\n\t4 - Localidade");
        printf("\n\n\t5 - Código de Postal");
        printf("\n\n\t6 - Email");
        printf("\n\n\t7 - Data de nascimento");
        printf("\n\n\t8 - Cartão de cidadão");
        printf("\n\n\t9 - NIF");
        printf("\n\n\t10 - Nº da Carta");
        printf("\n\n\t11 - Data de conclusão da carta");
        printf("\n\n\t12 - Idades");
        printf("\n\n\t13 - Situação do aluno");

        printf("\n\n\n\n< < < Listar(Maior -> Pequeno)/Alterar dados dos alunos > > >");
        printf("\n\n\t14 - Nº do aluno");
        printf("\n\n\t15 - Nome");
        printf("\n\n\t16 - Localidade");
        printf("\n\n\t17 - Código de Postal");
        printf("\n\n\t18 - Alunos que já concluiram a carta");
        printf("\n\n\t0 - Voltar");
        printf("\n\n\n\nInsira a sua opção: ");
        scanf("%d", &op);
        fflush(stdin);
        switch (op) {
            case 1:
                consultarTodos();
            break;
            case 2:
                consultarPorNumero();
            break;
            case 3:
                consultarPorNome();
            break;
            case 4:
                consultarPorLocalidade();
            break;
            case 5:
                consultarPorCpostal();
            break;
            case 6:
                consultarPorEmail();
            break;
            case 7:
                ConsultarPorDNascimento();
            break;
            case 8:
                consultarPorCc();
            break;
            case 9:
                consultarPorNif();
            break;
            case 10:
                consultarPorNcarta();
            break;
            case 11:
                ConsultarPorDConclusaoCarta();
            break;
            case 12:
                consultarPorIdade();
            break;
            case 13:
                consultarPorSituacao();
            break;
            case 14:
                listarNAluno();
            break;
            case 15:
                listarNome();
            break;
            case 16:
                listarLocalidade();
            break;
            case 17:
                listarCpostal();
            break;
            case 18:
                listarAlunosConclusaoCarta();
            break;
        }
    }while (op != 0);
}

//menu de gestão dos alunos
void menuAlunos(){
    int op;
    do{
        system("clear||cls");
        printf("\n\n< < < MENU GESTÃO DE ALUNOS > > >");
        printf("\n\n\t1 - Inserir aluno");
        printf("\n\n\t2 - Consultar/Alterar dados do aluno");
        printf("\n\n\t0 - Voltar");
        printf("\n\nInsira a sua opção: ");
        scanf("%d", &op);
        fflush(stdin);
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
    int nInstrutor;
    char nome[50];
    char email[50];
    char cartaoCidadao[50];
    int nif;
    int ativo;
    
    MORADA morada;
    DATA dataNascimento;
    DATA entradaEscola;
} INSTRUTORES;

INSTRUTORES instrutores[30];

int existeNoArrayINST(int dado_i, char dado_s[50], char tipo){
    int i;
    for(i = 0; i < nInstrutores; i++){
        switch (tipo){
            case 1:
                if(instrutores[i].nInstrutor == dado_i){
                    printf("\n\n\tJá existe um instrutor com esse numero! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 2:
                if(strcmp(instrutores[i].email, dado_s) == 0){
                    printf("\n\n\tJá existe um instrutor com esse email! Por favor insira outro.");
                    return 1; 
                }
            case 3:
                if(strcmp(instrutores[i].cartaoCidadao, dado_s) == 0){
                    printf("\n\n\tJá existe um instrutor com esse cartão de cidadão! Por favor insira outro.");
                    return 1; 
                }
            break;
            case 4:
                if(instrutores[i].nif == dado_i){
                    printf("\n\n\tJá existe um instrutor com esse nif! Por favor insira outro.");
                    return 1; 
                }
            break;
        }
    }
    return 0;
}

//insere um instrutor
void inserirInstrutor(){
    int i, j, flag  = 0, concluiCarta = 0;
    char msg[100];
    system("clear||cls");
    printf("\n\n< < < Inserção de Instrutor > > >");

    if(nInstrutores >= 30){
        strcpy(msg, "\n\n\tNumero máximo de instrutores (30) excedido! A redirecionar ....");
        esperaApaga(msg, 3);
    }else{

        do{
            printf("\n\n\tInsira o Nº do instrutor: ");
            scanf("%d", &instrutores[nInstrutores].nInstrutor);
            fflush(stdin);
            if(instrutores[nInstrutores].nInstrutor <= 0) do{
                printf("\n\n\tPor favor insira um nº do instrutor válido: ");
                scanf("%d", &instrutores[nInstrutores].nInstrutor);
                fflush(stdin);
            }while(instrutores[nInstrutores].nInstrutor <= 0);
        }while(existeNoArrayINST(instrutores[nInstrutores].nInstrutor, 0, 1) == 1);

        printf("\n\n\tInsira o nome do instrutor: ");
        scanf(" %50[^\n]s", &instrutores[nInstrutores].nome);

        printf("\n\n\tInsira a localidade:");
        scanf(" %50[^\n]s", &instrutores[nInstrutores].morada.localidade);

        printf("\n\n\tInsira a rua:");
        scanf(" %50[^\n]s", &instrutores[nInstrutores].morada.rua);

        printf("\n\n\tInsira a porta:");
        scanf("%d", &instrutores[nInstrutores].morada.porta);
        fflush(stdin);

        printf("\n\n\tInsira o código de postal:");
        scanf(" %50[^\n]s", &instrutores[nInstrutores].morada.cpostal);

        do{
            printf("\n\n\tInsira o email do instrutor: ");
            scanf(" %50[^\n]s", &instrutores[nInstrutores].email);
        }while(existeNoArrayINST(0, instrutores[nInstrutores].email, 2) == 1);
        
        printf("\n\n\tInsira a data de nascimento (dia/mês/ano): ");
        scanf("%d/%d/%d", &instrutores[nInstrutores].dataNascimento.dia, &instrutores[nInstrutores].dataNascimento.mes, &instrutores[nInstrutores].dataNascimento.ano);
        fflush(stdin);
        if(dataValida(instrutores[nInstrutores].dataNascimento.dia, instrutores[nInstrutores].dataNascimento.mes, instrutores[nInstrutores].dataNascimento.ano) != 1) do{
            printf("\n\n\tPor favor insira a data de nascimento válida (dia/mês/ano): ");
            scanf("%d/%d/%d", &instrutores[nInstrutores].dataNascimento.dia, &instrutores[nInstrutores].dataNascimento.mes, &instrutores[nInstrutores].dataNascimento.ano);
            fflush(stdin);
        }while(dataValida(instrutores[nInstrutores].dataNascimento.dia, instrutores[nInstrutores].dataNascimento.mes, instrutores[nInstrutores].dataNascimento.ano) != 1);

        do{
            printf("\n\n\tInsira o cartão de cidadão: ");
            scanf(" %50[^\n]s", &instrutores[nInstrutores].cartaoCidadao);
        }while(existeNoArrayINST(0, instrutores[nInstrutores].cartaoCidadao, 3) == 1);

        do{
            printf("\n\n\tInsira o NIF: ");
            scanf("%d", &instrutores[nInstrutores].nif);
            fflush(stdin);
            if(instrutores[nInstrutores].nif <= 0) do{
                printf("\n\n\tPor favor insira um nif válido: ");
                scanf("%d", &instrutores[nInstrutores].nif);
                fflush(stdin);
            }while(instrutores[nInstrutores].nif <= 0);
        }while(existeNoArrayINST(instrutores[nInstrutores].nif, 0, 4) == 1);     
         
        printf("\n\n\tInsira a data de entrada na escola (dia/mês/ano): ");
        scanf("%d/%d/%d", &instrutores[nInstrutores].entradaEscola.dia, &instrutores[nInstrutores].entradaEscola.mes, &instrutores[nInstrutores].entradaEscola.ano);
        fflush(stdin);
        if(dataValida(instrutores[nInstrutores].entradaEscola.dia, instrutores[nInstrutores].entradaEscola.mes, instrutores[nInstrutores].entradaEscola.ano) != 1) do{
            printf("\n\n\tPor favor insira a data de entrada na escola válida (dia/mês/ano): ");
            scanf("%d/%d/%d", &instrutores[nInstrutores].entradaEscola.dia, &instrutores[nInstrutores].entradaEscola.mes, &instrutores[nInstrutores].entradaEscola.ano);
            fflush(stdin);
        }while(dataValida(instrutores[nInstrutores].entradaEscola.dia, instrutores[nInstrutores].entradaEscola.mes, instrutores[nInstrutores].entradaEscola.ano) != 1);
       

        printf("\n\n\tInsira a situação do instrutor (1 - ATIVO / 0 - NÃO ATIVO): ");
        scanf("%d", &instrutores[nInstrutores].ativo);
        fflush(stdin);
        if(instrutores[nInstrutores].ativo != 0 && instrutores[nInstrutores].ativo != 1) do{
            printf("\n\n\tPor favor insira uma situação válida: ");
            scanf("%d", &instrutores[nInstrutores].ativo);
            fflush(stdin);
        }while(instrutores[nInstrutores].ativo != 0 && instrutores[nInstrutores].ativo != 1);

        nInstrutores++;
        strcpy(msg, "\n\n\tInstrutor inserido com sucesso! A redirecionar ....");
        esperaApaga(msg, 3);
    }
}

//consultar dados de um instrutor
int dadosInstrutor(int instrutor){
    if (instrutores[instrutor].nInstrutor == 0) return 0;
    system("clear||cls");
    printf("\n\n< < < Dados do instrutor %s > > >", instrutores[instrutor].nome);
    printf("\n\n\tNumero: %d", instrutores[instrutor].nInstrutor);
    printf("\n\n\tNome: %s", instrutores[instrutor].nome);
    printf("\n\n\tLocalidae: %s", instrutores[instrutor].morada.localidade);
    printf("\n\n\tRua: %s", instrutores[instrutor].morada.rua);
    printf("\n\n\tPorta: %d", instrutores[instrutor].morada.porta);
    printf("\n\n\tCódigo-postal: %s", instrutores[instrutor].morada.cpostal);
    printf("\n\n\tEmail: %s", instrutores[instrutor].email);
    printf("\n\n\tData de nascimento: %d/%d/%d", instrutores[instrutor].dataNascimento.dia, instrutores[instrutor].dataNascimento.mes, instrutores[instrutor].dataNascimento.ano);
    printf("\n\n\tCartão de cidadão: %s", instrutores[instrutor].cartaoCidadao);
    printf("\n\n\tNIF: %d", instrutores[instrutor].nif);
    printf("\n\n\tData de entrada na escola: %d/%d/%d", instrutores[instrutor].entradaEscola.dia, instrutores[instrutor].entradaEscola.mes, instrutores[instrutor].entradaEscola.ano);
    printf("\n\n\tSituação: %d", instrutores[instrutor].ativo);
}

//Funcção para alterar dados de um instrutor
int alteraInstrutor(int instrutor){
    if (instrutores[instrutor].nInstrutor == 0) return 0;
    /* temp_d -> dado temporario inteiro
       temp_s -> dado temporario string
       Nota: Estes dados temporarios estão aqui presentes para que os dados apenas fiquem
             guardados em um variavel local da funcao para que ao procurar no array (função existeNoArrayINST)
             não encontre os dados que estamos a alterar.
    */
    int op, temp_d;
    char temp_s[30];
    char msg[100];
    do{
        system("clear||cls");
        printf("\n\n< < < Alterar dados do instrutor %s > > >", instrutores[instrutor].nome);
        printf("\n\n\t1 - Número: %d", instrutores[instrutor].nInstrutor);
        printf("\n\n\t2 - Nome: %s", instrutores[instrutor].nome);
        printf("\n\n\t3 - Localidade: %s", instrutores[instrutor].morada.localidade);
        printf("\n\n\t4 - Rua: %s", instrutores[instrutor].morada.rua);
        printf("\n\n\t5 - Porta: %d", instrutores[instrutor].morada.porta);
        printf("\n\n\t6 - Código-postal: %s", instrutores[instrutor].morada.cpostal);
        printf("\n\n\t7 - Email: %s", instrutores[instrutor].email);
        printf("\n\n\t8 - Data de nascimento: %d/%d/%d", instrutores[instrutor].dataNascimento.dia, instrutores[instrutor].dataNascimento.mes, instrutores[instrutor].dataNascimento.ano);
        printf("\n\n\t9 - Cartão de cidadão: %s", instrutores[instrutor].cartaoCidadao);
        printf("\n\n\t10 - NIF: %d", instrutores[instrutor].nif);
        printf("\n\n\t11 - Situação: %d", instrutores[instrutor].ativo);
        printf("\n\n\t0 - Voltar");

        printf("\n\nInsira a opção que deseja alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        system("clear||cls");
        printf("\n\n< < < Alterar dados do instrutor %s > > >", instrutores[instrutor].nome);

        switch(op){
            case 1:
                strcpy(msg, "\n\n\tNão é possivel alerar o número do instrutor! A redirecionar ....");
            break;
            case 2:
                printf("\n\n\tAltere o nome do instrutor: ");
                scanf(" %50[^\n]s", &instrutores[instrutor].nome);
                strcpy(msg, "\n\n\tNome alterado com sucesso! A redirecionar ....");
            break;
            case 3:
                printf("\n\n\tAltere a localidade do instrutor: ");
                scanf(" %50[^\n]s", &instrutores[instrutor].morada.localidade);
                strcpy(msg, "\n\n\tLocalidade alterada com sucesso! A redirecionar ....");
            break;
            case 4:
                printf("\n\n\tAltere a rua do instrutor: ");
                scanf(" %50[^\n]s", &instrutores[instrutor].morada.rua);
                strcpy(msg, "\n\n\tRua alterado com sucesso! A redirecionar ....");
            break;
            case 5:
                printf("\n\n\tAltere a porta do instrutor: ");
                scanf("%d", &instrutores[instrutor].morada.porta);
                fflush(stdin);
                strcpy(msg, "\n\n\tPorta alterada com sucesso! A redirecionar ....");
            break;
            case 6:
                printf("\n\n\tAltere o código de postal do instrutor: ");
                scanf(" %50[^\n]s", &instrutores[instrutor].morada.cpostal);
                strcpy(msg, "\n\n\tCódigo de postal alterado com sucesso! A redirecionar ....");
            break;
            case 7:
                do{
                    //limpa string do array
                    memset(instrutores[instrutor].email, 0, 30);
                    printf("\n\n\tAltere o email do instrutor: ");
                    scanf(" %30[^\n]s", &temp_s);
                }while(existeNoArrayINST(0, temp_s, 2) == 1);
                strcpy(instrutores[instrutor].email, temp_s);
                strcpy(msg, "\n\n\tE-mail alterado com sucesso! A redirecionar ....");
            break;
            case 8:
                printf("\n\n\tAltere a data de nascimento (dia/mês/ano): ");
                scanf("%d/%d/%d", &instrutores[instrutor].dataNascimento.dia, &instrutores[instrutor].dataNascimento.mes, &instrutores[instrutor].dataNascimento.ano);
                fflush(stdin);
                if(dataValida(instrutores[instrutor].dataNascimento.dia, instrutores[instrutor].dataNascimento.mes, instrutores[instrutor].dataNascimento.ano) != 1) do{
                    printf("\n\n\tPor favor insira a data de nascimento válida (dia/mês/ano): ");
                    scanf("%d/%d/%d", &instrutores[instrutor].dataNascimento.dia, &instrutores[instrutor].dataNascimento.mes, &instrutores[instrutor].dataNascimento.ano);
                    fflush(stdin);
                }while(dataValida(instrutores[instrutor].dataNascimento.dia, instrutores[instrutor].dataNascimento.mes, instrutores[instrutor].dataNascimento.ano) != 1);
                strcpy(msg, "\n\n\tData de nascimento alterada com sucesso! A redirecionar ....");
            break;
            case 9:
                do{
                    //limpa string do array
                    memset(instrutores[instrutor].cartaoCidadao, 0, 30);
                    printf("\n\n\tAltere o cartão de cidadão do instrutor: ");
                    scanf(" %30[^\n]s", &temp_s);
                }while(existeNoArrayINST(0, temp_s, 3) == 1);
                strcpy(instrutores[instrutor].cartaoCidadao, temp_s);
                strcpy(msg, "\n\n\tCartão de cidadão alterado com sucesso! A redirecionar ....");
            break;
            case 10:
                do{
                    //"limpa" inteiro do array 
                    instrutores[instrutor].nif = -1;
                    printf("\n\n\tAltere o NIF do instrutor: ");
                    scanf("%d", &temp_d);
                    fflush(stdin);
                    if(temp_d <= 0) do{
                        printf("\n\n\tPor favor insira um nif válido: ");
                        scanf("%d", &temp_d);
                        fflush(stdin);
                    }while(temp_d <= 0);
                }while(existeNoArrayINST(temp_d, 0, 4) == 1);
                instrutores[instrutor].nif = temp_d;
                strcpy(msg, "\n\n\tNIF alterado com sucesso! A redirecionar ....");
            break;
            case 11:
                printf("\n\n\tAltere a situação do instrutor (1 - ATIVO / 0 - NÃO ATIVO): ");
                scanf("%d", &instrutores[instrutor].ativo);
                fflush(stdin);
                if(instrutores[instrutor].ativo != 0 && instrutores[instrutor].ativo != 1) do{
                    printf("\n\n\tPor favor insira uma situação válida: ");
                    scanf("%d", &instrutores[instrutor].ativo);
                    fflush(stdin);
                }while(instrutores[instrutor].ativo != 0 && instrutores[instrutor].ativo != 1);
                strcpy(msg, "\n\n\tSituação alterado com sucesso! A redirecionar ....");
            break;
        }
        if(op != 0) esperaApaga(msg, 3);
    }while(op != 0);
}

//consultar para consultar/alterar todos os instrutores
void consultarTodosINST(){
    int op, i;
    char op2;
    system("clear||cls");
    printf("\n\n< < < Listagem de instrutores > > >");
    for(i = 0; i<nInstrutores; i++){
        printf("\n\n\t %d - %s", i+1, instrutores[i].nome);
    }
    printf("\n\n\t 0 - Voltar");
    printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
    scanf("%d", &op);
    fflush(stdin);
    if(op != 0 && instrutores[op-1].nInstrutor != 0){
        op--;
        dadosInstrutor(op);
        printf("\n\n Pretende alterar este instrutor? (y/N): ");
        scanf(" %c", &op2);
        if(op2 == 'Y' || op2 == 'y'){
            alteraInstrutor(op);
        }
    }
}

//Procurar instrutor por nome
void consultarPorNomeINST(){
    int i, op, cont = 1, ids[30], flag = 0;
    char nome[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o nome do instrutor que pretende consultar: ");
    scanf(" %50[^\n]s", &nome);
    if(strlen(nome) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo nome: ");
        scanf(" %50[^\n]s", &nome);
    }while(strlen(nome) < 3);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (strstr(instrutores[i].nome, nome)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que contem '%s' no nome > > >", nome);
        for(i = 0; i < nInstrutores; i++){
            if (strstr(instrutores[i].nome, nome)){
                printf("\n\n\t %d - %s", cont, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i; 
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com esse numero encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por numero
void consultarPorNumeroINST(){
    int i, numero, op, flag = 0;
    char op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o numero do instrutor que pretende consultar: ");
    scanf("%d", &numero);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (instrutores[i].nInstrutor == numero){
            flag = 1;
            dadosInstrutor(i);
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(i);
            }
        }
    }
    if(flag == 0){
        strcpy(msg, "\n\n\tNenhum instrutor com esse numero encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por E-mail
void consultarPorEmailINST(){
    int i, op, cont = 1, ids[30], flag = 0;
    char email[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o email do instrutor que pretende consultar: ");
    scanf(" %50[^\n]s", &email);
    if(strlen(email) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo email: ");
        scanf(" %50[^\n]s", &email);
    }while(strlen(email) < 3);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (strstr(instrutores[i].email, email)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que contem '%s' no email > > >", email);
        for(i = 0; i < nInstrutores; i++){
            if (strstr(instrutores[i].email, email)){
                printf("\n\n\t %d - %s - %s", cont, instrutores[i].email, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com esse email encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por Cartão de Cidadão
void consultarPorCcINST(){
    int i, op, cont = 1, ids[30], flag = 0;
    char cc[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o Cartão de Cidadão do instrutor que pretende consultar: ");
    scanf(" %50[^\n]s", &cc);
    if(strlen(cc) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo Cartão de Cidadão: ");
        scanf(" %50[^\n]s", &cc);
    }while(strlen(cc) < 3);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (strstr(instrutores[i].cartaoCidadao, cc)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que contem '%s' no Cartão de Cidadão > > >", cc);
        for(i = 0; i < nInstrutores; i++){
            if (strstr(instrutores[i].cartaoCidadao, cc)){
                printf("\n\n\t %d - %s - %s", cont, instrutores[i].cartaoCidadao, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com esse Cartão de Cidadão encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por NIF
void consultarPorNifINST(){
    int i, op, cont = 1, ids[30], flag = 0;
    //str vai converter o inteiro para caracter para procurar uma parte do nif
    char nif[50], op2, msg[100], str[30];
    system("clear||cls");
    printf("\n\n\tInsira o NIF do instrutor que pretende consultar: ");
    scanf(" %50[^\n]s", &nif);
    if(strlen(nif) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo NIF: ");
        scanf(" %50[^\n]s", &nif);
    }while(strlen(nif) < 3);
    system("clear||cls");
    //verifica se existe no array
    for(i = 0; i < nInstrutores; i++){
        //str vai converter o inteiro para caracter para procurar uma parte do nif
        sprintf(str, "%d", instrutores[i].nif);
        if (strstr(str, nif)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que contem '%s' no NIF > > >", nif);
        for(i = 0; i < nInstrutores; i++){
            //str vai converter o inteiro para caracter para procurar uma parte do nif
            sprintf(str, "%d", instrutores[i].nif);
            if (strstr(str, nif)){
                printf("\n\n\t %d - %d - %s", cont, instrutores[i].nif, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com esse NIF encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por situação
void consultarPorSituacaoINST(){
    int i, situacao, op, cont = 1, flag = 0;
    char msg[100], ids[30], op2;
    system("clear||cls");
    printf("\n\n\tInsira a Situação que pretende consultar (1 - Ativo / 0 - Inativo): ");
    scanf("%d", &situacao);
    fflush(stdin);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if(instrutores[i].ativo == situacao){
            flag = 1;
            break;
        }
    }
    if((situacao == 1 || situacao == 0) && (flag = 1)){
        if(situacao == 1) printf("\n\n< < < Listagem de instrutores Ativos > > >");
        if(situacao == 0) printf("\n\n< < < Listagem de instrutores Inativos > > >");
        for(i = 0; i < nInstrutores; i++){
            if(instrutores[i].ativo == situacao){
               printf("\n\n\t %d - %s", cont, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;                 
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com essa Situação foi encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por cpostal
void consultarPorCpostalINST(){
    int i, op, cont = 1, ids[30], flag = 0;
    char cpostal[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira o Código de Postal do instrutor que pretende consultar: ");
    scanf(" %50[^\n]s", &cpostal);
    if(strlen(cpostal) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo Código de Postal: ");
        scanf(" %50[^\n]s", &cpostal);
    }while(strlen(cpostal) < 3);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (strstr(instrutores[i].morada.cpostal, cpostal)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que contem '%s' no Código de Postal > > >", cpostal);
        for(i = 0; i < nInstrutores; i++){
            if (strstr(instrutores[i].morada.cpostal, cpostal)){
                printf("\n\n\t %d - %s - %s", cont, instrutores[i].morada.cpostal, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com esse Código postal encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar instrutor por Localidade
void consultarPorLocalidadeINST(){
    int i, op, cont = 1, ids[30], flag = 0;
    char localidade[50], op2, msg[100];
    system("clear||cls");
    printf("\n\n\tInsira a localidade do instrutor que pretende consultar: ");
    scanf(" %50[^\n]s", &localidade);
    if(strlen(localidade) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pela localidade: ");
        scanf(" %50[^\n]s", &localidade);
    }while(strlen(localidade) < 3);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (strstr(instrutores[i].morada.localidade, localidade)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que contem '%s' na localidade > > >", localidade);
        for(i = 0; i < nInstrutores; i++){
            if (strstr(instrutores[i].morada.localidade, localidade)){
                printf("\n\n\t %d - %s - %s", cont, instrutores[i].morada.localidade, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com essa localidade encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar por data de nascimento
void ConsultarPorDNascimentoINST(){
    int i, op, cont = 1, ids[30], flag = 0, dia, mes, ano;
    char op2, msg[100];
    system("clear||cls");
    
    printf("\n\n\tInsira a data de nascimento do instrutor que pretende consultar (dia/mês/ano): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    if(dataValida(dia, mes, ano) != 1)do{
        printf("\n\n\tPor favor insira a data de nascimento válida (dia/mês/ano): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
    }while(dataValida(dia, mes, ano) != 1);
    
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (instrutores[i].dataNascimento.dia == dia && instrutores[i].dataNascimento.mes == mes && instrutores[i].dataNascimento.ano == ano){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que nasceram em %d/%d/%d ! > > >", dia, mes, ano);
        for(i = 0; i < nInstrutores; i++){
            if (instrutores[i].dataNascimento.dia == dia && instrutores[i].dataNascimento.mes == mes && instrutores[i].dataNascimento.ano == ano){
                printf("\n\n\t %d - %d/%d/%d - %s", cont, dia, mes, ano, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com essa data de nascimento encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

//Procurar por data de entrada na escola
void ConsultarPorDEntradEscolaINST(){
    int i, op, cont = 1, ids[30], flag = 0, dia, mes, ano;
    char op2, msg[100];
    system("clear||cls");
    
    printf("\n\n\tInsira a data de entrada na escola do instrutor que pretende consultar (dia/mês/ano): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    if(dataValida(dia, mes, ano) != 1)do{
        printf("\n\n\tPor favor insira a data de entrada na escola válida (dia/mês/ano): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
    }while(dataValida(dia, mes, ano) != 1);
    
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (instrutores[i].entradaEscola.dia == dia && instrutores[i].entradaEscola.mes == mes && instrutores[i].entradaEscola.ano == ano){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de instrutores que entraram na escola em %d/%d/%d ! > > >", dia, mes, ano);
        for(i = 0; i < nInstrutores; i++){
            if (instrutores[i].entradaEscola.dia == dia && instrutores[i].entradaEscola.mes == mes && instrutores[i].entradaEscola.ano == ano){
                printf("\n\n\t %d - %d/%d/%d - %s", cont, dia, mes, ano, instrutores[i].nome);
                //posicao de cada instrutor no array que corresponde a pesquisa
                ids[cont] = i;
                cont++;
            }
        }
        printf("\n\n\t 0 - Voltar");
        printf("\n\n Insira o numero do instrutor que deseja consultar/alterar: ");
        scanf("%d", &op);
        fflush(stdin);
        if(op != 0 && instrutores[op-1].nInstrutor != 0){
            dadosInstrutor(ids[op]); //posição do instrutor no array
            printf("\n\n Pretende alterar este instrutor? (y/N): ");
            scanf(" %c", &op2);
            if(op2 == 'Y' || op2 == 'y'){
                alteraInstrutor(ids[op]);
            }
        }
    }else{
        strcpy(msg, "\n\n\tNenhum instrutor com essa data de entrada na escola encontrado! A redirecionar ....");
        esperaApaga(msg, 4);
    }
}

// Listar por nº da instrutor
void listarNInstrutor () {
    int i, j, temp, numeroInstrutores[30];
    system("clear||cls");
    //copiar array para outro array para alterar array copiado do array original
    for(i = 0; i < nInstrutores; i++){
        numeroInstrutores[i] = instrutores[i].nInstrutor;
    }
    for(i = 0; i < nInstrutores; i++){
        for(j = i + 1; j < nInstrutores; j++){
            if(numeroInstrutores[i] > numeroInstrutores[j]){
                temp = numeroInstrutores[i];
                numeroInstrutores[i] = numeroInstrutores[j];
                numeroInstrutores[j] = temp;
            }
        }
    }
    printf("\n\n< < < Listagem de instrutores pelo número > > >");
    for(i = 0; i < nInstrutores; i++){
        for(j = 0; j < nInstrutores; j++){
            if(numeroInstrutores[i] == instrutores[j].nInstrutor){
                printf("\n %d - %s", numeroInstrutores[i], instrutores[j].nome);
            }
        }
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();    
}

// Listar por nome
void listarNomeINST(){
    int i, j;
    char temp[50];
    system("clear||cls");
    for(i=0;i<nInstrutores;i++){
        for(j=i+1;j<nInstrutores;j++){
            if(strcmp(instrutores[i].nome,instrutores[j].nome)>0){
                strcpy(temp,instrutores[i].nome);
                strcpy(instrutores[i].nome,instrutores[j].nome);
                strcpy(instrutores[j].nome,temp);
            }
        }
    }
    printf("\n\n< < < Listagem de instrutores pelo nome > > >");
    for(i = 0; i<nInstrutores; i++){
        printf("\n\n\t %d - %s", i+1, instrutores[i].nome);
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

// Listar por localidade
void listarLocalidadeINST() {
    int i, j;
    char localInstrutores[30][50], nomeInstrutores[30][50], temp1[50], temp2[50];
    system("clear||cls");
    //Copia da estrutura para o array dentro da funcao
    for(i = 0; i < nInstrutores; i++){
        strcpy(localInstrutores[i],instrutores[i].morada.localidade);
        strcpy(nomeInstrutores[i],instrutores[i].nome);
    }
    for(i=0;i<nInstrutores - 1;i++){
        for(j=i+1;j<nInstrutores - i - 1;j++){
            if(strcmp(localInstrutores[j],localInstrutores[j + 1])>0){
                strcpy(temp1,localInstrutores[j]);
                strcpy(localInstrutores[j],localInstrutores[j + 1]);
                strcpy(localInstrutores[j + 1],temp1);
                strcpy(temp2,nomeInstrutores[j]);
                strcpy(nomeInstrutores[j],nomeInstrutores[j +1]);
                strcpy(nomeInstrutores[j+1],temp2);
            }
        }
    }
    printf("\n\n< < < Listagem de instrutores pela localidade > > >");
    for(i = 0; i<nInstrutores; i++){
        for(j=0;j<nInstrutores;j++){
            if (strcmp(instrutores[j].morada.localidade,localInstrutores[i])==0){
                printf("\n\n\t %s - %s", localInstrutores[i], instrutores[j].nome);
            }
        }
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

// Listar por código postal
void listarCpostalINST() {
    int i, j;
    char cpostalInstrutores[30][50], nomeInstrutores[30][50], temp1[50], temp2[50];
    system("clear||cls");
    //Copia da estrutura para o array dentro da funcao
    for(i = 0; i < nInstrutores; i++){
        strcpy(cpostalInstrutores[i],instrutores[i].morada.cpostal);
        strcpy(nomeInstrutores[i],instrutores[i].nome);
    }
    for(i=0;i<nInstrutores - 1;i++){
        for(j=i+1;j<nInstrutores - i - 1;j++){
            if(strcmp(cpostalInstrutores[j],cpostalInstrutores[j +1])>0){
                strcpy(temp1,cpostalInstrutores[j]);
                strcpy(cpostalInstrutores[j],cpostalInstrutores[j +1]);
                strcpy(cpostalInstrutores[j +1],temp1);
                strcpy(temp2,nomeInstrutores[j]);
                strcpy(nomeInstrutores[j],nomeInstrutores[j +1]);
                strcpy(nomeInstrutores[j +1],temp2);
            }
        }
    }
    printf("\n\n< < < Listagem de instrutores pelo Código de Postal > > >");
    for(i = 0; i<nInstrutores; i++){
        for(j=0;j<nInstrutores;j++){
            if (strcmp(instrutores[j].morada.cpostal,cpostalInstrutores[i])==0){
                printf("\n\n\t %s - %s", cpostalInstrutores[i], instrutores[j].nome);
            }
        }
    }
    printf("\n\n (Prima qualquer tecla para voltar!)");
    getch();
}

//menu consultar/alterar
void menuConsutarAlterarInstrutores(){
	int op;
    do{
        /*
            Nº,Nome,Locali,Rua,Porta,CPostal,Email,DN,CC,Nif,Situa.
        */
        system("clear||cls");
        printf("\n\n< < < Consultar/Alterar dados dos instrutores > > >");
        printf("\n\n\t1 - Todos");
        printf("\n\n\t2 - Nº do instrutor");
        printf("\n\n\t3 - Nome");
        printf("\n\n\t4 - Localidade");
        printf("\n\n\t5 - Código de Postal");
        printf("\n\n\t6 - Email");
        printf("\n\n\t7 - Data de nascimento");
        printf("\n\n\t8 - Cartão de cidadão");
        printf("\n\n\t9 - NIF");
        printf("\n\n\t10 - Data de entrada na escola");
        printf("\n\n\t11 - Situação do instrutor");
        printf("\n\n\n\n< < < Listar(Maior -> Pequeno)/Alterar dados dos instrutores > > >");
        printf("\n\n\t12 - Nº do instrutor");
        printf("\n\n\t13 - Nome");
        printf("\n\n\t14 - Localidade");
        printf("\n\n\t15 - Código de Postal");
        printf("\n\n\t0 - Voltar");
        printf("\n\n\n\nInsira a sua opção: ");
        scanf("%d", &op);
        fflush(stdin);
        switch (op) {
            case 1:
                consultarTodosINST();
            break;
            case 2:
                consultarPorNumeroINST();
            break;
            case 3:
                consultarPorNomeINST();
            break;
            case 4:
                consultarPorLocalidadeINST();
            break;
            case 5:
                consultarPorCpostalINST();
            break;
            case 6:
                consultarPorEmailINST();
            break;
            case 7:
                ConsultarPorDNascimentoINST();
            break;
            case 8:
                consultarPorCcINST();
            break;
            case 9:
                consultarPorNifINST();
            break;
            case 10:
                ConsultarPorDEntradEscolaINST();
            break;
            case 11:
                consultarPorSituacaoINST();
            break;
            case 12:
                listarNInstrutor();
            break;
            case 13:
                listarNomeINST();
            break;
            case 14:
                listarLocalidadeINST();
            break;
            case 15:
                listarCpostalINST();
            break;
        }
    }while (op != 0);
}

//menu de gestão dos instrutores
void menuInstrutores(){
    int op;
    do{
        system("clear||cls");
        printf("\n\n< < < MENU GESTÃO DE INSTRUTORES > > >");
        printf("\n\n\t1 - Inserir instrutor");
        printf("\n\n\t2 - Consultar/Alterar dados do instrutor");
        printf("\n\n\t0 - Voltar");
        printf("\n\nInsira a sua opção: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                inserirInstrutor();
            break;
            case 2:
                menuConsutarAlterarInstrutores();
            break;
        }
    }while (op != 0);
}

////////////////////////////////////////////////////////////////////////////////////
//Aulas
////////////////////////////////////////////////////////////////////////////////////

//Estrutura de dados definida para as aulas

typedef struct {
    int aluno;
    int hora;
    int instrutor;
    DATA dataAula;
} AULAS;

AULAS aulas[100];

//marcar Aula
//marcar Aula
void marcarAula(){
    int i, cont = 1, flag = 0;
    char op, msg[100];
    system("clear||cls");
    printf("\n\n< < < Marcar Aula de Condução > > >");
    
    //Alunos Aula
    system("clear||cls");
    if (nAlunos == 0 || nInstrutores == 0){
    	strcpy(msg, "\n\n\tNão existem alunos ou intrutores inseridos!! A redirecionar ....");
        esperaApaga(msg, 4); 
	}
    else{
		printf("\n\n< < <  Marcar Aula - Listagem de alunos > > >");
    	for (i = 0; i < nAlunos; i++){
        	if (alunos[i].ativo == 1){
            	printf("\n\n%d - %s", alunos[i].nAluno, alunos[i].nome);
        	}
    	}
    	printf("\n\n Insira o nº do Aluno que deseja marcar a aula: ");
    	scanf("%d", &aulas[nAulas].aluno);
    	fflush(stdin);
	

    	//Instrutores Aula
    	system("clear||cls");
    	printf("\n\n< < <  Marcar Aula - Listagem de instrutores > > >");
    	for (i = 0; i < nInstrutores; i++){
        	if (instrutores[i].ativo == 1){
            	printf("\n\n%d - %s", instrutores[i].nInstrutor, instrutores[i].nome);
        	}
    	}
    	printf("\n\n Insira o nº do Instrutor que deseja marcar a aula: ");
    	scanf("%d", &aulas[nAulas].instrutor);
    	fflush(stdin);
	
		int exiteDataHora(int dia, int mes, int ano, int hora, int instrutor){
        	for(i = 0; i < nAulas; i++){
            	if(dia == aulas[i].dataAula.dia
            	&& mes == aulas[i].dataAula.mes
            	&& ano == aulas[i].dataAula.ano
            	&& hora == aulas[i].hora
	    		&& instrutor == instrutores[i].nInstrutor
            	)return 1;
        	}
        return 0;
    	}

    	do{
        	if(flag == 1) printf("\n\n\tJá existe uma aula marcada nesse dia a essa hora, com esse instrutor por favor ensira outro dia/hora!");
        	//Data Aula
        		system("clear||cls");
        		printf("\n\n\tInsira a data da aula (dia/mês/ano): ");
        		scanf("%d/%d/%d", &aulas[nAulas].dataAula.dia, &aulas[nAulas].dataAula.mes, &aulas[nAulas].dataAula.ano);
        		fflush(stdin);
        		if(dataValida(aulas[nAulas].dataAula.dia, aulas[nAulas].dataAula.mes, aulas[nAulas].dataAula.ano) != 1) do{
            		printf("\n\n\tPor favor insira uma data de aula válida (dia/mês/ano): ");
            		scanf("%d/%d/%d", &aulas[nAulas].dataAula.dia, &aulas[nAulas].dataAula.mes, &aulas[nAulas].dataAula.ano);
            		fflush(stdin);
        	}while(dataValida(aulas[nAulas].dataAula.dia, aulas[nAulas].dataAula.mes, aulas[nAulas].dataAula.ano) != 1);

        //Hora Aula
        printf("\n\n\tPor favor insira uma hora: ");
        scanf("%d", &aulas[nAulas].hora);
        fflush(stdin);

        flag = 1;

    	}while(exiteDataHora(aulas[nAulas].dataAula.dia, aulas[nAulas].dataAula.mes, aulas[nAulas].dataAula.ano, aulas[nAulas].hora, instrutores[i].nInstrutor) == 1);
		
		system("clear||cls");
		printf("\n\n< < < Dados da aula de %d/%d/%d > > >", aulas[nAulas].dataAula.dia, aulas[nAulas].dataAula.mes, aulas[nAulas].dataAula.ano);
    	printf("\n\n\tHora: %d", aulas[nAulas].hora);
    	printf("\n\n\tAluno: %d", aulas[nAulas].aluno);
    	printf("\n\n\tInstrutor: %d", aulas[nAulas].instrutor);
    	printf("\n\n(NOTA:Depois de confirmada a aula não pode ser desmaracada!!)\nPretende confirmar a marcação da aula?(y/N): ");
    	scanf("%c", &op);
    	nAulas++;
    	if (op == 'y' || op == 'Y'){
        	strcpy(msg, "\n\n\tAula marcada com sucesso!! A redirecionar ....");
        	esperaApaga(msg, 4); 
   		}
    	else{
    		nAulas--;
       		strcpy(msg, "\n\n\tAula não marcada! A redirecionar ....");
       		esperaApaga(msg, 4); 
    	}
	}
}



//Consultar aula por dia
void consultaAulaDia(){
	int i, j, k, op, flag = 0, dia, mes, ano;
    char op2, msg[100];
    system("clear||cls");
    
    printf("\n\n\tInsira a data da aula que pretende consultar (dia/mês/ano): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    if(dataValida(dia, mes, ano) != 1)do{
        printf("\n\n\tPor favor insira a data da aula válida (dia/mês/ano): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        fflush(stdin);
    }while(dataValida(dia, mes, ano) != 1);
    
    system("clear||cls");
    for(i = 0; i < nAulas; i++){
        if(aulas[i].dataAula.dia == dia && aulas[i].dataAula.mes == mes && aulas[i].dataAula.ano == ano){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        printf("\n\n< < < Listagem de aulas em %d/%d/%d > > >", dia, mes, ano);
        for(i = 0; i < nAulas; i++){
            if(aulas[i].dataAula.dia == dia && aulas[i].dataAula.mes == mes && aulas[i].dataAula.ano == ano){
            	printf ("\n\n\tAula - Data:%d/%d/%d - Hora:%d", dia, mes, ano, aulas[i].hora);
        	}
        
        	for(j = 0; j < nAlunos; j++){
            	if(aulas[i].dataAula.dia == dia && aulas[i].dataAula.mes == mes && aulas[i].dataAula.ano == ano && aulas[i].aluno == alunos[j].nAluno){
                	printf (" - Alunos:%d, %s", alunos[j].nAluno, alunos[j].nome);
            	}
    		}
        	for(k = 0; k < nInstrutores; k++){
            	if(aulas[i].dataAula.dia == dia && aulas[i].dataAula.mes == mes && aulas[i].dataAula.ano == ano && aulas[i].instrutor == instrutores[k].nInstrutor){
                	printf(" - Instrutor:%s, %s", instrutores[k].nome, instrutores[k].email);
				}
			}
		}
		printf("\n\nPrima uma tecla para sair!!");
		getch();
	}	
	else {
		strcpy(msg, "Nenhuma aula encontrada com essa data!! A redirecionar....");
		esperaApaga(msg, 4);
	}
}

//Consultar por aluno
void consultarAulaAluno(){
	char nome[50], msg[100];
	int i, j, k, flag = 0;
	system("clear||cls");
    printf("\n\n\tInsira o nome do aluno que pretende consultar as aulas: ");
    scanf(" %50[^\n]s", &nome);
    if(strlen(nome) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo nome: ");
        scanf(" %50[^\n]s", &nome);
    }while(strlen(nome) < 3);
    system("clear||cls");
    for(i = 0; i < nAlunos; i++){
        if (strstr(alunos[i].nome, nome)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
    	printf ("\n\n< < < Listagem das aulas de %s > > >", nome);
    	for(i = 0; i < nAulas; i++){
    		for(j = 0; j < nAlunos; j++){
            	if(aulas[i].aluno == alunos[j].nAluno && strstr(alunos[j].nome, nome)){
            		printf ("\n\n\tAula - Data:%d/%d/%d - Hora:%d", aulas[i].dataAula.dia, aulas[i].dataAula.mes, aulas[i].dataAula.ano, aulas[i].hora);
                	printf (" - Alunos:%d, %s", alunos[j].nAluno, alunos[j].nome);
                }
        		for(k = 0; k < nInstrutores; k++){
            		if(aulas[i].instrutor == instrutores[k].nInstrutor && aulas[i].aluno ==alunos[j].nAluno && strstr(alunos[j].nome, nome) ){
                		printf(" - Instrutor:%s, %s", instrutores[k].nome, instrutores[k].email);
					}
				}
			}
		}
		printf("\n\nPrima uma tecla para sair!!");
		getch();
	}
	else {
		strcpy(msg, "Nenhum aluno encontrado com esse nome!! A redirecionar....");
		esperaApaga(msg, 4);
	}
}

//Consultar por instrutor
void consultarAulaInstrutor(){
	char nome[50], msg[100];
	int i, j, k, flag = 0;
	system("clear||cls");
    printf("\n\n\tInsira o nome do instrutor que pretende consultar as aulas: ");
    scanf(" %50[^\n]s", &nome);
    if(strlen(nome) < 3) do{
        printf("\n\n\tPor favor insira pelo menos 3 caracteres para procurar pelo nome: ");
        scanf(" %50[^\n]s", &nome);
    }while(strlen(nome) < 3);
    system("clear||cls");
    for(i = 0; i < nInstrutores; i++){
        if (strstr(instrutores[i].nome, nome)){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
    	printf ("\n\n< < < Listagem das aulas de %s > > >", nome);
    	for(i = 0; i < nAulas; i++){
    		for(j = 0; j < nInstrutores; j++){
            	if(aulas[i].instrutor == instrutores[j].nInstrutor && strstr(instrutores[j].nome, nome)){
            		printf ("\n\n\tAula - Data:%d/%d/%d - Hora:%d", aulas[i].dataAula.dia, aulas[i].dataAula.mes, aulas[i].dataAula.ano, aulas[i].hora);
                	printf (" - Instrutor:%s, %s", instrutores[j].nome, instrutores[j].email);
                }
        		for(k = 0; k < nAlunos; k++){
            		if(aulas[i].aluno == alunos[k].nAluno && aulas[i].instrutor == instrutores[j].nInstrutor && strstr(instrutores[j].nome, nome)){
                		printf(" - Aluno:%d, %s", alunos[k].nAluno, alunos[k].nome);
					}
				}
			}
		}
		printf("\n\nPrima uma tecla para sair!!");
		getch();
	}
	else {
		strcpy(msg, "Nenhum instrutor encontrado com esse nome!! A redirecionar....");
		esperaApaga(msg, 4);
	}
}


//consultarAula
void consultarAulas(){
    int op;
    do {
    system("clear||cls");
    printf("\n\n< < < MENU CONSULTA DE AULAS > > >");
    printf("\n\n\t1 - Consultar por dia");
    printf("\n\n\t2 - Consultar por aluno");
    printf("\n\n\t3 - Consultar por instrutor");
    printf("\n\n\t0 - Voltar");
    printf("\n\nInsira a sua opção: ");
    scanf("%d", &op);
    fflush(stdin);
    switch(op){
        case 1:
            consultaAulaDia();
        break;
        case 2:
        	consultarAulaAluno();
        break;
        case 3:
        	consultarAulaInstrutor();
        break;
    } 
    }while (op != 0);
}

//menu de gestão de aulas
void menuAulas(){
    int op;
    do{
        system("clear||cls");
        printf("\n\n< < < MENU MARCAÇÃO/CONSULTA DE AULAS > > >");
        printf("\n\n\t1 - Marcar aulas");
        printf("\n\n\t2 - Consultar aulas");
        printf("\n\n\t0 - Voltar");
        printf("\n\nInsira a sua opção: ");
        scanf("%d", &op);
        fflush(stdin);
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
void menuPrincipal(){
    int op;
    do{
        system("clear||cls");
        printf("\n\n< < < MENU PRINCIPAL > > >");
        printf("\n\n\t1 - Gestão de Alunos");
        printf("\n\n\t2 - Gestão de Intrutores");
        printf("\n\n\t3 - Marcação/Consultas de aulas");
        printf("\n\n\t0 - Sair");
        printf("\n\nInsira a sua opção: ");
        scanf("%d", &op);
        fflush(stdin);
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
    }while(op != 0);
}

//função principal onde o programa é inicializado
int main(void){
    fullscreen();
    setlocale(LC_ALL, "Portuguese");
    mensagemBoasVindas();
    menuPrincipal();
    return 0;
}
