// TYP.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#include "Scaner.h"
#include "Diagram.h"
#include "Tree.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	TScaner * sc ;
	int type; TypeLex l;
	sc = new TScaner("input.txt");// ���� �� ���������
	TDiagram *dg = new TDiagram(sc);
	dg->P();
	/*type=sc->Scaner(l);
	if (type==TEnd) printf("�������������� ������ �� ����������\n");
	else sc->PrintError("������ ����� � ����� ���������","");*/
	//dg->tr->print();

	//std::cin.get();
	system("pause");
	return 0;
}

