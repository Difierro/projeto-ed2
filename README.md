# Sistema FarmaTech

<table>
<tr> 
Este repositório contém o Sistema de Gerenciamento de uma farmácia desenvolvido na Linguagem C para a disciplina de Algoritmos e Estruturas de Dados II.

</tr>
</table>


- **Funcionalidades presentes no programa**:
É possível realizar algumas atividades dentro do programa. Para utilizar essas funcionalidades, basta selecionar a desejada. As opções disponíveis são:

### Clientes

  - `Cadastro de Cliente:` Realiza o cadastro de um novo cliente no sistema.

  - `Alteração de dados de Cliente:` Realiza alteração no cadastro de um cliente já existente.

  - `Busca de Cliente:` Realiza a busca do cadastro de um cliente já existente

  - `Remoção de Cliente:` Realiza a remoção do cadastro de um cliente já existente

### Medicamento
  - `Cadastro de medicamento:` Realiza o cadastro de um novo medicamento no sistema.

  - `Alteração de dados de medicamento:` Realiza alteração no cadastro de um medicamento já existente.

  - `Busca de medicamento:` Realiza a busca dde um medicamento já existente.

  - `Remoção de medicamento:` Realiza a remoção do cadastro de um medicamento já existente.

### Vendas
 - `Adicionar medicamento ao carrinho:` Adiciona um medicamento ao carrinho de compras do cliente.

 - `Remover medicamento do carrinho:` Remove um medicamento do carrinho de compras do cliente.

 - `Finalizar venda:` Finaliza uma venda dos medicamentos do carrinho.
### Entregas
  - `Realizar entrega:` Realiza a entrega de um pedido.

  - `Visualizar proxima entrega:` Exibe a próxima entrega a ser reealizada.

  - `Visualizar todas as entregas:` Exibe todas as entregas a serem realizadas.
___

## **Organização do Repositório**
```
📁 - projeto-ed2


|
└─── data
        │
        ├── clientes.txt
        ├── medicamentos.txt
│
└─── include
        │
        ├── clientes.h
        ├── entregas.h
        ├── medicamentos.h
        ├── menu_funcoes.h
        ├── opcoes_menu.h
│
└─── src
        │
        ├── clientes.c
        ├── entregas.c
        ├── main.c
        ├── medicamentos.c
        ├── menu_funcoes.c
        ├── opcoes_menu.c
│
└───README.md
```

### **Tecnologias utilizadas**
___

![c](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)


## **Execução do projeto**
- Antes de compilar o programa, deve-se alterar o caminho dos arquivos `clientes.txt` e `medicamentos.txt` no arquivo `main.c`. Para isso, altere os caminhos presentes na **Linha 9** e **Linha 10** do arquivo `main.c` para o caminho dos arquivos em sua máquina.

- Certifique-se de que você possui algum compilador C em sua máquina. Recomendamos o uso do GCC para compilar o código.
```
gcc -o main.exe .\src\main.c 
```
## **Participantes** 


<table align="center">
  <tr>    
  <!-- GUSTAVO
    -->
    <td align="center">
      <a href="https://github.com/Difierro">
        <img src="https://github.com/classroom-ufersa/GerenciamentoLojaBrinquedos/assets/114101163/e9b27183-9c24-4a17-a2e1-5acdcc39c8d4" 
        width="120px;" alt="Foto de Gustavo Rodrigues"/><br>
        <sub>
          <b>Gustavo Rodrigues</b>
         </sub>
      </a>
    </td>
     <!-- KAYQUE
    -->
    <td align="center">
      <a href="https://github.com/KayqueLopes99">
        <img src="https://github.com/user-attachments/assets/34bf131d-f8df-4604-8268-95c601daed47"
        width="120px;" alt="Foto de Kayque Lopes"/><br>
        <sub>
          <b>Kayque Lopes</b>
         </sub>
      </a>
    </td>
    <!-- EDUARDA
    -->
    <td align="center">
      <a href="https://github.com/euduar-da">
        <img src="https://github.com/classroom-ufersa/GerenciamentoLojaBrinquedos/assets/114101163/8faa38fe-6027-4aa7-939b-bf10de1534cd" 
        width="120px;" alt="Foto de Eduarda Souza no GitHub"/><br>
        <sub>
          <b>Eduarda Souza</b>
         </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/pehandrade">
        <img src="https://github.com/user-attachments/assets/fe6e8d12-bb15-4fe3-8377-47a2ca9ae925"
        width="120px;" alt="Foto de Pedro Andrade"/><br>
        <sub>
          <b>Pedro Andrade</b>
         </sub>
      </a>
    </td>
  </tr>
</table>