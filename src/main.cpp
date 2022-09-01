#include <iostream>
#include <string>

using namespace std;
struct Medicamentos{
    string NomeMedicamento;
    string Descricao;
    string Laboratorio;
    string CodigoIndentificacao;
    int QuantidadeDisponivel;
    float PrecoUnitario;
    bool SituacaoProduto;
};
/*
Funcao Vazia Cadastro que gera os valores para serem cadastrados no registro Medicamentos 
*/
void Cadastro(int TamVetor, Medicamentos VecMed[]){
    for (int i = 0; i != TamVetor; i++){
        cout << "------------------------------------------------" << endl;
        cout << "Digite o nome do Produto: ";
        
        string NomeMed;
        getline(cin >> ws,NomeMed);
        VecMed[i].NomeMedicamento = NomeMed;

        cout << "Digite uma descrição do Produto: ";
        string Description;
        getline(cin >> ws,Description);
        VecMed[i].Descricao = Description;
        
        cout << "Digite o Laborátorio que criou o produto: ";
        string Labor;
        getline(cin >> ws,Labor);
        VecMed[i].Laboratorio = Labor;
        
        cout << "Digite o código de identificação do produto: ";
        string CodInd;
        getline(cin >> ws, CodInd);
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
        if (StatusProduto == "Ativo"){
            VecMed[i].SituacaoProduto = true;
        }else if (StatusProduto == "Inativo"){
            VecMed[i].SituacaoProduto = false;
        }
        cout << "Cadastro Efetuado com Sucesso!\n";
    }
    /*
    for (int i = 0; i != *TamVetor; i++){
        cout << VecMed[i].NomeMedicamento << endl << VecMed[i].Descricao << endl;
        cout << VecMed[i].Laboratorio << endl << VecMed[i].CodigoIndentificacao << endl;
        cout << VecMed[i].QuantidadeDisponivel << endl << VecMed[i].SituacaoProduto << endl;
    }
    */
}
/*
    Adicionando uma função simples de menu
*/
void consultar(){
	
}
/*
função pra listar medicamentos
*/ 
void listar(int TamVetor, Medicamentos VecMed[]){
	//mostra uma lista meio porca mas ta bao, dps melhoramos
	for (int i = 0; i != TamVetor; i++){
		cout<<"Produto Numero:"<<" "<<i<<endl;
        cout <<"Nome do Medicamento:"<<" "<<VecMed[i].NomeMedicamento << endl <<"Descrição do Medicamento:"<<" "<<VecMed[i].Descricao << endl;
        cout <<"Nome do Laboratório:"<<" "<<VecMed[i].Laboratorio << endl <<"Código do Medicamento:"<<" "<<VecMed[i].CodigoIndentificacao << endl;
        cout<<"Quantidade Restante:"<<" "<< VecMed[i].QuantidadeDisponivel << endl;
        if(VecMed[i].SituacaoProduto==true)
        cout<<"Situação do Medicamento:"<<" "<<"Ativo"<<endl;
        else{
		cout<<"Situação do Medicamento:"<<" "<<"Inativo"<<endl<<endl;
		}
    }
	
}
void menu(int TamVetor, Medicamentos VecMed[]){
    int Option = 0;
        while (Option != 8){
        cout << "------------------------------------------------" << endl;
        cout << "Lista de Opções:\n\t1 - Cadastrar Produto\n\t2 - Consultar Medicamento\n\t3 - Listar Medicamento\n";
        cout << "\t4 - Excluir Medicamento\n\t5 - Efetuar uma Venda\n\t6 - Listar dados de medicamentos em estoque\n\t";
        cout << "7 - Exportar Dados para arquivos\n\t8 - Sair\n";
        cout << "Digite a opção que você deseja realizar: ";
        cin >> Option;
        switch (Option){
            case 1:
                Cadastro(TamVetor, VecMed);
                break;
             case 3:
                listar(TamVetor, VecMed);
                break;
       
        }
    }
}

int main(){
	
 // Gerando um ponteiro cujo tamanho inicial comece com 3 para criar o vetor de registro
    int *TamVetor;
    TamVetor = new int;
    *TamVetor = 3;

    //Gerando um registro do tipo Medicamentos para o vetor
    Medicamentos VecMed[*TamVetor];


    menu(*TamVetor, VecMed);
    return 0;
}
