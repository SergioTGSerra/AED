#include <stdio.h>

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
}

void menuAlunos(){
    int op;
    printf ("\n\n< < < MENU GESTÃO DE ALUNOS > > >");
    printf ("\n\n\t1 - Inserir novos alunos");
    printf ("\n\n\t2 - Consultar/Alterar dados do aluno");
    printf ("\n\n\t0 - Voltar");
    printf ("\n\nInsira a sua opção: ");
    scanf ("%d", &op);
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
    int op;
    mensagemBoasVindas();
    do{
        op = menuPrincipal();
    }while(op != 0);

    return 0;
}
