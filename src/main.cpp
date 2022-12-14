/*
Nome do Aluno: Arthur Augusto Magalhães ------------- Matricula: 202110830
Nome do Aluno: Aaron Martins Leão Ferreira ---------- Matricula: 202120496
Nome do Aluno: Luís Gustavo Morais Cardoso ---------- Matricula: 202010816
*/

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct Medicamentos {
  char NomeMedicamento[50];
  char Descricao[100];
  char Laboratorio[100];
  char CodigoIndentificacao[100];
  int QuantidadeDisponivel;
  float PrecoUnitario;
  bool SituacaoProduto;
};

/*Funcão Exportar */

void exportar(Medicamentos *v, int TamVetor, int &quantidadeItens) {
  fstream dadosMedicamento;
  dadosMedicamento.open("dadosMedicamento.bin",
                        ios::out | ios::trunc | ios::binary | ios::in);
  for (int i = 0; i < TamVetor; i++) {
    Medicamentos aux = v[i];
    dadosMedicamento.write(reinterpret_cast<char *>(&aux), sizeof(aux));
  }
  cout << "Dados exportados com sucesso" << endl;
}

/*
Funcao nula Cadastro que gera os valores para serem cadastrados no registro
medicamentos
*/
int particiona(Medicamentos *v, int c, int f) {
  string pivo = v[c].CodigoIndentificacao;
  Medicamentos aux = v[c];
  int i = c + 1, j = f;
  while (i <= j) {
    if (v[i].CodigoIndentificacao <= pivo)
      i++;
    else if (pivo <= v[j].CodigoIndentificacao)
      j--;
    else {
      swap(v[i], v[j]);
      i++;
      j--;
    }
  }
  v[c] = v[j];
  v[j] = aux;
  return j; // retorna posição do pivô
}

//faz a ordenação em ordem alfabética do código
void quicksort(Medicamentos *a, int pos_pivo, int fim) {
  int pos_novo_pivo;
  if (pos_pivo < fim) {
    pos_novo_pivo = particiona(a, pos_pivo, fim);
    quicksort(a, pos_pivo, pos_novo_pivo - 1);
    quicksort(a, pos_novo_pivo + 1, fim);
  }
}

//função para realizar a busca binaria pelo código de indentificação
int BuscaBinaria(Medicamentos *V, int pos_inicial, int pos_final, string K) {
  int meio = (pos_inicial + pos_final) / 2;

  if (K == V[meio].CodigoIndentificacao) { // caso base: elemento encontrado
    return meio;
  } else if (pos_inicial < pos_final) { // caso geral: processo de busca
    if (V[meio].CodigoIndentificacao < K)
      return BuscaBinaria(V, meio + 1, pos_final, K);
    else
      return BuscaBinaria(V, pos_inicial, meio - 1, K);
  } else { // caso base: elemento não encontrada
    return -1;
  }
}

//função para consultar o medicamento pelo código
void Consultar(Medicamentos *VecMed, int tam) {

  string codigoBusca;
  cout << "Digite o código do produto que deseja buscar: ";
  cin >> codigoBusca;

  int posicao = BuscaBinaria(VecMed, 0, tam - 1, codigoBusca);

  if (posicao == -1) {

    cout << "Produto não encontrado." << endl;
  }

  else {

    cout << "Código do produto:"
         << " " << VecMed[posicao].NomeMedicamento << endl;
    cout << "Quantidade em estoque:"
         << " " << VecMed[posicao].QuantidadeDisponivel << endl;
    cout << "Preço unitário:"
         << " " << VecMed[posicao].PrecoUnitario << endl;

    if (VecMed[posicao].SituacaoProduto == true) {
      cout << "Situação:"
           << " "
           << "Ativo" << endl;
    }

    else {
      cout << "Situação:"
           << " "
           << "Inativo" << endl
           << endl;
    }
  }
}

// função para excluir medicamento
void excluir(Medicamentos *VecMed, int tam) {

  string codigoBusca;
  int confirmacao;
  cout << "Digite o código do produto que deseja exluir: ";
  cin >> codigoBusca;

  int posicao = BuscaBinaria(VecMed, 0, tam - 1, codigoBusca);

  if (posicao == -1) {

    cout << "Produto não encontrado." << endl;
  }

  else if (VecMed[posicao].SituacaoProduto == true) {
    cout << "Confirma exclusão? 1-sim 2-não" << endl;
    cin >> confirmacao;
    if (confirmacao == 1) {
      cout << "Produto exluído com sucesso" << endl;
      VecMed[posicao].SituacaoProduto = false;
    } else {
      cout << "Exclusão cancelada";
    }
  }

  else {

    cout << "Produto já exluído" << endl;
  }
}

