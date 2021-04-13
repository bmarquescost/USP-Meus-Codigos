# PROJETO MINI GOOGLE BOT - PARTE 2

## Planejamento
Pensamos em mudar a estrutura geral para uma árvore AVL, que guardaria de maneira ordenada e balanceada todos os sites que são inseridos.
As palavras chaves serão armazenadas em um vetor de palavras, um char **
Uma vez que são 10 palavras (no máximo), não é relevante realizar uma ordenação destas palavras para ter a possibilidade de utilizar buscas binárias.

## Para a primeira função nova a ser implementada
A nova função deverá receber uma palavra, e conferir em cada um dos sites se esta palavra existe entre suas palavras chaves.
Construiremos um vetor, armazenando ponteiros para estes sites que possuem tal palavra.
Será ordenado este vetor de maneira decresente em relação a relevância dos sites.

## Para a segunda função nova a ser implementada
A nova função deverá receber uma palavra e conferir em cada um dos sites se esta palavra existe entre suas palavras chaves.
Encontrado todos os sites que possuem tal palavra entre suas palavras chaves, devemos recolher todas suas palavras chave, construindo uma estrutura de dados com todas estas palavras
Para cada palavra chave nesta nova estrutura, devemos ir na árvore avl incicial de todos os sites, e procurar todos os sites que possuem ao menos uma das palavras que foram armazenadas anteriormente.

### Solução encontrada
Iremos procurar normalemente a palavra chave em todos os nós da árvore
Caso seja encontrada a palavra entre as palavras chaves do site, construiremos uma estrutura de dados "trie" para armazenar suas palavras chave
Iremos adicionar nesta mesma trie todas as palavras chaves dos sites que possuem a palavra chave inicalemente buscada (de forma a não inserir palavras chaves iguais)
Após completa, iremos voltar na árvore inicial e conferir todas as palavras chaves dos sites, verificando a existência dela na estrutura trie. Caso esteja, acrescentaremos um ponteiro para este site em um vetor, que em seguida será ordenado com um algoritmo de ordenação estável (quicksort ??)