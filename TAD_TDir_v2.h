#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dir{
    char nome[100];
    int tam;
    char *conteudo; // Novo: armazena o conteúdo do arquivo
    struct dir *pFilho;
    struct dir *prox;
}Dir;

// Protótipos das funções
void nomeDiretorio(Dir *d);
void listarDiretorio(Dir *d);
Dir* abrirDiretorio(Dir *d, char *nome);
Dir* voltarDiretorio(Dir *raiz, Dir *atual);
void criarDiretorio(Dir *d, char *nome);
void excluirDiretorio(Dir *d, char *nome);
int tamanhoDiretorio(Dir *d);
void criarArquivo(Dir *d, char *nome, int tamanho);
void excluirArquivo(Dir *d, char *nome);
void editarArquivo(Dir *d, char *nome);
void liberarDiretorio(Dir *d);
Dir* encontrarPai(Dir* noBusca, Dir* alvo);

// Implementações

void nomeDiretorio(Dir *d){
    if (d != NULL) {
        printf("\nDiretorio atual: %s\n\n", d->nome);
    }
}

void listarDiretorio(Dir *d){
    Dir* aux;

    if (d->pFilho == NULL){
        printf("\nDIRETORIO VAZIO.\n\n");
        return;
    }

    printf("\nConteudo do diretorio:\n");
    for (aux = d->pFilho; aux != NULL; aux = aux->prox){
        if (aux->tam == 0) {
            printf("[DIR]  %s\n", aux->nome);
        } else {
            printf("[ARQ]  %s (%d bytes)\n", aux->nome, aux->tam);
        }
    }
    printf("\n");
}

Dir* abrirDiretorio(Dir *d, char *nome){
    Dir* aux;
    
    if (d->pFilho == NULL){
        printf("\nDIRETORIO VAZIO. Nao foi possivel abrir '%s'.\n\n", nome);
        return d;
    }

    for (aux = d->pFilho; aux != NULL; aux = aux->prox){
        if (strcmp(aux->nome, nome) == 0){
            if (aux->tam == 0){
                printf("\nAbrindo diretorio: %s\n\n", aux->nome);
                return aux;
            } else {
                printf("\n'%s' eh um arquivo, nao um diretorio.\n\n", nome);
                return d;
            }
        }
    }

    printf("\n'%s' nao encontrado.\n\n", nome);
    return d;
}

Dir* encontrarPai(Dir* noBusca, Dir* alvo) {
    if (noBusca == NULL || noBusca->pFilho == NULL) {
        return NULL;
    }

    Dir* aux;
    for (aux = noBusca->pFilho; aux != NULL; aux = aux->prox) {
        if (aux == alvo) {
            return noBusca;
        }
    }

    for (aux = noBusca->pFilho; aux != NULL; aux = aux->prox) {
        Dir* paiEncontrado = encontrarPai(aux, alvo);
        if (paiEncontrado != NULL) {
            return paiEncontrado;
        }
    }
    return NULL;
}

Dir* voltarDiretorio(Dir *raiz, Dir *atual){
    if (atual == raiz) {
        printf("\nJa esta no diretorio raiz.\n\n");
        return atual;
    }

    Dir* pai = encontrarPai(raiz, atual);

    if (pai != NULL){
        printf("\nRetornando para: %s\n\n", pai->nome);
        return pai;
    } else {
        printf("\nErro ao encontrar diretorio pai. Mantendo em %s\n\n", atual->nome);
        return atual;
    }
}

