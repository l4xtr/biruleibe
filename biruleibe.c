#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Personagem{
	char nome[50];
	float forca;
}TPersonagem;

typedef struct anjo{
	char nome[50];
	float cap_voo;
	float peso;
	float alt;
	float forca; // salva força apos calc
}TAnjo;

typedef struct humano{
	char nome[50];
	float forca;
}THumano;

typedef struct demonio{
	char nome[50];
	float den_esc;
	float visao;
	float forca; // salva força apos calc
}TDemonio;

typedef struct cidadeAnjo{
	char nome[30];
	int num_hab;
	TAnjo *habitantes;
	float forca;
}TCidadeAnjo;

typedef struct cidadeHumano{
	char nome[30];
	int num_hab;
	THumano *habitantes;
	float forca;
}TCidadeHumano;

typedef struct cidadeDemonio{
	char nome[30];
	int num_hab;
	TDemonio *habitantes;
	float forca;
}TCidadeDemonio;

typedef struct mundoAnjo{
	int num_cidades;
	TCidadeAnjo *cidades;
}TMundoAnjo;

typedef struct mundoHumano{
	int num_cidades;
	TCidadeHumano *cidades;
}TMundoHumano;

typedef struct mundoDemonio{
	int num_cidades;
	TCidadeDemonio *cidades;
}TMundoDemonio;

TMundoAnjo *lerAnjos(){
	FILE *arq;
	int i, j;
	
	arq = fopen("anjos.txt","r");
	
	if(arq != NULL){
		TMundoAnjo *mundo = (TMundoAnjo*) calloc (1,sizeof(TMundoAnjo)); // aloca o mundo dos anjos

		fscanf(arq,"%d",&mundo->num_cidades);	// armazeno o numero de cidades 
		
		mundo->cidades = (TCidadeAnjo*) calloc (mundo->num_cidades,sizeof(TCidadeAnjo)); // aloca o vetor de cidades do mundo dos anjos
		
		for(i = 0; i < mundo->num_cidades; i++){
			fscanf(arq,"%s\t%d",&mundo->cidades[i].nome,&mundo->cidades[i].num_hab); // armazena o nome da cidade e a quantidade de habitantes
			
			mundo->cidades[i].forca = 0; // inicia a força da cidade como 0 (ZERO)
			
			mundo->cidades[i].habitantes = (TAnjo*) calloc (mundo->cidades[i].num_hab,sizeof(TAnjo));	// aloca o vetor de habitantes da cidade
			
			for(j = 0; j < mundo->cidades[i].num_hab; j++){
				fscanf(arq,"\t%s\t%f\t%f\t%f",&mundo->cidades[i].habitantes[j].nome,&mundo->cidades[i].habitantes[j].cap_voo,&mundo->cidades[i].habitantes[j].peso,&mundo->cidades[i].habitantes[j].alt); // armazena cada habitante da cidade
			}
		}
		
		fclose(arq); // fecha o arquivo
		
		return mundo;
	}else{
		printf("\nArquivo nao existe!");
		
		return NULL;
	}
}

TMundoHumano *lerHumanos(){
	FILE *arq;
	int i, j;
	
	arq = fopen("humanos.txt","r");
	
	if(arq != NULL){
		TMundoHumano *mundo = (TMundoHumano*) calloc (1,sizeof(TMundoHumano)); // aloca o mundo dos anjos

		fscanf(arq,"%d",&mundo->num_cidades);	// armazeno o numero de cidades 
		
		mundo->cidades = (TCidadeHumano*) calloc (mundo->num_cidades,sizeof(TCidadeHumano)); // aloca o vetor de cidades do mundo dos anjos
		
		for(i = 0; i < mundo->num_cidades; i++){
			fscanf(arq,"%s\t%d",&mundo->cidades[i].nome,&mundo->cidades[i].num_hab); // armazena o nome da cidade e a quantidade de habitantes
			
			mundo->cidades[i].forca = 0; // inicia a força da cidade como 0 (ZERO)
			
			mundo->cidades[i].habitantes = (THumano*) calloc (mundo->cidades[i].num_hab,sizeof(THumano));	// aloca o vetor de habitantes da cidade
			
			for(j = 0; j < mundo->cidades[i].num_hab; j++){
				fscanf(arq,"\t%s\t%f",&mundo->cidades[i].habitantes[j].nome,&mundo->cidades[i].habitantes[j].forca); // armazena cada habitante da cidade
			}
		}
		
		fclose(arq); // fecha o arquivo
		
		return mundo;
	}else{
		printf("\nArquivo nao existe!");
		
		return NULL;
	}
}

