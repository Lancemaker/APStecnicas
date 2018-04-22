#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//tamanho maximo das "strings"
#define MAX 30


//APS: Tecnicas de Programação.
//Alunos:
//Gil Felipe da Silva RA : 21039722
//Daniel Silva Cadete RA : 21029862
//Humberto Macedo Matos RA : 20465566


//Considerações :
//Arrays são em sua base ponteiros. por exemplo:
//int a[10]
//"a" seria um apontamento para o primeiro elemento de um array de tamanho 10.
//Prototipos de funçoes;
void esvaziaLista(char (*nome)[MAX],char (*telefone)[MAX]);// char (*arr)[N] é um ponteiro para um array de N elementos do tipo char.
void adicionaContato(int *i,char (*nome)[MAX],char (*telefone)[MAX]);
void removeContato(int *i,char (*nome)[MAX],char (*telefone)[MAX]);
void listaContatos(char (*nome)[MAX],char (*telefone)[MAX]);
void pesquisaContatos(char (*nome)[MAX],char (*telefone)[MAX]);
void editaContato(char (*nome)[MAX],char (*telefone)[MAX]);
char *toLowerCase(char string[MAX]);

//main.
int main(){

    //declaração de variáveis:

    char nome[100][MAX], telefone[100][MAX];
    char buscar[MAX];
    int menu,i,compare;

    //incializando os arrays com strings vazias.

    esvaziaLista(nome,telefone);
    i=0;//este i serve para orientar o programa. Ele mostra qual o proximo espaço vazio, ajuda a editar e apagar nomes e telefones.
    while (menu != 6){
        printf("|-------------------------------------|\n");
        printf("|Digite a funcao desejada:            |\n");
        printf("|-------------------------------------|\n");
        printf("|1 - Adicionar um contato.            |\n");
        printf("|2 - Remover um contato.              |\n");
        printf("|3 - Listar todos contatos.           |\n");
        printf("|4 - Pesquisar Contatos na lista      |\n");
        printf("|5 - Editar um contato.               |\n");
        printf("|6 - Finalizar programa.              |\n");
        printf("|-------------------------------------|\n");
        scanf("%d",&menu);
        fflush(stdin);
        switch(menu){
            case 1:
                adicionaContato(&i,nome,telefone);
                break;
            case 2:
                removeContato(&i,nome,telefone);
                break;
            case 3:
                listaContatos(nome,telefone);
                break;
            case 4:
                pesquisaContatos(nome,telefone);

                break;
            case 5:
                editaContato(nome,telefone);
                break;
            case 6:
                printf("Finalizando programa!!!");
                break;
            default:
                printf("Erro! Redigite o comando desejado!!!\n\n");
                break;
        }
    }
}
//funcoes de apoio :
void esvaziaLista(char (*nome)[MAX],char (*telefone)[MAX]){//esvazia os nomes e os telefones colocando um '\0' em todos os arr[i][0] (isto é todas as primeiras letras de cada palavra).
        int i =0;
        for(i=0;i<100;i++){
        nome[i][0] = '\0';
        telefone[i][0] = '\0';
    }
}

char *toLowerCase(char string[MAX]){//converte um array de char em no mesmo array de char em lower case. Usado para fazer a pesquisa com nomes.
    int i=0;
    while(string[i]!='\0'){
        if((int)string[i]<91 && (int)string[i]>64){
            string[i]=(char)string[i]+32;
        }
        i++;
    }
    return string;
}

//funcoes principais.
void adicionaContato(int *i,char (*nome)[MAX],char (*telefone)[MAX]){
    printf("Digite o nome do contato: ");
    gets(nome[*i]);//aponta pra o endereco : nome[i][0];
    printf("Digite o numero do telefone: ");
    gets(telefone[*i]);
    (*i)++;
    printf("Contato adicionado!!!\n\n");
}

void removeContato(int *i,char (*nome)[MAX],char (*telefone)[MAX]){
    printf("Digite o numero do contado que deseja apagar: \n");
    for(*i=0;nome[*i][0]!='\0';(*i)++){
        printf("%d - nome: %s  telefone: %s\n",*i,nome[*i],telefone[*i]);
    }
    scanf("%d",i);//i é um pointer, logo, nao precisa do operador &;

    *nome[*i] = '\0'; //aponta pro conteudo de um endereco de memoria de um array de char na posicao i isto é nome[i][0]
    *telefone[*i] = '\0';//mesma coisa da linha acima so que pro telefone.
    (*i)++;

    while(*nome[*i]!='\0'){//este while existe para preencher o buraco provocado quando se remove um contato.
        strcpy(nome[(*i)-1],nome[*i]);
        strcpy(telefone[(*i)-1],telefone[*i]);
        *nome[*i] = '\0';
        *telefone[*i] = '\0';
        (*i)++;
    }
    *i=0;
    while(*nome[*i]!='\0'){// este while retorna o i para a primeira posicao vazia do array.
        (*i)++;
    }
    printf("Contato apagado!!!\n\n");


}

void listaContatos(char (*nome)[MAX],char (*telefone)[MAX]){//lista todos os contatos.
    int i;
    for(i=0;nome[i][0]!='\0';(i)++){
        printf("Nome     : %s\nTelefone : %s\n\n",nome[i],telefone[i]);
    }
    if(nome[0]=='\0'){
        printf("Nao existe nenhum contato em sua agenda!\n\n");
    }
}

void pesquisaContatos(char (*nome)[MAX],char (*telefone)[MAX]){// pesquisa os contatos por coincidencia de substrings. funciona tanto pra nome como pra telefone.
    int i=0;
    int acumulador=0;
    char fragmento[MAX];
    printf("Digite sua pesquisa: ");
    gets(fragmento);
    fflush(stdin);


    for(i=0;(nome[i][0]!='\0');i++){//compara o fragmento contra as listas de nomes e telefones.
        char tempNome[MAX];
        char tempTel[MAX];
        strcpy(tempNome,nome[i]);
        strcpy(tempTel,telefone[i]);
        if((strstr( toLowerCase(tempNome), toLowerCase(fragmento))!=NULL)||(strstr(toLowerCase(tempTel), toLowerCase(fragmento))!=NULL)) {
            printf("dentro\n");
            printf("ID : %d\nNome  : %s\nTelefone : %s\n",i,nome[i],telefone[i]);
            acumulador++;
        }
    }
    printf("%d contatos encontrados.\n",acumulador);
}

void editaContato(char (*nome)[MAX],char (*telefone)[MAX]){
    char buscar[MAX];
    int compare;
    int i =0;
    printf("Digite o nome do contado que deseja editar: ");
    gets(buscar);
    for(i=0;nome[i][0]!='\0';i++){
        compare = strcasecmp(buscar,nome[i]);
        if(compare==0){
            break;
        }
    }
    if(compare==0){
            printf("Nome: %s e Telefone: %s\n",nome[i],telefone[i]);
            printf("Digite a edicao que deseja do nome: ");
            gets(nome[i]);
            printf("Digite a edicao que deseja do telefone: ");
            gets(telefone[i]);
    }
    else{
        printf("Nenhum contato encontrado!\n\n");
    }
}
