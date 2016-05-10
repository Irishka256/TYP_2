#ifndef __DIAGRAM
#define __DIAGRAM
#include "tree.h"
class TDiagram
{
private:
	TScaner *sc;
	bool flagInt;
public:
	tree *tr;
	tree *pt;
	TDiagram(void){ pt = tr = new tree(); flagInt = 1; };
	TDiagram(TScaner *s){ sc = s; pt = tr = new tree(); flagInt = 1; };
	~TDiagram(){}
	void P(); //программа
	void OP(); //описание переменных
	void MS(); //массив
	void M(); //main
	void B(); //блок
	void O(); //операторы
	void O1(); //1 оператор
	void PR(); //присваивание
	void V(int *type, TVal *value); //выражение
	void V1(int *type, TVal *value); //выражение 1
	void V2(int *type, TVal *value); //выражение 2
	void V3(int *type, TVal *value); //выражение 3
	void I(); //if
	void HelpForOP(char *type);
};
#endif