// função para vender medicamento
void efetuarVenda(Medicamentos *VecMed, int tam) {

  int vender = 0;

  string codigoBusca;
  cout << "Digite o código do produto que deseja vender: ";
  cin >> codigoBusca;

  int posicao = BuscaBinaria(VecMed, 0, tam - 1, codigoBusca);

  if (posicao == -1) {

    cout << "Produto não encontrado." << endl;
  }

  else if (VecMed[posicao].SituacaoProduto == true) {
    cout << "Código do medicamento:"
         << " " << VecMed[posicao].CodigoIndentificacao << endl;
    cout << "Descrição:"
         << " " << VecMed[posicao].Descricao << endl;
    cout << "Quantidade em estoque:"
         << " " << VecMed[posicao].QuantidadeDisponivel << endl;
    cout << "Quantos medicamentos serão vendidos?:";
    cin >> vender;
    if (vender <= VecMed[posicao].QuantidadeDisponivel) {
      VecMed[posicao].QuantidadeDisponivel -= vender;
      // após realizar as vendas, caso o estoque chegue a 0 o produto é
      // automaticamente desativado
      cout << "Quantidade em estoque:"
           << " " << VecMed[posicao].QuantidadeDisponivel << endl;
      if (VecMed[posicao].QuantidadeDisponivel == 0) {
        VecMed[posicao].SituacaoProduto = false;
      }
    } else {
      cout << "Operação inválida, sem medicamentos suficientes para concluir a "
              "venda"
           << endl;
    }
  }
}

//faz a realocação do vetor quando o limite é atingido
Medicamentos *realocar(int &TamVetor, Medicamentos *VecMed,
                       int itensCadastrados) {
  Medicamentos *aux = new Medicamentos[TamVetor + 3];

  memcpy(aux, VecMed, sizeof(Medicamentos) * TamVetor);

  delete[] VecMed;
  VecMed = aux;
  aux = nullptr;

  TamVetor += 3;

  return VecMed;
}

//o magnum opus, a parte principal que realiza o cadastro de cada medicamento
Medicamentos *Cadastro(int &TamVetor, Medicamentos *VecMed,
                       int &itensCadastrados) {
  // ler direto no vetor de char
  int i = itensCadastrados;
  cout << "------------------------------------------------" << endl;
  //é preciso apertar enter duas vezes
  //para que seja cadastrado corretamente o nome.
  cout << "Digite o nome do Produto: ";
  string NomeProd;
  getline(cin >> ws, NomeProd);
  cout<< "Pressione Enter mais uma vez!" <<endl;
  cin.ignore(' ', '\n');

  cout << "Digite uma descrição do Produto: ";
  string DescricaoProd;
  getline(cin, DescricaoProd);

  cout << "Digite o Laborátorio que criou o produto: ";
  string LaboratorioProd;
  getline(cin, LaboratorioProd);

  cout << "Digite o código de identificação do produto: ";
  string CodigoID;
  cin >> CodigoID;

  cout << "Digite o tamanho do estoque deste produto: ";
  cin >> VecMed[i].QuantidadeDisponivel;
  cin.ignore(' ', '\n');

  cout << "Digite o preço Unitário do produto: ";
  cin >> VecMed[i].PrecoUnitario;

  cout << "Digite o status do produto: ";
  string StatusProduto;
  cin >> StatusProduto;
  if (StatusProduto == "Ativo") {
    VecMed[i].SituacaoProduto = true;
  } else if (StatusProduto == "Inativo") {
    VecMed[i].SituacaoProduto = false;
  }
  //faz a trasferencia de string para char, assim permitindo a exportação
  //também realiza a função de verificar se o produto já foi cadastrado
  //por meio do Código do Medicamento
  int existe = BuscaBinaria(VecMed, 0, itensCadastrados - 1, CodigoID);
  if (existe == -1) {
    strcpy(VecMed[i].NomeMedicamento, NomeProd.c_str());
    strcpy(VecMed[i].Descricao, DescricaoProd.c_str());
    strcpy(VecMed[i].Laboratorio, LaboratorioProd.c_str());
    strcpy(VecMed[i].CodigoIndentificacao, CodigoID.c_str());
    itensCadastrados++;
    cout << "Cadastro Efetuado com Sucesso!\n";
    quicksort(VecMed, 0, itensCadastrados - 1);
    if (itensCadastrados == TamVetor) {
      VecMed = realocar(TamVetor, VecMed, itensCadastrados);
    }
  } else {
    cout << "ERRO: Produto já foi cadastrado!" << endl;
  }
  return VecMed;
}

