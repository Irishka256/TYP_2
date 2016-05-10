#ifndef __DEFS
#define __DEFS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 10000 //���� ����� ������ ��
#define MAX_LEX 100 //���� ����� �������
#define MAX_KEYW 7 // ����� �������� ����
#define MAX_CONST 9 // 
#define MAX_N 8

#define LetterSmall ( (t[uk]>='a') && (t[uk]<='z') )
#define LetterBig ( (t[uk]>='A') && (t[uk]<='Z') )
#define Number ( (t[uk]>='0') && (t[uk]<='9') )

typedef char TypeMod[MAX_TEXT]; // ����� ��
typedef char TypeLex[MAX_LEX]; // �������

//��������������, ��������� � �������
#define TIdent 1
#define TConstInt10 2
#define TConstSymvol 3


//�������� �����
#define TInt 5
#define TDouble 6
#define TIf 7
#define TElse 8
#define TTypedef 9
#define TMain 4
#define TVoid 32


//����������� �����
#define TZap 10
#define TLSkob 11
#define TRSkob 12
#define TLFigScob 13
#define TRFigScob 14
#define TTochkaZap 15
#define TLKvScob 30
#define TRKvScob 31

//����� ��������
#define TPlusPlus 16
#define TMinusMinus 17
#define TBolshe 18
#define TBolsheRavno 19
#define TMenshe 20
#define TMensheRavno 21
#define TRavno 22
#define TNeRavno 23
#define TPlus 24
#define TMinus 25
#define TMul 26
#define TDiv 27
#define TMod 28
#define TPris 29

//����� ��������� ������
#define TEnd 100

//��������� ������
#define TError 101

#define TypeInt 33
#define TypeDouble 34

#endif