## Projeto


Em um primeiro desenvolvimento do sistema, implementei uma função de interface visual com o objetivo de facilitar a interação do usuário com o programa. Para isso, utilizei a função gotoxy, responsável por posicionar o cursor do console em coordenadas específicas da tela, permitindo que elementos fossem impressos em locais determinados. A partir dessa função, desenvolvi a função tela, que desenha a estrutura principal do sistema no console, com bordas, linhas e títulos, simulando uma interface organizada. Nela são exibidas informações como o nome do desenvolvedor, o título do sistema e o tipo de lista utilizada, além de uma área reservada para mensagens e interações. Dessa forma, o programa apresenta um layout mais limpo e intuitivo, contribuindo para uma melhor experiência de uso.

`````c
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

    gotoxy(3,2);  printf("Joao Victor dos Santos Bento");
    gotoxy(36,3);  printf("Sistema de Livros");
    gotoxy(62,4); printf("Lista Estatica");

    gotoxy(2, 23);
    printf("MSG:");
}
`````


Após isso, realizei a estruturação dos dados do sistema, definindo inicialmente uma constante MAX com valor 5, que representa o tamanho máximo da lista, ou seja, a quantidade de livros que poderão ser armazenados. Em seguida, criei a estrutura reg_livros, responsável por armazenar as informações de cada livro, contendo os campos id, titulo, autor e ano, permitindo assim o registro individual de cada item. Logo depois, desenvolvi a estrutura Lista, que agrupa os registros de livros em um vetor fixo de tamanho MAX e mantém o controle dos índices inicio e fim, utilizados para gerenciar a inserção e a remoção dos elementos. Dessa forma, a estrutura do programa foi organizada para permitir o armazenamento, manipulação e acesso eficiente aos dados cadastrados.

`````c

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

`````

Após esse primeiro momento, realizei a estrutura inicial da função main, onde foi desenvolvido o menu principal do sistema utilizando a estrutura de controle switch. Primeiramente, foi criada uma variável do tipo Lista, chamada l, responsável por armazenar os livros cadastrados. Em seguida, os índices inicio e fim foram inicializados com zero, garantindo que a lista começasse vazia. A função tela() foi chamada para exibir a interface gráfica do sistema, e o comando system("color 02") foi utilizado para alterar a cor do texto no console, deixando a aparência mais agradável. Dentro de um laço do...while, o menu principal é exibido na tela por meio da função gotoxy, apresentando as opções de adicionar, inserir em posição específica, remover, buscar e finalizar o programa. Após o usuário digitar sua escolha, o switch direciona o fluxo para a função correspondente a cada operação, manipulando os dados da lista conforme necessário. Caso uma opção inválida seja informada, o sistema limpa a tela e exibe uma mensagem de erro, mantendo a interação dinâmica e organizada.

`````c
    Lista l;
    int opcao=0;
    l.inicio=0;
    l.fim=0;

    tela();
    system("color 02");

    do {

        gotoxy(35,7);
        printf("MENU PRINCIPAL");

        gotoxy(23,10);
        printf("1- Adicionar Livro na Biblioteca");
        gotoxy(23,11);
        printf("2- Inserir o Livro em uma posicao especifica");
        gotoxy(23,12);
        printf("3- Remover Livro da Bliblioteca");
        gotoxy(23,13);
        printf("4- Buscar Livro na Biblioteca");
        gotoxy(23,14);
        printf("5- Finalizar Programa");

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
                system("cls");
                tela();

                gotoxy(7,23);
                printf("Nenhuma opcao valida foi inserida......");
                break;
        }

    } while(opcao >= 1 && opcao <= 4);


    return 0;
`````

Com isso em mente, comecei a desenvolver as funções responsáveis pelas operações do sistema, iniciando pela função adicionarLivro. Essa função tem como objetivo inserir novos registros na lista de livros, permitindo que o usuário cadastre cada obra individualmente. Inicialmente, é criada uma variável do tipo reg_livros, que armazena temporariamente as informações do livro a ser adicionado, e uma variável inteira opcao, usada para controlar a repetição do processo.

Dentro do laço do...while, a função verifica se a lista está cheia, comparando o valor de fim com o limite máximo definido por MAX. Caso a lista já esteja completa, o sistema exibe uma mensagem informando que não é possível adicionar novos livros e retorna ao menu principal. Caso contrário, o programa limpa a tela, redesenha a interface com tela() e tela_livro(), e solicita ao usuário os dados do livro — como o identificador (id), título, autor e ano — posicionando o cursor adequadamente com gotoxy.

Após o preenchimento dos campos, as informações são armazenadas na posição indicada por l->fim, e o contador fim é incrementado, atualizando o número de elementos da lista. Em seguida, uma mensagem de confirmação é exibida informando que o livro foi cadastrado com sucesso. O usuário então é questionado se deseja inserir outro livro, e, caso opte por continuar, o processo se repete. Ao final, a tela é novamente limpa e o programa retorna ao menu principal, garantindo uma navegação clara e organizada.


`````c

void adicionarLivro(Lista *l){
    reg_livros liv;
    int opcao=0;

    do {
        if(l->fim >= MAX){
            system("cls");
            tela();

            limpa_MSG();
            gotoxy(2,23);
            printf("A sua lista esta cheia");

            getch();

            system("cls");
            tela();
            printf("Pressione qualquer tecla para voltar ao menu principal.....");

            getch();

            return;
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
`````

