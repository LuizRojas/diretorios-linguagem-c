#include "TAD_tDir.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    // Cria o diretório raiz
    Dir *raiz = (Dir*) malloc(sizeof(Dir));
    strcpy(raiz->nome, "Raiz");
    raiz->tam = 0;
    raiz->pFilho = NULL;
    raiz->prox = NULL;

    Dir *diretorioAtual = raiz;

    int opcao = 0;
    char nomeDigitado[100];
    int tamanhoArquivo;

    printf("=== SISTEMA DE DIRETORIOS ===\n");
    printf("Iniciando no diretorio: Raiz\n\n");

    do {
        printf("================================\n");
        printf("1.  Nome Diretorio\n");
        printf("2.  Listar Diretorio\n");
        printf("3.  Abrir Diretorio\n");
        printf("4.  Voltar Diretorio\n");
        printf("5.  Criar Diretorio\n");
        printf("6.  Excluir Diretorio\n");
        printf("7.  Tamanho Diretorio\n");
        printf("8.  Criar Arquivo\n");
        printf("9.  Excluir Arquivo\n");
        printf("10. Sair\n");
        printf("================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer após ler o número

        switch (opcao)
        {
        case 1:
            nomeDiretorio(diretorioAtual);
            break;
            
        case 2:
            listarDiretorio(diretorioAtual);
            break;
            
        case 3:
            printf("\nDigite o nome do diretorio que deseja abrir: ");
            fgets(nomeDigitado, 100, stdin);
            nomeDigitado[strcspn(nomeDigitado, "\n")] = 0; // Remove o \n
            diretorioAtual = abrirDiretorio(diretorioAtual, nomeDigitado);
            break;
            
        case 4:
            diretorioAtual = voltarDiretorio(raiz, diretorioAtual);
            break;
            
        case 5:
            printf("\nDigite o nome do novo diretorio: ");
            fgets(nomeDigitado, 100, stdin);
            nomeDigitado[strcspn(nomeDigitado, "\n")] = 0; // Remove o \n
            criarDiretorio(diretorioAtual, nomeDigitado);
            break;
            
        case 6:
            printf("\nDigite o nome do diretorio a excluir: ");
            fgets(nomeDigitado, 100, stdin);
            nomeDigitado[strcspn(nomeDigitado, "\n")] = 0; // Remove o \n
            excluirDiretorio(diretorioAtual, nomeDigitado);
            break;
            
        case 7:
            {
                int tamanho = tamanhoDiretorio(diretorioAtual);
                printf("\nTamanho total do diretorio '%s': %d bytes\n\n", 
                       diretorioAtual->nome, tamanho);
            }
            break;
            
        case 8:
            printf("\nDigite o nome do arquivo: ");
            fgets(nomeDigitado, 100, stdin);
            nomeDigitado[strcspn(nomeDigitado, "\n")] = 0; // Remove o \n
            
            printf("Digite o tamanho do arquivo (em bytes): ");
            scanf("%d", &tamanhoArquivo);
            limparBuffer(); // Limpa o buffer após ler o número
            
            if (tamanhoArquivo <= 0) {
                printf("\nTamanho invalido. O arquivo deve ter tamanho maior que zero.\n\n");
            } else {
                criarArquivo(diretorioAtual, nomeDigitado, tamanhoArquivo);
            }
            break;
            
        case 9:
            printf("\nDigite o nome do arquivo a excluir: ");
            fgets(nomeDigitado, 100, stdin);
            nomeDigitado[strcspn(nomeDigitado, "\n")] = 0; // Remove o \n
            excluirArquivo(diretorioAtual, nomeDigitado);
            break;
            
        case 10:
            printf("\nEncerrando o programa...\n");
            liberarDiretorio(raiz);
            printf("Programa encerrado.\n");
            break;
            
        default:
            printf("\nOpcao invalida! Tente novamente.\n\n");
            break;
        }
    } while (opcao != 10);

    return 0;
}
