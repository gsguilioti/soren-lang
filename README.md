# soren-lang

## sintaxe

Um arquivo fonte .srn pode conter os seguintes itens:
- variáveis
- funções
- expressões
- e comentários.

> Um comentário começa com o caractere `#` e o restante da linha após o caractere terá seu conteúdo ignorado

> toda expressão deve ser encerrada com o caractere `;`
existem os seguintes tipos de expressões:
- operações lógicas: &&, ||, ==, !=, <, <=, >, >=
- operações numéricas: +, -, *, /
- atribuição: =
- estruturas de controle: if else, loop
- valores literais

#### Os valores literais são:
- número: qualquer valor inteiro ou decimal, usa-se o `.` para separar as casas decimais.
- booleano: as palavras reservadas `true` ou `false`, ou qualquer valor numérico, sendo o 0 considerado falso e o restante verdadeiro.
- string: cadeias de caracteres entre aspas simples. ex. 'texto'
- identificadores: qualquer palavra iniciada por uma letra ou `_`. Está associado a um tipo.

#### Tipos primitivos
- num
- bool
- str

#### Declarações

###### Variáveis
Uma variável é um espaço de memória que guarda um valor atrelado a um tipo primitivo.
A declaração segue a palavra reservada `var`, um identificador seguido pelo caractere `:` e um tipo primitivo.
Ainda é possível ter um valor inicial por uma atribuição.
ex.
    var nome: bool;
    var _nome: str = 'test';

###### Funções
Uma função é declarada pela palavra reservada `fn` seguida de um identificador e sua lista de parâmetros.
Parâmetros são opcionais na declaração da mesma forma que o tipo de retoro. Para declarar um tipo de retorno 
use o operador `->` seguido de um tipo primitivo.
ex.
    fn nome() { },
    fn _nome(a: num) -> num { }

> Uma função pode parar sua execução por meio da palavra reservada `return`, caso a função não tenha um tipo, o retorno não pode conter
nenhuma expressão, do contrário a expressão deverá ter um valor do mesmo tipo da função.
ex.
    return;
    return a + 3;

###### Estruturas de controle

- if else
O controle pode ser feito pela decisão de um caminho, a estrutura vai avaliar se a expressão é verdadeira e executar as expressões.
ex. 
    if(true) { }
    if(false) { } else { }

- loop
Um loop pode executar uma sequência de ações enquanto a expressão for verdadeira.
ex.
    loop(true) { }
    loop(a < 5) { }

###### Chamadas
Uma chamada pode ser feita por um identificador, caso seja uma variável, apenas o nome é o suficiente,
no caso de uma função, é necessário informar os parâmetros com tipos e quantidade correta.
ex.
    a = b + 1;
    test(a, true);

###### Blocos
Um bloco é uma sequência de expressões limitadas pelos caracteres `{` no inicio e `}` no fim.

Cada bloco cria um novo escopo, os identificadores passam a existir no escopo em que foram declarados e podem
ser vistos em escopos filhos. Uma nova declaração de um identificador em um escopo filho é descartada no fim do escopo.
ex.
    var a: num = 1;
    {
        var a: num = 3;
    }
    a; # a vale 1