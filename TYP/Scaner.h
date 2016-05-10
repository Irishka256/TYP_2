#ifndef __SCANER
#define __SCANER
#include "defs.h"

class TScaner{
private:
	TypeMod t; // исходный текст
	int uk; // указатель текущей позиции в исходном тексте
	int stroka;
public:
	void PutUK (int i);
	int GetUK (void);
	void PrintError(char *, char *);
	int Scaner (TypeLex l);
	void GetData(char *);
	TScaner(char *);
	void PutStroka (int i);
	int GetStroka  (void);
	~TScaner() {}
};
#endif
