#pragma once
#include "Defs.h"
#include <string.h>

struct TVal{
	int datAsInt;
	double datAsDouble;
	TVal(){}
};

struct node{
	char id[MAX_LEX]; // �������������
	char type; // �������� ����
	bool is_type; // ������� ����
	TVal *value;

	int N; // ����������� �������
	int hg[MAX_N]; // ������� ������� ���������

	node(){
		id[0]='*';
		id[1]='*';
		id[2]='*';
		id[3]='*';
		id[4]='*';
		id[5]='\0';
		type=-1;
		N=0;
		value = new TVal();
	}
	node(char *i){
		strcpy(id,i);
		type=-1;
		is_type=false;
		N=0;
		value = new TVal();
	}
	node(char *i,int t){
		strcpy(id,i);
		type = t;
		N=0;
		is_type=false;
		value = new TVal();
	}
	node(char *i, int t, bool it){
		strcpy(id,i);
		type = t;
		N=0;
		is_type=it;
		value = new TVal();
	}
};

class tree
{
public:
	node *n; // ������ �������
	tree *up, *left, *right; //�������� � �������
	//�-�� ��������� ��������� ������
	tree(void);
	tree(tree *u, tree *l, tree *r, node *data);
	void set_left(node *data); 
	void set_right(node *data); 
	tree *find_up(char *id);
	//tree *find_right_left(char *id);
	bool sosed(char *id);
	void print(void);

	//������������� ������������
	bool sem_get_type(char *id, int line); //��� OP,MS
	bool sem_override(char *id, int line); // ���������������� M,MS,HelpForOP
	bool sem_var_declared(char *id, int line); //���������� ���������� PR,V3
	bool sem_arr_rank(char *id, int r, int line); //���-�� ��������� �������
	
	tree *sem_add_var(char *id, char *type); //HelpForOP
	tree *sem_add_type(char *id, char *type); //MS
	void sem_set_dim(int hg, int line); //HelpForOP, MS

	~tree(void);
};