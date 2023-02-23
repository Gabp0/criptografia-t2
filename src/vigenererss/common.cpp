#include "common.h"

//Deslocamento para 95 caracteres
int commonVigenereNormal::fromAscii(char t) {
	return t - 32;
}

//Deslocamento para 95 caracteres
char commonVigenereNormal::toAscii(int t) {
	return t + 32;
}

//Deslocamento para 37 caracteres, lendo letras maiscula e codificando como minusculas
int commonVigenereDiferente::fromAscii(char t) {
	switch (t) {
	case ' ':
		return 26;
		break;
	case '.':
		return 27;
		break;
	default:
		if (t >= 97)
			return t - 97;
		return t - 65;
	}
}

//Deslocamento para 37 caracteres
char commonVigenereDiferente::toAscii(int t) {
	switch (t) {
	case 26:
		return ' ';
		break;
	case 27:
		return '.';
		break;
	default:
		if (t <= 97)
			return t + 97;
		return t + 65;
	}
}