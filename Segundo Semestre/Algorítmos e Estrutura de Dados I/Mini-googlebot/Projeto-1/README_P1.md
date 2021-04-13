# <div align="center"> Projeto – Mini Googlebot(Parte I)
## <div align="center"> SCC0202 - Algoritmos e Estruturas de Dados
#### <div align="center"> Aluno: Bernardo Marques Costa - Número USP: 11795551

#### <div align="center"> Aluno: Fernando Henrique Paes Generich - Número USP: 11795342

#### **Compilador utilizado:** 
GNU Compiler Collection


#### **Estrutura de Dados utilizada:** 
Para o projeto, julgamos que a lista encadeada seria a estrutura mais adequada, visto a facilidade de inserção e remoção de dados (sites) independente de sua posição dentro da lista. Desta forma, a lista encadeada deixa mais prática a inserção de múltiplos nós/elementos como por exemplo na adição viabilizada por um arquivo CSV com os dados a serem adicionados.
Além disso, o fato da lista ser dinâmica e encadeada permite uma flexibilidade na utilização da memória do computador, visto que é armazenada na memória heap e os elementos das listas não são alocados sequencialmente em blocos da memória.


#### **Funções:**
As funções são acessadas através de um menu que é imprimido ao abrir o programa e após a chamada de cada função que não seja a função de finalização do programa.

|Número do Comando| Função|Nome no código       |O que faz                                                                                 |
|:---------------:|:-----:|:-------------------:|:----------------------------------------------------------------------------------------:|
|0| Inserir um site       |inserir_site         |Permite a inserção de um novo site                                                        |
|1| Remover um site       |remover_site         |Permite a remoção se um site já existente na lista                                        |
|2| Inserir palavra-chave |inserir_palavra_chave|Permite adicionar uma nova palavra-chave a um site já existente na lista                  |
|3| Atualizar relevância  |atualizar_relevancia |Permite alterar a relevância de um site já existente na lista                             |
|4| Mostrar lista         |lista_mostrar        |Imprime a lista na tela site por site                                                     |
|5| Ler arquivo CSV       |carrega_dados_csv    |Permite a leitura de dados de outros sites a partir de um arquivo txt passado pelo usuário|
|6| Sair                  |-                    |Fecha o programa                                                                          |

#### **Métodos:**

Inserção: Julgamos que eram necessárias duas formas de inserir dados na lista, uma através de um arquivo csv, e outra através da entrada padrão (stdin). Dessa forma foi necessária a modularização do código de forma a facilitar a aplicação das duas vias de inserção, permitindo uma melhor interação com o usuário.

Remoção: Foi implementada uma remoção levando em consideração três casos (que devem ser tratados de forma diferente): website no começo, no fim e no meio da lista encadeada. Nos três casos, primeiro efetuamos a reorganização dos encadeamentos entre os nós da lista e depois liberamos a memória utilizada pelo website que desejávamos remover.

Busca: Implementamos duas funções de busca, uma de verificação de existência e outra que retorna o website procurado ao achá-lo, as duas foram implementadas seguindo o molde de busca sequencial para percorrer a lista.


