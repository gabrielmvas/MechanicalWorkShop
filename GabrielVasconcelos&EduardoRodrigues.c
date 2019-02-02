// Aluno : Gabriel de Medeiros Vasconcelos e Eduardo Rodrigues de Morais
// Matrícula: UC16100459 / UC15000222


#include <stdio.h>
#include <conio.c>
#include <time.h>
#include <string.h>
//DEFINES
#define TAM_NOME 101
#define TAM_TELEFONE 12
#define TAM_CHASSI 18
#define TAM_CPF 12
#define TAM_PLACA 8
#define TAM_MODELO 31
#define TAM_FABRICANTE 101
#define TAM_DESCRICAO 501
#define TAM_DESCRICAO_ENDERECO 30
#define TAM_CIDADE 20
#define TAM_ESTADO 3
#define TAM_NOME_OFICINA 50
//
#define MAX_PROP 200
#define MAX_VEICULOS 500
#define MAX_VENDAS 200
//
#define ARQ_PROPRIETARIOS "proprietarios.txt"
#define ARQ_VEICULOS "veiculos.txt"
#define ARQ_MANUTENCOES "manutencoes.txt"
#define ARQ_OFICINA "oficina.txt"
//
#define BRANCO 15
#define PRETO 0
#define VERDE 2
#define CINZA_CLARO 7
#define VERDE_CLARO 10

//STRUCTS
typedef struct {
	char descricao[TAM_DESCRICAO_ENDERECO], cidade[TAM_CIDADE], estado[TAM_ESTADO];
} Endereco;

typedef struct {
	char nome[TAM_NOME];
	Endereco endereco;
} Oficina;

typedef struct {
	int dia, mes, ano;
} Data;

typedef struct {
	Endereco endereco;
	char nome[TAM_NOME];
	char cpf[TAM_CPF];//chave 
	char telefone[TAM_TELEFONE];
} Proprietario;

typedef struct {
	Data data;
	char descricaoServico[TAM_DESCRICAO];
	float valorPecas, valorMaoDeObra;
	char cpfCliente[TAM_CPF], placa[TAM_PLACA];
} Manutencao;

typedef struct {
	//placa chave primaria
	char chassi[TAM_CHASSI], placa[TAM_PLACA], fabricante[TAM_FABRICANTE], modelo[TAM_MODELO];
	Data anoFabricacao;
} Veiculo;

//PROTOTIPOS

void apresentaTodosProp();
void apresentaManuTempo();
void apresentaTodosVeic();			
void apresentaNomeOficina(int , int ,char );	
void apresentaTodasManu();
void apresentaDadosPropNom();
void excluiManutencao();
int recuperaDadosManutencao(int , Manutencao *);
int apresentaManutencoes();
int menuSimNao(char *);
int verificaExisteManutencaoCarro(char *);
void excluiVeiculo() ;
void gravaDadosVeiculo(Veiculo *, int );
void apresentaVeiculo(Veiculo );
int recuperaDadosVeiculo(int , Veiculo *) ;
void alteraVeiculo();
void desenhaMoldura(int , int , int , int , int , int );
int menuVertical(int ,char *imenu[],int ,int ,int ,int ,int , int ,int , int );
void retornaCor(int ,int );
void limpaJanela(int ,int ,int , int ,int );
void menuProprietarios();
void menuVeiculos();
void menuManutencao();
Oficina criaArquivoOficina();
void pesquisasConsultas();
void pause(int , int );
void cadastroProprietario();
void tiraTerminador(char *);
void leValidaTexto(char *, char *, char *, int , int , int );
void criaArquivoNaoExistente(char *);
void fechaArquivo(FILE *);
void apresentaDados();
FILE * abreArquivo(char *, char *);
int verificaExistenciaArquivo( char *);
char *validaTelefone(char *, int *);
int validaCPFrepetido(char *);
char *formataCPF(char *);
char *formataTelefone(char *);
char *formataPlaca(char *);
void pesquisaPeloRegistro();
int validaPlaca(char *);
int validaChassiRepetido(char *);
void cadastraVeiculo();
int validaData(int , int , int );
char *obtemEstado(int , char *);
void leValidaInt(char *, char *, int , int , int *, int , int );
void leInt(char *, int *, int , int );
void leFloat(char *, float *, int , int );
void leValidaFloat(char *, char *, int , int , float *, int , int );
void cadastroManutencoes();
int validaPlacaRepetida(char *);
void obtemDataAtual(int *, int *, int *);
void apresentaMsg(char *);
void *obtemDadosArquivo(char *, int , int *);
int apresentaProprietarios();
void alteraProprietario();
void apresentaProprietario(Proprietario );
int recuperaDadosProprietario(int , Proprietario *);
void leValidaOpcao(char *, char *, char *, char *, int , int );
void gravaDadosProprietario(Proprietario *, int );
void excluiProprietario();
int verificaExisteManutencao(char *);
void pulaLinhas(char *, int *, int *);
void apresentaVeiculosManutencao();
void consultaDadosVeiculo();
int comparaNome(const void *, const void *);


