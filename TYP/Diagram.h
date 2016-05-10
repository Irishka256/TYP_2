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
	void P(); //���������
	void OP(); //�������� ����������
	void MS(); //������
	void M(); //main
	void B(); //����
	void O(); //���������
	void O1(); //1 ��������
	void PR(); //������������
	void V(int *type, TVal *value); //���������
	void V1(int *type, TVal *value); //��������� 1
	void V2(int *type, TVal *value); //��������� 2
	void V3(int *type, TVal *value); //��������� 3
	void I(); //if
	void HelpForOP(char *type);
};
#endif