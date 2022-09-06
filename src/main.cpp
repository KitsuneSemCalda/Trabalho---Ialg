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

Medicamentos* realocar(int &TamVetor, Medicamentos* VecMed, int itensCadastrados) {
	Medicamentos* aux = new Medicamentos[TamVetor + 3];
	
	//memcpy(aux, VecMed, sizeof(Medicamentos)*TamVetor);
	
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

Medicamentos* Cadastro(int &TamVetor, Medicamentos* VecMed, int &itensCadastrados) {
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
	
	//ordenar(tamVetor, VecMed); IMPLEMENTAR FUNÇÃO
	
	if (itensCadastrados == TamVetor) {
		cout << "entrou";
		VecMed = realocar(TamVetor, VecMed, itensCadastrados);
	}
	return VecMed;
}
/*
    Adicionando uma função simples de menu
*/
void Consultar(int &TamVetor, Medicamentos* VecMed, int &itensCadastrados) {
	string codigoproduto;
	cout<<"Insira o nome do produto desejado:"<<" "<<endl;
	cin>>codigoproduto;
	for (int i = 0; i < itensCadastrados; i++) {
		if(codigoproduto==VecMed[i].NomeMedicamento){
			cout<<"Código do produto:"<<" "<<VecMed[i].NomeMedicamento<<endl;
			cout<<"Quantidade em estoque:"<<" "<<VecMed[i].QuantidadeDisponivel<<endl;
			cout<<"Preço unitário:"<<" "<<VecMed[i].PrecoUnitario<<endl;
			if (VecMed[i].SituacaoProduto == true){
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
}
/*
função pra listar medicamentos
*/
void Listar(int &TamVetor, Medicamentos* VecMed, int &itensCadastrados) {
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
    }
    else {
      cout << "Situação do Medicamento:"
           << " "
           << "Inativo" << endl
           << endl;
    }
    cout << "------------------------------------------------" << endl;
  }
}
void Menu(int &TamVetor, Medicamentos* VecMed, int &itensCadastrados) {
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
      Consultar(TamVetor, VecMed, itensCadastrados);
      break;
    case 3:
      Listar(TamVetor, VecMed, itensCadastrados);
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
  Medicamentos* VecMed = new Medicamentos[TamVetor];

  Menu(TamVetor, VecMed, itensCadastrados);
  return 0;
}
