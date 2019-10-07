# Projeto de Software Básico - Java Virtual Machine (JVM)

Projeto de desenvolvimento de uma JVM.


## Referência

[Introducão à JVM](https://www.devmedia.com.br/introducao-ao-java-virtual-machine-jvm/27624)
[Documentacão JVM](https://www.guru99.com/java-virtual-machine-jvm.html)


## Setup do ambiente

No desenvolvimento do projeto serão utilizadas as ferramentas de checagem estática e checagem dinânica do código. Para checagem estática será usado o [cppcheck](http://cppcheck.sourceforge.net/) e para checagem dinâmica será utilizado o [GDB](https://www.gnu.org/software/gdb/download/). Os dois devem ser instalados na máquina local de cada um, visto que o código passa por checagem estática a cada commit (sem o cppcheck o programa nem pode ser commitado, de modo a manter qualidade de código).

Para que isso funcione, basta rodar o script

```
./relocate.sh
```

Ele vai mandar os hooks para a pasta .git local.
Assim, toda vez que for feito o commit o cppcheck vai rodar e verificar que está de acordo com as diretrizes.  

Outro software legal pra se ter é um linter do cppcheck pra conseguir ver os erros do cppcheck direto no seu editor de texto. No sublime o pacote chama **SublimeLinter-cppcheck**.

## Build do projeto

Para compilar o projeto basta executar 

```
make
```

na pasta base do projeto.  
A execucão é feita executando o arquivo **main** gerado pelo make:

```
./main
```