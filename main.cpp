#include "TAD_tDir.h"

int main(){

    Dir *raiz = (Dir*) malloc(sizeof(Dir));
    strcpy(raiz->nome, "Raiz");
    raiz->tam = 0;
    raiz->pFilho = NULL;
    raiz->prox = NULL;

    Dir *diretorioAtual = raiz;

    int opcao = 0;
    char nomeDigitado[100];
    int tamDigitado = 0;

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

        switch (opcao){
        case 1:
            nomeDiretorio(diretorioAtual);
            break;
        case 2:
            listarDiretorio(diretorioAtual);
            break;
        case 3:
            printf("Digite o nome do diretorio que deseja abrir: ");
            scanf("%99s", nomeDigitado);
            diretorioAtual = abrirDiretorio(diretorioAtual, nomeDigitado);
            break;
        case 4:
            diretorioAtual = voltarDiretorio(raiz, diretorioAtual);
            break;
        case 5:
            printf("Digite o nome do novo diretorio: ");
            scanf("%99s", nomeDigitado);
            criarDiretorio(diretorioAtual, nomeDigitado);
            break;
        case 6:
            printf("Digite o nome do diretorio para excluir: ");
            scanf("%99s", nomeDigitado);
            excluirDiretorio(diretorioAtual, nomeDigitado);
            break;
        case 7:
            printf("Digite o nome do novo arquivo: ");
            scanf("%99s", nomeDigitado);
            printf("Digite o tamanho do arquivo: ");
            scanf("%d", &tamDigitado);
            criarArquivo(diretorioAtual, nomeDigitado, tamDigitado);
            break;
        case 8:
            printf("Digite o nome do novo arquivo: ");
            scanf("%99s", nomeDigitado);
            printf("Digite o tamanho do arquivo: ");
            scanf("%d", &tamDigitado);
            criarArquivo(diretorioAtual, nomeDigitado, tamDigitado);
            break;
        case 9:
            printf("Digite o nome do arquivo para excluir: ");
            scanf("%99s", nomeDigitado);
            excluirArquivo(diretorioAtual, nomeDigitado);
            break;
        case 10:
            printf("Liberando toda a memoria...\n");
            liberarDiretorio(raiz);
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 10);
    return 0;
}