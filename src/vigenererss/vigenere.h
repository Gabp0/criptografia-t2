#ifndef __VRSS__
#define __VRSS__

#include <string>
#define String std::string
#define VinSize 95

char cryptChar(int t, int k);
char decryptChar(int t, int k);
String crypt(String plain, String key);
String decrypt(String chyper, String key);
String crypt(String plain, String key, int n);
String decrypt(String chyper, String key, int n);

#endif