void criarDiretorio(Dir *d, char *nome){
    // Verifica se já existe um diretório ou arquivo com esse nome
    Dir* aux;
    for (aux = d->pFilho; aux != NULL; aux = aux->prox) {
        if (strcmp(aux->nome, nome) == 0) {
            printf("\nJa existe um item com o nome '%s'.\n\n", nome);
            return;
        }
    }

    // Cria o novo diretório
    Dir *novoDir = (Dir*) malloc(sizeof(Dir));
    strcpy(novoDir->nome, nome);
    novoDir->tam = 0;
    novoDir->conteudo = NULL;
    novoDir->pFilho = NULL;
    novoDir->prox = NULL;

    // Insere no início da lista de filhos
    if (d->pFilho == NULL) {
        d->pFilho = novoDir;
    } else {
        novoDir->prox = d->pFilho;
        d->pFilho = novoDir;
    }

    printf("\nDiretorio '%s' criado com sucesso.\n\n", nome);
}

void liberarDiretorioRecursivo(Dir *d) {
    if (d == NULL) return;
    
    // Libera todos os filhos recursivamente
    Dir* aux = d->pFilho;
    while (aux != NULL) {
        Dir* temp = aux;
        aux = aux->prox;
        liberarDiretorioRecursivo(temp);
    }
    
    // Libera o conteúdo se existir
    if (d->conteudo != NULL) {
        free(d->conteudo);
    }
    
    // Libera o nó atual
    free(d);
}

void excluirDiretorio(Dir *d, char *nome){
    if (d->pFilho == NULL) {
        printf("\nDiretorio vazio. Nada para excluir.\n\n");
        return;
    }

    Dir* aux = d->pFilho;
    Dir* anterior = NULL;

    // Procura o diretório a ser excluído
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            // Verifica se é um diretório (tam == 0)
            if (aux->tam != 0) {
                printf("\n'%s' eh um arquivo. Use a opcao de excluir arquivo.\n\n", nome);
                return;
            }

            // Remove da lista
            if (anterior == NULL) {
                d->pFilho = aux->prox;
            } else {
                anterior->prox = aux->prox;
            }

            // Libera o diretório e todos seus filhos
            liberarDiretorioRecursivo(aux);
            printf("\nDiretorio '%s' e todo seu conteudo foram excluidos.\n\n", nome);
            return;
        }
        anterior = aux;
        aux = aux->prox;
    }

    printf("\nDiretorio '%s' nao encontrado.\n\n", nome);
}

int tamanhoDiretorio(Dir *d){
    if (d == NULL) return 0;

    int tamanhoTotal = 0;

    // Percorre todos os filhos
    Dir* aux;
    for (aux = d->pFilho; aux != NULL; aux = aux->prox) {
        if (aux->tam == 0) {
            // É um diretório, soma recursivamente
            tamanhoTotal += tamanhoDiretorio(aux);
        } else {
            // É um arquivo, soma o tamanho
            tamanhoTotal += aux->tam;
        }
    }

    return tamanhoTotal;
}

void criarArquivo(Dir *d, char *nome, int tamanho){
    // Verifica se já existe um item com esse nome
    Dir* aux;
    for (aux = d->pFilho; aux != NULL; aux = aux->prox) {
        if (strcmp(aux->nome, nome) == 0) {
            printf("\nJa existe um item com o nome '%s'.\n\n", nome);
            return;
        }
    }

    // Cria o novo arquivo
    Dir *novoArq = (Dir*) malloc(sizeof(Dir));
    strcpy(novoArq->nome, nome);
    novoArq->tam = tamanho;
    novoArq->conteudo = (char*) calloc(tamanho + 1, sizeof(char)); // +1 para o \0
    novoArq->pFilho = NULL;
    novoArq->prox = NULL;

    // Insere no início da lista de filhos
    if (d->pFilho == NULL) {
        d->pFilho = novoArq;
    } else {
        novoArq->prox = d->pFilho;
        d->pFilho = novoArq;
    }

    printf("\nArquivo '%s' criado com sucesso (%d bytes).\n\n", nome, tamanho);
}

