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

![Captura de tela de 2022-09-19 22-20-15](https://user-images.githubusercontent.com/78819692/191146735-1ca79056-c720-4d9e-bed0-d7d0ec6440e6.png)

* Menu exibido na iniciação do programa

![Captura de tela de 2022-08-28 20-53-11](https://user-images.githubusercontent.com/78819692/187100035-d55b569b-581d-40d1-ad7a-5adaaada1184.png) 

* Exemplo de saída da hash dos items, na qual a key é composta pela coluna e o item, e em seguida as posições nas quais a key se repetem.

![Captura de tela de 2022-08-28 20-53-26](https://user-images.githubusercontent.com/78819692/187100160-e4566379-65c1-42e6-862c-68743402fe29.png)

* Exemplo de sáida da hash de classes, sendo a key o nome da classe e em seguida as posições das linhas em que repete cada classe.

![Captura de tela de 2022-09-19 22-20-46](https://user-images.githubusercontent.com/78819692/191146768-92de063a-70fa-4c0a-8bae-dc3220a13624.png)

* Exemplo de saída da hash de processos[T.csv]

![Captura de tela de 2022-09-19 22-21-45](https://user-images.githubusercontent.com/78819692/191146819-e3346398-c978-4cde-822a-905f2c1f284d.png)

* Exemplo do formato do aquivo txt que é criado referente as combinações das hash's.


