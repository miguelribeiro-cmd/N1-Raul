#include <stdio.h>
#include <string.h>

void fopcao(int *opcao);
void carregartotal();
void cadastrar();
void listar();
void buscar();
void atualizar();
void remover();
void pular();

struct Pessoa{
    char nome[51];
    char sobrenome[51];
    char cpf[12];
    int idade;
    char email[101];
}pessoa[100];
int total = 0;



int main(void){
    carregartotal();
    int opcao = 0;
    printf("\n============Menu============\n");
    printf("Bem vindo ao trabalho de algoritmo\n");
    pular();
    fopcao(&opcao);
    printf("Pressione Enter para sair...");
    getchar();
    getchar();
    return 0;
}

void fopcao(int *opcao){
    do{
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("6 - Sair\n");
        printf("O que deseja fazer? ");
        scanf("%d", opcao);

        pular();

        switch (*opcao){
        case 1:
            cadastrar();
            break;
        
        case 2:
            listar();
            break;

        case 3:
            buscar();
            break;

        case 4:
            atualizar();
            break;

        case 5:
            remover();
            break;

        case 6:
            printf("Ate mais!\n");
            break;
 
        default:
            printf("Opcao invalida, escolha novamente!\n");
            break;
        }
        
        pular();
    } while (*opcao !=6);
    pular();
}

void pular(){
    printf("\n");
}

void carregartotal(){
    FILE *f = fopen("Dadospessoas.bin", "rb");
    if (f == NULL){
        total = 0;
        return;
    }

    struct Pessoa temp;
    total = 0;

    while (fread(&temp, sizeof(struct Pessoa), 1, f) == 1){
        total++;
    }

    fclose(f);
}

void cadastrar(){
    struct Pessoa temp;
    char cpfTemp[12];
    int existe = 0;

    printf("Digite o primeiro nome: ");
    scanf("%50s", pessoa[total].nome);

    printf("Digite o sobrenome: ");
    scanf("%50s", pessoa[total].sobrenome);

    printf("Digite o CPF (sem pontos e hifens): ");
    scanf("%11s", cpfTemp);

    FILE *f = fopen("Dadospessoas.bin", "rb");
    if (f != NULL){
        while (fread(&temp, sizeof(struct Pessoa), 1, f) == 1){
            if (strcmp(temp.cpf, cpfTemp) == 0){
                existe = 1;
                break;
            }
        }
        fclose(f);
    }

    if (existe){
        printf("\nCPF ja existente! Cadastro cancelado.\n\n");
        return;
    }

    strcpy(pessoa[total].cpf, cpfTemp);

    printf("Digite a idade: ");
    scanf("%d", &pessoa[total].idade);

    printf("Digite o email: ");
    scanf("%100s", pessoa[total].email);

    f = fopen("Dadospessoas.bin", "ab");
    fwrite(&pessoa[total], sizeof(struct Pessoa), 1, f);
    fclose(f);

    total++;

    pular();
    printf("Cadastro realizado com sucesso!\n");
    pular();
}

void listar(){
    struct Pessoa temporario;
    FILE *f = fopen("Dadospessoas.bin", "rb");
    if (f == NULL){
        printf("Nenhum arquivo encontrado!\n");
        return;
    }else{
        printf("===Lista de dados===\n");
        pular();
        while (fread(&temporario, sizeof(struct Pessoa), 1, f) == 1){
            printf("Nome: %s %s\n", temporario.nome, temporario.sobrenome);
            printf("CPF: %s\n", temporario.cpf);
            printf("Idade: %d\n", temporario.idade);
            printf("Email: %s\n", temporario.email);
            pular();
            printf("===============================\n");
            pular();
        }
    }
    fclose(f);
    
    pular();
}

