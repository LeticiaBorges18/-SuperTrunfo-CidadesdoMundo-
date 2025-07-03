# Super Trunfo - Cidades do Mundo

Um jogo de cartas no estilo Super Trunfo, onde cada carta representa uma cidade, incluindo atributos como estado, código, população, PIB, área, pontos turísticos, densidade populacional e PIB per capita.

## Funcionalidades

- Cadastro de cartas de cidades
- Listagem de cartas (todas, por estado ou por população mínima)
- Comparação entre cartas por atributo escolhido
- Edição e remoção de cartas
- Salvamento/carregamento em arquivo CSV

## Como compilar

No terminal, execute:
```sh
gcc -o super_trunfo_cidades super_trunfo_cidades.c
```

## Como executar

```sh
./super_trunfo_cidades
```

## Estrutura do arquivo de cartas

As cartas são salvas em `cartas.csv` no formato:
```
"Estado",codigo,"Cidade",populacao,PIB,area,pontosTuristicos,densidadePopulacional,PIBperCapita
```
Exemplo:
```
"São Paulo",3550308,"São Paulo",12300000,730.00,1521.00,10,8082.22,59349.59
```

## Licença

MIT
