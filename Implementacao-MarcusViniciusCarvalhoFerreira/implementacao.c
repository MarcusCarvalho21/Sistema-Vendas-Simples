#include <stdio.h>
#include <locale.h>

typedef int boolean;
#define true 1
#define false 0

//Fun��o para exibir o menu de produtos
void menuProdutos(){

	printf("\n10 - Refrigerante - R$2,5\n" );
	printf("15 - Casquinha Simples - R$1,5\n");
	printf("20 - Casquinha Dupla - R$2,5\n\n");

}

//Fun��o para armazenar informa��es das vendas
void armazenar_informacoes(int vendas[2][1000], int codigo, int quantidade, int numeroPedido){
	
	vendas[0][numeroPedido] = codigo;
	vendas[1][numeroPedido] = quantidade;
		
}

//Fun��o para emitir o relatorio final do dia
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
	
	//La�o para verificar a quantidade vendida de cada produto
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
	printf("\nM�dia de valor pago por pedido: R$%.2f", valorMedioPedido);
}

//Fun��o principal
int main(){
	
	//Localizando para o portugu�s
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
	
	//Pedindo para informar a opera��o a ser realizada
	printf("Qual opera��o realizar? \n[1] - Efetuar uma nova venda. \n[2] - Encerrar o movimento do dia\n");
	scanf(" %d", &operacao);

	//La�o para verificar se o usuario deseja finalizar o programa
	while(finaliza == false){

		//La�o para verificar se a opera��o informada pelo usuario � valida
		while((operacao != 1) && (operacao != 2)){
			printf("\nOpera��o invalida!\n\n");
			printf("Qual opera��o realizar? \n[1] - Efetuar uma nova venda. \n[2] - Encerrar o movimento do dia\n");
			scanf(" %d", &operacao);
		}
		if(operacao == 1){
			
			menuProdutos();
		
			//Pedindo para informar o codigo do produto
			printf("Informe o c�digo do produto:\n");
			scanf(" %d", &codigo);
			
			//Verificando se o codigo informado pelo usuario � valido	
			while((codigo != 10) && (codigo != 15) && (codigo != 20)){
				printf("\nCodigo invalido!\n\n");
				printf("Informe o c�digo do produto:\n");
				scanf(" %d", &codigo);
			}
			
			//Pedindo para informar a quantidade do produto vendida
			printf("Informe a quantida da venda:\n");
			scanf(" %d", &quantidade);
			
			//Verificando se existe estoque desse produto informado. 
			//Se sim, conclui a venda e registra na fun��o armazena_informacoes()
			//Se n�o, Informa ao usuario que n�o � possivel realizar a opera��o
			if((codigo == 10)){
				if((estoqueRefrigerante - quantidade) >= 0){
					armazenar_informacoes(vendas, codigo, quantidade, numeroPedido);
					estoqueRefrigerante = estoqueRefrigerante - quantidade;
					numeroPedido++;	
				}
				else{
					printf("\nImpossivel realizar a opera��o. Estoque insuficiente!\n");
				}	
			}
			else if(codigo == 15){
				if((estoqueCasquinha - quantidade) >= 0){
					armazenar_informacoes(vendas, codigo, quantidade, numeroPedido);
					estoqueCasquinha = (estoqueCasquinha - quantidade);
					numeroPedido++;	
				}
				else{
					printf("\nImpossivel realizar a opera��o. Estoque insuficiente!\n");
				}			
			}
			else if(codigo == 20){
				if((estoqueCasquinha - (quantidade * 2)) >= 0){
					armazenar_informacoes(vendas, codigo, quantidade, numeroPedido);
					estoqueCasquinha = estoqueCasquinha - (quantidade * 2);
					numeroPedido++;	
				}
				else{
					printf("\nImpossivel realizar a opera��o. Estoque insuficiente!\n");
				}
			}
			printf("\nQual opera��o realizar? \n[1] - Efetuar uma nova venda. \n[2] - Encerrar o movimento do dia\n");
			scanf(" %d", &operacao);		
		}
		else if(operacao == 2){
			//Emitindo o relatorio final
			emitir_relatorio(vendas, numeroPedido);
			//Informando ao la�o de repeti��o que o usuario deseja fechar o servi�o do dia
			finaliza = true;
		}
	}

	return 0;
}

