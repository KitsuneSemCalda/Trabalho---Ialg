#include <iostream>
#include <string>

using namespace std;

struct Medicamentos {
  string NomeMedicamento;
  string Descricao;
  string Laboratorio;
  string CodigoIndentificacao;
  int QuantidadeDisponivel;
  float PrecoUnitario;
  bool SituacaoProduto;
};

/*
Funcao nula Cadastro que gera os valores para serem cadastrados no registro
medicamentos
*/
int particiona(Medicamentos *v, int c, int f) { // c = começo, f = fim
  string pivo = v[c].CodigoIndentificacao;
  Medicamentos aux = v[c];
  int i = c + 1, j = f;
  while (i <= j) {
    if (v[i].CodigoIndentificacao <= pivo)
      i++;
    else if (pivo <= v[j].CodigoIndentificacao)
      j--;
    else { // (v[i] > pivo) e (v[j] < pivo)
      swap(v[i], v[j]);
      i++;
      j--;
    }
  } // agora i == j+1
  v[c] = v[j];
  v[j] = aux;
  return j; // retorna posição do pivô
}

void quicksort(Medicamentos *a, int pos_pivo, int fim) {
  int pos_novo_pivo;
  if (pos_pivo < fim) {
    pos_novo_pivo = particiona(a, pos_pivo, fim);
    quicksort(a, pos_pivo, pos_novo_pivo - 1);
    quicksort(a, pos_novo_pivo + 1, fim);
  }
}

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

//função para excluir medicamento
void excluir(Medicamentos *VecMed, int tam) {

  string codigoBusca;
  cout << "Digite o código do produto que deseja exluir: ";
  cin >> codigoBusca;

  int posicao = BuscaBinaria(VecMed, 0, tam - 1, codigoBusca);

  if (posicao == -1) {

    cout << "Produto não encontrado." << endl;
  }
  
  else if (VecMed[posicao].SituacaoProduto == true) {
     
      cout << "Produto exluído com sucesso"<<endl;
      VecMed[posicao].SituacaoProduto = false;

  }

  else {
     
      cout << "Produto já exluído"<<endl;
  }
}


Medicamentos *realocar(int &TamVetor, Medicamentos *VecMed,
                       int itensCadastrados) {
  Medicamentos *aux = new Medicamentos[TamVetor + 3];

  // memcpy(aux, VecMed, sizeof(Medicamentos)*TamVetor);

  for (int i = 0; i < itensCadastrados; i++) {
    aux[i].NomeMedicamento = VecMed[i].NomeMedicamento;
    aux[i].Descricao = VecMed[i].Descricao;
    aux[i].Laboratorio = VecMed[i].Laboratorio;
    aux[i].CodigoIndentificacao = VecMed[i].CodigoIndentificacao;
    aux[i].QuantidadeDisponivel = VecMed[i].QuantidadeDisponivel;
    aux[i].PrecoUnitario = VecMed[i].PrecoUnitario;
    aux[i].SituacaoProduto = VecMed[i].SituacaoProduto;
  }

  delete[] VecMed;
  VecMed = aux;
  aux = nullptr;

  TamVetor += 3;

  return VecMed;
}

Medicamentos *Cadastro(int &TamVetor, Medicamentos *VecMed,
                       int &itensCadastrados) {
  int i = itensCadastrados;
  cout << "------------------------------------------------" << endl;
  cout << "Digite o nome do Produto: ";

  string NomeMed;
  cin.ignore();
  getline(cin, NomeMed);
  VecMed[i].NomeMedicamento = NomeMed;

  cout << "Digite uma descrição do Produto: ";
  string Description;
  getline(cin, Description);
  VecMed[i].Descricao = Description;

  cout << "Digite o Laborátorio que criou o produto: ";
  string Labor;
  getline(cin, Labor);
  VecMed[i].Laboratorio = Labor;

  cout << "Digite o código de identificação do produto: ";
  string CodInd;
  getline(cin, CodInd);
  VecMed[i].CodigoIndentificacao = CodInd;

  cout << "Digite o tamanho do estoque deste produto: ";
  int EstoqueDisponivel;
  cin >> EstoqueDisponivel;
  VecMed[i].QuantidadeDisponivel = EstoqueDisponivel;

  cout << "Digite o preço Unitário do produto: ";
  float PrecoUnitario;
  cin >> PrecoUnitario;
  VecMed[i].PrecoUnitario = PrecoUnitario;

  cout << "Digite o status do produto: ";
  string StatusProduto;
  cin >> StatusProduto;
  if (StatusProduto == "Ativo") {
    VecMed[i].SituacaoProduto = true;
  } else if (StatusProduto == "Inativo") {
    VecMed[i].SituacaoProduto = false;
  }
  itensCadastrados++;
  cout << "Cadastro Efetuado com Sucesso!\n";

  // ordenar(tamVetor, VecMed); IMPLEMENTAR FUNÇÃO
  quicksort(VecMed, 0, itensCadastrados - 1);

  if (itensCadastrados == TamVetor) {
    cout << "entrou";
    VecMed = realocar(TamVetor, VecMed, itensCadastrados);
  }
  return VecMed;
}

// função pra listar medicamentos
void Listar(int &TamVetor, Medicamentos *VecMed, int &itensCadastrados) {
  // mostra uma lista meio porca mas ta bao, dps melhoramos
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

//função do menu principal
void Menu(int &TamVetor, Medicamentos *VecMed, int &itensCadastrados) {
  int Option = 0;
  while (Option != 8) {
    cout << "------------------------------------------------" << endl;
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