// função pra listar medicamentos em ordem alfabética pelos códigos
void Listar(int &TamVetor, Medicamentos *VecMed, int &itensCadastrados) {
  cout << "------------------------------------------------" << endl;
  for (int i = 0; i < itensCadastrados; i++) {
    cout << "Produto Numero:"
         << " " << i << endl;
    cout << "Nome do Medicamento:"
         << " " << VecMed[i].NomeMedicamento << endl
         << "Descrição do Medicamento:"
         << " " << VecMed[i].Descricao << endl;
    cout << "Nome do Laboratório:"
         << " " << VecMed[i].Laboratorio << endl
         << "Código do Medicamento:"
         << " " << VecMed[i].CodigoIndentificacao << endl;
    cout << "Quantidade Restante:"
         << " " << VecMed[i].QuantidadeDisponivel << endl;
    cout << "Preço unitário:"
         << " " << VecMed[i].PrecoUnitario << endl;

    if (VecMed[i].SituacaoProduto == true) {
      cout << "Situação do Medicamento:"
           << " "
           << "Ativo" << endl;
    } else {
      cout << "Situação do Medicamento:"
           << " "
           << "Inativo" << endl
           << endl;
    }
    cout << "------------------------------------------------" << endl;
  }
}
// função para listar medicamentos em estoque, quase o mesmo conceito
//do listar padrão, apenas mostrando os produtos ativados
void listarDadosdoEstoque(int &TamVetor, Medicamentos *VecMed,
                          int &itensCadastrados) {
  cout << "------------------------------------------------" << endl;
  for (int i = 0; i < itensCadastrados; i++) {
    if (VecMed[i].SituacaoProduto == true) {
      cout << "Produto Numero:"
           << " " << i << endl;
      cout << "Nome do Medicamento:"
           << " " << VecMed[i].NomeMedicamento << endl
           << "Descrição do Medicamento:"
           << " " << VecMed[i].Descricao << endl;
      cout << "Nome do Laboratório:"
           << " " << VecMed[i].Laboratorio << endl
           << "Código do Medicamento:"
           << " " << VecMed[i].CodigoIndentificacao << endl;
      cout << "Quantidade Restante:"
           << " " << VecMed[i].QuantidadeDisponivel << endl;
      cout << "Preço unitário:"
           << " " << VecMed[i].PrecoUnitario << endl;
      cout << "Situação do Medicamento:"
           << " "
           << "Ativo" << endl;
    }
    cout << "------------------------------------------------" << endl;
  }
}

// função do menu principal
void Menu(int &TamVetor, Medicamentos *VecMed, int &itensCadastrados) {
  quicksort(VecMed, 0, itensCadastrados);
  int Option = 0;
  while (Option != 8) {
    cout << "------------------------------------------------" << endl;
    cout << "DIGITE UM NÚMERO DE 1 A 8!\n";
    cout << "Lista de Opções:\n\t1 - Cadastrar Produto\n\t2 - Consultar "
            "Medicamento\n\t3 - Listar Medicamento\n";
    cout << "\t4 - Excluir Medicamento\n\t5 - Efetuar uma Venda\n\t6 - Listar "
            "dados de medicamentos em estoque\n\t";
    cout << "7 - Exportar Dados para arquivos\n\t8 - Sair\n";
    cout << "Digite a opção que você deseja realizar: ";
    cin >> Option;
    switch (Option) {
    case 1:
      VecMed = Cadastro(TamVetor, VecMed, itensCadastrados);
      break;
    case 2:
      Consultar(VecMed, itensCadastrados);
      break;
    case 3:
      Listar(TamVetor, VecMed, itensCadastrados);
      break;
    case 4:
      excluir(VecMed, itensCadastrados);
      break;
    case 5:
      efetuarVenda(VecMed, itensCadastrados);
      break;
    case 6:
      listarDadosdoEstoque(TamVetor, VecMed, itensCadastrados);
      break;
    case 7:
      exportar(VecMed, TamVetor, itensCadastrados);
      break;
    }
  }
}

int main() {

  // Gerando um ponteiro cujo tamanho inicial comece com 3 para criar o vetor de
  // registro
  int TamVetor = 3;
  int itensCadastrados = 0;

  // Gerando um registro do tipo Medicamentos para o vetor
  Medicamentos *VecMed = new Medicamentos[TamVetor];

  Menu(TamVetor, VecMed, itensCadastrados);
  return 0;
}