void buscar(){
    int encontrado = 0;
    struct Pessoa temporario;
    char busca[12];
    FILE *f = fopen("Dadospessoas.bin", "rb");
    if (f == NULL){
        printf("Nenhum arquivo encontrado!\n");
        return;
    }else{
        printf("Busque quem deseja pelo CPF\n");
        printf("CPF: ");
        scanf("%s", busca);
        pular();
    }
    
    while (fread(&temporario, sizeof(struct Pessoa), 1, f) == 1){
        if (strcmp(busca, temporario.cpf) == 0){
            encontrado = 1;
            printf("Nome: %s %s\n", temporario.nome, temporario.sobrenome);
            printf("CPF: %s\n", temporario.cpf);
            printf("Idade: %d\n", temporario.idade);
            printf("Email: %s\n", temporario.email);
            pular();   
        }
    }
    if (encontrado == 0){
        printf("CPF nao encotrado!\n");
    }
    
    fclose(f);
    pular();
        
}

void atualizar(){
    int encontrado = 0;
    struct Pessoa temporario;
    char busca[12];
    FILE *f = fopen("Dadospessoas.bin", "rb+");
    if (f == NULL){
        printf("Nenhum arquivo encontrado!\n");
        return;
    }

    printf("Busque quem deseja atualizar pelo CPF\n");
    printf("CPF: ");
    scanf("%s", busca);
    pular();
    
    while (fread(&temporario, sizeof(struct Pessoa), 1, f) == 1){
        if (strcmp(busca, temporario.cpf) == 0){
            encontrado = 1;

            printf("===============================\n");
            printf("Nome: %s %s\n", temporario.nome, temporario.sobrenome);
            printf("CPF: %s\n", temporario.cpf);
            printf("Idade: %d\n", temporario.idade);
            printf("Email: %s\n", temporario.email);
            printf("===============================\n\n");

            char desejar;
            printf("Deseja realmente atualizar estes dados? (Y/N): ");
            scanf(" %c", &desejar);

            if (desejar == 'Y' || desejar == 'y'){
                printf("Digite o novo nome: ");
                scanf("%50s", temporario.nome);

                printf("Digite o novo sobrenome: ");
                scanf("%50s", temporario.sobrenome);

                printf("Digite a nova idade: ");
                scanf("%d", &temporario.idade);

                printf("Digite o novo email: ");
                scanf("%100s", temporario.email);

                fseek(f, -sizeof(struct Pessoa), SEEK_CUR);
                fwrite(&temporario, sizeof(struct Pessoa), 1, f);

                printf("\nDados atualizados com sucesso!\n\n");
            }
            break;    
        }
    }

    if (encontrado == 0){
        printf("Pessoa não encontrada!\n\n");
    }

    fclose(f);
}

void remover(){
    int encontrado = 0;
    struct Pessoa temporario;
    char busca[12];

    FILE *f = fopen("Dadospessoas.bin", "rb");
    if (f == NULL){
        printf("Nenhum arquivo encontrado!\n");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL){
        printf("Erro ao criar arquivo temporario!\n");
        fclose(f);
        return;
    }

    printf("Busque quem deseja remover pelo CPF\n");
    printf("CPF: ");
    scanf("%11s", busca);
    pular();  

    while (fread(&temporario, sizeof(struct Pessoa), 1, f) == 1){
        if (strcmp(busca, temporario.cpf) == 0){
            encontrado = 1;

            printf("===============================\n");
            printf("Nome: %s %s\n", temporario.nome, temporario.sobrenome);
            printf("CPF: %s\n", temporario.cpf);
            printf("Idade: %d\n", temporario.idade);
            printf("Email: %s\n", temporario.email);
            printf("===============================\n\n");

            char desejar;
            printf("Deseja realmente remover estes dados? (Y/N): ");
            scanf(" %c", &desejar);
            pular();

            if (desejar == 'Y' || desejar == 'y'){
                printf("Registro removido com sucesso!\n");
                pular();
            } else {
                fwrite(&temporario, sizeof(struct Pessoa), 1, temp);
            }
        } else {
            fwrite(&temporario, sizeof(struct Pessoa), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove("Dadospessoas.bin");
    rename("temp.bin", "Dadospessoas.bin");

    if (encontrado == 0){
        printf("CPF nao encontrado!\n");
        pular();
    } else {
        carregartotal();
    }
}