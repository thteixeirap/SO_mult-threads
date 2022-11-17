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


## Etapa 3 :heavy_check_mark:

Para cada permutação encontrada vocês precisam buscar individualmente os valores dos itens em hash, executando em seguida uma interseção desses valores. Se a interseção for não nula, aplique essa na hash de todas as classes. A classe que apresentar um valor de sobreposição maior após processar todas as permutações será apresentada como classe da tarefa em T.

## Etapa 4 :heavy_check_mark:

Elaborar um cache utilizando uma hash para armazenar o resultado das interseções já realizadas. Adote como chave as permutações e como valor o resultado das interseções. Feito isso, modifique o algoritmo para trabalhar da seguinte forma: Para cada nova permutação, buscar em cache se há resultado já processado. Em caso afirmativo, apenas teste as classes para o resultado. Caso contrário, faça toda a computação envolvida.

## Execução 

```sh
    make clean
```
```sh
    make
```
```sh
    make run
```
## Estruturas principais

* Exemplo de saída da hash dos itens e como é feita sua lógica .

<img src="https://user-images.githubusercontent.com/78819692/197308765-4190830a-1c01-4960-b421-36e48b3a5803.png" width="950">

* Exemplo de saida da hash de classes, sendo a key o nome da classe e em seguida as posições das linhas em que repete cada classe.

<!-- ![Captura de tela de 2022-10-21 21-46-44](https://user-images.githubusercontent.com/78819692/197308913-93a7243d-dc5a-4894-a426-eb556e5a6aeb.png) -->
<img src="https://user-images.githubusercontent.com/78819692/197308913-93a7243d-dc5a-4894-a426-eb556e5a6aeb.png" width="950">

* Exemplo de como é montado a CACHE

<!-- ![Diagrama sem nome-Página-11 drawio](https://user-images.githubusercontent.com/78819692/202572335-2545f627-1633-41ed-8e86-e233d343cc54.png) -->
<img src="https://user-images.githubusercontent.com/78819692/202572335-2545f627-1633-41ed-8e86-e233d343cc54.png" width="950">


## Combinações

Aqui está um exemplo de como fica as combinações.

No exemplo pegamos a primeira linha do arquivo T.csv
<!-- ![s00](https://user-images.githubusercontent.com/78819692/197306530-ecfaf9a1-2e17-4e76-826b-86a8b8f435bd.png) -->
<img src="https://user-images.githubusercontent.com/78819692/197306530-ecfaf9a1-2e17-4e76-826b-86a8b8f435bd.png" width="400">



## Interseções das combinações

- Tendo já feito as combinações possíveis para cada linha do arquivo de T.csv, iremos procurar essas chaves da combinação e, caso encontrado essas chaves na hash de itens, iremos fazer uma interseção entre os itens de cada chave pertencente a essa combinação.

- Quando enviamos a combinação para procurar a chave na hash de itens, primeiro verificamos se essa combinação tem em CACHE

<h1></h1>

Exemplos de alguns casos possíveis ao realizar o procedimento de interseção:



- Caso 1: Quando em nenhum momento é encontrado a combinação em CACHE </h3>
<!-- ![Diagrama sem nome-Página-4 drawio (3)](https://user-images.githubusercontent.com/78819692/202564546-046bf022-97ff-49e7-8922-61d57dfa781f.png) -->
<img src="https://user-images.githubusercontent.com/78819692/202564546-046bf022-97ff-49e7-8922-61d57dfa781f.png" width="620">

> É importante resaltar que as verificações do restante da combinação é feita apenas quando restam duas chaves ou mais, pois é considerado que quando resta apenas uma chave é mais vantajoso verificar na hash de itens do que em cache.

- Caso 2: Quando é encontrado a combinação em CACHE em algum momento do processo

<!-- ![SO2](https://user-images.githubusercontent.com/78819692/197306969-5ea75149-c8fe-4c78-8c93-0e175ab60bac.png) -->
<img src="https://user-images.githubusercontent.com/78819692/197306969-5ea75149-c8fe-4c78-8c93-0e175ab60bac.png" width="620">

* Caso 3: Quando uma das chaves da combinação não é encontrada na hash de itens

<!-- ![SO3](https://user-images.githubusercontent.com/78819692/197307016-06dc1fe4-9684-4e1e-948d-2b0d46c1ecc1.png) -->
<img src="https://user-images.githubusercontent.com/78819692/202565204-15799603-c101-4e26-867d-b59c70b07c64.png" width="620">

* Caso 4: Quando em algum momento é verificado que a combinação ou parte dela é inválida (não possui interseções entre as chaves)
<img src="https://user-images.githubusercontent.com/78819692/202565736-4b05a82d-40f3-4f99-91ad-bd0175d3e091.png" width="620">


## Interseção com a hash de classes

- Sempre que encontramos uma interseção de uma combinação fazemos uma outra interseção com a hash de classes com o objetivo de saber qual é a classe que mais tem itens em comum com as interseções das combinações.

- O resultado encontrado foi:

![Captura de tela de 2022-10-21 21-48-38](https://user-images.githubusercontent.com/78819692/197309064-ab30f15c-7c1b-4c34-b9ba-a4431ab16aa9.png)




