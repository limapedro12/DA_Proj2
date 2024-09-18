# DA: Projeto de Programação II
## Algoritmos de Rotas para Entregas Urbanas e Oceânicas

### Representação dos dados fornecidos

Grafo

• Nós com id (e coordenadas nos grafos do mundo real)

• Arestas bidirecionais

• Nós ordenados por id para facilitar e agilizar busca (𝑂(1))


Foram implementados os seguintes algoritmos:

### Força Bruta com Backtracking

• Implementado através de uma função recursiva que explora todos os
caminhos (que começam e acabam no nó de índice 0) possíveis no
grafo.

• Se, num dado ponto do caminho, o tamanho no momento é maior do
que o menor tamanho até então encontrado, o caminho deixa de ser
explorado.

• Complexidade temporal: $$𝑂(𝑉!)$$

### Aproximação Triangular

• Produz-se uma MST do dado grafo através do Algoritmo de Prim,
sendo retornada, por esse algoritmo, uma ordem de nós (não inclui o
nó de índice 0).

• Os nós são visitados pela ordem anteriormente retornada e é
calculada a distância entre eles, recorrendo às arestas já existentes.

• No caso de não existir aresta entre dois nós, é concebida uma aresta
fictícia cuja distância é calculada recorrendo à fórmula de haversine.

• Complexidade temporal: $$𝑂( 𝑉 + 𝐸 log 𝐸)$$

### Heurística 2-opt

• Começando com um caminho qualquer (aleatório), o algoritmo procura interseções entre arestas. Para cada interseçãoencontrada, “descruza-se” as respetivas arestas, tal como na imagem.O procedimento é repetido até não haver mais melhorias possíveis.

Dessa forma, o comprimento total do caminho vai sendo reduzido.

• Complexidade temporal:

• Média: $$𝑂(𝑉^3 * log 𝑉)$$

• Pior caso: $$𝑂(2^V)$$

### Heurística 3-opt

• Começando com um caminho aleatório, seleciona-se 3 arestas desse
caminho. Se as removermos, criamos 3 sub-caminhos. Existem 7
maneiras diferentes de os reconectar, pelo que se analisa todas
e escolhe-se a que contribui para um menor custo ou, ainda, por
manter

• Este processo é repetido até todas as combinações de 3 arestas
tenham sido testadas.

• Complexidade temporal: $$𝑂(𝑉^4)$$

### Créditos

Trabalho realizado por:

• Francisco Alves, 202006281

• Pedro Lima, 202108806

• Pedro Januário, 202108768