TMundoDemonio *lerDemonios(){
	FILE *arq;
	int i, j;
	
	arq = fopen("demonios.txt","r");
	
	if(arq != NULL){
		TMundoDemonio *mundo = (TMundoDemonio*) calloc (1,sizeof(TMundoDemonio)); // aloca o mundo dos anjos

		fscanf(arq,"%d",&mundo->num_cidades);	// armazeno o numero de cidades 
		
		mundo->cidades = (TCidadeDemonio*) calloc (mundo->num_cidades,sizeof(TCidadeDemonio)); // aloca o vetor de cidades do mundo dos anjos
		
		for(i = 0; i < mundo->num_cidades; i++){
			fscanf(arq,"%s\t%d",&mundo->cidades[i].nome,&mundo->cidades[i].num_hab); // armazena o nome da cidade e a quantidade de habitantes
			
			mundo->cidades[i].forca = 0; // inicia a força da cidade como 0 (ZERO)
			
			mundo->cidades[i].habitantes = (TDemonio*) calloc (mundo->cidades[i].num_hab,sizeof(TDemonio));	// aloca o vetor de habitantes da cidade
			
			for(j = 0; j < mundo->cidades[i].num_hab; j++){
				fscanf(arq,"\t%s\t%f\t%f\t%f",&mundo->cidades[i].habitantes[j].nome,&mundo->cidades[i].habitantes[j].den_esc,&mundo->cidades[i].habitantes[j].visao); // armazena cada habitante da cidade
			}
		}
		
		fclose(arq); // fecha o arquivo
		
		return mundo;
	}else{
		printf("\nArquivo nao existe!");
		
		return NULL;
	}
}

void calcForcaCidadesAnjos(TMundoAnjo *mundo){
	int i, j;
	
	// calcula as forças das cidades
	for(i = 0; i < mundo->num_cidades; i++){
		for(j = 0; j < mundo->cidades[i].num_hab; j++){
			mundo->cidades[i].forca = mundo->cidades[i].forca + (mundo->cidades[i].habitantes[j].cap_voo * pow(mundo->cidades[i].habitantes[j].alt,2) * mundo->cidades[i].habitantes[j].peso);
		}
	}
	
	printf("--- ANJOS ---\n");
	// exibe as forças das cidades
	for(i = 0; i < mundo->num_cidades; i++){
		printf("%s tem forca de %.2f\n\n",mundo->cidades[i].nome,mundo->cidades[i].forca);
	}
}

void calcForcaCidadesHumano(TMundoHumano *mundo){
	int i, j;
	
	// calcula as forças das cidades
	for(i = 0; i < mundo->num_cidades; i++){
		for(j = 0; j < mundo->cidades[i].num_hab; j++){
			mundo->cidades[i].forca = mundo->cidades[i].forca + (mundo->cidades[i].habitantes[j].forca);
		}
	}
	
	printf("--- Humanos ---\n");
	// exibe as forças das cidades
	for(i = 0; i < mundo->num_cidades; i++){
		printf("%s tem forca de %.2f\n\n",mundo->cidades[i].nome,mundo->cidades[i].forca);
	}
}

void calcForcaCidadesDemonios(TMundoDemonio *mundo){
	int i, j;
	
	// calcula as forças das cidades
	for(i = 0; i < mundo->num_cidades; i++){
		for(j = 0; j < mundo->cidades[i].num_hab; j++){
			mundo->cidades[i].forca = mundo->cidades[i].forca + pow(mundo->cidades[i].habitantes[j].den_esc - (mundo->cidades[i].habitantes[j].visao/2),2);
		}
	}
	
	printf("--- Demonios ---\n");
	// exibe as forças das cidades
	for(i = 0; i < mundo->num_cidades; i++){
		printf("%s tem forca de %.2f\n\n",mundo->cidades[i].nome,mundo->cidades[i].forca);
	}
}

void calcForcaHabAnjo(TMundoAnjo *mundo){
	int i, j ;
	
	// forçca anjo
	for(i = 0; i < mundo->num_cidades; i++){
		for(j = 0; j < mundo->cidades[i].num_hab; j++){
			mundo->cidades[i].habitantes[j].forca = (mundo->cidades[i].habitantes[j].cap_voo * pow(mundo->cidades[i].habitantes[j].alt,2) * mundo->cidades[i].habitantes[j].peso);
		}
	}
}

void calcForcaHabDem(TMundoDemonio *mundo){
	int i, j ;
	
	// forçca demonio
	for(i = 0; i < mundo->num_cidades; i++){
		for(j = 0; j < mundo->cidades[i].num_hab; j++){
			mundo->cidades[i].habitantes[j].forca = pow((mundo->cidades[i].habitantes[j].den_esc - (mundo->cidades[i].habitantes[j].visao / 2)),2);
		}
	}
}

