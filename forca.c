#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");	
}

void chuta() {
    char chute;
	
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;

	chutesdados++;
}
int jachutou(char letra) {
	int achou = 0;
	for (int j = 0; j < chutesdados; j++) {
		if(chutes[j] == letra) { 
			achou = 1;
			break;
		} 
	}	
	return achou;
}

void desenhaforca() {
	int erros = chuteserrados();

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
		(erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
		(erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), 
		(erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	for (int i = 0; i < strlen(palavrasecreta); i++) {

		int achou = jachutou(palavrasecreta[i]);

		if(achou) {
			printf("%c ", palavrasecreta[i]);
		} else {
			printf("_ ");
		}		
	}
	printf("\n");
}

void adicionapalavra() {
	char quer;

	printf("Voce deseja adicionar uma nova palavra no jogo? (S/N) ");
	scanf(" %c", &quer);

	if(quer == 'S') {
		char novapalavra[20];

		printf("Qual a nova palavra? ");
		scanf("%s", novapalavra);

		FILE* f;

		f = fopen("palavras.txt", "r+");
		if(f == 0) {
			printf("Banco de dados de palavras nao disponivel");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		
		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);
	}
}

void escolhepalavra() {
	FILE* f; 

	f = fopen("palavras.txt", "r");
	
	if(f == 0) {
		printf("Banco de dados de palavras não disponível");
		exit(1);
	}

	int qtdpalavras;
	fscanf(f, "%d", &qtdpalavras);

	srand(time(0));
	int randomico = rand() % qtdpalavras;

	for(int i = 0; i < randomico; i++) {
		fscanf(f, "%s", palavrasecreta);
	}

	fclose(f);
}

int chuteserrados() {
	int erros = 0;
	for(int i = 0; i < chutesdados; i++) {
		int existe = 0;

		for(int j = 0; j < strlen(palavrasecreta); j++) {
			if(chutes[i] == palavrasecreta[j]) {
				existe = 1;
				break;
			}
		}
		if(!existe) erros++;
	}

	return erros;
}

int enforcou() {

	return chuteserrados() >= 5;

}

int ganhou() {
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}

	return 1;
}

int main() {
	escolhepalavra();
	abertura();

	do {

		desenhaforca();
		chuta();

	} while(!ganhou() && !enforcou());

	if(ganhou()) {
    printf("\nParabens, voce ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

} else {
    printf("\nPuxa, voce foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
}
	adicionapalavra();

	return 0;
}