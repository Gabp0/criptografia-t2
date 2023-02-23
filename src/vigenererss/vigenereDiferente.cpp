#include "vigenereDiferente.h"
#include "common.h"
#include <string>
#include <iostream>

using namespace commonVigenereDiferente;

//Criptografa um char a partir de uma chave
char cryptCharDif(int t, int k) {
	return toAscii((fromAscii(t) + fromAscii(k)) % VinDifSize);
}

//Decriptografa um char a partir de uma chave
char decryptCharDif(int t, int k) {
	k = fromAscii(k);
	t = fromAscii(t);

	int r;
	int c = k - t;
	if (c < 0)
		c = c * -1;

	r = c;
	if (k > t) {
		r = VinDifSize - k;
		r = r + t;
	}

	return toAscii(r % VinDifSize);
}

//Criptografa uma string a partir de uma chave
String cryptDif(String plain, String key) {
	key.append(plain);
	String s;
	for (char t : plain) {
		int i = 0;
		s += cryptCharDif(t, key[i]);
		i++;
	}
	return s;
}

//Decriptografa uma string a partir de uma chave
String decryptDif(String cypher, String key) {
	String s;
	char r;
	for (char t : cypher) {
		int i = 0;
		r = decryptCharDif(t, key[i]);
		s += r;
		key += r;
		i++;
	}
	return s;
}

String cryptDiferente(String plain) {
	String key = "nerfthis";
	plain.append("hs ahead");
	String subplain;
	for (int i = 0; i < 3; i++) {
		subplain = plain.substr(plain.size() - key.size(), key.size());
		plain = cryptDif(plain, key);
		key = cryptDif(key, subplain);
	}
	return plain;
}


String decryptDiferente(String cypher) {
	cypher = decryptDif(cypher, "rivjxlmw");
	if(cypher.size() >= 8){
	cypher.erase(cypher.size() - 8, 8);
	}
	return cypher;
}