void calcForcaLetraA(TMundoAnjo m1, TMundoHumano m2, TMundoDemonio m3){
	int i, j, k, qtd;
	float soma = 0.0;
	
	// força dos individiduos anjos
	for(i = 0; i < m1.num_cidades; i++){
		for(j = 0; j < m1.cidades[i].num_hab; j++){
			qtd = 0;
			
			for(k = 0; k < strlen(m1.cidades[i].habitantes[j].nome); k++){
				if(m1.cidades[i].habitantes[j].nome[k] == 'a' || m1.cidades[i].habitantes[j].nome[k] == 'A'){	// verifica se o individuo tem letra a ou A no nome
					qtd++;
				}
			}
			
			if(qtd == 2){	// se houver mais de duas letras a, soma a força do anjo[i] com as duas letras no nome com a soma atual das forças de nomes com letras a
				soma = soma + m1.cidades[i].habitantes[j].forca;
			}
		}
	}
	
	// força dos individuos humano
	for(i = 0; i < m2.num_cidades; i++){
		for(j = 0; j < m2.cidades[i].num_hab; j++){
			qtd = 0;
			
			for(k = 0; k < strlen(m2.cidades[i].habitantes[j].nome); k++){
				if(m2.cidades[i].habitantes[j].nome[k] == 'a' || m2.cidades[i].habitantes[j].nome[k] == 'A'){	// verifica se o individuo tem letra a ou A no nome
					qtd++;
				}
			}
			
			if(qtd == 2){	// se houver mais de duas letras a, soma a força do humano[i] com as duas letras no nome com a soma atual das forças de nomes com letras a
				soma = soma + m2.cidades[i].habitantes[j].forca;
			}
		}
	}
	
	
	for(i = 0; i < m3.num_cidades; i++){
		for(j = 0; j < m3.cidades[i].num_hab; j++){
			qtd = 0;
			
			for(k = 0; k < strlen(m3.cidades[i].habitantes[j].nome); k++){
				if(m3.cidades[i].habitantes[j].nome[k] == 'a' || m3.cidades[i].habitantes[j].nome[k] == 'A'){	// verifica se o individuo tem letra a ou A no nome
					qtd++;
				}
			}
			
			if(qtd == 2){	// se houver mais de duas letras a, soma a força do demonio[i] com as duas letras no nome com a soma atual das forças de nomes com letras a
				soma = soma + m3.cidades[i].habitantes[j].forca;
			}
		}
	}
	
	printf("\nA soma das forcas dos individuos com 2 letras 'a' no nome e %.2f\n\n",soma);
}

void calcForcaOrdemCrescente(TMundoAnjo ma, TMundoHumano mb, TMundoDemonio mc){
	
	
	float somama, somamb, somamc;
	int i;
	
	for(i = 0; i < ma.num_cidades; i++){
		somama += ma.cidades[i].forca;	
	}
	for(i = 0; i < mb.num_cidades; i++){
		somamb += mb.cidades[i].forca;	
	}
	for(i = 0; i < mc.num_cidades; i++){
		somamc += mc.cidades[i].forca;	
	}
	
	if(somama > somamb)                                          
        if(somamb > somamc) printf("Ordem de forca e: Anjos , Humanos , Demonios");   
		else    										
            if(somama > somamc) printf("Ordem de forca e: Anjos, Demonios , Humanos");   
           	else printf("Ordem de forca e: Demonios, Anjos, Humanos");         
    else                                                
        if (somamb > somamc)                                       
            if (somama > somamc) printf("Ordem de forca e: Humanos, Anjos, Demonios");  
            else printf("Ordem de forca e: Humanos, Demonios, Anjos");        
        else printf("Ordem de forca e: Demonios, Humanos, Anjos");          
}

void imprime(TPersonagem *vet, int n){ // (Só pra testar)
	int i;
	
	for(i = 0; i < n; i++){
		if(vet[i].forca != 0){
			printf("%s, ",vet[i].nome);
		}
	}
} 

void ordernarVetor(TPersonagem *vetor, int tam){
	int i, j;  
	TPersonagem key;
	
	for (i = 1; i < tam; i++) {  
        key = vetor[i];  
        j = i - 1;  

        while ((j >= 0) && (vetor[j].forca > key.forca)) {  
            vetor[j + 1] = vetor[j];  
            j = j - 1;  
        }  
        vetor[j + 1] = key;  
    }  

}

