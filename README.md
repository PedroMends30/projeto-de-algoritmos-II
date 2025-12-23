# Árvore Rubro-Negra (RBTree)

Este repositório contém a implementação de uma **Árvore Rubro-Negra (RBTree)**, uma estrutura de dados balanceada que garante operações eficientes de inserção, remoção e busca, mantendo propriedades de balanceamento através de cores e rotações.

## Funcionalidades
- **Inserção**: Adiciona novos elementos à árvore, mantendo as propriedades da Árvore Rubro-Negra.
- **Remoção**: Remove um elemento da árvore, realizando ajustes para manter o balanceamento.
- **Busca**: Pesquisa por um valor específico na árvore.
- **Exibição**: Exibe a árvore em pré-ordem, com a cor de cada nó.

## Definições e Classes

### **Macros de Cores**
- **RED** e **BLACK**: Representam as cores dos nós na árvore. `RED` é definido como `false` e `BLACK` como `true`.
- **RED_COLOR** e **BLACK_COLOR**: Usados para colorir a saída no terminal, destacando os nós vermelhos e pretos durante a exibição.

### **Classe `TreeNode`**
Representa um nó na árvore. Cada nó contém:
- **data**: O valor armazenado no nó.
- **color**: A cor do nó (vermelho ou preto).
- **parent, left, right**: Ponteiros para o nó pai e seus filhos esquerdo e direito, respectivamente.

### **Classe `RBTree`**
A classe `RBTree` gerencia a árvore rubro-negra e contém a lógica para inserir, remover, e balancear nós, mantendo a árvore binária de busca balanceada. A árvore possui um nó especial chamado `NIL`, que é um nó sentinela utilizado para representar folhas e nós ausentes.

## Principais Funções

### **Busca e Subárvores**
- **findNode**: Procura um nó com um valor específico na árvore.
- **sucessor** e **predecessor**: Encontram o nó sucessor ou predecessor de um nó, respectivamente.

### **Inserção de Nó**
1. O nó é inserido de acordo com as regras da árvore binária de busca.
2. Após a inserção, a função **fixInsert** é chamada para ajustar a árvore, garantindo que as propriedades de cor e balanceamento sejam mantidas.

### **Remoção de Nó**
A remoção de um nó segue a lógica padrão de uma árvore binária de busca:
1. Se o nó removido for preto, a função **fixDelete** é chamada para restaurar o balanceamento da árvore, realizando ajustes de cores e rotações, se necessário.
2. O nó removido é substituído por seu sucessor ou predecessor, conforme a escolha de implementação (sucessor ou predecessor).

### **Função de Reparação de Remoção**
A função **fixDelete** é responsável por restaurar o balanceamento após a remoção de um nó preto:
- Ela verifica as cores dos nós adjacentes (irmão, pais) e, dependendo da situação, realiza rotações e mudanças de cores.

### **Rotações**
As rotações são usadas para manter o balanceamento da árvore:
- **Rotação à esquerda**: Movimenta um nó para a esquerda e troca o lugar com o seu filho direito.
- **Rotação à direita**: Movimenta um nó para a direita e troca o lugar com o seu filho esquerdo.

Essas rotações garantem que o caminho mais longo entre a raiz e as folhas seja no máximo o dobro do caminho mais curto.

### **Exibição da Árvore**
A função **preOrderTraversal** percorre a árvore em pré-ordem, exibindo as cores dos nós para facilitar a visualização da estrutura da árvore.

### **Troca de Cor de Nó**
A função **switchColor** altera a cor de um nó, sendo essencial para garantir que a árvore mantenha suas propriedades de balanceamento durante inserções e remoções.

## Funções Auxiliares

### **Busca Recursiva**
A função **searchTreeHelper** realiza a busca de um nó na árvore de forma recursiva. Ela compara o valor procurado com o valor de cada nó, decidindo se deve continuar a busca à esquerda ou à direita.

### **Função Principal (`main`)**
A função `main` apresenta um menu interativo para o usuário, permitindo realizar as seguintes operações:
- Inserir um valor
- Buscar um valor
- Remover um valor
- Sair do programa

Após cada operação, a árvore é exibida para o usuário, mostrando a estrutura atual.
