<h1 align="center"> 
 Sistema multitarefa
</h1>

## Sobre 

<p>
Neste trabalho vamos construir um sistema de classificação cujas características nos permitirão observar conceitos importantes como: escalonamento e gestão de memória primária. Neste sistema, vamos considerar duas bases de dados D e T. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional.

Já a base T representará os processos a serem executados, cada um produzindo uma série de computações pesadas e necessárias, as quais vamos coordenar utilizando um sistema de escalonamento em dois níveis: mecanismo e política. Além disso, abordaremos o conceito de memória tratando de chavear os processos entre memória primária e processador, 
claro, tudo de forma simulada para que possamos extrair resultados mensuráveis para avaliação.

Para saber mais sobre as etapas do trabalho -> [Wiki](https://github.com/thteixeirap/sistemaoperacional/wiki)
</p>

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
<!-- ![Diagrama sem nome-Página-11 drawio (1)](https://user-images.githubusercontent.com/78819692/202572775-82eefcbb-8e85-45f9-9e89-f7ce1adba354.png) -->
<img src="https://user-images.githubusercontent.com/78819692/202572775-82eefcbb-8e85-45f9-9e89-f7ce1adba354.png" width="950">

> Caso na etapa 1 é verificado que não é possél ter interseção entre as chaves da combinação, é adicionado em CACHE como chave a combinação e o valor que representa que essa combinação é inválida {-1}

## Combinações

Aqui está um exemplo de como fica as combinações.

No exemplo pegamos a primeira linha do arquivo T.csv
<!-- ![s00](https://user-images.githubusercontent.com/78819692/197306530-ecfaf9a1-2e17-4e76-826b-86a8b8f435bd.png) -->
<img src="https://user-images.githubusercontent.com/78819692/197306530-ecfaf9a1-2e17-4e76-826b-86a8b8f435bd.png" width="400">



## Interseções das combinações e classes

- Tendo já feito as combinações possíveis para cada linha do arquivo de T.csv, iremos procurar essas chaves da combinação e, caso encontrado essas chaves na hash de itens, iremos fazer uma interseção entre os itens de cada chave pertencente a essa combinação.

- Quando enviamos a combinação para procurar a chave na hash de itens, verificamos se essa combinação tem em CACHE.

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

<h1></h1>

 Comparação:

- No teste 1 está o temmpo das interseções utilizando do método de verificação em CACHE explicado anteriormente
- No teste 2 foi feito os teste do tempo das interseções utilizando apenas a verificação em CACHE no início do processo (a combinação inteira)

Valores em segundo do tempo de interseção

Teste 1     | Teste 2
----------- | ----------
0.00502197  | 0.0138698
0.00712295  | 0.00414172
0.021678    | 0.0127659
0.0043139   | 0.0179619
0.0180693   | 0.0039672
0.00671301  | 0.0176281
0.00535444  | 0.0107708
0.0145622   | 0.0126174
0.00583671  | 0.0167257
0.00510638  | 0.0171573
0.0098867   | 0.0174442

Media 1     | Media 2
----------- | ----------
0.01006050  | 0.01318636

> Conclui se que no método de verificação do restante das combinações temos cerca de 31% no ganho de tempo na execução das interseções em relação a execução na qual veriicamos apenas no ínicio em CACHE.

## Política

Dentro do código, estamos considerando que o processo é:

- Pegar uma combinação
- Fazer a interseção entre as chaves dessa combinação
- Pegar essa interseção encontrada e realizar uma interseção com a HASH de classes para obter a quantidade de sobreposições existentes.

1 - No modelo padrão, estamos usando a política `FIFO` ( Firt In, Firt Out), na qual enviamos pra realizar o processo a combinação que chegou primeiro.

<!-- <img src="https://user-images.githubusercontent.com/78819692/202767118-bbaa14c3-d30d-43cf-8cd0-d7fd624b93ae.png" width="950"> -->
| <img src="https://user-images.githubusercontent.com/78819692/202767118-bbaa14c3-d30d-43cf-8cd0-d7fd624b93ae.png" width="950">
|:--:| 
| Imagem exemplifica a sequência do envio das combinações para processo. Começamos na primeira fila, enviando as combinações de 1, depois de 2, 3 e 4, Após isso fazemos o mesmo procedimento pra as demais linhas abaixo|

2 - Para mudarmos a politica, passando para `Menor job primeiro`, temos que mandar para processo as combinações de 1 todas primeiro, depois as combinações de 2 e por seguinte 3 e 4. Para tanto então, usaremos ainda a ideia da politica da FIFO porém mudando a sequencia das combinações.


<!-- ![Captura de tela de 2022-11-18 15-03-47](https://user-images.githubusercontent.com/78819692/202772781-e6ddbeb0-9492-4780-ba6a-2cb68ae3e8a3.png) -->
<!-- <img src="https://user-images.githubusercontent.com/78819692/202767118-bbaa14c3-d30d-43cf-8cd0-d7fd624b93ae.png" width="950"> -->
| <img src="https://user-images.githubusercontent.com/78819692/202772781-e6ddbeb0-9492-4780-ba6a-2cb68ae3e8a3.png" width="950">
|:--:| 
| Imagem exemplifica a nova sequência de envio das combinações para processo. Estamos passando para a fila os processos considerados menores primeiro|

* Comparação

Valores referentes a execução das interseções ( em segundos )

FIFO        | SJF
----------- | ----------
0.0155707   | 0.00574528
0.01173  | 0.00814319
0.0172626    | 0.0127659
0.0171599  | 0.012068
0.00893674   | 0.00783486
0.00931155  | 0.0119587
0.0106861  | 0.00770536
0.00668645   | 0.00717361
0.0115985  | 0.00742447
0.00707733  | 0.00802264
0.0166281   | 0.00659891

Media FIFO     | Media SJF
----------- | ----------
0,0120589  | 0.00826750

> Portanto, conclui se que temos uma diminuição em 0,003791 segundos da FIFO para a SJF, que é cerca de 31,44% de ganho de tempo na execução das interseções

## Threads 

- Com a implementação das thread's mudamos algumas características do código. A thread `Produtor` é responsável em adiconar no buffer as combinações, portanto, a cada combinação feita é adicionada dentro do buffer que será consumida pela thread `Consumidor`. A consumidor é responsável por ficar procurando no buffer se há combinações feita, encontrando-as ele já as manda para realizar as interseções.

Para teste, usamos 1 thread produtor e 1 consumidor ( tempo em segundos )

THREAD      |
----------- | 
0.0324383  |
0.00661514 |
0.0155683 |   
0.0104903 |
0.0128829 | 
0.00661514 |
0.00502375 |
0.0126837 |  
0.0109973  |
0.018953 |
0.00724647  |

Media THREAD |
----------- |
0,0126831  |

> Com os valores obtidos, conclui que com a implementação das thread's não obtemos um ganho significante, o que na verdade tempos um aumento de tempo comparado com a politica de SJF. 


## Interseção com a hash de classes

- Sempre que encontramos uma interseção de uma combinação fazemos uma outra interseção com a hash de classes com o objetivo de saber qual é a classe que mais tem itens em comum com as interseções das combinações em relação .

- O resultado encontrado foi:

![Captura de tela de 2022-10-21 21-48-38](https://user-images.githubusercontent.com/78819692/197309064-ab30f15c-7c1b-4c34-b9ba-a4431ab16aa9.png)




