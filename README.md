<h1 align="center"> 
 Sistema multitarefa
</h1>




## Sobre 

<p>
Neste trabalho vamos construir um sistema de classificação cujas características nos permitirão observar conceitos importantes como: escalonamento e gestão de memória primária. Neste sistema, vamos considerar duas bases de dados D e T. A base D será utilizada para simular a inicialização, fornecendo assim o conceito de bootstrapping, tal como no sistema operacional.

Já a base T representará os processos a serem executados, cada um produzindo uma série de computações pesadas e necessárias, as quais vamos coordenar utilizando um sistema de escalonamento em dois níveis: mecanismo e política. Além disso, abordaremos o conceito de memória tratando de chavear os processos entre memória primária e processador, 
claro, tudo de forma simulada para que possamos extrair resultados mensuráveis para avaliação.
</p>


## Execução 


```sh
    make
```
```sh
    make run
```
## Saídas
![Captura de tela de 2022-08-28 20-52-56](https://user-images.githubusercontent.com/78819692/187100000-08a6946e-85d2-47b8-b173-766c2a1ce142.png)

<p>Menu exibido na iniciação do programa</p>


![Captura de tela de 2022-08-28 20-53-11](https://user-images.githubusercontent.com/78819692/187100035-d55b569b-581d-40d1-ad7a-5adaaada1184.png)
<p>Exemplo de saída da hash dos items, na qual a key é composta pela coluna e o item, e em seguida as posições nas quais a key se repete</p>