Após isso, iniciei a criação da função inserirPosicao, responsável por permitir que o usuário adicione um novo livro em uma posição específica dentro da lista. Diferente da função adicionarLivro, que insere sempre no final, essa função oferece maior flexibilidade, possibilitando reorganizar os elementos conforme a necessidade.

Logo no início, é feita uma verificação para identificar se a lista está vazia, comparando os valores de inicio e fim. Caso não haja livros cadastrados, o sistema informa o usuário e retorna ao menu principal, evitando erros de manipulação. Em seguida, o programa solicita ao usuário a posição onde deseja inserir o novo livro e pede uma confirmação para garantir que a escolha seja intencional.

Se a posição digitada for inválida — isto é, menor que zero ou maior que o número atual de elementos (fim) —, uma mensagem de erro é exibida e a função é encerrada. Caso contrário, o sistema realiza um deslocamento dos elementos da lista, movendo todos os registros a partir do final até a posição desejada, abrindo espaço para a nova inserção.

Depois disso, é feita a coleta dos dados do novo livro (id, título, autor e ano), e as informações são armazenadas na posição escolhida. O contador fim é incrementado, atualizando o total de elementos cadastrados. Por fim, uma mensagem de sucesso é exibida, informando que o livro foi adicionado corretamente, e o sistema retorna ao menu principal, mantendo a interface organizada e funcional.

`````c
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
`````

Nesse viés, a função removerLivro ficou responsável por realizar a exclusão de um livro previamente cadastrado na lista, a partir do seu identificador (ID). Inicialmente, são declaradas variáveis auxiliares para armazenar o código digitado pelo usuário, a posição do livro dentro da lista, e opções de confirmação e repetição do processo.

Dentro de um laço do...while, o sistema limpa a tela e exibe a interface com o título “REMOVENDO LIVRO”. Em seguida, solicita ao usuário o ID do livro que deseja excluir e utiliza a função pesquisa para localizar sua posição no vetor. Caso o ID informado não seja encontrado, o programa exibe uma mensagem informando que o livro não foi localizado e retorna ao menu principal, evitando falhas na manipulação dos dados.

Quando o livro é encontrado, o sistema exibe suas informações — como ID, título, autor e ano — para que o usuário possa confirmar se realmente deseja removê-lo. Se a opção escolhida for “1” (Sim), é executado um laço que desloca os elementos seguintes uma posição para trás, sobrescrevendo o registro removido e garantindo que não haja espaços vazios na lista. Em seguida, o contador fim é decrementado, atualizando a quantidade total de livros armazenados.

Caso o usuário opte por não realizar a exclusão, o sistema apenas exibe uma mensagem informando que a operação foi cancelada. Após o término de cada remoção (ou cancelamento), o programa pergunta se o usuário deseja excluir outro livro. Se a resposta for negativa, o laço é encerrado e o sistema retorna ao menu principal. Dessa forma, a função garante o controle seguro e interativo da exclusão de registros dentro da lista estática.

`````c
void removerLivro(Lista *l){
    
    int codigo;
    int i;
    int posicao=0;
    int opcao=0;
    int continuar=0;

    
    do {

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

        } else {

            system("cls");
            tela();

            gotoxy(7,23);
            printf("A exclusao foi cancelada.....");

            getch();

        }

        system("cls");
        tela();

        limpa_MSG();
        gotoxy(2,23);
        printf("Deseja remover outro livro(1-Sim, 2-Nao)? ");
        scanf("%d", &continuar);

    } while(continuar != 2);

    system("cls");
    tela();

    limpa_MSG();
    gotoxy(2,23);
    printf("Pressione qualquqer tecla para voltar ao menu principal....");

    getch();
    return;
}
`````

Por fim, foi desenvolvida a função buscarLivro, que permite ao usuário consultar informações de um livro específico na lista a partir do seu ID. Essa função se apoia na função auxiliar pesquisa, que percorre o vetor de livros comparando o código informado com o campo id de cada registro. Se o livro for encontrado, a função retorna sua posição no vetor; caso contrário, retorna -1, indicando que o registro não existe.

Na função buscarLivro, dentro de um laço do...while, o programa limpa a tela e exibe a interface principal antes de solicitar ao usuário que digite o ID do livro que deseja consultar. Utilizando a função pesquisa, é verificada a existência do livro na lista. Se o registro for localizado, suas informações — como ID, título, autor e ano — são exibidas em tela organizada, permitindo que o usuário confirme os dados.

Se o ID informado não corresponder a nenhum livro cadastrado, o sistema exibe mensagens de alerta informando que o livro não foi encontrado e retorna à tela principal, garantindo uma navegação segura e sem erros. Ao final de cada consulta, o programa pergunta se o usuário deseja realizar outra pesquisa; caso contrário, encerra o laço e retorna ao menu principal. Assim, a função buscarLivro fornece uma forma eficiente e interativa de acessar os dados armazenados na lista.

`````c

int pesquisa(int codigo, Lista *l){
    int i;
    
    for(i=l->inicio;i < l->fim;i++){
        if(codigo == l->liv[i].id){
            return i;
        }
    }
    return -1;
}

void buscarLivro(Lista *l){
    
    int codigo;
    int posicao=0;
    int continuar=0;

    do {
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

            gotoxy(7,23);
            printf("Realizando Consulta");

            getch();


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
            return;
        }

        system("cls");
        tela();

        limpa_MSG();
        gotoxy(2,23);
        printf("Deseja realizar outra consulta(1-Sim, 2-Nao): ");
        scanf("%d", &continuar);

    } while(continuar != 2);

}
``````