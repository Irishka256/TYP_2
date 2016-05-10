#include "StdAfx.h"
#include "tree.h"
#include <iostream>
#include <string.h>

tree::tree(void){ //���������� ������ ����� ���� � ������� ������� � �������
	n = new node();
	up = NULL;
	left = NULL;
	right = NULL;
}
tree::tree(tree *u, tree *l, tree *r, node *data){ //���������� ������ ���� � ��������� ������� � �������
	n = data;
	up = u;
	left = l; //���������� ������
	right = r;
	memcpy(n,data,sizeof(node)); //���������� ������
}
void tree::set_left(node *data){ // ������� ������ ������� �� ������� ������� this
	tree *a = new tree(this,NULL,NULL,data); //����� �������
	left = a;								//������� this � ����� ��������
}
void tree::set_right(node *data){ // ������� ������� ������� �� ������� ������� this
	tree *a = new tree(this,NULL,NULL,data); //����� �������
	right = a;									//������� this � ����� ��������
}
tree *tree::find_up(char *id){ // ����� ������ � ������, ������� �� �������� ������� �� ��� ���� ����� �� ������
	tree *i = this;
	while (i != NULL){
		if (strcmp(i->n->id, id) == 0) break;
		i = i->up;
	}
	return i;
}
/*tree *tree::find_right_left(char *id){ //����� ������ �������� �������� �������
	tree *i = right;
	while (i != NULL){
		if (strcmp(i->n->id, id) == 0) break;
		i = i->left;
	}
	return i;
}*/
bool tree::sosed(char *id){
	tree *i = this;
	while (i != NULL){
		if (strcmp(i->n->id, id) == 0) return true;
		if (i->up != NULL && i->up->left == i) i = i->up;
		else break;
	}
	return false;
}

void tree::print(void){ //������
	std::cout << "�������������: " << (n->id) << " (";
	if (n->type == TypeInt) std::cout << "int";
	else if (n->type == TypeDouble) std::cout << "double";
	else std::cout << "��� ����";
	for (int i = 0; i<n->N; i++){//////////////////////////////////////////////////////////////////////////////////////
		std::cout << "[" << (n->hg[i]) << "]";
	}
	/*std::cout<<"������� � ������� "<<(n->id)<<" ("<<(n->type);
	for (int i=0;i<n->N;i++){//////////////////////////////////////////////////////////////////////////////////////
		std::cout<<"["<<(n->hg[i])<<"]";
	}*/
	std::cout<<")"<<std::endl;

	std::cout << "��������: ";
	if (n->type == TypeInt){
		std::cout << (n->value->datAsInt);
	}
	else if (n->type == TypeDouble){
		std::cout << (n->value->datAsDouble);
	}
	std::cout << std::endl;

	if (left != NULL) std::cout<<"����� ������ "<<(left->n->id)<<std::endl;
	if (right != NULL) std::cout<<"������ ������ "<<(right->n->id)<<std::endl;
	std::cout<<std::endl;
	if (left != NULL) left->print();
	if (right != NULL)right->print();
}

bool tree::sem_get_type(char *id, int line){
	tree *fnup = NULL;
	fnup = this->find_up(id);
	if (fnup == NULL){
		std::cout<<"������������� �� ��������: "<<id<<" � ������ "<<line<<std::endl;
		return false;
	}else if (fnup->n->is_type == false){
		std::cout<<"�� �������� �����: "<<id<<" � ������ "<<line<<std::endl;
		return false;
	}
	return true;
}

bool tree::sem_override(char *id, int line){
	if (this->sosed(id)){
		std::cout<<"���������������: "<<id<<" � ������ "<<line<<std::endl;
		return true;
	}
	return false;
}

bool tree::sem_var_declared(char *id, int line){
	tree *fnup = this->find_up(id);
	if (fnup == NULL){
		std::cout<<"������������� �� ��������: "<<id<<" � ������ "<<line<<std::endl;
		return false;
	}else if (fnup->n->is_type){
		//std::cout<<"�� �������� ����������: "<<id<<" � ������ "<<line<<std::endl;
		return false;
	}
	return true;
}

bool tree::sem_arr_rank(char *id, int r, int line){
	tree *nd = this->find_up(id);
	if (nd != NULL && r != nd->n->N){////////////////////////////////////////////////////////////////////////////////////////////////
		std::cout<<"���������� ��������� ������� �� ��������� � ������ "<<line<<std::endl;
		return true;
	}
	return false;
}

tree *tree::sem_add_var(char *id, char *type){
	int typ = -1;
	tree *fnup = NULL;
	if (strcmp(type, "int") == 0){
		typ = TypeInt;
	}
	else if (strcmp(type, "double") == 0){
		typ = TypeDouble;
	}
	else{
		fnup = this->find_up(type);
		if (fnup != NULL) typ = fnup->n->type;
	}
	set_left(new node(id,typ));
	if (fnup != NULL){
		left->n->N = fnup->n->N;
		for (int i=0;i<fnup->n->N;i++){
			left->n->hg[i] = fnup->n->hg[i];
		}
	}
	return left;
}

tree *tree::sem_add_type(char *id, char *type){
	int typ = -1;
	tree *fnup = NULL;
	if (strcmp(type, "int") == 0){
		typ = TypeInt;
	}
	else if (strcmp(type, "double") == 0){
		typ = TypeDouble;
	}
	else{
		fnup = this->find_up(type);
		if (fnup != NULL) typ = fnup->n->type;
	}
	set_left(new node(id,typ,true));
	if (fnup != NULL){
		left->n->N = fnup->n->N;
		for (int i=0;i<fnup->n->N;i++){
			left->n->hg[i] = fnup->n->hg[i];
		}
	}
	return left;
}

void tree::sem_set_dim(int hg, int line){
	if (this->n->N < MAX_N){
		this->n->hg[this->n->N] = hg;
		this->n->N++;
	}else 
		std::cout<<"���������� ��������� ������� ��������� "<<MAX_N<<" � ������ "<<line<<std::endl;
	
}

tree::~tree(void){}