#include "TAD_tDir.h"

int main(){

    Dir *raiz = (Dir*) malloc(sizeof(Dir));
    strcpy(raiz->nome, "Raiz");
    raiz->tam = 0;
    raiz->pFilho = NULL;
    raiz->prox = NULL;

    Dir *diretorioAtual = raiz;

    int opcao = 0;
    do {
        printf("1. Nome Diretorio\n");
        printf("2. Listar Diretorio\n");
        printf("3. Abrir Diretorio\n");
        printf("4. Voltar Diretorio\n");
        printf("5. Criar Diretorio\n");
        printf("6. Excluir Diretorio\n");
        printf("7. Tamanho Diretorio\n");
        printf("8. Criar Arquivo\n");
        printf("9. Excluir Arquivo\n");
        printf("10. Sair\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            nomeDiretorio(diretorioAtual);
            break;
        case 2:
        listarDiretorio(diretorioAtual);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        }
    } while (opcao != 10);
    

    return 0;
}