void editarArquivo(Dir *d, char *nome){
    if (d->pFilho == NULL) {
        printf("\nDiretorio vazio.\n\n");
        return;
    }

    Dir* aux = d->pFilho;

    // Procura o arquivo
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            // Verifica se é um arquivo (tam != 0)
            if (aux->tam == 0) {
                printf("\n'%s' eh um diretorio, nao um arquivo.\n\n", nome);
                return;
            }

            // Editor simples
            printf("\n========== EDITOR DE ARQUIVO ==========\n");
            printf("Arquivo: %s (%d bytes)\n", aux->nome, aux->tam);
            printf("=======================================\n");
            
            // Mostra conteúdo atual se existir
            if (aux->conteudo != NULL && strlen(aux->conteudo) > 0) {
                printf("\nConteudo atual:\n");
                printf("---\n%s\n---\n", aux->conteudo);
            } else {
                printf("\n[Arquivo vazio]\n");
            }

            printf("\nDigite o novo conteudo (maximo %d caracteres).\n", aux->tam);
            printf("Pressione ENTER duas vezes para finalizar:\n");
            printf("=======================================\n");

            // Limpa o conteúdo antigo
            memset(aux->conteudo, 0, aux->tam + 1);

            // Lê o novo conteúdo
            char buffer[1000];
            int totalLido = 0;
            int linhasVazias = 0;

            while (linhasVazias < 2 && totalLido < aux->tam) {
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    // Verifica se é linha vazia
                    if (strcmp(buffer, "\n") == 0) {
                        linhasVazias++;
                        if (linhasVazias < 2) {
                            strncat(aux->conteudo, buffer, aux->tam - totalLido);
                            totalLido += strlen(buffer);
                        }
                    } else {
                        linhasVazias = 0;
                        int espacoRestante = aux->tam - totalLido;
                        if (espacoRestante > 0) {
                            strncat(aux->conteudo, buffer, espacoRestante);
                            totalLido += strlen(buffer);
                        }
                    }
                }
            }

            // Remove os dois \n finais se existirem
            int len = strlen(aux->conteudo);
            if (len >= 2 && aux->conteudo[len-1] == '\n' && aux->conteudo[len-2] == '\n') {
                aux->conteudo[len-2] = '\0';
            }

            printf("\n=======================================\n");
            printf("Arquivo salvo com sucesso!\n");
            printf("Bytes utilizados: %d/%d\n", (int)strlen(aux->conteudo), aux->tam);
            printf("=======================================\n\n");
            return;
        }
        aux = aux->prox;
    }

    printf("\nArquivo '%s' nao encontrado.\n\n", nome);
}

void excluirArquivo(Dir *d, char *nome){
    if (d->pFilho == NULL) {
        printf("\nDiretorio vazio. Nada para excluir.\n\n");
        return;
    }

    Dir* aux = d->pFilho;
    Dir* anterior = NULL;

    // Procura o arquivo a ser excluído
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            // Verifica se é um arquivo (tam != 0)
            if (aux->tam == 0) {
                printf("\n'%s' eh um diretorio. Use a opcao de excluir diretorio.\n\n", nome);
                return;
            }

            // Remove da lista
            if (anterior == NULL) {
                d->pFilho = aux->prox;
            } else {
                anterior->prox = aux->prox;
            }

            // Libera o conteúdo se existir
            if (aux->conteudo != NULL) {
                free(aux->conteudo);
            }

            // Libera o arquivo
            free(aux);
            printf("\nArquivo '%s' excluido com sucesso.\n\n", nome);
            return;
        }
        anterior = aux;
        aux = aux->prox;
    }

    printf("\nArquivo '%s' nao encontrado.\n\n", nome);
}

void liberarDiretorio(Dir *d){
    if (d == NULL) return;
    
    // Libera todos os filhos recursivamente
    Dir* aux = d->pFilho;
    while (aux != NULL) {
        Dir* temp = aux;
        aux = aux->prox;
        liberarDiretorioRecursivo(temp);
    }
    
    // Libera o conteúdo da raiz se existir
    if (d->conteudo != NULL) {
        free(d->conteudo);
    }
    
    // Libera a raiz
    free(d);
    printf("\nMemoria liberada com sucesso.\n");
}
