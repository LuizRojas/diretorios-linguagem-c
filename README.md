# Sistema de Diretórios em C

Trabalho de Estruturas de Dados - 2º Bimestre 2025/2  
**Disciplina:** Estruturas de Dados  
**Instituição:** MULTIVIX  
**Professor:** Matheus Brunoro Dilem

---

## 📋 Descrição do Projeto

Sistema de gerenciamento de diretórios e arquivos implementado em linguagem C, utilizando estrutura de dados de **árvore com número variável de filhos**. O sistema simula o comportamento de um sistema de arquivos básico, permitindo navegação entre diretórios, criação, exclusão e manipulação de arquivos e pastas.

---

## 🗂️ Estrutura do Projeto

O projeto possui **duas versões**:

### Versão 1 - Básica
- **`main.c`** - Programa principal com menu de 10 opções
- **`TAD_tDir.h`** - TAD (Tipo Abstrato de Dados) da árvore de diretórios

### Versão 2 - Com Editor ⭐
- **`main_v2.c`** - Programa principal com menu expandido (11 opções)
- **`TAD_tDir_v2.h`** - TAD com funcionalidade adicional de edição de arquivos
- **Funcionalidade extra:** Editor de texto integrado (opção 8.1)

---

## 🏗️ Estrutura de Dados

```c
typedef struct dir {
    char nome[100];        // Nome do diretório ou arquivo
    int tam;              // Tamanho (0 para diretórios, >0 para arquivos)
    char *conteudo;       // Conteúdo do arquivo (apenas v2)
    struct dir *pFilho;   // Ponteiro para primeiro filho
    struct dir *prox;     // Ponteiro para próximo irmão
} Dir;
```



## 🚀 Funcionalidades

### Versão 1 - Funcionalidades Básicas

| Opção | Função | Descrição |
|-------|--------|-----------|
| 1 | Nome Diretório | Exibe o nome do diretório atual |
| 2 | Listar Diretório | Lista arquivos e subdiretórios do diretório atual |
| 3 | Abrir Diretório | Navega para um subdiretório |
| 4 | Voltar Diretório | Retorna ao diretório pai |
| 5 | Criar Diretório | Cria um novo subdiretório |
| 6 | Excluir Diretório | Remove diretório e todo seu conteúdo (recursivo) |
| 7 | Tamanho Diretório | Calcula tamanho total do diretório (recursivo) |
| 8 | Criar Arquivo | Cria um novo arquivo com tamanho especificado |
| 9 | Excluir Arquivo | Remove um arquivo específico |
| 10 | Sair | Libera memória e encerra o programa |

### Versão 2 - Funcionalidade Adicional 🆕

| Opção | Função | Descrição |
|-------|--------|-----------|
| **8.1** | **Editar Arquivo** | **Editor de texto integrado estilo nano/vim** |

**Características do Editor:**
- ✅ Edição multilinha
- ✅ Visualização do conteúdo atual antes de editar
- ✅ Limite de tamanho respeitado automaticamente
- ✅ Finalização com duplo ENTER
- ✅ Contador de bytes utilizados
- ✅ Interface amigável e intuitiva

---

## 💻 Compilação e Execução

### Versão 1 (Básica)
```bash
# Compilar
gcc main.c -o diretorio -std=c99

# Executar
./diretorio
```

### Versão 2 (Com Editor)
```bash
# Compilar
gcc main_v2.c -o diretorio_v2 -std=c99

# Executar
./diretorio_v2
```
## 📦 Arquivos do Projeto

```
projeto/
├── README.md                    # Este arquivo
├── main.c                       # Versão 1 - Básica
├── TAD_tDir.h                   # TAD Versão 1
├── main_v2.c                    # Versão 2 - Com Editor
├── TAD_tDir_v2.h                # TAD Versão 2
└── Estruturas_de_Dados_AP2.pdf  # Especificação do trabalho
```

---

## 🎯 Requisitos Atendidos

- [x] Implementação da estrutura TAD
- [x] Árvore com número variável de filhos
- [x] 10 opções do menu funcionais
- [x] Navegação entre diretórios
- [x] Criação e exclusão de arquivos/diretórios
- [x] Exclusão recursiva
- [x] Cálculo recursivo de tamanho
- [x] Liberação completa de memória
- [x] Validações e tratamento de erros
- [x] **EXTRA:** Editor de arquivos integrado (v2)

---

## 👥 Equipe

- **Integrantes:** Luiz Fernando Pereira Rojas dos Santos e Tadeu Augusto Vilela da Silva

**Disciplina:** Estruturas de Dados  
**Turma:** 2025/2  
**Data de Entrega:** 15/11/2025

---

## 📝 Observações Importantes

### Diferenças entre Arquivo e Diretório
- **Diretório:** `tam = 0`, pode ter filhos
- **Arquivo:** `tam > 0`, não pode ter filhos

### Gerenciamento de Memória
- Todo `malloc()` tem seu `free()` correspondente
- Liberação recursiva garante que não há memory leaks
- Conteúdo de arquivos também é liberado (v2)

### Limitações
- Nome máximo: 99 caracteres
- Tamanho de arquivo: limitado pela memória disponível
- Editor (v2): suporta arquivos de até o tamanho especificado


## ⚖️ Licença

Este projeto foi desenvolvido para fins educacionais como parte da avaliação da disciplina de Estruturas de Dados da MULTIVIX.

---