int main(void) {
// Declaracoes
	int resp;
		char opcao;
	    char *menu[] = {"Proprietarios", "Veiculo", "Manutencao", "Apresentar/Pesquisar dados", "Encerrar programa"};
	
	// Instrucoes

	criaArquivoNaoExistente(ARQ_PROPRIETARIOS);
	criaArquivoNaoExistente(ARQ_VEICULOS);
	criaArquivoNaoExistente(ARQ_MANUTENCOES);

	do {	
		apresentaNomeOficina(40,7,'S');
		opcao = menuVertical(5, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
		switch(opcao) {
			case 1:
				menuProprietarios();
				break;
			case 2:
				menuVeiculos();
				break;
			case 3:
				menuManutencao();
				break;
			case 4:
				pesquisasConsultas();
				break;
			case 5:
				system("cls");
				apresentaMsg("Programa ecerrado.");	
		}
	} while(opcao != 5);
	
  getch();
  return 0;
}
//Objetivo: Apresentar o nome, e o endereço da oficina
//Parâmetro: Linha e coluna de onde vai apresentar os dados e S/N para apresenda o endereço
//Retorno: nenhum
void apresentaNomeOficina(int coluna, int linha,char resp){
	Oficina oficina;
	int cont;

	
	oficina = criaArquivoOficina();
	for(cont=0;cont<strlen(oficina.nome);cont++){
		oficina.nome[cont]=toupper(oficina.nome[cont]);
	}
	system("cls");
	gotoxy(coluna,linha);
	printf("Oficina = %s", oficina.nome);
	if(resp=='S'){	
		gotoxy(coluna,linha+1);	
		printf("Endereco= %s, %s, %s", oficina.endereco.descricao, oficina.endereco.cidade, oficina.endereco.estado);
	}
}
//Objetivo: ler uma resposta de sim e nao
//Parametro: nada
//Retorno: 1 pra sim, 0 pra nao
int menuSimNao(char *msg){
	int colunaInicial;

	char opcao,*menu[] = {"Sim", "Nao"};
	int resp=0;
	
	do{
	   gotoxy(11, 13);
	   fprintf(stdout, "%s", msg);
		opcao = menuVertical(2, menu, BRANCO, VERDE, 13, 41, 1, 0, PRETO, BRANCO);
		switch(opcao){
			case 1:
				return resp=1;
				break;
			case 2:
				return resp=0;
		}
		
	}while(opcao!=2);

}
//Objetivo: excluir veiculo
//Parâmetros: nenhum
//Retorno: nenhuhm
void excluiVeiculo() {
	Veiculo veiculo;
	FILE *arq, *arqTemp;
	int posicao, cont = 0, flag = 1,resp;
	char opcao;
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM VEICULO");
	posicao = apresentaVeiculos();
	if(posicao != 0) {
		if(recuperaDadosVeiculo(posicao,&veiculo) == 1) {
			if(verificaExisteManutencaoCarro(veiculo.placa) == 0) {
				apresentaMsg("Veiculo nao pode ser excluido pois ja realizou manutencao.");
				return;
			}
			system("cls");
			apresentaNomeOficina(45,5,'S');
			gotoxy(11, 9);
			printf("%-20.20s | %-15.15s | %-15s | %-20.20s | %-15.15s", 
			"Fabricante", "Modelo", "Placa", "Chassi", "Ano fabricacao");
			desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaVeiculo(veiculo);
			resp=menuSimNao("Deseja excluir veiculo?");

			switch(resp) {
				case 1:
					system("cls");
					if((arq = abreArquivo(ARQ_VEICULOS, "rb")) != NULL) {
						if((arqTemp = abreArquivo("temp.txt", "wb")) != NULL) {
							while(fread(&veiculo, sizeof(Veiculo), 1, arq) == 1) {
								cont++;
								if(cont != posicao) {
									if(fwrite(&veiculo, sizeof(Veiculo), 1, arqTemp) != 1) {
										apresentaMsg("Erro ao gravar dados.");
										flag = 0;
										break;
									}
								}
							}
						} else {
							apresentaMsg("Nao foi possivel abrir o arquivo veiculos.txt");
						    fechaArquivo(arq);
						  	return;
						} 
					}else {
						apresentaMsg("Nao foi possivel criar o arquivo veiculos.txt");
					    fechaArquivo(arq);
					  	return;						
					}
					fechaArquivo(arq);
					fechaArquivo(arqTemp);
					break;
				case 0:
					return;
			}
		}
		if(flag == 1) {
			if(remove(ARQ_VEICULOS) == 0) {
				if(rename("temp.txt", ARQ_VEICULOS) != 0)
			        apresentaMsg("Erro ao renomear aquivo veiculos.txt");
			    else
			    	apresentaMsg("Veiculo excluido com sucesso.");
			} else
				apresentaMsg("Erro ao remover aquivo veiculos.txt");
		}
	}
}
// Objetivo : Gravar dados no arquivo
// parâmetros: endereco da variavel veiculo, posicao do veiculo
// Retorno : nenhum
void gravaDadosVeiculo(Veiculo *veiculo, int posicao) {
	FILE *arq;
	
	if((arq = abreArquivo(ARQ_VEICULOS, "r+b")) != NULL){
		if(fseek(arq, sizeof(Veiculo) * (posicao - 1), SEEK_SET) == 0) {
			if(fwrite(veiculo, sizeof(Veiculo), 1, arq) == 1) {
				apresentaMsg("Dados gravados com sucesso.");
			}else
				apresentaMsg("Erro ao escrever os dados no arquivo.");
		}else
			apresentaMsg("Erro ao posicionar os dados no arquivo.");
			
		fechaArquivo(arq);
	}
}
//Objetivo: apresentar veiculos no menu
//Parâmetros: nenhum
//Retorno: opcao do menu
int apresentaVeiculos() {
	FILE *arq;
	Veiculo *veiculos = NULL;
	int cont = 0, qtdDados = 0, opcao, aux;
	char **menu = NULL, dados[100];

	veiculos = (Veiculo *)obtemDadosArquivo(ARQ_VEICULOS, sizeof(Veiculo), &qtdDados);
	menu = (char **) malloc(sizeof(char *) * (qtdDados));
	aux = qtdDados;
	if(menu != NULL) {
		for(cont = 0; cont < aux; cont++) {
			sprintf(dados,"%-20.20s | %-15.15s | %-15s | %-20.20s | %-4d ", (veiculos + cont)->fabricante, (veiculos + cont)->modelo,
			formataPlaca((veiculos + cont)->placa), (veiculos + cont)->chassi,veiculos[cont].anoFabricacao.ano);
			
			*(menu + cont) = (char *) malloc(sizeof(char) * sizeof(dados));
			if(*(menu + cont) != NULL) {
				strcpy(*(menu + cont), dados);
			} else
				apresentaMsg("Erro ao alocar memoria para dados.");
		}
	} else{
		apresentaMsg("Erro ao alocar memoria.");
		opcao = 0;
	}
	
	if(menu != NULL) {
		if(qtdDados == 0) {
			apresentaMsg("Nao existem veiculos cadastrados.");
			opcao = 0;
		} else {
			gotoxy(10, 8);
			printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s |  %-20.20s ", 
			"Fabricante", "Modelo", "Placa", "Chassi","Ano fabricacao");
			opcao = menuVertical(qtdDados, menu, BRANCO, VERDE, 10, 10, 1, 1, PRETO, BRANCO);
		}
		for(cont = 0; cont < aux; cont++) {
			free(*(menu + cont));
		}
		free(menu);
	}
	system("cls");
	
	return opcao;
}
// Objetivo : ler os dados de um veiculo do arquivo
// parâmetros: numero do veiculo, endereco da variavel veiculo
// Retorno : 0- erro 1-sucesso
int recuperaDadosVeiculo(int posicao, Veiculo *veiculos) {
	FILE *arq;
	int flag = 0;	
	
	if( (arq = abreArquivo(ARQ_VEICULOS, "rb")) != NULL) {
		if(fseek(arq, sizeof(Veiculo) * (posicao - 1), SEEK_SET) == 0) {
			if(fread(veiculos,sizeof(Veiculo), 1, arq) == 1) {
				apresentaMsg("Dados recuperados com sucesso.");
				flag = 1;
			} else
				apresentaMsg("Erro na leitura.");
		} else
			apresentaMsg("Erro no posicionamento do arquivo.");

		fechaArquivo(arq);
	}
	
	return flag;
} 
//Objetivo: apresentar os dados de uma manutencao
//Parâmetros: variavel proprietario
//Retorno: nenhum
void apresentaManutencao(Manutencao manutencao) {
	
	printf("%-20.20s | %-15.15s | %-10s | %-16.2f | %-20.2f | %-2d/%-2d/%-4d ", manutencao.descricaoServico,
			formataCPF(manutencao.cpfCliente), formataPlaca(manutencao.placa), manutencao.valorPecas, 
			manutencao.valorMaoDeObra, manutencao.data.dia, manutencao.data.mes, manutencao.data.ano);
	
}
//Objetivo: apresentar os dados de um veiculo
//Parâmetros: variavel proprietario
//Retorno: nenhum
void apresentaVeiculo(Veiculo veiculo) {
	
	printf("%-20.20s | %-15.15s | %-15s | %-20.20s | %-4d",veiculo.fabricante,veiculo.modelo,veiculo.placa,
	veiculo.chassi,veiculo.anoFabricacao.ano);
	
}
//Objetivo: Alterar dado de um veiculo
//Parâmetro: Nada
//Retorna: nada
void alteraVeiculo(){
	Veiculo veiculo;
	int posicao, qtdDados, opcaoMenu, opcaoEstado, flag, erro,resp;
	char  *msg, *menu[]={"Modelo","Chassi","Ano de fabricacao","Fabricante","Salvar e sair"};
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM VEICULO");
	posicao = apresentaVeiculos();
	if(posicao != 0) {
		if(recuperaDadosVeiculo(posicao, &veiculo) == 1) {
			apresentaNomeOficina(35,3,'S');
			gotoxy(11, 9);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ","Fabricante", "Modelo", "Placa", "Chassi","Ano Fab");
			desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaVeiculo(veiculo);
			resp=menuSimNao("Deseja alterar dados?");
			if(resp == 1) {
				system("cls");
				do{
					apresentaNomeOficina(35,4,'S');
					gotoxy(43,8);
					printf("Alterar Dados");
					opcaoMenu = menuVertical(5, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
					switch(opcaoMenu) {	
						case 1:						
							leValidaTexto("Informe o modelo: ", "*Modelo invalido*", veiculo.modelo, TAM_MODELO, 11, 11);
							break;
						case 2:
							leValidaTexto("Informe o chassi: ", "*Chassi invalido*", veiculo.chassi, TAM_CHASSI, 11, 11);
							break;
						case 3:	
							leValidaInt("Informe o ano da fabricacao do veiculo: ", "*Ano invalido*", 1000, 3000, &veiculo.anoFabricacao.ano, 11, 11);
							break;
						case 4:
							leValidaTexto("Informe a fabricante: ", "*Fabricante invalido*", veiculo.fabricante, TAM_FABRICANTE, 11, 11);
							break;
					}
				} while(opcaoMenu != 5 && opcaoMenu != 0);
				
				gravaDadosVeiculo(&veiculo, posicao);
			}
		}
	}
}
//Objetiro: criar um arquivo caso nao exista
//Parâmetros: endereço do nome
//Retorno: nenhum
void criaArquivoNaoExistente(char *nome) {
	int verifica;
	FILE *arq;
	
	if(verificaExistenciaArquivo(nome) == 0) {
		arq = abreArquivo(nome, "wb");
		fechaArquivo(arq);
	}
}
//Objetivo: caso seja a primeira execução do programa, ler dados da oficina, caso não, ler esses dados
//Parâmetros: nenhum
//Retorno: oficina
Oficina criaArquivoOficina() {
	Oficina oficina;
	FILE *arq;
	int opcao;
	char *menu[] = {"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI", "RJ",
				    "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"};
	
	if((arq = abreArquivo(ARQ_OFICINA, "rb")) == NULL) {
		if( (arq = abreArquivo(ARQ_OFICINA, "wb")) != NULL) {
			leValidaTexto("Informe o nome da oficina: ", "*Nome invalido.*", oficina.nome, TAM_NOME_OFICINA, 11, 11);
	
			leValidaTexto("Informe a descricao do endereco da oficina: ", "*Descricao invalido*", oficina.endereco.descricao, TAM_DESCRICAO_ENDERECO, 11, 11);
	
			leValidaTexto("Informe a cidade da oficina: ", "*Cidade invalida.*", oficina.endereco.cidade, TAM_CIDADE, 11, 11);
			
			opcao = menuVertical(27, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
	
			*obtemEstado(opcao, oficina.endereco.estado);
			
			if(fwrite(&oficina, sizeof(Oficina), 1, arq) == 1) {
				apresentaMsg("Dados salvos com sucesso.");
			}
			fechaArquivo(arq);
		}
	} else {
		if(fread(&oficina, sizeof(Oficina), 1, arq) == 1) {
			
		}
		fechaArquivo(arq);
	}
	
	return oficina;
}
//Objetiro: verificar existencia de um arquivo
//Parâmetros: endereço do nome 
//Retorno: 0 nao existe 1 existe
int verificaExistenciaArquivo( char *nome) {
	int verifica = 0;
	FILE *arq;
	
	if((arq = abreArquivo(nome, "rb")) != NULL) {
		verifica = 1;
		fechaArquivo(arq);
	} 

	return verifica;
}
//Objetiro: fechar um arquivo
//Parâmetros: endereço do arquivo
//Retorno: nenhum
void fechaArquivo(FILE *arq) {
	if(fclose(arq) != 0) {
		apresentaMsg("Erro ao fechar arquivo.");
	}
}
//Objetiro: abrir um arquivo
//Parâmetros: endereço do nome e modo de abertura do arquivo
//Retorno: nenhum
FILE * abreArquivo(char *nome, char *modoAbertura) {
    FILE *arq;
    char msg[100];
    
    arq = fopen(nome, modoAbertura);
    if(arq == NULL){
    	sprintf(msg, "Nao foi possivel abrir o arquivo: %s no modo: %s", nome, modoAbertura);
        apresentaMsg(msg);
    }
    
    return  arq; 
}
//Objetivo: obter o estado que foi lido pelo menu vertical
//Parâmetros: posicao(menu vertical) e endereço da string
//Retorno: estado
char *obtemEstado(int posicao, char *str) {
	switch(posicao) {
		case 1:
			strcpy(str,"AC");
			break;
		case 2:
			strcpy(str,"AL");
			break;
		case 3:
			strcpy(str,"AP");
			break;
		case 4:
			strcpy(str,"AM");
			break;
		case 5:
			strcpy(str,"BA");
			break;
		case 6:
			strcpy(str,"CE");
			break;
		case 7:
			strcpy(str,"DF");
			break;
		case 8:
			strcpy(str,"ES");
			break;
		case 9:
			strcpy(str,"GO");
			break;
		case 10:
			strcpy(str,"MA");
			break;
		case 11:
			strcpy(str,"MT");
			break;
		case 12:
			strcpy(str,"MS");
			break;
		case 13:
			strcpy(str,"MG");
			break;
		case 14:
			strcpy(str,"PA");
			break;
		case 15:
			strcpy(str,"PB");
			break;
		case 16:
			strcpy(str,"PR");
			break;
		case 17:
			strcpy(str,"PE");
			break;
		case 18:
			strcpy(str,"PI");
			break;
		case 19:
			strcpy(str,"RJ");
			break;
		case 20:
			strcpy(str,"RN");
			break;
		case 21:
			strcpy(str,"RA");
			break;
		case 22:
			strcpy(str,"RO");
			break;
		case 23:
			strcpy(str,"RR");
			break;
		case 24:
			strcpy(str,"SC");
			break;
		case 25:
			strcpy(str,"SP");
			break;
		case 26:
			strcpy(str,"SE");
			break;
		case 27:
			strcpy(str,"TO");	
	}
	
	return str;
}
// Objetivo: Le numero inteiro
// Parâmetros: endereco de memoria  da string  mensagem 
// Retorna: 
void leInt(char *msn, int *valor, int linha, int coluna) {
	int ret = 0;
	
	do {
		desenhaMoldura(linha - 1, coluna - 1, 15, 100, PRETO, BRANCO);
		gotoxy(coluna, linha);
		printf(msn);
		fflush(stdin);
		ret = scanf("%d", valor);
		fflush(stdin);
		
		if(ret == 0) {
			apresentaMsg("Erro ao ler numero.");
		}		
	} while(ret == 0);
}
// Objetivo: Le e validar numero inteiro
// Parâmetros: endereco de memoria  da string  mensagem e mensagem de erro
//              valor minimo e valor maximo, endereço da variavel sendo lida, linha e coluna
// Retorna: 
void leValidaInt(char *msn, char *msnErro, int valorMin, int valorMax, int *valor, int linha, int coluna) {	

	do {
		leInt(msn, valor, linha, coluna + 1);
		
		if(*valor < valorMin || *valor > valorMax) {
			gotoxy(coluna + 1, linha + 1);
			printf(msnErro);
			gotoxy(coluna + 1, linha + 2);
			printf("*Informe um valor entre %d e %d.*", valorMin, valorMax);
			getch();	
		}
		system("cls");
	} while(*valor < valorMin || *valor > valorMax);
}
// Objetivo: Le numero real
// Parâmetros: endereco de memoria  da string  mensagem e da variavel a ser lida e linha e coluna
// Retorna: 
void leFloat(char *msn, float *valor, int linha, int coluna) {
	int ret = 0;
	
	do {
		desenhaMoldura(linha - 1, coluna - 1, 15, 100, PRETO, BRANCO);
		gotoxy(coluna, linha);
		printf(msn);
		fflush(stdin);
		ret = scanf("%f", valor);
		fflush(stdin);
		
		if(ret == 0) {
			apresentaMsg("Erro ao ler numero.");
		}		
	} while(ret == 0);
}
// Objetivo: Le e validar numero real
// Parâmetros: endereco de memoria  da string  mensagem e mensagem de erro
//              valor minimo e valor maximo, endereço da variavel sendo lida, linha e coluna
// Retorna: 
void leValidaFloat(char *msn, char *msnErro, int valorMin, int valorMax, float *valor, int linha, int coluna) {	

	do {
		leFloat(msn, valor, linha, coluna + 1);
		
		if(*valor < valorMin || *valor > valorMax) {
			gotoxy(coluna + 1, linha + 1);
			printf(msnErro);
			gotoxy(coluna + 1, linha + 2);
			printf("*Informe um valor entre %d e %d.*", valorMin, valorMax);
			getch();	
		}
		system("cls");
	} while(*valor < valorMin || *valor > valorMax);
}
//Objetivo   : ler e validar uma string.
//Parâmetros : Endereço da string titulo,endereço da msg de Erro string e endereço da string,
//            além da quantidade máxima de caracteres.
//Retorno    : Nenhum
void leValidaTexto(char *titulo, char *msgErro, char *str, int max, int coluna, int linha) {
     int tam, cont;

     do {
     	 desenhaMoldura(linha - 1, coluna - 1, 15, 100, PRETO, BRANCO);
         fflush(stdin);
         gotoxy(coluna, linha);
         printf("%s", titulo);
         fgets(str, max, stdin);
         tiraTerminador(str);
         tam = strlen(str);
         if (tam < 1 || str[0] == ' ') {
             	apresentaMsg(msgErro);
         }
         system("cls");
     } while(tam < 1 || str[0] == ' ');
}
//Objetivo   : Tirar um terminador
//Parâmetros : Endereços dastring
//Retorno    : Nenhum
void tiraTerminador(char *str) {
     if (str[strlen(str) - 1] == '\n'){
         str[strlen(str) - 1] = '\0';
     }
}
//Descricao : Desenha uma moldura na tela                    
//Parâmetros: linhaInicial - linha inicial da moldura, colunaInicial - coluna inicial da moldura      
//            linhaFinal   - linha final da moldura, colunaFinal - coluna final da moldura          
//            corFundoAtual - cor do fundo atual, corLetra  - cor do fundo atual                 
//Retorno   : nenhum                                           
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal, int corFundoAtual, int corLetraAtual) {
    int i = 0, qtdeLinhas, qtdeColunas;
    
    qtdeLinhas  = (linhaFinal - linhaInicial);
    qtdeColunas = (colunaFinal - colunaInicial);
    textbackground(CINZA_CLARO);
    textcolor(VERDE_CLARO);
    // faz a borda superior
    gotoxy(colunaInicial, linhaInicial);
    for(i = 0; i <= qtdeColunas; i++) {
        printf("\xCD");
    }

    // faz a borda inferior
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    for(i = 0; i <= qtdeColunas; i++) {
        printf("\xCD");
    }

    // faz a lateral esquerda    
    for(i = 0; i <= qtdeLinhas; i++) {
        gotoxy(colunaInicial, linhaInicial + i);
        printf("\xBA");
    }
    // faz a lateral direita
    for(i = 0; i <= qtdeLinhas; i++) {
        gotoxy(colunaInicial + qtdeColunas, linhaInicial + i);
        printf("\xBA");
    }

    // fecha os cantos da moldura
    gotoxy(colunaInicial, linhaInicial);
    printf("\xC9");
    gotoxy(colunaInicial + qtdeColunas, linhaInicial);
    printf("\xBB");
    gotoxy(colunaInicial, linhaInicial + qtdeLinhas);
    printf("\xC8");
    gotoxy(colunaInicial + qtdeColunas, linhaInicial + qtdeLinhas);
    printf("\xBC");
    retornaCor(corFundoAtual, corLetraAtual);
}
//Descricao : retorna a cor de fundo e de texto              
//Parâmetros: corFundo - cor de fundo e corTexto - cor do texto  
//Retorno   : nenhum                                          
void retornaCor(int corFundo,int corTexto) {
    textbackground(corFundo);
    textcolor(corTexto);
}   
//Descricao : formatar um telefone                                  
//Parâmetros: endereço da string telefone                 
//Retorno   : telefone formatado
char *formataTelefone(char *telefone) {
	static char telefoneAux[15];
	int flag, erro;
		
	if(validaTelefone(telefone, &erro) == 0) 
		return NULL;
	else {
		if(strlen(telefone) == 11) {
			sprintf(telefoneAux, "%2.2s %5.5s-%4.4s", telefone, telefone + 2, telefone + 7);
			return telefoneAux;
		} else if(strlen(telefone) == 10) {
			sprintf(telefoneAux, "%2.2s %4.4s-%4.4s", telefone, telefone + 2, telefone + 6);
			return telefoneAux;
		}
	}
} 
//Descricao : formatar uma placa
//Parâmetros: endereço da string placa
//Retorno   : placa formatada
char *formataPlaca(char *placa) {
	static char placaAux[10];
	
	if(validaPlaca(placa) == 0)
		return NULL;
	else {
		sprintf(placaAux, "%3.3s-%4.4s", placa, placa + 3);
		return placaAux;
	}
}
//Descricao : formatar um CPF                                  
//Parâmetros: endereço da string cpf                 
//Retorno   : cpf formatado
char *formataCPF(char *cpf) {
	static char cpfAux[15];
	
	if(validaCPF(cpf) == 0)
		return NULL;
    else {
        sprintf(cpfAux,"%3.3s.%3.3s.%3.3s-%2.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
        return cpfAux;    
    }   
    
}                                       
//Descricao : Valida um CPF                                  
//Parâmetros: endereço inicial da string cpf                 
//Retorno   : 1 - cpf válido, 0 - cpf inválido                
int validaCPF(char *cpf) {
	// cpfs inválidos        
	char *cpfInval[] = {"00000000000","11111111111", "22222222222", "33333333333", "44444444444", 
		"55555555555", "66666666666", "77777777777", "88888888888", "99999999999"}; 
	int cont, retorno = 1, aux2, dig[11], soma = 0, digVeri[2];
		
	if(strlen(cpf) != 11)
		return 0;
		 
     // verifica se cpf so contem nros iguais  
     for(cont = 0; cont < 9; cont++) {
           if(strcmp(cpfInval[cont], cpf) == 0) {
              retorno = 0;
              break;
           }
     } 
     
     if(retorno == 0)
        return retorno;
      
     // transforma os caracteres do cpf em números     
     for(cont = 0; cont < strlen(cpf); cont++) {
            dig[cont] = cpf[cont] - '0';
     }
     
     // obtem o primeiro digito verificador
     aux2 = 10;
     for(cont = 0; cont < 9; cont++, aux2--) {
        soma += dig[cont] * aux2;
     }
     digVeri[0] = soma % 11;
     digVeri[0] = digVeri[0] < 2 ? 0 : 11 - digVeri[0];
     
     // obtem o segundo digito verificador
     soma = 0;
     aux2 = 11;
     for(cont = 0; cont < 10 ; cont++ , aux2--) {
           if(cont == 9)
              soma += digVeri[0] * aux2;
           else
              soma += dig[cont] * aux2;
     }
     digVeri[1] = soma % 11;
     digVeri[1] = digVeri[1]<2 ? 0 : 11-digVeri[1];
     if(digVeri[0] != dig[9] || digVeri[1] != dig[10]) {
           retorno = 0;               
     }
     return retorno;
}
//Descricao : Apresenta um menu vertical e retorna a opcao selecionada                                    * 
//Parâmetros: n - Numero de itens                            
//            imenu - Descrição dos itens                    
//            c1 - cor do texto do menu                      
//            c2 - cor da marca do item selecionado          
//            linha - linha inicial para instalação do menu  
//            coluna - coluna inicial para instalação do menu
//            ini - número da opção inicial do menu a ser  selecionada                          
//             moldura - indicador se deve desenhar o menu dentro de uma moldura                       
//             corFundoAtual - cor do fundo a ser restituida a tela com a retirada do menu                       
//             corLetra - cor da letra a ser restituida a tela com a retirada do menu                       
//Retorno   : número do item do menu selecionado              
int menuVertical(int n, char *imenu[], int c1, int c2, int linha, int coluna, int ini, int moldura, int corFundoAtual, int corLetraAtual) {
	int tecla, sel_b, sel, i, val, tamMaiorTexto;
         
    // verifica se desenha com moldura e menu comeca na linha 1
    if(linha == 1 && moldura)
       linha++;
    // verifica se desenha com moldura e menu comeca na coluna 1
    if(coluna == 1 && moldura)
       coluna++;
        
	textcolor(c1);	// Atributo da cor das letras
	if(ini < 1)
	    ini=1;
	else if(ini > n)
       ini=n;
           
	sel=ini-1; 	// Primeiro item selecionado
	for (i = 0; i <= n - 1; i++) {
		if (i == ini - 1)
			textbackground(c2); // Escreve itens do menu
		else 
			textbackground(corFundoAtual);           // e seleciona o item inicial
		gotoxy(coluna, linha + i);                    // setado no argumento passado
		printf(imenu[i]);
		if(i == 0)
			tamMaiorTexto = strlen(imenu[i]);
		else if(strlen(imenu[i]) > tamMaiorTexto)
			tamMaiorTexto = strlen(imenu[i]);           
	}
	// desenha a moldura
	if(moldura) {
	    desenhaMoldura(linha - 1, coluna - 1, linha + n, coluna + tamMaiorTexto + 2, corFundoAtual, corLetraAtual);
	}    
	do {
		do {
			tecla=toupper(getch());
			// Verificar pelas teclas validas pressionadas
			if (tecla == 72 || tecla == 75 || tecla == 65) 
				val = 1;
			else if (tecla == 77 || tecla == 80 || tecla == 90)
				 val = 1;
			else 	if (tecla == 27 || tecla == 13) 
				val = 1;
			else 
				val = 0;
		} while (!val);
		sel_b = sel; // Backup do item atual antes de modifica-lo
		if (tecla == 72 || tecla == 75 || tecla == 65) 
			sel--; // Sobe
		if (tecla == 80 || tecla == 77 || tecla == 90) 
			sel++; // Desce
		if (tecla == 27) 
			sel_b = -1; 		  // Sai com ESC
		if (sel <= -1) 
			sel = n - 1; // Se for menor vai para o ultmo item
		if (sel >= n) 
			sel = 0; // Se for maior vai para o primeiro item
		textcolor(c1);
		if (tecla != 13 && tecla != 27) {
			// Desseleciona o antigo item do menu...
			gotoxy(coluna, sel_b + linha); textbackground(corFundoAtual); printf(imenu[sel_b]);
			// Seleciona o novo item do menu...
			gotoxy(coluna, sel + linha); textbackground(c2); printf(imenu[sel]);
			// Descarrega o buffer do teclado...
			fflush(stdin);
		}		
	} while (tecla != 13 && tecla != 27);

    if(moldura)
       	limpaJanela(linha - 2, coluna - 1, linha + n, coluna + tamMaiorTexto + 2, corFundoAtual);
    else
       	limpaJanela(linha, coluna, linha + n, coluna + tamMaiorTexto, corFundoAtual);

	return(sel_b + 1); 	// Retorna item selecionado + 1 (nao retorna 0)
}
//Objetivo: validar o número do telefone
//Parâmetros: endereço da string telefone
//Retorno: 0 caso seja invalido ou 1 caso seja valido
char *validaTelefone(char *telefone, int *erro) {
	int cont, i;
	static char msg[100];
	char sddd[2], primeiro[2];
	short int ddd, primeiroNro;
	
	msg[0] = '\0';
	*erro = 1;
	
	//verifica se existem letras no telefone. Caso exista encerra
	for(i = 0; i < strlen(telefone); i++) {
		if(isdigit(telefone[i]) == 0) {
			sprintf(msg, "Telefone/celular com letras.");
			*erro = 0;
			break;
		}
	}
	if(*erro == 0)
		return msg;
	
	for(i = 0; i < 2; i++) {
		memcpy(sddd, telefone, 2);
	}
	ddd = atoi(sddd);
	//verifica se o codigo do ddd é valido
	if(ddd < 11 || ddd > 99 || ddd % 10 == 0) {
		*erro = 0;
		sprintf(msg, "Telefone/celular com ddd invalido.");
	}
	if(*erro == 0)
		return msg;
		
	
	//verifica se o telefone é celular ou fixo
	if(strlen(telefone) == 11) {
		//pega o primeiro numero apos o ddd
		for(i = 2; i < 3; i++) {
			memcpy(primeiro, (telefone + i), 1);
		}
		primeiroNro = atoi(primeiro);
		//verifica se o primeiro numero apos o ddd é 9
		if(primeiroNro != 9) {
			*erro = 0;
			sprintf(msg, "O primeiro digito apos o ddd do celular deve ser 9.");
		}
		if(*erro == 0)
			return msg;
		//verifica se o numero apos o nove esta entre 6 e 9(padrao celular)
		if(primeiroNro < 6 || primeiroNro > 9) {
			*erro = 0;
			sprintf(msg, "O digito apos o 9 do celular deve estar entre 6 e 9.");
		}
		if(*erro == 0)
			return msg;
		
	} else if(strlen(telefone) == 10) {
		//pega o primeiro numero apos o ddd
		for(i = 2; i < 3; i++) {
			memcpy(primeiro, (telefone + i), 1);
		}
		primeiroNro = atoi(primeiro);
		if(primeiroNro < 2 || primeiroNro > 5) {
			*erro = 0;
			sprintf(msg, "O primeiro digito do telefone deve estar entre 2 e 5.");
		}
		if(*erro == 0)
			return msg;
	} else {
		*erro = 0;
		sprintf(msg, "Telefone/celular no formato invalido.");
	} 
		
	return msg;	
}
//Objetivo: validar placa
//Parâmetros: endereço da string placa
//Retorno: 0 caso seja invalida ou 1 caso seja valida
int validaPlaca(char *placa) {
	int flag = 1, cont, cont2, tam;
	
	tam = strlen(placa);
		
	//verifica se a placa esta no formato correto
	if(tam != 7)
		flag = 0;
	
	if(flag == 0)
		return flag;
	
	//verifica os 3 primeiros digitos da placa, que devem ser letras(abc-1234)
	for(cont = 0; cont < tam; cont++) {
		for(cont2 = 0; cont2 < 3; cont2++) {
			if(isdigit(placa[cont2]) != 0) {
				flag = 0;
				break;
			}	
		}		
	}
	
	if(flag == 0)
		return flag;
	
	//verifica os 4 ultimos digitos da placa, que devem ser numeros(abc-1234)
	for(cont = 0; cont < tam; cont++) {
		for(cont2 = 3; cont2 < 7; cont2++) {
			if(isdigit(placa[cont2]) == 0) {
				flag = 0;
				break;
			}
				
		}		
	}
	
	if(flag == 0)
		return flag;	
}
//Objetivo: validar data
//Parâmetros: dia, mes e ano
//Retorno: 0 erro 1 sucesso
int validaData(int dia, int mes, int ano) {
	int retorno = 1;    
    
	if(ano < 0 || mes < 1 || mes > 12 || dia > 31)
       return 0;
	             
    switch(mes) {
       case 4:
       case 6:
       case 9:
       case 11:
            if(dia > 30)
               retorno = 0;
            break;
       case 2:
            printf(" %d\n",(ano % 4 == 0 && ano % 100 != 0) ||(ano % 400 == 0));
            if((ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0)) {
               if(dia > 29)
                  retorno = 0;
            }      
            else {
               if(dia > 28)
                  retorno = 0;                                      
            }
            break;      
    }      
    return retorno;
}
//Objetivo: validar cpf repetido
//Parâmetros: endereço da string cpf
//Retorno: 0 caso seja invalido ou 1 caso seja valido
int validaCPFrepetido(char *cpf) {
	FILE *arq;
	Proprietario proprietario;
	int flag = 1;
	
	if( (arq = abreArquivo(ARQ_PROPRIETARIOS, "rb")) != NULL ) {
		while(!feof(arq)) {
			if(fread(&proprietario, sizeof(Proprietario), 1, arq) == 1) {
				if( memcmp(proprietario.cpf, cpf, TAM_CPF) == 0) {
					flag = 0;
					break;
				}
			}
		}
		fechaArquivo(arq);
	}
	
	return flag;
}
//Objetivo: validar placa repetida
//Parâmetros: endereço da string placa
//Retorno: 0 caso seja invalido ou 1 caso seja valido
int validaPlacaRepetida(char *placa) {
	FILE *arq;
	Veiculo veiculo;
	int flag = 1;
	
	if( (arq = abreArquivo(ARQ_VEICULOS, "rb")) != NULL ) {
		while(!feof(arq)) {
			if(fread(&veiculo, sizeof(Veiculo), 1, arq) == 1) {
				if( memcmp(veiculo.placa, placa, TAM_PLACA) == 0) {
					flag = 0;
					break;
				}
			}
		}
		fechaArquivo(arq);
	}
	
	return flag;
}
//Objetivo   : Gerenciar vendas
//Parâmetros : nenhum
//Retorno    : nenhum
void menuManutencao() {
	char *menu[] = {"Adicionar manutencao", "Excluir manutencao", "Voltar"}, opcao;
	
	do {
		system("cls");
		apresentaNomeOficina(40,7,'S');
		gotoxy(45,5);
        printf("MANUTENCAO");
		opcao = menuVertical(3, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
		switch(opcao) {
			case 1:
				cadastroManutencoes();
				break;
			case 2:
				excluiManutencao();
				break;				
		}
	} while(opcao != 3 && opcao != 0);
}
//Objetivo: excluir manutencao
//Parâmetros: nenhum
//Retorno: nenhuhm
void excluiManutencao() {
	Manutencao manutencao;
	FILE *arq, *arqTemp;
	int posicao, cont = 0, flag = 1,resp;
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UMA MANUTENCAO PARA A EXCLUSAO");
	posicao = apresentaManutencoes();
	if(posicao != 0) {
		if(recuperaDadosManutencao(posicao, &manutencao) == 1) {
			apresentaNomeOficina(35,3,'S');
			gotoxy(11, 9);
			printf("%-20.20s   %-15.15s   %-10.10s   %-15.15s   %-10.20s   %-10.15s ", 
			"Descricao do servico", "CPF do cliente", "Placa", "Valor das pecas", "Valor da mao de obra", "Data da manutencao");
			desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaManutencao(manutencao);
			resp=menuSimNao("Deseja excluir manutencao?");
			switch(resp) {
				case 1:
					system("cls");
					if((arq = abreArquivo(ARQ_MANUTENCOES, "rb")) != NULL) {
						if((arqTemp = abreArquivo("temp.txt", "wb")) != NULL) {
							while(fread(&manutencao, sizeof(Manutencao), 1, arq) == 1) {
								cont++;
								if(cont != posicao) {
									if(fwrite(&manutencao, sizeof(Manutencao), 1, arqTemp) != 1) {
										apresentaMsg("Erro ao gravar dados.");
										flag = 0;
										break;
									}
								}
							}
						} else {
							apresentaMsg("Nao foi possivel abrir o arquivo manutencao.txt");
						} 
					}else {
						apresentaMsg("Nao foi possivel criar o arquivo manutencao.txt");
					  					
					}
					fechaArquivo(arq);
					fechaArquivo(arqTemp);
					break;
				case 0:
					return;
			}
			if(flag == 1) {
				if(remove(ARQ_MANUTENCOES) == 0) {
					if(rename("temp.txt", ARQ_MANUTENCOES) != 0)
				        apresentaMsg("Erro ao renomear aquivo manutencoes.txt");
				    else
				    	apresentaMsg("Manutencao excluida com sucesso.");
				} else
					apresentaMsg("Erro ao remover aquivo manutencoes.txt");
			}
			
		}
	
	}
}
// Objetivo : ler os dados de um funcionario do arquivo
// parâmetros: numero do proprietario, endereco da variavel proprietario
// Retorno : 0- erro 1-sucesso
int recuperaDadosManutencao(int posicao, Manutencao *manutencao) {
	FILE *arq;
	int flag = 0;	
	
	if( (arq = abreArquivo(ARQ_MANUTENCOES, "rb")) != NULL) {
		if(fseek(arq, sizeof(Manutencao) * (posicao - 1), SEEK_SET) == 0) {
			if(fread(manutencao,sizeof(Manutencao), 1, arq) == 1) {
				apresentaMsg("Dados recuperados com sucesso.");
				flag = 1;
			} else
				apresentaMsg("Erro na leitura.");
		} else
			apresentaMsg("Erro no posicionamento do arquivo.");

		fechaArquivo(arq);
	}
	
	return flag;
} 

//Objetivo: apresentar manutenções no menu
//Parâmetros: nenhum
//Retorno: opcao do menu
int apresentaManutencoes() {
	FILE *arq;
	Manutencao *manutencoes=NULL;
	int cont, qtdDados = 0, opcao;
	char **menu = NULL, dados[150];

	manutencoes = (Manutencao *)obtemDadosArquivo(ARQ_MANUTENCOES, sizeof(Manutencao), &qtdDados);
	menu = (char **) malloc(sizeof(char *) * (qtdDados));
	if(menu != NULL) {
		for(cont = 0; cont < qtdDados; cont++) {
			sprintf(dados, "%-20.20s | %-15.15s | %-15.15s | %-20.2f | %-20.2f | %-2d/%-2d/%-4d ", (manutencoes + cont)->descricaoServico,
			formataCPF((manutencoes + cont)->cpfCliente), formataPlaca((manutencoes + cont)->placa), (manutencoes + cont)->valorPecas, 
			(manutencoes + cont)->valorMaoDeObra, manutencoes[cont].data.dia, manutencoes[cont].data.mes, manutencoes[cont].data.ano);
		//	sprintf(dados, "%-15.15s | %-15.15s | %-15.15d | %-15.2f | %-15.2f | %-20.20s ",formataPlaca(( manutencoes + cont)->placa), formataCPF((manutencoes + cont)->cpfCliente), manutencoes[cont].data,
		//	 manutencoes[cont].valorPecas, manutencoes[cont].valorMaoDeObra, manutencoes[cont].descricaoServico);
			*(menu + cont) = (char *) malloc(sizeof(char) * strlen(dados));

			if(*(menu + cont) != NULL) { 
				strcpy(*(menu + cont), dados);
			} else
				apresentaMsg("Erro ao alocar memoria para dados.");
		}
	} else{
		apresentaMsg("Erro ao alocar memoria."); 
		opcao = 0;
	}
	
	if(menu != NULL) {
		if(qtdDados == 0) {
			apresentaMsg("Nao existem proprietarios cadastrados.");
			opcao = 0;
		} else {
			gotoxy(10, 8);
			printf("%-20.20s  %-15.15s  %-15.15s  %-20.20s  %-20.20s  %-15.15s", "Descricao servico", 
			   "Id Proprietario", "Id Veiculo", "Valor pecas", "Valor mao de obra", "Data realizacao");
		//	printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s   %-10.10s   %-25.25s ", 
		//	"Placa", "CPF do cliente", "Data da manutencao", "Valor das pecas", "Valor da mao de obra", "Descricao do servico");
			opcao = menuVertical(qtdDados, menu, BRANCO, VERDE, 10, 10, 1, 1, PRETO, BRANCO);
		}
		for(cont = 0; cont < qtdDados; cont++) {
			free(*(menu + cont));
		}
		free(menu);
	}
	system("cls");
	
	return opcao;
}
//Objetivo   : cadastrar dados da manutencao
//Parâmetros : nenhum
//Retorno    : nenhum
void cadastroManutencoes() {
	FILE *arq;
	Manutencao manutencao;
	Proprietario proprietario;
	Veiculo veiculo;
	int flag,posicaoProp,posicaoVeic,resp;
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM PROPRIETARIO PARA MANUTENCAO");
	posicaoProp = apresentaProprietarios();
	if(recuperaDadosProprietario(posicaoProp, &proprietario) == 1) {
		apresentaNomeOficina(35,3,'S');
		gotoxy(11, 9);
		printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s   %-10.10s   %-7.7s ", 
		"Nome", "CPF", "Telefone", "Desc endereco", "Cidade", "Estado");
		desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
		gotoxy(11, 11);
		apresentaProprietario(proprietario);
		resp=menuSimNao("Deseja adcionar a manutencao?");
		if(resp==1){
			strcpy(manutencao.cpfCliente,proprietario.cpf);
			apresentaNomeOficina(35,3,'S');
			gotoxy(35,6);
			printf("ESCOLHA UM VEICULO PARA MANUTENCAO");
			posicaoVeic = apresentaVeiculos();
			if(recuperaDadosVeiculo(posicaoVeic, &veiculo) == 1) {
				if(verificaManutencaoDia(posicaoVeic, veiculo.placa) != 0) {
					apresentaNomeOficina(35,3,'S');
					gotoxy(11, 9);
					printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ","Fabricante", "Modelo", "Placa", "Chassi","Ano fabricacao");
					desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
					gotoxy(11, 11);
					apresentaVeiculo(veiculo);
					resp=menuSimNao("Deseja adcionar a manutencao?");	
					if(resp==1){
						strcpy(manutencao.placa,veiculo.placa);
						apresentaNomeOficina(35,7,'N');
						leValidaFloat("Informe o valor das pecas: ", "*Valor invalido.*", 1, 5000000, &manutencao.valorPecas, 11, 11);
						apresentaNomeOficina(35,7,'N');
						leValidaFloat("Informe o valor da mao de obra: ", "*Valor invalido.*", 1, 50000, &manutencao.valorMaoDeObra, 11, 11);
						apresentaNomeOficina(35,7,'N');
						leValidaTexto("Informe a descricao do servico realizado: ", "*Descricao invalida*", manutencao.descricaoServico, TAM_DESCRICAO, 11, 11);
						
						obtemDataAtual(&manutencao.data.dia, &manutencao.data.mes, &manutencao.data.ano);
						
						arq = abreArquivo(ARQ_MANUTENCOES, "ab");
						if(arq != NULL) {
							desenhaMoldura(10,10,15,70,PRETO,BRANCO);
							if( fwrite(&manutencao, sizeof(Manutencao), 1, arq) == 1 ) {
								apresentaMsg("Dados salvos com sucesso.");
							} else {
								apresentaMsg("Erro ao gravar dados no arquivo.");
							}		
							fechaArquivo(arq);
						} 
					}
				}
			
			}
		}
	}	
}
//Objetivo: Verificar se o veiculo ja realizou manutenção no dia
//Parâmetros: Posição do veículo no arquivo e a placa do veículo
//Retorno: 0 caso o veiculo ja tenha realizado manutenção no dia ou 1 caso nao tenha realizado
int verificaManutencaoDia(int posicaoVeic, char *placa){
	Data dataAux;
	Manutencao manutencaoAux;
	int flag = 1;
	FILE *arq;
	
	obtemDataAtual(&dataAux.dia,&dataAux.mes,&dataAux.ano);
	
	arq = abreArquivo(ARQ_MANUTENCOES, "rb");
	if(arq != NULL) {
		while(!feof(arq)) {
			if(fread(&manutencaoAux, sizeof(Manutencao), 1, arq) == 1) {
				if(stricmp(manutencaoAux.placa, placa) == 0) {
					if(manutencaoAux.data.dia==dataAux.dia && manutencaoAux.data.mes==dataAux.mes && manutencaoAux.data.ano==dataAux.ano){
						flag = 0;
						apresentaMsg("Veiculo ja realizou manutencao hoje.");
						break;
					}
				}
			}
		}		
		fechaArquivo(arq);
	}
	 
	return flag;
}
//Objetivo: obter hora do sistema
//Parâmetros: edereco de dia, mes e ano
//Retorno: nenhum
void obtemDataAtual(int *dia, int * mes, int *ano) {
   time_t t;
   struct tm *dataAtual;
   t = time(NULL);
   dataAtual = localtime(&t);
   
   *dia      = dataAtual->tm_mday;
   *mes      = dataAtual->tm_mon+1;
   *ano      = 1900+dataAtual->tm_year;
}
//Objetivo: pular linhas e fazer a separação
//Parâmetros: endereco do titulo, linha e coluna
//Retorno: nenhum
void pulaLinhas(char *titulo, int *linha, int *coluna) {
	int cont;
	
	//(*linha)++;
	*linha += 2;
	gotoxy(*coluna, *linha);
	for(cont = *coluna; cont < 132; cont++) {
		printf("-");
	}
	(*linha)++;
	gotoxy(61, *linha);
	printf(titulo);
	(*linha)++;
	gotoxy(*coluna, *linha);
	for(cont = *coluna; cont < 132; cont++) {
		printf("-");
	}
	*linha += 2;
	gotoxy(*coluna, *linha);
}
//Objetivo   : apresentar dados cadastrados
//Parâmetros : nenhum
//Retorno    : nenhum
void apresentaDados() {
	char *menu[] = {"Proprietarios", "Veiculos","Manutencao","Voltar"}, opcao;
	
	do {
		system("cls");
		apresentaNomeOficina(40,7,'N');
		gotoxy(45,5);
        printf("APRESENTA DADOS");
		opcao = menuVertical(4, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
		switch(opcao) {
			case 1:
				apresentaTodosProp();
				break;
			case 2:		
				 apresentaTodosVeic();			
				break;
			case 3:		
				apresentaTodasManu();
				break;				
		}
	} while(opcao != 4 && opcao != 0);
}
//Objetivo: Apresentar todos os proprietarios
//Parâmetro: nada
//Retorno:nada
void apresentaTodosProp(){
	FILE *arq;
	Proprietario *proprietarios;
	int linha, coluna, linhaFinal, qtdDadosProp, cont;
	linha = coluna = 10;

	proprietarios = (Proprietario *)obtemDadosArquivo(ARQ_PROPRIETARIOS, sizeof(Proprietario), &qtdDadosProp);
	apresentaNomeOficina(55,7,'S');
	if(qtdDadosMan<6){
		desenhaMoldura(10,7,6*4,133, PRETO, BRANCO);
	} else {
		desenhaMoldura(10,7,qtdDadosMan*8,133, PRETO, BRANCO);
	}
	if(qtdDadosProp != 0) {

		pulaLinhas("PROPRIETARIOS", &linha, &coluna);
		printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", "Nome", "CPF", "Telefone", "Descricao endereco", "Cidade", "Estado");
		for(cont = 0; cont < qtdDadosProp; cont++) {
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", " ", " ", " ", " ", " ", "");
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", (proprietarios + cont)->nome, formataCPF((proprietarios + cont)->cpf),
			formataTelefone((proprietarios + cont)->telefone), proprietarios[cont].endereco.descricao, proprietarios[cont].endereco.cidade, proprietarios[cont].endereco.estado);
		}
		getch();
	}else{
		apresentaMsg("Não existem dados cadastrados.");
	}
}
//Objetivo:Apresentar todos os veiculos
//Parâmetro: Nada
//Retorno:Nada
void apresentaTodosVeic(){
	FILE *arq;
	Veiculo *veiculos;
	int linha, coluna, linhaFinal, qtdDadosVeic, cont;
	linha=coluna=10;
	
	system("cls");
	veiculos = (Veiculo *)obtemDadosArquivo(ARQ_VEICULOS, sizeof(Veiculo), &qtdDadosVeic);
	apresentaNomeOficina(55,7,'S');
	if(qtdDadosMan<6){
		desenhaMoldura(10,7,6*4,133, PRETO, BRANCO);
	} else {
		desenhaMoldura(10,7,qtdDadosMan*8,133, PRETO, BRANCO);
	}
	if(qtdDadosVeic != 0) {
		pulaLinhas("VEICULOS", &linha, &coluna);
		printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ", "Fabricante", "Modelo", "Placa", "Chassi", "Ano fabricacao");
		for(cont = 0; cont < qtdDadosVeic; cont++) {
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ", " ", " ", " ", " ", " ");
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15s | %-20.20s | %-4d ", (veiculos + cont)->fabricante, (veiculos + cont)->modelo,
			formataPlaca((veiculos + cont)->placa), (veiculos + cont)->chassi,veiculos[cont].anoFabricacao.ano);
		}
		getch();
	}else{
		apresentaMsg("Não existem dados cadastrados.");
	}
}
//Objetivo:Apresentar todos as manutencoes
//Parâmetro: Nada
//Retorno:Nada
void apresentaTodasManu(){
	FILE *arq;
	Manutencao *manutencoes;
	int linha, coluna, linhaFinal, qtdDadosMan, cont;
	linha=coluna=10;
	
	system("cls");
	manutencoes = (Manutencao *)obtemDadosArquivo(ARQ_MANUTENCOES, sizeof(Manutencao), &qtdDadosMan);
	apresentaNomeOficina(55,7,'S');
	if(qtdDadosMan<6){
		desenhaMoldura(10,7,6*4,133, PRETO, BRANCO);
	} else {
		desenhaMoldura(10,7,qtdDadosMan*8,133, PRETO, BRANCO);
	}
	if(qtdDadosMan != 0) {
		pulaLinhas("MANUTENCOES", &linha, &coluna);
		printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s\n", "Descricao servico", 
			   "Id Proprietario", "Id Veiculo", "Valor pecas", "Valor mao de obra", "Data realizacao");
		for(cont = 0; cont < qtdDadosMan; cont++) {	
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", " ", " ", " ", " ", " ", "");
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15s | %-20.2f | %-20.2f | %-2d/%-2d/%-4d \n", (manutencoes + cont)->descricaoServico,
			formataCPF((manutencoes + cont)->cpfCliente), formataPlaca((manutencoes + cont)->placa), (manutencoes + cont)->valorPecas, 
			(manutencoes + cont)->valorMaoDeObra, manutencoes[cont].data.dia, manutencoes[cont].data.mes, manutencoes[cont].data.ano);
		}
		getch();
	}else{
		apresentaMsg("Não existem dados cadastrados.");
	}
}
//Objetivo   : Gerenciar apresentações e pesquisas
//Parâmetros :
//Retorno    :
void pesquisasConsultas() {
	char *menu[] = {"Apresentar dados cadastrados", "Apresentar veiculos de um proprietario", "Consultar dados de um veiculo",
	"Consultar manutencoes em um periodo", "Pesquisar dados proprietario pelo nome",  "Voltar"}, opcao;
	
	do {
		system("cls");
		apresentaNomeOficina(40,7,'S');
		gotoxy(45,5);
        printf("CONSULTAS/PESQUISAS");
		opcao = menuVertical(6, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
		switch(opcao) {
			case 1:
				apresentaDados();
				break;
			case 2:
				apresentaVeiculosManutencao();
				break;
			case 3:
				consultaDadosVeiculo();
				break;
			case 4:
				apresentaManuTempo();
				break;
			case 5:
				apresentaDadosPropNom();
				break;
		
		}
	} while(opcao != 6&& opcao != 0);
}
//Objetivo   : apresentar dados das manutencoes de um periodo de tempo
//Parâmetros : nenhum
//Retorno    : nenhum
void apresentaManuTempo(){
	FILE *arqMan;
	Manutencao manutencao, *manutencoesAux=NULL, *manutencoes=NULL;
	Data dataDE,dataATE;
	int qtdManu=0,linhaFinal, linha, coluna,cont,calculaDataDE=0,calculaDataATE=0,calculaDataManu=0;
	float somaValorMaoDeObra=0,somaValorPecas=0,somaValorTotal=0;
	char titulo[100];

	apresentaNomeOficina(35,3,'N');
	gotoxy(10,7);
	printf("INFORME UM DIA DE PARA PESQUISA");
	leValidaInt("Do dia: ", "*Dia invalido*", 1, 31,&(dataDE.dia), 10, 10);
	apresentaNomeOficina(35,3,'N');
	gotoxy(10,8);
	printf("INFORME UM MES  PARA PESQUISA");
	leValidaInt("Do mes: ", "*Mes invalido*", 1, 12, &(dataDE.mes), 10, 10);
	apresentaNomeOficina(35,3,'N');
	gotoxy(10,9);
	printf("INFORME UM ANO PARA PESQUISA");
	leValidaInt("Do ano: ", "*Ano invalido*", 1000, 3000, &(dataDE.ano), 12, 10);
	
	apresentaNomeOficina(35,3,'N');
	gotoxy(10,7);
	printf("INFORME UM DIA PARA PESQUISA");
	leValidaInt("Ate o dia: ", "*Dia invalido*", 1, 31,&(dataATE.dia), 10, 10);
	apresentaNomeOficina(35,3,'N');
	gotoxy(10,8);
	printf("INFORME UM MES PARA PESQUISA");
	leValidaInt("Ate o mes: ", "*Mes invalido*", 1, 12, &(dataATE.mes), 11, 10);
	apresentaNomeOficina(35,3,'N');
	gotoxy(10,9);
	printf("INFORME UM ANO PARA PESQUISA");
	leValidaInt("Ate o ano: ", "*Ano invalido*", 1000, 3000, &(dataATE.ano), 12, 10);
	
	
	calculaDataDE=(dataDE.dia*1 )+(dataDE.mes*100 )+(dataDE.ano*1000 );
	calculaDataATE=(dataATE.dia*1 )+(dataATE.mes*100 )+(dataATE.ano*1000 );

	arqMan = abreArquivo(ARQ_MANUTENCOES, "rb");
	if(arqMan != NULL) {
		
		while(!feof(arqMan)) {		
			if(fread(&manutencao, sizeof(Manutencao), 1, arqMan) == 1) {
				calculaDataManu=(manutencao.data.dia*1)+(manutencao.data.mes*100)+(manutencao.data.ano*1000);
				if(calculaDataManu>=calculaDataDE && calculaDataManu<=calculaDataATE){
					manutencoesAux = (Manutencao *)realloc(manutencoes, sizeof(Manutencao) * (qtdManu + 1));
					if(manutencoesAux != NULL) {
						manutencoes = manutencoesAux;
						*(manutencoesAux + qtdManu) = manutencao;
						qtdManu++;
					}
				}	
			}	
		}
		fechaArquivo(arqMan);
	}
	if(qtdManu!=0){
		linha = coluna = 10;
		apresentaNomeOficina(55,9,'S');
		desenhaMoldura(linha-3, coluna-3, 50 , 135, PRETO, BRANCO);
		pulaLinhas("MANUTENCOES", &linha, &coluna);
		printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s\n", "Descricao servico", 
					   "Id Proprietario", "Id Veiculo", "Valor pecas", "Valor mao de obra", "Data realizacao");
		for(cont = 0; cont < qtdManu; cont++) {	
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", " ", " ", " ", " ", " ", "");
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15s | %-20.2f | %-20.2f | %-2d/%-2d/%-4d \n", (manutencoes + cont)->descricaoServico,
			formataCPF((manutencoes + cont)->cpfCliente), formataPlaca((manutencoes + cont)->placa), (manutencoes + cont)->valorPecas, 
			(manutencoes + cont)->valorMaoDeObra, manutencoes[cont].data.dia, manutencoes[cont].data.mes, manutencoes[cont].data.ano);
			
			somaValorMaoDeObra+=(manutencoes + cont)->valorMaoDeObra;
			somaValorPecas+=(manutencoes + cont)->valorPecas;
		}
		somaValorTotal+= (somaValorMaoDeObra+somaValorPecas);
		gotoxy(coluna+3, linha+3);
		printf("Valor das pecas: %.2f",somaValorPecas);
		gotoxy(coluna+3, linha+4);
		printf("Valor da mao de obra: %.2f",somaValorMaoDeObra);
		gotoxy(coluna+3, linha+5);
		printf("Valor total: %.2f",somaValorTotal);
		getch();
		if(manutencoes != NULL)
			free(manutencoes);
	}else{
		apresentaMsg("Nao existem manutencoes.");
	}
}
//Objetivo: Consultar manutenções e dados do proprietário de um veículo
//Parâmetros: nenhum
//Retorno: nenhum
void consultaDadosVeiculo() {
	int posicao, qtdManutencoes = 0, cont, qtdProps = 0, posicaoRep, flag = 0, linha, coluna, existeMan = 0;
	Manutencao *manutencoesAux = NULL, *manutencoes = NULL, manutencao;
	Veiculo veiculo;
	Proprietario proprietario, *proprietarios = NULL, *proprietariosAux = NULL;
	char resp;
	FILE *arqMan, *arqProp;
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM VEICULO");
	posicao = apresentaVeiculos();
	if(posicao != 0) {
		if(recuperaDadosVeiculo(posicao, &veiculo) == 1) {
			apresentaNomeOficina(35,6,'S');
			gotoxy(11, 9);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ","Fabricante", "Modelo", "Placa", "Chassi","Ano fabricacao");
			desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaVeiculo(veiculo);
			resp = menuSimNao("Deseja consultar dados?");
			if(resp == 1) {
				
				arqMan = abreArquivo(ARQ_MANUTENCOES, "rb");
				if(arqMan != NULL) {
					while(!feof(arqMan)) {
						if(fread(&manutencao, sizeof(Manutencao), 1, arqMan) == 1) {
							if(stricmp(manutencao.placa, veiculo.placa) == 0) {
								existeMan = 1;
								manutencoesAux = (Manutencao *)realloc(manutencoes, sizeof(Manutencao) * (qtdManutencoes + 1));
								if(manutencoesAux != NULL) {
									manutencoes = manutencoesAux;
									*(manutencoesAux + qtdManutencoes) = manutencao;
									qtdManutencoes++;
								}
							}
						}
					}
					fechaArquivo(arqMan);
				}
				if(existeMan == 0)
					apresentaMsg("Veiculo nao possui nenhuma manutencao.");
				else {
					arqProp = abreArquivo(ARQ_PROPRIETARIOS, "rb");
					if(arqProp != NULL) {
						while(!feof(arqProp)) {
							if(fread(&proprietario, sizeof(Proprietario), 1, arqProp) == 1) {
								for(cont = 0; cont < qtdManutencoes; cont++) {
									if(strcmp((manutencoes + cont)->cpfCliente, proprietario.cpf) == 0) {
										proprietariosAux = (Proprietario *)realloc(proprietarios, sizeof(Proprietario) * (qtdProps + 1));
										if(proprietariosAux != NULL) {
											proprietarios = proprietariosAux;
											*(proprietariosAux + qtdProps) = proprietario;
											qtdProps++;
										}
										
									}
									
								}	
							}
						}
						fechaArquivo(arqProp);
					}
					if(qtdProps != 0) {
						if(qtdProps > 1){
							for(cont = 0; cont < qtdProps; cont++) {
								if(stricmp((proprietarios + cont)->cpf, proprietarios[cont + 1].cpf) == 0) {
									posicaoRep = cont + 1;
									flag = 1;								
								}
							}
							if(flag == 1) {
								for(cont = posicaoRep; cont < qtdProps; cont++) {
									*(proprietarios + cont) = proprietarios[cont + 1];
								}
								qtdProps -= 1;
							}
							
						}
						linha = coluna = 10;					
						system("cls");
						apresentaNomeOficina(55,6,'S');
						desenhaMoldura(linha, coluna, 50 , 132, PRETO, BRANCO);
						coluna++;
						pulaLinhas("PROPRIETARIO", &linha, &coluna);
						printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", "Nome", "CPF", "Telefone", "Descricao endereco", "Cidade", "Estado");
						for(cont = 0; cont < qtdProps; cont++) {
								linha++;
								gotoxy(coluna, linha);
								printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", " ", " ", " ", " ", " ", "");						linha++;
								gotoxy(coluna, linha);
								printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", (proprietarios + cont)->nome, formataCPF((proprietarios + cont)->cpf),
								formataTelefone((proprietarios + cont)->telefone), proprietarios[cont].endereco.descricao, proprietarios[cont].endereco.cidade, proprietarios[cont].endereco.estado);		
						}
						
						pulaLinhas("MANUTENCOES", &linha, &coluna);
						printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s\n", "Descricao servico", 
									   "Id Proprietario", "Id Veiculo", "Valor pecas", "Valor mao de obra", "Data realizacao");
						for(cont = 0; cont < qtdManutencoes; cont++) {	
							linha++;
							gotoxy(coluna, linha);
							printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", " ", " ", " ", " ", " ", "");
							linha++;
							gotoxy(coluna, linha);
							printf("%-20.20s | %-15.15s | %-15s | %-20.2f | %-20.2f | %-2d/%-2d/%-4d \n", (manutencoes + cont)->descricaoServico,
							formataCPF((manutencoes + cont)->cpfCliente), formataPlaca((manutencoes + cont)->placa), (manutencoes + cont)->valorPecas, 
							(manutencoes + cont)->valorMaoDeObra, manutencoes[cont].data.dia, manutencoes[cont].data.mes, manutencoes[cont].data.ano);
						}
						getch();
						if(manutencoes != NULL)
							free(manutencoes);
						if(proprietarios != NULL)
							free(proprietarios);
					}
				}		
			}
		}
	}	
}
//Objetivo   : apresentar dados de um proprietario pelo nome
//Parâmetros : nenhum
//Retorno    : nenhum
void apresentaDadosPropNom() {
	FILE *arqProp;
	Proprietario *proprietarios = NULL, *proprietariosAux = NULL, proprietario;
	int linha, coluna, linhaFinal, qtdDados, cont,opcao, qtdProps, existeNome = 0;
	linha = coluna = 10;
	char nomePesq[TAM_NOME];
	
	apresentaNomeOficina(35,6,'S');	
	leValidaTexto("Informe o nome para pesquisa: ", "*Nome invalido*", nomePesq, TAM_NOME, 11, 11);
	
	arqProp = abreArquivo(ARQ_PROPRIETARIOS, "rb");
	if(arqProp != NULL) {
		while(!feof(arqProp)) {
			if(fread(&proprietario, sizeof(Proprietario), 1, arqProp) == 1) {
				if(strstr(proprietario.nome, nomePesq) != NULL) {
					proprietariosAux = (Proprietario *)realloc(proprietarios, sizeof(Proprietario) * (qtdProps + 1));
					if(proprietariosAux != NULL) {
						proprietarios = proprietariosAux;
						*(proprietariosAux + qtdProps) = proprietario;
						qtdProps++;
						existeNome = 1;
					}	
				}
			}
		}
		fechaArquivo(arqProp);
	}
	
	if(existeNome == 0) {
		apresentaMsg("Nome nao encontrado.");
	} else {
		qsort(proprietarios, qtdProps, sizeof(Proprietario), comparaNome);
		apresentaNomeOficina(50,6,'S');
		desenhaMoldura(linha,coluna,linha + (qtdProps * 10),133, PRETO, BRANCO);
		coluna++;
		linha++;
		gotoxy(coluna, linha);
		printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", "Nome", "CPF", "Telefone", "Descricao endereco", "Cidade", "Estado");
		for(cont = 0; cont < qtdProps; cont++) {
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", " ", " ", " ", " ", " ", "");
			linha++;
			gotoxy(coluna, linha);
			printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s | %-15.15s ", (proprietarios + cont)->nome, formataCPF((proprietarios + cont)->cpf),
			formataTelefone((proprietarios + cont)->telefone), proprietarios[cont].endereco.descricao, proprietarios[cont].endereco.cidade, proprietarios[cont].endereco.estado);
		}
		getch();
		if(proprietarios != NULL)
			free(proprietarios);
	}
}
//Objetivo: comparar dois nomes
//Parâmetros: dois endereços de memoria
//Retorno: 0, menor ou maior que zero
int comparaNome(const void *p1, const void *p2) {
	Proprietario *f1,*f2;
	
	f1 = (Proprietario *) p1;
	f2 = (Proprietario *) p2;	
	
	return stricmp(f1->nome,f2->nome); 
}
//Objetivo: apresentar veiculos de um proprietario que ja sofreu manutenção
//Parâmetros: nenhum
//Retorno: nenhum
void apresentaVeiculosManutencao() {
	FILE *arq;	
	int posicao, qtdDadosVeic, qtdDadosMan, cont, linha, coluna, resp, qtdManutencoesPro = 0, qtdVeiculosMan = 0;
	int flag = 0, posicaoRep, erro = 0;
	Proprietario proprietario;
	Veiculo veiculo, *veiculosManAux = NULL, *veiculosMan = NULL, *veiculos = NULL;
	Manutencao manutencao, *manutencoesPropAux = NULL, *manutencoesProp = NULL;
	char  **placas;
	FILE *arqMan, *arqVeic;
	
	linha = coluna = 10;
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM PROPRIETARIO");
	posicao = apresentaProprietarios();
	if(posicao != 0) {
		if(recuperaDadosProprietario(posicao, &proprietario) == 1) {
			apresentaNomeOficina(35,6,'S');
			gotoxy(11, 9);
			printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s   %-10.10s   %-7.7s ", 
			"Nome", "CPF", "Telefone", "Desc endereco", "Cidade", "Estado");
			desenhaMoldura(10, 10, 20, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaProprietario(proprietario);
			resp=menuSimNao("Deseja verificar dados?");
			switch(resp) {
				case 1:
					system("cls");
					if(verificaExisteManutencao(proprietario.cpf) != 0) {
						apresentaMsg("Proprietario nao possui nenhum veiculo que sofreu manutencao.");
					} else {
						arqMan = abreArquivo(ARQ_MANUTENCOES, "rb");
						if(arqMan != NULL) {
							
							while(!feof(arqMan)) {
								
								if(fread(&manutencao, sizeof(Manutencao), 1, arqMan) == 1) {
									if(strcmp(manutencao.cpfCliente, proprietario.cpf) == 0) {
										manutencoesPropAux = (Manutencao *)realloc(manutencoesProp, sizeof(Manutencao) * (qtdManutencoesPro + 1));
										if(manutencoesPropAux != NULL) {
											manutencoesProp = manutencoesPropAux;
											*(manutencoesPropAux + qtdManutencoesPro) = manutencao;
											qtdManutencoesPro++;
										}
									}	
								} 
							}
							fechaArquivo(arqMan);
						}
						if(qtdManutencoesPro != 0) {
							arqVeic = abreArquivo(ARQ_VEICULOS, "rb");
							if(arqVeic != NULL) {
								while(!feof(arqVeic)) {
									if(fread(&veiculo, sizeof(Veiculo), 1, arqVeic) == 1) {
										for(cont = 0; cont < qtdManutencoesPro; cont++) {
											if(stricmp((manutencoesProp + cont)->placa, veiculo.placa) == 0) {
												veiculosManAux = (Veiculo *)realloc(veiculosMan, sizeof(Veiculo) * (qtdVeiculosMan + 1));
												if(veiculosManAux != NULL) {
													veiculosMan = veiculosManAux;
													*(veiculosManAux + qtdVeiculosMan) = veiculo;
													qtdVeiculosMan++;
												}
												
											}
											
										}	
									}
								}
								fechaArquivo(arqVeic);
							}
							if(qtdVeiculosMan != 0) {
								if(qtdVeiculosMan > 1) {
									for(cont = 0; cont < qtdVeiculosMan; cont++) {
										if(stricmp((veiculosMan + cont)->placa, veiculosMan[cont + 1].placa) == 0) {
											posicaoRep = cont + 1;
											flag = 1;								
										}
									}
									if(flag == 1) {
										for(cont = posicaoRep; cont < qtdVeiculosMan; cont++) {
											*(veiculosMan + cont) = veiculosMan[cont + 1];
										}
										qtdVeiculosMan -= 1;
									}	
								}
								apresentaNomeOficina(35,6,'S');
								desenhaMoldura(linha, coluna, linha + (qtdVeiculosMan * 5) , 120, PRETO, BRANCO);
								linha++;
								coluna++;
								gotoxy(coluna, linha);
								printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ", "Fabricante", "Modelo", "Placa", "Chassi", "Ano fabricacao");
								for(cont = 0; cont < qtdVeiculosMan; cont++) {
									linha++;
									gotoxy(coluna, linha); 
									printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-20.20s ", " ", " ", " ", " ", " ");
									linha++;
									gotoxy(coluna, linha);
									printf("%-20.20s | %-15.15s | %-15s | %-20.20s | %-4d ", (veiculosMan + cont)->fabricante, (veiculosMan + cont)->modelo,
									formataPlaca((veiculosMan + cont)->placa), (veiculosMan + cont)->chassi, veiculosMan[cont].anoFabricacao.ano);							
								}
								getch();
								if(veiculosMan != NULL)
									free(veiculosMan);
								if(manutencoesProp != NULL)
									free(manutencoesProp);	
							}
						}
					}
					break;
				case 0:
					return;
			}
		}
	}
}
//Objetivo   : Gerenciar proprietarios
//Parâmetros : nenhum
//Retorno    : nenhum
void menuProprietarios() {
	char *menu[] = {"Adicionar proprietario", "Alterar proprietario","Excluir proprietario", "Voltar"}, opcao;
	
	do {
		system("cls");
		
		apresentaNomeOficina(40,7,'S');
		gotoxy(45,5);
        printf("PROPRIETARIOS");
		opcao = menuVertical(4, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
		switch(opcao) {
			case 1:
				cadastroProprietario();
				break;
			case 2:
				alteraProprietario();
				break;
			case 3:
				excluiProprietario();
				break;				
		}
	} while(opcao != 4 && opcao != 0);
}
//Objetivo: verificar se existe no arquivo de manutenções uma placa
//Parâmetros: endereço da placa
//Retorno: 0 caso exista 1 caso nao exista
int verificaExisteManutencaoCarro(char *placa) {
	Manutencao manutencao;
	FILE *arq;
	int flag = 1;
	
	if( (arq = abreArquivo(ARQ_MANUTENCOES, "rb")) != NULL) {
		while(!feof(arq)) {
			if(fread(&manutencao, sizeof(Manutencao), 1, arq) == 1) {
				if(memcmp(manutencao.placa, placa, TAM_PLACA) == 0) {
					flag = 0;
					break;
				}
			}
		}
	}
	
	return flag;
}
//Objetivo: verificar se existe no arquivo de manutenções
//Parâmetros: endereço de cpf
//Retorno: 0 caso exista 1 caso nao exista
int verificaExisteManutencao(char *cpf) {
	Manutencao manutencao;
	FILE *arq;
	int flag = 1;
	
	if( (arq = abreArquivo(ARQ_MANUTENCOES, "rb")) != NULL) {
		while(!feof(arq)) {
			if(fread(&manutencao, sizeof(Manutencao), 1, arq) == 1) {
				if(memcmp(manutencao.cpfCliente, cpf, TAM_CPF) == 0) {
					flag = 0;
					break;
				}
			}
		}
	}
	
	return flag;
}
//Objetivo: excluir proprietario
//Parâmetros: nenhum
//Retorno: nenhuhm
void excluiProprietario() {
	Proprietario proprietario;
	FILE *arq, *arqTemp;
	int posicao, cont = 0, flag = 1,resp;

	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM PROPRIETARIO PARA A EXCLUSAO");
	posicao = apresentaProprietarios();
	if(posicao != 0) {
		if(recuperaDadosProprietario(posicao, &proprietario) == 1) {
			if(verificaExisteManutencao(proprietario.cpf) == 0) {
				apresentaMsg("Proprietario nao pode ser excluido pois ja realizou manutencao.");
				return;
			}
			system("cls");
			gotoxy(11, 9);
			printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s   %-10.10s   %-7.7s ", 
			"Nome", "CPF", "Telefone", "Desc endereco", "Cidade", "Estado");
			desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaProprietario(proprietario);
			resp=menuSimNao("Deseja excluir prorpietario?");
			switch(resp) {
				case 1:
					system("cls");
					if((arq = abreArquivo(ARQ_PROPRIETARIOS, "rb")) != NULL) {
						if((arqTemp = abreArquivo("temp.txt", "wb")) != NULL) {
							while(fread(&proprietario, sizeof(Proprietario), 1, arq) == 1) {
								cont++;
								if(cont != posicao) {
									if(fwrite(&proprietario, sizeof(Proprietario), 1, arqTemp) != 1) {
										apresentaMsg("Erro ao gravar dados.");
										flag = 0;
										break;
									}
								}
							}
						} else {
							apresentaMsg("Nao foi possivel abrir o arquivo proprietarios.txt");
						    fclose(arq);
						  	return;
						} 
					}else {
						apresentaMsg("Nao foi possivel criar o arquivo proprietarios.txt");
					    fclose(arq);
					  	return;						
					}
					fechaArquivo(arq);
					fechaArquivo(arqTemp);
					break;
				case 0:
					return;
			}
		}
		if(flag == 1) {
			if(remove(ARQ_PROPRIETARIOS) == 0) {
				if(rename("temp.txt", ARQ_PROPRIETARIOS) != 0)
			        apresentaMsg("Erro ao renomear aquivo proprietarios.txt");
			    else
			    	apresentaMsg("Proprietario excluido com sucesso.");
			} else
				apresentaMsg("Erro ao remover aquivo proprietarios.txt");
		}
	}
}
//Objetivo: alterar dados do proprietario menos o codigo chave(cpf)
//Parametros: nenhum
//Retorno: nenhum
void alteraProprietario() {
	Proprietario proprietario;
	int posicao, qtdDados, opcaoMenu, opcaoEstado, flag, erro,resp;
	char  *msg, *menu[]={"Nome", "Endereco", "Telefone", "Voltar e salvar"};
	char *menuEstados[] = {"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS", "MG", 
	                       "PA", "PB", "PR", "PE", "PI", "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"};
	
	apresentaNomeOficina(35,3,'S');
	gotoxy(35,6);
	printf("ESCOLHA UM PROPRIETARIO");
	posicao = apresentaProprietarios();
	if(posicao != 0){
		if(recuperaDadosProprietario(posicao, &proprietario) == 1) {
			apresentaNomeOficina(35,6,'N');
			gotoxy(11, 9);
			printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s   %-10.10s   %-7.7s ", 
			"Nome", "CPF", "Telefone", "Desc endereco", "Cidade", "Estado");
			desenhaMoldura(10, 10, 16, 120, PRETO, BRANCO);
			gotoxy(11, 11);
			apresentaProprietario(proprietario);
			resp=menuSimNao("Deseja alterar dados ?");
			if(resp == 1) {
				system("cls");
				do{
					apresentaNomeOficina(35,6,'S');
					opcaoMenu = menuVertical(4, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
					switch(opcaoMenu) {
						apresentaNomeOficina(35,6,'N');
						case 1:
							leValidaTexto("Informe o novo nome: ", "*Nome invalido*", proprietario.nome, TAM_NOME, 11, 11);
							break;
						case 2:
							leValidaTexto("Informe a nova descricao do endereco: ", "*Descricao invalido*", proprietario.endereco.descricao, TAM_DESCRICAO_ENDERECO, 11, 11);
							apresentaNomeOficina(35,6,'N');
							leValidaTexto("Informe a nova cidade: ", "*Cidade invalida.*", proprietario.endereco.cidade, TAM_CIDADE, 11, 11);
							
							apresentaNomeOficina(35,7,'N');
							gotoxy(15,14);
							printf("Escolha o estado:");
							opcaoEstado = menuVertical(27, menuEstados, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
							
							*obtemEstado(opcaoEstado, proprietario.endereco.estado);
							break;
						case 3:
							do {
								apresentaNomeOficina(35,7,'N');
								flag = 0;
								leValidaTexto("Informe o novo telefone(com ddd) do proprietaio: ", "*Telefone invalido*", proprietario.telefone, TAM_TELEFONE, 11, 11);
								msg = validaTelefone(proprietario.telefone, &erro);
								if(erro == 0) {
									apresentaMsg(msg);
									flag = 1;
								}	
							} while(flag == 1);
					}
				} while(opcaoMenu != 4&& opcaoMenu != 0);
				
				gravaDadosProprietario(&proprietario, posicao);
			}
		}
	}
}
// Objetivo : ler os dados de um funcionario do arquivo
// parâmetros: numero do proprietario, endereco da variavel proprietario
// Retorno : 0- erro 1-sucesso
int recuperaDadosProprietario(int posicao, Proprietario *proprietario) {
	FILE *arq;
	int flag = 0;	
	
	if( (arq = abreArquivo(ARQ_PROPRIETARIOS, "rb")) != NULL) {
		if(fseek(arq, sizeof(Proprietario) * (posicao - 1), SEEK_SET) == 0) {
			if(fread(proprietario,sizeof(Proprietario), 1, arq) == 1) {
				apresentaMsg("Dados recuperados com sucesso.");
				flag = 1;
			} else
				apresentaMsg("Erro na leitura.");
		} else
			apresentaMsg("Erro no posicionamento do arquivo.");

		fechaArquivo(arq);
	}
	
	return flag;
} 
// Objeyivo : Gravar dados no arquivo
// parâmetros: endereco da variavel funcionarios, numero do funcionario
// Retorno : nenhum
void gravaDadosProprietario(Proprietario *proprietario, int posicao) {
	FILE *arq;
	
	if((arq = abreArquivo(ARQ_PROPRIETARIOS, "r+b")) != NULL){
		if(fseek(arq, sizeof(Proprietario) * (posicao - 1), SEEK_SET) == 0) { //Vai pra posição dentro do arquivo.
			if(fwrite(proprietario, sizeof(Proprietario), 1, arq) == 1) {
				apresentaMsg("Dados gravados com sucesso.");
			}else
				apresentaMsg("Erro ao escrever os dados no arquivo.");
		}else
			apresentaMsg("Erro ao posicionar os dados no arquivo.");
			
		fechaArquivo(arq);
	}
}
//Objetivo: apresentar os dados de um proprietario
//Parâmetros: variavel proprietario
//Retorno: nenhum
void apresentaProprietario(Proprietario proprietario) {
	printf("%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-10.10s | %-7.7s \n",proprietario.nome,formataCPF(proprietario.cpf), 
	formataTelefone(proprietario.telefone),proprietario.endereco.descricao, proprietario.endereco.cidade, proprietario.endereco.estado);
}
//Objetivo: apresentar funcionarios no menu
//Parâmetros: nenhum
//Retorno: opcao do menu
int apresentaProprietarios() {
	FILE *arq;
	Proprietario *proprietarios = NULL;
	int cont = 0, qtdDados = 0, opcao, aux;
	char **menu = NULL, dados[200];

	proprietarios = (Proprietario *)obtemDadosArquivo(ARQ_PROPRIETARIOS, sizeof(Proprietario), &qtdDados);
	menu = (char **) malloc(sizeof(char *) * (qtdDados));
	if(menu != NULL) {
		for(cont = 0; cont < qtdDados; cont++) {
			sprintf(dados, "%-20.20s | %-15.15s | %-15.15s | %-20.20s | %-10.10s | %-7.7s ", (proprietarios + cont)->nome, formataCPF((proprietarios + cont)->cpf),
			formataTelefone((proprietarios + cont)->telefone), proprietarios[cont].endereco.descricao, proprietarios[cont].endereco.cidade, proprietarios[cont].endereco.estado);
			*(menu + cont) = (char *) malloc(sizeof(char) * sizeof(dados));
			if(*(menu + cont) != NULL) {
				strcpy(*(menu + cont), dados);
			} else
				apresentaMsg("Erro ao alocar memoria para dados.");
		}
	} else{
		apresentaMsg("Erro ao alocar memoria.");
		opcao = 0;
	}
	
	if(menu != NULL) {
		if(qtdDados == 0) {
			apresentaMsg("Nao existem proprietarios cadastrados.");
			opcao = 0;
		} else {
			gotoxy(10, 8);
			printf("%-20.20s   %-15.15s   %-15.15s   %-20.20s   %-10.10s   %-7.7s ", 
			"Nome", "CPF", "Telefone", "Desc endereco", "Cidade", "Estado");
			opcao = menuVertical(qtdDados, menu, BRANCO, VERDE, 10, 10, 1, 1, PRETO, BRANCO);
		}
		for(cont = 0; cont < qtdDados; cont++) {
			free(*(menu + cont));
		}
		free(menu);
	}
	system("cls");
	
	return opcao;
}
//Objetivo: obter quantidade de dados presentes no arquivo
//Parâmetros: endereço do nome do arquivo e tamanho dos dados
//Retorno: quantidade de dados no arquivo
int obtemQtdDadosArquivo(char *nomeArquivo, int tamDados) {
	FILE *arq;
	int qtdDados;
	
	if( (arq = abreArquivo(nomeArquivo, "rb")) != NULL) {
		if(fseek(arq, 0, SEEK_END) == 0) {
			qtdDados = ftell(arq) / tamDados;
		}
		fechaArquivo(arq);
	}
	
	return qtdDados;
}
//Objetivo: obter dados do arquivo
//Parâmetros: endereco do nome do arquivo, tamanho dos dados e endereco da quantidade de dados
//Retorno: dados recuperado
void *obtemDadosArquivo(char *nomeArquivo, int tamDados, int *qtdDados) {
	FILE *arq;
	void *dados = NULL;
	
	*qtdDados=0;
	if( (arq = abreArquivo(nomeArquivo, "rb")) != NULL) {
		if(fseek(arq, 0, SEEK_END) == 0) {
			*qtdDados = obtemQtdDadosArquivo(nomeArquivo, tamDados);
			dados = (void *) malloc(*qtdDados * tamDados);
			rewind(arq);
			if(fread(dados, tamDados, *qtdDados, arq) != *qtdDados) {
				apresentaMsg("*Erro na leitura de dados.*");
				free(dados);
				dados=NULL;
				*qtdDados=0;
			} 
		}
		fechaArquivo(arq);
	}
	
	return dados;
}
//Objetiro: cadastrar proprietario
//Parâmetros: endereço do nome e modo de abertura do arquivo
//Retorno: nenhum
void cadastroProprietario() {
	FILE *arq;
	Proprietario proprietario;
	int flag, opcaoEstado, erro;
	char *msg, *menu[] = {"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS", "MG", "PA", "PB", 
						  "PR", "PE", "PI", "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO"};
	
	apresentaNomeOficina(35,7,'N');
	flag = 0;
	leValidaTexto("Informe o CPF do proprietario: ", "*CPF invalido.*", proprietario.cpf, TAM_CPF, 11, 11);
	if(validaCPF(proprietario.cpf) == 0) {
		apresentaMsg("*CPF no formato invalido.*");
	} else {
		if(validaCPFrepetido(proprietario.cpf) == 0) {
			apresentaMsg("*CPF repetido.*");	
		} else {
			apresentaNomeOficina(35,7,'N');
			leValidaTexto("Informe o nome do proprietaio: ", "*Nome invalido*", proprietario.nome, TAM_NOME, 11, 11);
			apresentaNomeOficina(35,7,'N');
			leValidaTexto("Informe a descricao do endereco do proprietaio: ", "*Descricao invalido*", proprietario.endereco.descricao, TAM_DESCRICAO_ENDERECO, 11, 11);
			apresentaNomeOficina(35,7,'N');
			leValidaTexto("Informe a cidade do proprietario: ", "*Cidade invalida.*", proprietario.endereco.cidade, TAM_CIDADE, 11, 11);
			apresentaNomeOficina(35,7,'n');
			gotoxy(15,14);
			printf("Escolha o estado:");
			opcaoEstado = menuVertical(27, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
			
			*obtemEstado(opcaoEstado, proprietario.endereco.estado);
			
			do {
				apresentaNomeOficina(35,7,'n');
				flag = 0;
				leValidaTexto("Informe o telefone(com ddd) do proprietaio: ", "*Telefone invalido*", proprietario.telefone, TAM_TELEFONE, 11, 11);
				msg = validaTelefone(proprietario.telefone, &erro);
				if(erro == 0) {
					apresentaMsg(msg);
					flag = 1;
				}	
			} while(flag == 1);
			
			
			arq = abreArquivo(ARQ_PROPRIETARIOS, "ab");
			if(arq != NULL) {
				desenhaMoldura(10, 10, 15, 70, PRETO, BRANCO);
				if( fwrite(&proprietario, sizeof(Proprietario), 1, arq) == 1 ) {
					apresentaMsg("Dados salvos com sucesso.");
				} else {
					apresentaMsg("Erro ao gravar dados no arquivo.");
				}		
				fechaArquivo(arq);
			} 				
		}
	}
}
//Objetivo   : Gerenciar veiculos
//Parâmetros :
//Retorno    :
void menuVeiculos() {
	char *menu[] = {"Adicionar veiculo", "Alterar veiculo", "Excluir veiculo", "Voltar"}, opcao;
	
	do {
		system("cls");
		apresentaNomeOficina(40,7,'S');
		gotoxy(45,5);
        printf("VEICULOS");
		opcao = menuVertical(4, menu, BRANCO, VERDE, 10, 40, 1, 1, PRETO, BRANCO);
		switch(opcao) {
			case 1:
				cadastraVeiculo();
				break;
			case 2:		
				 alteraVeiculo();			
				break;
			case 3:		
				excluiVeiculo();
				break;				
		}
	} while(opcao != 4 && opcao != 0);
}
//Objetivo   : cadastrar dados de veiculos
//Parâmetros : nenhum
//Retorno    : nenhum
void cadastraVeiculo() {
	FILE *arq;
	Veiculo veiculo;
	int flag;
	
	apresentaNomeOficina(35,3,'S');
	leValidaTexto("Informe a placa do veiculo: ", "*Placa invalida.*", veiculo.placa, TAM_PLACA, 10, 10);
	if(validaPlaca(veiculo.placa) == 0) {
		apresentaMsg("*Placa no formato invalido.*");
	} else {
		if(validaPlacaRepetida(veiculo.placa) == 0) {
			apresentaMsg("*Placa repetida.*");

		} else {
			do {
				apresentaNomeOficina(35,3,'N');
				leValidaTexto("Informe o chassi do veiculo: ", "*Chassi invalida.*", veiculo.chassi, TAM_CHASSI, 10, 10);
				if(strlen(veiculo.chassi) != 17) {
					gotoxy(11, 12);
					printf("O Chassi deve ter 17 digitos.");
				}
			} while(strlen(veiculo.chassi) != 17);
			apresentaNomeOficina(35,3,'N');
			leValidaTexto("Informe o modelo do veiculo: ", "*Modelo invalida.*", veiculo.modelo, TAM_MODELO, 10, 10);
			apresentaNomeOficina(35,3,'N');
			leValidaTexto("Informe o fabricante do veiculo: ", "*Fabricante invalida.*", veiculo.fabricante, TAM_FABRICANTE, 10, 10);
			apresentaNomeOficina(35,3,'N');
			leValidaInt("Informe o ano da fabricacao do veiculo: ", "*Ano invalido*", 1000, 3000, &veiculo.anoFabricacao.ano, 10, 10);
			
			arq = abreArquivo(ARQ_VEICULOS, "ab");
			if(arq != NULL) {
				desenhaMoldura(10, 10, 15, 70, PRETO, BRANCO);
				if( fwrite(&veiculo, sizeof(Veiculo), 1, arq) == 1 ) {
					apresentaMsg("Dados salvos com sucesso.");
				} else {
					apresentaMsg("Erro ao gravar dados no arquivo.");
				}		
				fechaArquivo(arq);
			} 
		}
	}
}
//Descricao : apresentar mensagem de erro          
//Parâmetros: msg                    
//Retorno   : nenhum                                          
void apresentaMsg(char *msg) {
   int colunaInicial;
   
   system("cls");
   colunaInicial = ((80 - strlen(msg)) / 2);
   desenhaMoldura(10, colunaInicial - 1, 15, (strlen(msg) + colunaInicial), PRETO, BRANCO);
   gotoxy(colunaInicial, 11);
   fprintf(stdout, "%s", msg);
   getch();
   system("cls");
}
// Objetivo: Ler uma opcao 
// Parâmetros: endereco de memoria  da string  mensagem, mensagem de erro e das opcoes validas e endereço da opcao
// Retorna: opcao valida
void leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas, char *opcao, int linha, int coluna) {
        
	do {
        gotoxy(coluna,linha);
		printf(msn);
		fflush(stdin);
		*opcao = toupper(getch());
		if(strchr(opcoesValidas, *opcao) == NULL) {
            gotoxy(coluna, linha + 1);
			printf("%s\n", msnErro);
			getch();
			gotoxy(coluna, linha + 1);
			printf("                                                                   ");
		}
	} while(strchr(opcoesValidas, *opcao) == NULL);
}
//Descricao : limpa uma janela da tela                       
//Parâmetros: linhaInicial - linha inicial da janela         
//            colunaInicial - coluna inicial da janela       
//     
//       linhaFinal   - linha final da janela           
//            colunaFinal - coluna final da janela           
//            corFundo - cor do fundo da janela a ser limpa  
//Retorno   : nenhum                                         
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, int colFinal,int corFundo) {
	int coluna=0,linha=0;

    for(coluna=colFinal;coluna>=colunaInicial;coluna--) {
        for(linha=linhaFinal;linha>=linhaInicial;linha--) {
            textbackground(corFundo);
            gotoxy(coluna,linha);
            printf(" ");

        }
    }
}
