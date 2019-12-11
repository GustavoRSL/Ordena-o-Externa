# Ordenação Externa
- A base para ordenação externa em geral é o uso de ordenação por intercalação, que implica em combinar dois ou mais blocos ordenados em um único bloco ordenado.
Métodos devem minimizar número de passadas sobre o arquivo, que é base para a medida de complexidade. Isso torna complicado o uso de abordagens gerais e paralelização. 

## Estratégia Geral
- Dividir o arquivo em blocos do tamanho da memória interna disponível.
- Ordenar cada bloco na memória interna.
- Intercalar os blocos ordenados, fazendo várias passadas sobre o arquivo. A cada passada são criados blocos ordenados cada vez maiores, até que todo o arquivo esteja ordenado.

## Merge Sort em Memória
- O merge sort é um algoritmo de ordenação eficiente bastante popular, sendo a implementação preferida em listas encadeadas e como base para ordenação externa. 
- É um algoritmo recursivo, baseado na ideia de dividir para conquistar, cujas bases estão no problema da intercalação (ou separação):
