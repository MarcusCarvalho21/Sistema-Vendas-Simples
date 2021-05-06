#include <stdio.h>
#include <locale.h>

typedef int boolean;
#define true 1
#define false 0

//Função para exibir o menu de produtos
void menuProdutos(){

	printf("\n10 - Refrigerante - R$2,5\n" );
	printf("15 - Casquinha Simples - R$1,5\n");
	printf("20 - Casquinha Dupla - R$2,5\n\n");

}

//Função para armazenar informações das vendas
void armazenar_informacoes(int vendas[2][1000], int codigo, int quantidade, int numeroPedido){
	
	vendas[0][numeroPedido] = codigo;
	vendas[1][numeroPedido] = quantidade;
		
}

//Função para emitir o relatorio final do dia
void emitir_relatorio(int vendas[2][1000], int numeroPedido){
	
	//Declarando variaveis
	int j = 0;
	int qtdRefrigerante = 0;
	int qtdCasquinhaSimples = 0;
	int qtdCasquinhaDupla = 0;
	float valorTotal_Refrigerante = 0;
	float valorTotal_CasquinhaSimples = 0;
	float valorTotal_CasquinhaDupla = 0;
	float totalArrecadado = 0;
	int qtdTotal = 0;
	float valorMedioPedido = 0;
	
	//Laço para verificar a quantidade vendida de cada produto
	for(j = 0; j < numeroPedido; j++){
		if(vendas[0][j] == 10){
			qtdRefrigerante += vendas[1][j];		
		}
		else if(vendas[0][j] == 15){
			qtdCasquinhaSimples += vendas[1][j];
		}
		else if(vendas[0][j] == 20){
			qtdCasquinhaDupla += vendas[1][j];
		}
	}
	
	//Informando as quantidades para o usuario 
	printf("\nHoje foram vendidos:\n");
	printf("%d Refrigerantes vendidos\n", qtdRefrigerante);
	printf("%d Casquinhas Simples vendidos\n", qtdCasquinhaSimples);
	printf("%d Casquinhas Duplas vendidos\n", qtdCasquinhaDupla);

	//Calculando o valor arrecadado por produto
	valorTotal_Refrigerante = (qtdRefrigerante * 2.5);
	valorTotal_CasquinhaSimples = (qtdCasquinhaSimples * 1.5);
	valorTotal_CasquinhaDupla = (qtdCasquinhaDupla * 2.5);
	printf("\nValor faturado:\n");
	printf("R$%.2f Refrigerantes\n", valorTotal_Refrigerante);
	printf("R$%.2f Casquinha Simples\n", valorTotal_CasquinhaSimples);
	printf("R$%.2f Casquinha Dupla\n", valorTotal_CasquinhaDupla);	
	
	//Calculando o total arrecadado no dia
	totalArrecadado = (valorTotal_Refrigerante + valorTotal_CasquinhaSimples + valorTotal_CasquinhaDupla);
	printf("\nValor total arrecadado: R$%.2f\n", totalArrecadado);
	
	//Calculando a media arrecadado por pedido
	if(numeroPedido != 0){
		valorMedioPedido = (totalArrecadado / numeroPedido);
	}
	else{
		valorMedioPedido = 0;
	}
	printf("\nMédia de valor pago por pedido: R$%.2f", valorMedioPedido);
}

//Função principal
int main(){
	
	//Localizando para o português
	setlocale(LC_ALL, "Portuguese");

	//Declarando variaveis
	int operacao = 0;
	boolean finaliza = false;
	int codigo = 0;
	int quantidade = 0;
	int estoqueRefrigerante = 300;
	int estoqueCasquinha = 700;
	int numeroPedido = 0;
	int vendas[2][1000];
	
	//Pedindo para informar a operação a ser realizada
	printf("Qual operação realizar? \n[1] - Efetuar uma nova venda. \n[2] - Encerrar o movimento do dia\n");
	scanf(" %d", &operacao);

	//Laço para verificar se o usuario deseja finalizar o programa
	while(finaliza == false){

		//Laço para verificar se a operação informada pelo usuario é valida
		while((operacao != 1) && (operacao != 2)){
			printf("\nOperação invalida!\n\n");
			printf("Qual operação realizar? \n[1] - Efetuar uma nova venda. \n[2] - Encerrar o movimento do dia\n");
			scanf(" %d", &operacao);
		}
		if(operacao == 1){
			
			menuProdutos();
		
			//Pedindo para informar o codigo do produto
			printf("Informe o código do produto:\n");
			scanf(" %d", &codigo);
			
			//Verificando se o codigo informado pelo usuario é valido	
			while((codigo != 10) && (codigo != 15) && (codigo != 20)){
				printf("\nCodigo invalido!\n\n");
				printf("Informe o código do produto:\n");
				scanf(" %d", &codigo);
			}
			
			//Pedindo para informar a quantidade do produto vendida
			printf("Informe a quantida da venda:\n");
			scanf(" %d", &quantidade);
			
			//Verificando se existe estoque desse produto informado. 
			//Se sim, conclui a venda e registra na função armazena_informacoes()
			//Se não, Informa ao usuario que não é possivel realizar a operação
			if((codigo == 10)){
				if((estoqueRefrigerante - quantidade) >= 0){
					armazenar_informacoes(vendas, codigo, quantidade, numeroPedido);
					estoqueRefrigerante = estoqueRefrigerante - quantidade;
					numeroPedido++;	
				}
				else{
					printf("\nImpossivel realizar a operação. Estoque insuficiente!\n");
				}	
			}
			else if(codigo == 15){
				if((estoqueCasquinha - quantidade) >= 0){
					armazenar_informacoes(vendas, codigo, quantidade, numeroPedido);
					estoqueCasquinha = (estoqueCasquinha - quantidade);
					numeroPedido++;	
				}
				else{
					printf("\nImpossivel realizar a operação. Estoque insuficiente!\n");
				}			
			}
			else if(codigo == 20){
				if((estoqueCasquinha - (quantidade * 2)) >= 0){
					armazenar_informacoes(vendas, codigo, quantidade, numeroPedido);
					estoqueCasquinha = estoqueCasquinha - (quantidade * 2);
					numeroPedido++;	
				}
				else{
					printf("\nImpossivel realizar a operação. Estoque insuficiente!\n");
				}
			}
			printf("\nQual operação realizar? \n[1] - Efetuar uma nova venda. \n[2] - Encerrar o movimento do dia\n");
			scanf(" %d", &operacao);		
		}
		else if(operacao == 2){
			//Emitindo o relatorio final
			emitir_relatorio(vendas, numeroPedido);
			//Informando ao laço de repetição que o usuario deseja fechar o serviço do dia
			finaliza = true;
		}
	}

	return 0;
}

