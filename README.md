<h1 align="center"> 
 Sistema multitarefa
</h1>




## Sobre 

<p>
Neste trabalho vamos construir um sistema de classificação cujas características nos permitirão observar conceitos importantes como: escalonamento e gestão de memória primária. Neste sistema, vamos considerar duas bases de dados D e T. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional.

Já a base T representará os processos a serem executados, cada um produzindo uma série de computações pesadas e necessárias, as quais vamos coordenar utilizando um sistema de escalonamento em dois níveis: mecanismo e política. Além disso, abordaremos o conceito de memória tratando de chavear os processos entre memória primária e processador, 
claro, tudo de forma simulada para que possamos extrair resultados mensuráveis para avaliação.
</p>

## Etapa 1 :heavy_check_mark:

Elaboração das tabelas hash para itens e classes. Dado uma linha do arquivo, considerar item as colunas de 0 a n - 1. Considere a coluna n de cada linha como classe. Nessas tabelas é preciso armazenar cada item como chave e seus índices no arquivo como valor. Considere como índice a linha que aquele valor específico aparece. Considere também item específico aquele item pertencente a coluna x. Logo, para itens de mesmo valor, a indexação deve ser feita de forma separada, ou seja, se um item aparece na coluna 1 e 3 com valor 23.4, considere como chave da hash (1, 23.4) e (3,23.4). Repita esse processo para as classes, armazenando como chave sua descrição e como valor suas indexações.

## Etapa 2 :heavy_check_mark:

Agora vamos considerar o conteúdo de T. Leia o conteúdo de T em uma Fila em que cada posição detenha uma linha inteira já tokenizada. O tipo Vector do C++ consegue auxiliar vocês nessa tarefa. Depois de carregar todo o conteúdo de T, processar linha a linha. Considere como processar a ação de comparar os itens de T com a tabela hash de itens, selecionando apenas os itens em comum. Feito isso, realize a permutação dos itens comuns de 1 a N, com N definido estaticamente com define diretamente no código. Armazene todas as permutações de uma entrada em T em um segundo Vector.

## Execução 


```sh
    make
```
```sh
    make run
```
## Saídas!
:exclamation::exclamation: No menu, é necessário executar sequencialmente as opções para a execução correta do código :exclamation::exclamation:




* Menu exibido na iniciação do programa

![Captura de tela de 2022-10-14 20-35-26](https://user-images.githubusercontent.com/78819692/195957834-4426c91c-3351-4de5-a1f7-3ef234e114de.png)


* Exemplo de saída da hash dos items, na qual a key é composta pela coluna e o item, e em seguida as posições nas quais a key se repetem.

![Captura de tela de 2022-08-28 20-53-26](https://user-images.githubusercontent.com/78819692/187100160-e4566379-65c1-42e6-862c-68743402fe29.png)

* Exemplo de sáida da hash de classes, sendo a key o nome da classe e em seguida as posições das linhas em que repete cada classe.

![Captura de tela de 2022-09-19 22-20-46](https://user-images.githubusercontent.com/78819692/191146768-92de063a-70fa-4c0a-8bae-dc3220a13624.png)

* Exemplo de saída da hash de processos[T.csv]


Aqui esta a primeira linha do arquivo T.csv:

![Captura de tela de 2022-10-14 20-24-43](https://user-images.githubusercontent.com/78819692/195957181-c73ef6e4-d56a-4e85-942d-a8d4f733d3de.png)

Aqui esta como foi feita todas as combinações possíveis da linha, sendo primeiro a combinação de 4 em 1, até ser de 4 em 4:
![Captura de tela de 2022-10-14 20-24-21](https://user-images.githubusercontent.com/78819692/195957379-433c8b2e-8344-4976-9b62-a108bb0bd847.png)


## Etapa 3 :heavy_check_mark:

Para cada permutação encontrada vocês precisam buscar individualmente os valores dos itens em hash, executando em seguida uma interseção desses valores. Se a interseção for não nula, aplique essa na hash de todas as classes. A classe que apresentar um valor de sobreposição maior após processar todas as permutações será apresentada como classe da tarefa em T.

- Agora, a partir das combinações que temos, iremos fazer a intersecção das linhas dessas combinações e depois a intersecção desse resultado com a hash de classes. Assim, somaremos a quantidade de intersecção que existe em casa classe e depois exibiremos o resultado.

- Exemplo da saída:

![Captura de tela de 2022-10-14 20-35-17](https://user-images.githubusercontent.com/78819692/195958041-059e10f8-c056-474f-844b-e32aeeed8215.png)
