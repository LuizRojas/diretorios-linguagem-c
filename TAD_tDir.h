#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dir{
    // O atributo nome deve conter o nome completo do diretório ou arquivo (ex: Raiz/Teste/Pasta/arq.txt).
    char nome[100];
    // armazenar o tamanho do diretório ou arquivo. Caso o nó represente um diretório, o tamanho deve ser zero, caso seja um arquivo, a informação do tamanho deve ser lida do teclado.
    int tam;
    // aponta para o primeiro filho da lista de filhos do nó em questão
    struct dir *pFilho;
    // aponta para o próximo irmão do nó em questão
    struct dir *prox;
}Dir;

// deve exibir o nome do diretório atual.
void nomeDiretorio(Dir *d);

// deve listar os diretórios e arquivos presentes no diretório 
// atual. Não deve ser exibido todos os diretórios abaixo do atual (netos, etc, 
// apenas os imediatamente abaixo (filhos). Caso o diretório atual esteja vazio, o 
// programa deve exibir uma mensagem informando o fato.
void listarDiretorio(Dir *d);

// deve abrir um subdiretório pertencente ao diretório atual a 
// partir do nome informado pelo usuário. Caso o subdiretório com o nome 
// informado não exista, o programa deve exibir uma mensagem informando o 
// fato.
void abrirDiretorio();

// deve retornar ao diretório pai do diretório atual. Caso o 
// diretório atual seja a Raiz, o programa deve permanecer na Raiz. 
void voltarDiretorio();

//  deve criar um subdiretório dentro do diretório atual a partir 
// do valor lido do teclado.
void criarDiretorio();

// deve excluir o diretório a partir do nome informado pelo 
// teclado. Além de excluir o diretório informado, todos os subdiretórios e 
// arquivos abaixo do informado também devem ser excluídos. Caso o diretório a 
// ser excluído não exista no diretório atual, o programa deve exibir uma 
// mensagem informando o fato.
void excluirDiretorio();

// deve exibir o tamanho total do diretório atual, lembrando 
// que cada diretório armazena a informação do seu tamanho no atributo tam 
// como zero.
void tamanhoDiretorio();

// deve criar um arquivo no diretório atual. O nome e o 
// tamanho do arquivo devem ser lidos do teclado.
void criarArquivo();

// deve excluir o arquivo a partir do nome informado pelo 
// teclado. Caso o arquivo a ser excluído não exista no diretório atual, o programa 
// deve exibir uma mensagem informando o fato.
void excluirArquivo();

// deve liberar a memória da estrutura de diretório completa 
// antes de ser encerrado.
void liberarDiretorio();

void nomeDiretorio(Dir *d){
    if (d != NULL) {
        printf("\nDiretorio atual: %s\n", d->nome);
    }
}

void listarDiretorio(Dir *d){
    // listar então os filhos do diretorio d
    // se existir
    //         A  -> listarDiretorio();
    //   B            C
    // Saída vai ser: B C
    // precisa percorrer todos os nós de d mostrando o nomeDiretorio(); de cada um, retornando os valores obtidos

    Dir* aux;

    // se estiver vazio
    if (d->pFilho == NULL){
        printf("\nDIRETORIO VAZIO.\n");
        return;
    }

    for (aux = d->pFilho; aux != NULL; aux->prox){
        printf("%s\n", aux->nome);
    }
}

Dir* abrirDiretorio(Dir *d, char *nome){

    Dir* aux;
    // vou entrar no diretorio que tem o mesmo nome buscado
    if (d->pFilho == NULL){
        printf("\nDIRETORIO VAZIO. Nao foi possivel abrir '%s'.\n", nome);
        return d;
    }

    for (aux = d->pFilho; aux != NULL; aux = aux->prox){
        // entrei no nó, é igual o que estou procurando?
        if (strcmp(aux->nome, nome) == 0){
            // é um diretorio?
            if (aux->tam == 0){
                printf("Abrindo diretorio: %s\n", aux->nome);
                return aux;
            } else {
                printf("'%s' eh um arquivo, nao um diretorio.\n", nome);
                return d;
            }
        }
    }

    // caso não encotre nada em lugar nenhum do diretorio
    printf("'%s' nao encontrado", nome);
    return d;  // volta pro inicio (ou seja, sem mudanças)
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
        printf("Ja esta no diretorio raiz.\n");
    }

    Dir* pai = encontrarPai(raiz, atual);

    if (pai != NULL){
        printf("Retornando para: %s\n", pai->nome);
        return pai;
    } else {
        printf("Foi comprar cigarro. Mantendo em %s\n", atual->nome);
        return atual;
    }

}

// Dir* criarDiretorio(){
//     printf("Digite ")
//     Dir *diretorio = (Dir*) malloc(sizeof(Dir));
//     strcpy(diretorio->nome, c);
//     diretorio->tam = 0;
//     diretorio->pFilho = NULL;
//     diretorio->prox = NULL;
//     return diretorio;
// }