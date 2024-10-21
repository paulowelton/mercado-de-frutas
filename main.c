#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
}fruta;

int cods[1000];
fruta frutas[1000];

int id();
void cadastrar_fruta();
void mostrar(fruta f);
void listar_frutas();
void buscar_fruta();
void alterar_fruta();
void excluir_fruta();
void vender_fruta();
void registrar_venda(int codigo, char nome[], int quantidade, float preco);

int main()
{
    int res;
    
    do{
        printf("\ngerenciamento de frutas\n");
        printf("\n1-cadastrar_fruta\n");
        printf("2-listar_frutas\n");
        printf("3-buscar_fruta\n");
        printf("4-alterar_fruta\n");
        printf("5-excluir_fruta\n");
        printf("6-vender_fruta\n");
        printf("7-sair\n");
        printf("\n");
        
        scanf("%d", &res);
        if(res > 7 || res < 1){
            printf("valor indisponível\n");
            break;
        }
        if(res == 1){
            cadastrar_fruta();
        }
        if(res == 2){
            listar_frutas();
        }
        if(res == 3){
            buscar_fruta();
        }
        if(res == 4){
            alterar_fruta();
        }
        if(res == 5){
            excluir_fruta();
        }
        if(res == 6){
            vender_fruta();
        }
        
    }while(res != 7);
    return 0;
}

int id(){
    int quant = 0;
    
    for(int i = 0;i<1000;i++){
        if(cods[i] != 0){
            quant++;
        }
    }
    
    cods[quant] = quant + 1;
    
    return cods[quant];
}

void mostrar(fruta f){
    printf("\ncodigo: %d\nnome:%s\nquantidade:%d\npreco:%.2f\n", f.codigo, f.nome,f.quantidade,f.preco);
}

void cadastrar_fruta(){
    char nome[50];
    int quantidade;
    float preco;
    
    printf("\ncadastro de fruta\n");
    printf("\nnome: ");
    scanf("%s", nome);
    printf("quantidade: ");
    scanf("%d", &quantidade);
    printf("preco: ");
    scanf("%f", &preco);
    
    fruta f;
    f.codigo = id();
    strcpy(f.nome, nome);
    f.quantidade = quantidade;
    f.preco = preco;
    
    int pos_fruta = 0;
    for(int i = 0;i<1000;i++){
        if(frutas[i].codigo != 0){
            pos_fruta++;
        }
    }
    
    frutas[pos_fruta] = f;
    
    printf("\ncadastrado\n");
}

void listar_frutas(){
    printf("\nlista de produtos\n");
    for(int i=0;i<1000;i++){
        if(frutas[i].codigo == 0){
            break;
        }else{
            mostrar(frutas[i]);
        }
    }
}

void buscar_fruta(){
    printf("\ninforme o codigo: ");
    int codigo;
    scanf("%d", &codigo);

    for(int i=0;i<1000;i++){
        if(frutas[i].codigo == codigo){
            mostrar(frutas[i]);
        }
    }
}

void alterar_fruta(){
    printf("informe o codigo: ");
    int codigo;
    scanf("%d", &codigo);

    char novo_nome[50];
    int nova_quantidade;
    float novo_preco;
    
    printf("alterar_fruta:\n");
    for(int i=0;i<1000;i++){
        if(frutas[i].codigo == codigo){
            
            mostrar(frutas[i]);
            
            printf("\nnome: ");
            scanf("%s", &novo_nome);
            printf("quantidade: ");
            scanf("%d", &nova_quantidade);
            printf("preco: ");
            scanf("%f", &novo_preco);
            
            strcpy(frutas[i].nome, novo_nome);
            frutas[i].quantidade = nova_quantidade;
            frutas[i].preco = novo_preco;
        }
        
    }
}

//dando erro
void excluir_fruta(){
    printf("informe o codigo: ");
    int codigo;
    scanf("%d", &codigo);
    
    for(int i=0;i<1000;i++){
        if(frutas[i].codigo == codigo){
            frutas[codigo].codigo = 0;
            strcpy(frutas[codigo].nome, "");
            frutas[codigo].quantidade = 0;
            frutas[codigo].preco = 0;
        }
    }
}

void registrar_venda(int codigo, char nome[], int quantidade, float preco){
    FILE *arq;
    int result;
    char str[100];

    arq = fopen("vendas.txt", "at");

    if(arq == NULL){
        printf("erro ao registrar");

        return;
    }

    sprintf(str, "\nvenda realizada:\ncodigo: %d\nnome: %s\nquantidade: %d\nvalor total: %.2f", codigo, nome, quantidade, preco);

    result = fputs(str, arq);
    if(result == EOF){
        printf("erro na gravacao");
    }

    fclose(arq);
}

void vender_fruta(){
    int codigo;
    int quantidade;
    

    printf("\nvender fruta\ninforme o codigo da fruta:");
    scanf("%d", &codigo);
    printf("informe a quantidade: ");
    scanf("%d", &quantidade);
    
    for(int i=0;i<1000;i++){
        if(frutas[i].codigo == codigo){
            if(frutas[i].quantidade < quantidade){
                printf("quantidade invalida\n");
                printf("quantidade de %s disponiveis: %d un", frutas[i].nome,frutas[i].quantidade);
                return;
            }
            frutas[i].quantidade = frutas[i].quantidade - quantidade;

            float valor_tot = quantidade * frutas[i].preco;

            printf("vendido\n");
            sleep(2);
            printf("registrado\n");
            sleep(2);
            printf("quantidade restante: %d", frutas[i].quantidade);

            registrar_venda(frutas[i].codigo,frutas[i].nome, quantidade,valor_tot);
        }
    }
}