void calcForcaMaisForteFraco(TMundoAnjo ma, TMundoHumano mb, TMundoDemonio mc){
	int i, j, z, num_hab;
	TPersonagem *vetPersonagens, *vetAux;
	num_hab = 0; // total habitantes dos tres mundos
	z = 0; // posição inicial do vetor Forças
	
	// numero hab mundo anjos
	for(i = 0; i < ma.num_cidades; i++){
		num_hab = num_hab + ma.cidades[i].num_hab;
	}
	
	// numero hab mundo huma
	for(i = 0; i < mb.num_cidades; i++){
		num_hab = num_hab + mb.cidades[i].num_hab;
	}
	
	// numero hab mundo demo
	for(i = 0; i < mc.num_cidades; i++){
		num_hab = num_hab + mc.cidades[i].num_hab;
	}
	
	// alocação do vetorForças
	vetPersonagens = (TPersonagem*) calloc(num_hab,sizeof(TPersonagem));
	vetAux = (TPersonagem*) calloc(num_hab,sizeof(TPersonagem));
	
	// pegando as forças dos habitantes anjos
	for(i = 0; i < ma.num_cidades; i++){
		for(j = 0; j < ma.cidades[i].num_hab; j++){
			strcpy(vetPersonagens[z].nome,ma.cidades[i].habitantes[j].nome); // copio o nome do anjo
			vetPersonagens[z].forca = ma.cidades[i].habitantes[j].forca;
			z++;
		}
	}
	
	// pegando as forças dos habitantes hum
	for(i = 0; i < mb.num_cidades; i++){
		for(j = 0; j < mb.cidades[i].num_hab; j++){
			strcpy(vetPersonagens[z].nome,mb.cidades[i].habitantes[j].nome); // copio o nome do anjo
			vetPersonagens[z].forca = mb.cidades[i].habitantes[j].forca;
			z++;
		}
	}
	
	// pegando as forças dos habitantes demo
	for(i = 0; i < mc.num_cidades; i++){
		for(j = 0; j < mc.cidades[i].num_hab; j++){
			strcpy(vetPersonagens[z].nome,mc.cidades[i].habitantes[j].nome); // copio o nome do anjo
			vetPersonagens[z].forca = mc.cidades[i].habitantes[j].forca;
			z++;
		}
	}
	
	
	// ordenrar as forças
	ordernarVetor(vetPersonagens,num_hab);
	
	//imprime(vetPersonagens,num_hab);
	
	// incializa variaveis
	j = 0; 
	
	// percorrendo pra saber os mais fortes
	for(i = num_hab - 1; i >= 0; i--){
		// adiciona o primeiro personagem, pois ele ja é o mais forte
		if( i == num_hab - 1){
			vetAux[j] = vetPersonagens[i];
			j++;
		}else if(vetPersonagens[i].forca == vetPersonagens[i+1].forca){
			vetAux[j] = vetPersonagens[i];
			j++;
		}else{
			break;
		}
	}
	
	printf("\n\nOs seres mais fortes sao: ");
	imprime(vetAux,num_hab);
	
	// incializa variaveis
	j = 0; 
	memset(vetAux,0,num_hab * sizeof(TPersonagem)); // reseta a vetAux
	
	// percorrendo pra saber os mais fracos
	for(i = 0; i < num_hab; i++){
		// adiciona o primeiro personagem, pois ele ja é o mais fraco
		if(i == 0){
			vetAux[j] = vetPersonagens[i];
			j++;
		}else if(vetPersonagens[i].forca == vetPersonagens[i-1].forca){
			vetAux[j] = vetPersonagens[i];
			j++;
		}else{
			break;
		}
	}
	
	printf("\n\nOs seres mais fracos sao: ");
	imprime(vetAux,num_hab);
}

int main(){
	
	
	TMundoAnjo *mundoAnjos = lerAnjos();
	TMundoHumano *mundoHumanos = lerHumanos();
	TMundoDemonio *mundoDemonios = lerDemonios();
	
	// calcula força das ciddades
	calcForcaCidadesAnjos(mundoAnjos);
	calcForcaCidadesHumano(mundoHumanos);
	calcForcaCidadesDemonios(mundoDemonios);
	
	// calcula força dos habitantes
	calcForcaHabAnjo(mundoAnjos);
	calcForcaHabDem(mundoDemonios);
	
	calcForcaLetraA(*mundoAnjos,*mundoHumanos,*mundoDemonios);
	
	calcForcaOrdemCrescente(*mundoAnjos,*mundoHumanos,*mundoDemonios);
	
	calcForcaMaisForteFraco(*mundoAnjos,*mundoHumanos,*mundoDemonios);
	
	
	return(0);
}
