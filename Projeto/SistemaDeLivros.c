#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

void gotoxy(int x, int y){
    COORD coord;
    coord.X = (short) x;
    coord.Y = (short) y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tela(){
    int i, c;

    for(i=1;i<=24;i++){
        gotoxy(1,i);   printf("|");
        gotoxy(79,i);  printf("|");
    }

    for(c=2;c<=78;c++){
        gotoxy(c,1);   printf("-");
        gotoxy(c,5);   printf("-");
        gotoxy(c,22);  printf("-");
        gotoxy(c,24);  printf("-");
    }

    gotoxy(1,1);   printf("+");   gotoxy(79,1);  printf("+");
    gotoxy(1,5);   printf("+");   gotoxy(79,5);  printf("+");
    gotoxy(1,22);  printf("+");   gotoxy(79,22); printf("+");
    gotoxy(1,24);  printf("+");   gotoxy(79,24); printf("+");

    gotoxy(3,3);  printf("       ");



    gotoxy(3,2);  printf("Joao Victor dos Santos Bento");
    gotoxy(36,3);  printf("Sistema de Livros");
    gotoxy(62,4); printf("Lista Estatica");

    gotoxy(2, 23);
    printf("MSG:");
}

void limpa_MSG(){
    
    gotoxy(2,23);
    printf("                                                                         ");
}


void tela_livro(){

    gotoxy(10,10);
    printf("ID do livro....................: ");

    gotoxy(10,12);
    printf("Nome do Titulo do Livro........: ");

    gotoxy(10,14);
    printf("Autor do Livro.................: ");

    gotoxy(10,16);
    printf("Ano de Lancamento do Livro.....: ");
}

#define MAX 5

typedef struct{
    int id;
    char titulo[50];
    char autor[30];
    char ano[30];
}reg_livros;


typedef struct{
    int inicio;
    int fim;
    reg_livros liv[MAX];
}Lista;


int pesquisa(int codigo, Lista *l){
    
    int i;
    
    for(i=l->inicio;i < l->fim;i++){
        if(codigo == l->liv[i].id){
            return i;
        }
    }

    return -1;

}

void adicionarLivro(Lista *l){
    reg_livros liv;
    int opcao=0;


    do {
        if(l->fim >= MAX){

            limpa_MSG();

            gotoxy(2,23);
            printf("A sua lista esta cheia");
        } else {

            system("cls");

            tela();
            tela_livro();

            gotoxy(32, 6);
            printf("ADICIONANDO LIVRO");


            gotoxy(43,10);
            scanf("%d", &liv.id);

            gotoxy(43,12);
            fflush(stdin);
            fgets(liv.titulo, 50, stdin);

            gotoxy(43,14);
            fflush(stdin);
            fgets(liv.autor, 30, stdin);

            gotoxy(43,16);
            fflush(stdin);
            fgets(liv.ano, 50, stdin);

            }

            l->liv[l->fim] = liv;

            l->fim++;

            limpa_MSG();

            gotoxy(2,23);
            printf("O livro foi cadastrado com sucesso!!!");
            getch();

            system("cls");
            tela();
            limpa_MSG();

            gotoxy(2,23);
            printf("Deseja inserir outro(1-Sim, 2-Nao): ");
            scanf("%d", &opcao);

    } while(opcao != 2);

    system("cls");
    tela();

    return;

}


void inserirPosicao(Lista *l){
    
    reg_livros liv;
    int i;
    int posicao=0;
    int verificacao=0;

    if(l->fim == l->inicio){
        
        system("cls");
        tela();

        gotoxy(7,23);
        printf("A sua biblioteca esta vazia, pode adicionar um livro de forma manual");

        getch();

        limpa_MSG();

        gotoxy(2,23);
        printf("Pressione qualquer tecla para voltar ao menu....");

        getch();

        system("cls");
        tela();

        return;

    }

    system("cls");
    tela();

    limpa_MSG();

    do {

        limpa_MSG();
        gotoxy(2,23);
        printf("Digite a posicao em que deseja inserir o livro: ");
        scanf("%d", &posicao);

        system("cls");

        tela();

        limpa_MSG();

        gotoxy(2,23);
        printf("Tem certeza que vai ser essa posicao(1-Sim, 2-Nao): ");
        scanf("%d", &verificacao);
    

    } while(verificacao != 1);

    if(posicao < 0 || posicao > l->fim){
        
        limpa_MSG();

        gotoxy(2,23);
        printf("Posicao invalida");
        return;
    }

    for(i=l->fim;i>posicao;i--){
        l->liv[i] = l->liv[i-1];

    }

    system("cls");

    tela();
    tela_livro();

    gotoxy(25,6);
    printf("CADASTRANDO O LIVRO DESEJADO NA POSICAO %d ", posicao);

    gotoxy(43,10);
    scanf("%d", &liv.id);

    gotoxy(43,12);
    fflush(stdin);
    fgets(liv.titulo, 50, stdin);

    gotoxy(43,14);
    fflush(stdin);
    fgets(liv.autor, 30, stdin);

    gotoxy(43,16);
    fflush(stdin);
    fgets(liv.ano, 50, stdin);


    l->liv[posicao] = liv;

    l->fim++;

    system("cls");
    tela();

    limpa_MSG();
    gotoxy(2,23);
    printf("O livro foi cadastrado com sucesso!!!");
    getch();

    system("cls");
    tela();

    limpa_MSG();
    gotoxy(2,23);
    printf("Pressione qualquer tecla para voltar ao menu principal.....");

    getch();

    return;


}

void removerLivro(Lista *l){
    
    int codigo;
    int i;
    int posicao=0;
    int opcao=0;

    system("cls");
    tela();

    gotoxy(32,6);
    printf("REMOVENDO LIVRO");

    limpa_MSG();
    gotoxy(2,23);
    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d", &codigo);

    posicao = pesquisa(codigo, l);

    if(posicao == -1){

        system("cls");
        tela();

        limpa_MSG();
        gotoxy(2,23);
        printf("O ID do livro nao foi encontrado...");
        getch();


        system("cls");
        tela();

        limpa_MSG();
        gotoxy(2,23);
        printf("Pressione qualquer tecla para voltar ao menu principal");

        getch();


        return;
    }

    system("cls");
    tela();
    tela_livro();

    gotoxy(25,6);
    printf("EXCLUINDO LIVRO %s", l->liv[posicao].titulo);

    gotoxy(43,10);
    printf("%d", l->liv[posicao].id);

    gotoxy(43,12);
    printf("%s", l->liv[posicao].titulo);

    gotoxy(43,14);
    printf("%s", l->liv[posicao].autor);

    gotoxy(43,16);
    printf("%s", l->liv[posicao].ano);

    limpa_MSG();
    gotoxy(2,23);
    printf("Tem certeza que deseja excluir esse livro? (1-Sim, 2-Nao): ");
    scanf("%d", &opcao);

    if(opcao == 1){

        for(i = posicao; i < l->fim - 1; i++){
            l->liv[i] = l->liv[i+1];
        }
        l->fim--;

        system("cls");
        tela();

        gotoxy(2,23);
        printf("O Livro foi excluido com sucesso....");

        getch();

        system("cls");
        tela();

        limpa_MSG();
        gotoxy(2,23);
        printf("Pressione qualquer tecla para voltar ao menu principal....");

        getch();

        return;

    } else {

        system("cls");
        tela();


        limpa_MSG();
        gotoxy(2,23);
        printf("A exclusao foi cancelada, volte ao menu principal.....");

        getch();

        return;
    }

}

void buscarLivro(Lista *l){
    
    int codigo;
    int posicao=0;

    system("cls");
    tela();

    limpa_MSG();

    gotoxy(2,23);
    printf("Digite o ID do livro que deseja consultar: ");
    scanf("%d", &codigo);

    posicao = pesquisa(codigo, l);

    if(posicao != -1){

        system("cls");
        tela();
        tela_livro();

        gotoxy(32,6);
        printf("CONSULTA LIVRO %d ", l->liv[posicao].id);


        gotoxy(43,10);
        printf("%d", l->liv[posicao].id);

        gotoxy(43,12);
        printf("%s", l->liv[posicao].titulo);

        gotoxy(43,14);
        printf("%s", l->liv[posicao].autor);

        gotoxy(43,16);
        printf("%s", l->liv[posicao].ano);

        gotoxy(2,23);
        printf("Pressione qualquer tecla para voltar ao menu principal.....");
        getch();

        system("cls");
        tela();

    } else {
        system("cls");
        tela();

        limpa_MSG();

        gotoxy(2,23);
        printf("ID do livro nao foi encontrada, tente novamente....");

        getch();

        system("cls");
        tela();

        limpa_MSG();

        gotoxy(2,23);
        printf("Pressione qualquer tecla para continuar....");

        getch();
    }

}


int main(){

    Lista l;
    int opcao=0;

    tela();
    system("color 02");


    l.inicio=0;
    l.fim=0;

    do {
        gotoxy(23,10);
        printf("1- Adicionar livro na biblioteca");
        gotoxy(23,11);
        printf("2- Inserir livro em uma posicao especifica");
        gotoxy(23,12);
        printf("3- Remover livro por ID");
        gotoxy(23,13);
        printf("4- Buscar livro pelo ID");
        gotoxy(23,14);
        printf("5- Sair");

        limpa_MSG();
        gotoxy(2,23);
        printf("Digite a sua opcao: ");
        scanf("%d", &opcao); 
        
        switch(opcao){
            case 1:
                adicionarLivro(&l);
                break;
            case 2:
                inserirPosicao(&l);
                break;
            case 3:
                removerLivro(&l);
                break;
            case 4:
                buscarLivro(&l);
                break;
            case 5:
                break;
            default:
                limpa_MSG();
                gotoxy(2,23);
                printf("Nenhuma opcao valida foi inserida......");
                break;
        }

} while(opcao != 7);

}
