#include "stdafx.h"
#include "Defs.h"
#include "Scaner.h"
#include "Diagram.h"
#include <iostream>	

void TDiagram::P(){
	//программа
	TypeLex l; int t,uk1,str;
	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l); sc->PutUK(uk1); sc->PutStroka(str);
	while (t==TTypedef||t==TInt||t==TDouble||t==TIdent/*||t==TMain*/||t==TVoid)
	{
		if (t==TTypedef) {sc->PutUK(uk1); sc->PutStroka(str); MS();}
		else if (t==TDouble||t==TIdent||t==TInt){sc->PutUK(uk1); sc->PutStroka(str); OP();}
		else if (t==TVoid||t==TIdent||t==TInt)  {sc->PutUK(uk1); sc->PutStroka(str); M();}
		uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);// sc->PutUK(uk1);
	}
}

void TDiagram::HelpForOP(char *type){
	int typ = -1;

	TypeLex l; int t, uk1, str;

	if (strcmp(type, "int") == 0){
		typ = TypeInt;
	}
	else if (strcmp(type, "double") == 0){
		typ = TypeDouble;
	}
	else{
		if (flagInt){
			tree *fnup = pt->find_up(type);
			if (fnup != NULL) typ = fnup->n->type;
		}
	}

	/*tree *fnup = pt->find_up(type);
	if (fnup != NULL) type = fnup->n->type;*/

	do{

		bool flag = false;

		t=sc->Scaner(l);
		if (t!=TIdent) 
			sc->PrintError("Ожидался идентификатор",l);
		else{
			if (flagInt){
				if (!pt->sem_override(l, str = sc->GetStroka())){
					pt = pt->sem_add_var(l, type);
					std::cout << "Объявлена переменная " << l << std::endl;
					//flag = true;//////////////////// для N      мб надо?????????????????
				}
			}
		}

		if (flag) pt->sem_set_dim(atoi(l),str=sc->GetStroka());

		uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
		if(t==TPris){
			/*t=sc->Scaner(l);
			if (t!=TConstInt10&&t!=TLFigScob) 
				sc->PrintError("Ожидалась константа или массив",l);
			else if (t==TLFigScob){
				MS();
				t=sc->Scaner(l);
				if (t!=TRFigScob) 
					sc->PrintError("Ожидался символ }",l);
			}
			uk1=sc->GetUK(); 
			str=sc->GetStroka();
			t=sc->Scaner(l);*/

			// новое
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			int VyrType;
			TVal VyrVal;
			V(&VyrType, &VyrVal);
			if (flagInt){
				if (VyrType == TypeInt){
					if (pt->n->type == TypeInt){
						pt->n->value->datAsInt = VyrVal.datAsInt;
					}
					else if (pt->n->type == TypeDouble){
						pt->n->value->datAsDouble = VyrVal.datAsInt;
					}
					std::cout << (pt->n->id) << " = " << (VyrVal.datAsInt) << std::endl;
				}
				else if (VyrType == TypeDouble){
					if (pt->n->type == TypeInt){
						pt->n->value->datAsInt = VyrVal.datAsDouble;
					}
					else if (pt->n->type == TypeDouble){
						pt->n->value->datAsDouble = VyrVal.datAsDouble;
					}
					std::cout << (pt->n->id) << " = " << (VyrVal.datAsDouble) << std::endl;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//V();
			uk1 = sc->GetUK();
			str = sc->GetStroka();
			t = sc->Scaner(l);
		}
		else if (t == TLKvScob){
			int size = 1;
			do{
				t = sc->Scaner(l);
				if (t != TConstInt10){
					sc->PrintError("Ожидалась константа в строке", l);
					break;
				}

				int dim = atoi(l);
				if (flagInt){
					if (flag) pt->sem_set_dim(atoi(l), str = sc->GetStroka());
				}
				size *= dim;
				t = sc->Scaner(l);
				if (t != TRKvScob){
					sc->PrintError("Ожидалась закрывающая квадратная скобка в строке", l);
				}
				uk1 = sc->GetUK();
				t = sc->Scaner(l);
				sc->PutUK(uk1);
				if (t != TLKvScob) break;
				sc->Scaner(l);
			} while (true);
			if (flagInt) pt->n->value = (TVal *)malloc(size*sizeof(TVal));
			uk1 = sc->GetUK();
			str = sc->GetStroka();
			t = sc->Scaner(l);
		}
	}while(t==TZap);
	sc->PutUK(uk1);
	sc->PutStroka(str);
}

void TDiagram::OP(){
	//описание переменных
	TypeLex l; int t, uk1, str;
	char typebuf[MAX_LEX];
	typebuf[0]='\0';
	char* type2;
	
	t=sc->Scaner(l);
	if (t!=TInt&&t!=TDouble&&t!=TIdent) 
		sc->PrintError("Ожидался int, double или идентификатор",l);
	else{
		if (t == TIdent){
			if (flagInt) pt->sem_get_type(l, str = sc->GetStroka());
		}
		strcpy(typebuf,l);
	}

	HelpForOP(typebuf);
	/*tree *fnup = pt->find_up(type);
	if (fnup != NULL) 
		type2 = fnup->n->type; */
	//HelpForOP(typebuf);
	/*type2=HelpForOP(typebuf);

	do{

		bool flag = false;

		t=sc->Scaner(l);
		if (t!=TIdent) 
			sc->PrintError("Ожидался идентификатор",l);
		else{
			if (!pt->sem_override(l, str=sc->GetStroka())){
				pt = pt->sem_add_var(l,type2);
				flag = true;
			}
		}

		if (flag) pt->sem_set_dim(atoi(l),str=sc->GetStroka());

		uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
		if(t==TPris){
			t=sc->Scaner(l);
			if (t!=TConstInt10&&t!=TLFigScob) 
				sc->PrintError("Ожидалась константа или массив",l);
			else if (t==TLFigScob){
				MS();
				t=sc->Scaner(l);
				if (t!=TRFigScob) 
					sc->PrintError("Ожидался символ }",l);
			}
			uk1=sc->GetUK(); 
			str=sc->GetStroka();
			t=sc->Scaner(l);
		}
	}while(t==TZap);
	sc->PutUK(uk1);
	sc->PutStroka(str);*/
	t=sc->Scaner(l);
	if (t!=TTochkaZap) sc->PrintError("Ожидался символ ;",l);
}

void TDiagram::MS(){
	//массив
	TypeLex l; int t, uk1, str;
	t=sc->Scaner(l);
	if (t!=TTypedef) sc->PrintError("Ожидался спецификатор typedef",l);

	char typebuf[MAX_LEX];
	typebuf[0] = '\0';

	t=sc->Scaner(l);
	if (t!=TInt&&t!=TDouble&&t!=TIdent) 
		sc->PrintError("Ожидался int, double или идентификатор",l);
	else{
		if (t == TIdent){
			if (flagInt) pt->sem_get_type(l, str = sc->GetStroka());
		}
		strcpy(typebuf,l);
	}

	bool flag = false;

	t=sc->Scaner(l);
	if (t!=TIdent) 
		sc->PrintError("Ожидался идентификатор",l);
	else{
		if (flagInt){
			if (!pt->sem_override(l, str = sc->GetStroka())){
				pt = pt->sem_add_type(l, typebuf);
				flag = true;
			}
		}
	}

	//uk1=sc->GetUK();
	t=sc->Scaner(l);
	if (t!=TLKvScob) 
		sc->PrintError("Ожидался символ [",l);
	do{
		t=sc->Scaner(l);
		if (t!=TConstInt10) 
			sc->PrintError("Ожидалась константа",l);

		if (flagInt){
			if (flag) pt->sem_set_dim(atoi(l), str = sc->GetStroka());
		}

		t=sc->Scaner(l);
		if (t!=TRKvScob) 
			sc->PrintError("Ожидался символ ]",l);
		uk1=sc->GetUK(); 
		str=sc->GetStroka();
		t=sc->Scaner(l);
	}while (t==TLKvScob);
	sc->PutUK(uk1);
	sc->PutStroka(str);
	t=sc->Scaner(l);
	if (t!=TTochkaZap) sc->PrintError("Ожидался символ ;",l);
}

void TDiagram::M(){
	//main
	TypeLex l; int t, str;
	t=sc->Scaner(l);
	if (t!=TVoid) sc->PrintError("Ожидался void",l);
	t=sc->Scaner(l);
	if (t!=TMain) sc->PrintError("Ожидался main",l);
	else if (!pt->sem_override("main", str=sc->GetStroka())){
		if (flagInt){
			pt->set_left(new node("main", -1));
			pt = pt->left;
		}
	}
	t=sc->Scaner(l);
	if (t!=TLSkob) sc->PrintError("Ожидался символ (",l);
	t=sc->Scaner(l);
	if (t!=TRSkob) sc->PrintError("Ожидался символ )",l);
	B();
} 

void TDiagram::B(){
	//блок
	TypeLex l; int t,uk1,str;
	t=sc->Scaner(l);
	if (t!=TLFigScob) sc->PrintError("Ожидался символ {",l);
	uk1=sc->GetUK();
	str=sc->GetStroka();
	t=sc->Scaner(l);
	sc->PutUK(uk1);
	sc->PutStroka(str);


	if (flagInt) std::cout << "{" << std::endl; 


	tree *pt_old = pt;
	if (flagInt){
		pt->set_right(new node());
		pt = pt->right;
	}

	O();
	
	uk1=sc->GetUK();
	str=sc->GetStroka();
	t=sc->Scaner(l);
	//t=sc->Scaner(l);
	if (t!=TRFigScob) sc->PrintError("Ожидался символ }",l);

	if (flagInt) std::cout << "}" << std::endl;

	pt = pt_old;
} 

void TDiagram::O(){
	//операторы
	TypeLex l; int t,uk1, str;

	/*pt->set_left(new node());
	pt = pt->left;
	tree *pt_old = pt;
	pt->set_right(new node());
	pt = pt->right;*/
	
	
	uk1=sc->GetUK(); 
	str=sc->GetStroka();
	sc->PutUK(uk1); sc->PutStroka(str);
	t=sc->Scaner(l); 
	//while (t!=TRFigScob)
	while (t==TTypedef||t==TInt||t==TDouble||t==TIdent||t==TIf||t==TTochkaZap||t==TLFigScob)
	{
		if (t==TTypedef) {sc->PutUK(uk1); sc->PutStroka(str); MS();}
		else if (t==TInt||t==TDouble) {sc->PutUK(uk1); sc->PutStroka(str); OP();}
		else if (t==TIdent){
			t=sc->Scaner(l); // не работает если 1 оператор после всего идёт или несколько 1 операторов
			if (t==TIdent) {sc->PutUK(uk1); sc->PutStroka(str); OP();}
			else {sc->PutUK(uk1); sc->PutStroka(str); O1();}
		}
		else {sc->PutUK(uk1); sc->PutStroka(str); O1();}
		uk1=sc->GetUK(); 
		str=sc->GetStroka();
		t=sc->Scaner(l); 
		/*sc->PutUK(uk1);
		sc->PutStroka(str);*/
	}
	/*uk1=sc->GetUK(); 
	str=sc->GetStroka();
	//*
	/**//*sc->PutUK(uk1);
	sc->PutStroka(str);//*/
	sc->PutUK(uk1);
	sc->PutStroka(str);
}

void TDiagram::O1(){
	//1 оператор
	TypeLex l; int t,uk1,str;
	int VyrType;
	TVal VyrVal;
	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
	if (t==TTochkaZap) return; // пустой оператор
	if (t==TIf) { sc->PutUK(uk1); I();}
	if (t==TLFigScob) { sc->PutUK(uk1); sc->PutStroka(str); 
	
	pt->set_left(new node()); //////////////////////////////////////////////////////////////////////////
	pt = pt->left;
	
	B(); }
	if (t==TIdent) { 
		t=sc->Scaner(l);
		if (t==TPris||t==TLKvScob) { 
			sc->PutUK(uk1); sc->PutStroka(str); PR(); }
		else { 
			sc->PutUK(uk1); sc->PutStroka(str);	V(&VyrType, &VyrVal);
		}
	}
	
	/*pt->set_left(new node());
	pt = pt->left;
	tree *pt_old = pt;
	pt->set_right(new node());
	pt = pt->right;*/
	
}

void TDiagram::PR(){
	//присваивание
	TypeLex l; int t,uk1,str;
	t=sc->Scaner(l);

	char varname[MAX_LEX];
	varname[0]='\0';

	if (t!=TIdent) 
		sc->PrintError("Ожидался идентификатор",l);
	else{
		if (flagInt) pt->sem_var_declared(l, str = sc->GetStroka());
		strcpy(varname,l);
	}
	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);

	tree *VarTree;
	if (flagInt){
		VarTree = pt->find_up(varname);
	}
	int VarHg[MAX_N];

	int rank = 0;

	if (t == TLKvScob)
	{
		do{
			//rank++;
			int VyrType;
			TVal VyrVal;
			V(&VyrType, &VyrVal);

			if (flagInt){
				if (VyrType != TypeInt){
					sc->PrintError("Индекс должен быть целым в строке", l);
				}
			}
			if (flagInt) VarHg[rank] = VyrVal.datAsInt;

			t = sc->Scaner(l);
			if (t != TRKvScob)
				sc->PrintError("Ожидался символ ]", l);
			uk1 = sc->GetUK();
			str = sc->GetStroka();
			t = sc->Scaner(l);
			//pt->sem_arr_rank(varname,rank,str=sc->GetStroka());
			rank++;
		} while (t == TLKvScob);
		//pt->sem_arr_rank(varname,rank,str=sc->GetStroka());


		int dif = 0;
		if (flagInt){
			pt->sem_arr_rank(varname, rank, str = sc->GetStroka());    //у Миши используется, а у меня нет, поэтому хз надо ли
			//У ОПИСАНИИ ТОГДА РАССКОМЕНТИРОВАТЬ ДЛЯ N
			for (int i = 0; i<rank; i++){
				if (VarHg[i] >= VarTree->n->hg[i]){
					sc->PrintError("Размер массива превышен в строке ", l);
					//std::cout << "Размер массива превышен в строке " << (sc->lines[sc->GetUK()]) << std::endl; throw 0;
				}
				if (i > 0) dif *= VarTree->n->hg[i - 1];
				dif += VarHg[i];
			}
		}



		//pt->sem_arr_rank(varname,rank,str=sc->GetStroka());///////////////////////////////////

		sc->PutUK(uk1);
		sc->PutStroka(str);
		t = sc->Scaner(l);
		if (t != TPris) sc->PrintError("Ожидался символ =", l);
		//sc->PutUK(uk1);

		int VyrType;
		TVal VyrVal;
		V(&VyrType, &VyrVal);
		if (flagInt){
			if (VarTree->n->type == TypeInt){
				if (VyrType == TypeInt){
					(VarTree->n->value + dif)->datAsInt = VyrVal.datAsInt;
					std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VyrVal.datAsInt) << std::endl;
				}
				else if (VyrType == TypeDouble){
					(VarTree->n->value + dif)->datAsInt = VyrVal.datAsDouble;
					std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VyrVal.datAsDouble) << std::endl;
				}
			}
			else if (VarTree->n->type == TypeDouble){
				if (VyrType == TypeInt){
					(VarTree->n->value + dif)->datAsDouble = VyrVal.datAsInt;
					std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VyrVal.datAsInt) << std::endl;
				}
				else if (VyrType == TypeDouble){
					(VarTree->n->value + dif)->datAsDouble = VyrVal.datAsDouble;
					std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VyrVal.datAsDouble) << std::endl;
				}
			}
		}
	}
	else {
		sc->PutUK(uk1);
		sc->PutStroka(str);
		t = sc->Scaner(l);
		if (t != TPris) sc->PrintError("Ожидался символ =", l);
		int VyrType;
		TVal VyrVal;
		V(&VyrType, &VyrVal);
		if (flagInt){
			if (VarTree->n->type == TypeInt){
				if (VyrType == TypeInt){
					(VarTree->n->value)->datAsInt = VyrVal.datAsInt;
					std::cout << (VarTree->n->id) << " = " << (VyrVal.datAsInt) << std::endl;
				}
				else if (VyrType == TypeDouble){
					(VarTree->n->value)->datAsInt = VyrVal.datAsDouble;
					std::cout << (VarTree->n->id) << " = " << (VyrVal.datAsDouble) << std::endl;
				}
			}
			else if (VarTree->n->type == TypeDouble){
				if (VyrType == TypeInt){
					(VarTree->n->value)->datAsDouble = VyrVal.datAsInt;
					std::cout << (VarTree->n->id) << " = " << (VyrVal.datAsInt) << std::endl;
				}
				else if (VyrType == TypeDouble){
					(VarTree->n->value)->datAsDouble = VyrVal.datAsDouble;
					std::cout << (VarTree->n->id) << " = " << (VyrVal.datAsDouble) << std::endl;
				}
			}
		}
	}
	//uk1=sc->GetUK(); 
	t=sc->Scaner(l);
	if (t!=TTochkaZap) sc->PrintError("Ожидался символ ;",l);
}

void TDiagram::V(int *type, TVal *value){
	//выражение
	int sign = 1;
	TypeLex l; int t,uk1, str;
	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
	if (t == TPlus){ // возможно это не надо
		sign = 1;
	}
	else if (t == TMinus){
		sign = -1;
	}
	if ( (t!=TPlus) && (t!=TMinus) )
	{
		sc->PutUK(uk1); sc->PutStroka(str);
	}
	int VyrType;
	TVal VyrVal;
	V1(&VyrType, &VyrVal);

	*type = VyrType;
	if (flagInt){
		if (VyrType == TypeInt){
			value->datAsInt = sign*(VyrVal.datAsInt);
		}
		else if (VyrType == TypeDouble){
			value->datAsDouble = sign*(VyrVal.datAsDouble);
		}
	}

	uk1=sc->GetUK(); 
	str=sc->GetStroka();
	t=sc->Scaner(l);
	if ((t<=TNeRavno) && (t>=TBolshe)) {
		while ((t<=TNeRavno) && (t>=TBolshe)) 
		{
			int VyrType;
			TVal VyrVal;
			V1(&VyrType, &VyrVal);

			switch (*type){
			case TypeInt:
				switch (VyrType){
				case TypeInt:
					switch (t){
					case TBolshe:
						if (flagInt) value->datAsInt = value->datAsInt > VyrVal.datAsInt;
						break;
					case TBolsheRavno:
						if (flagInt) value->datAsInt = value->datAsInt >= VyrVal.datAsInt;
						break;
					case TMenshe:
						if (flagInt) value->datAsInt = value->datAsInt < VyrVal.datAsInt;
						break;
					case TMensheRavno:
						if (flagInt) value->datAsInt = value->datAsInt <= VyrVal.datAsInt;
						break;
					case TRavno:
						if (flagInt) value->datAsInt = value->datAsInt == VyrVal.datAsInt;
						break;
					case TNeRavno:
						if (flagInt) value->datAsInt = value->datAsInt != VyrVal.datAsInt;
						break;
					}
					break;
				case TypeDouble:
					switch (t){
					case TBolshe:
						if (flagInt) value->datAsInt = value->datAsInt > VyrVal.datAsInt;
						break;
					case TBolsheRavno:
						if (flagInt) value->datAsInt = value->datAsInt >= VyrVal.datAsInt;
						break;
					case TMenshe:
						if (flagInt) value->datAsInt = value->datAsInt < VyrVal.datAsInt;
						break;
					case TMensheRavno:
						if (flagInt) value->datAsInt = value->datAsInt <= VyrVal.datAsInt;
						break;
					case TRavno:
						if (flagInt) value->datAsInt = value->datAsInt == VyrVal.datAsInt;
						break;
					case TNeRavno:
						if (flagInt) value->datAsInt = value->datAsInt != VyrVal.datAsInt;
						break;
					}
					break;
				}
				break;
			case TypeDouble:
				switch (VyrType){
				case TypeInt:
					switch (t){
					case TBolshe:
						if (flagInt) value->datAsInt = value->datAsInt > VyrVal.datAsInt;
						break;
					case TBolsheRavno:
						if (flagInt) value->datAsInt = value->datAsInt >= VyrVal.datAsInt;
						break;
					case TMenshe:
						if (flagInt) value->datAsInt = value->datAsInt < VyrVal.datAsInt;
						break;
					case TMensheRavno:
						if (flagInt) value->datAsInt = value->datAsInt <= VyrVal.datAsInt;
						break;
					case TRavno:
						if (flagInt) value->datAsInt = value->datAsInt == VyrVal.datAsInt;
						break;
					case TNeRavno:
						if (flagInt) value->datAsInt = value->datAsInt != VyrVal.datAsInt;
						break;
					}
					break;
				case TypeDouble:
					switch (t){
					case TBolshe:
						if (flagInt) value->datAsInt = value->datAsInt > VyrVal.datAsInt;
						break;
					case TBolsheRavno:
						if (flagInt) value->datAsInt = value->datAsInt >= VyrVal.datAsInt;
						break;
					case TMenshe:
						if (flagInt) value->datAsInt = value->datAsInt < VyrVal.datAsInt;
						break;
					case TMensheRavno:
						if (flagInt) value->datAsInt = value->datAsInt <= VyrVal.datAsInt;
						break;
					case TRavno:
						if (flagInt) value->datAsInt = value->datAsInt == VyrVal.datAsInt;
						break;
					case TNeRavno:
						if (flagInt) value->datAsInt = value->datAsInt != VyrVal.datAsInt;
						break;
					}
					break;
				}
				break;
			}
			*type = TypeInt;

			uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
		}
		sc->PutUK(uk1);
		sc->PutStroka(str);
	}
	else 
		if (t==TPlusPlus||t==TMinusMinus) //////////////////////////////////////////косячная???????????????????
			//sc->PrintError("Ожидался символ ++ или --",l);
			//return; 
			//sc->PutUK(uk1);
		{
				uk1=sc->GetUK();
				str=sc->GetStroka();
		}
	sc->PutUK(uk1);
	sc->PutStroka(str);
}

void TDiagram::V1(int *type, TVal *value){
	//выражение 1
	TypeLex l; int t,uk1, str;
	//uk1=sc->GetUK(); t=sc->Scaner(l);
	int VyrType;
	TVal VyrVal;
	V2(&VyrType, &VyrVal);

	*type = VyrType;
	if (flagInt){
		if (VyrType == TypeInt){
			value->datAsInt = (VyrVal.datAsInt);
		}
		else if (VyrType == TypeDouble){
			value->datAsDouble = (VyrVal.datAsDouble);
		}
	}

	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
	while ((t==TMinus) || (t==TPlus)) 
	{
		int VyrType;
		TVal VyrVal;
		V2(&VyrType, &VyrVal);

		switch (*type){
		case TypeInt:
			switch (VyrType){
			case TypeInt:
				*type = TypeInt;
				switch (t){
				case TPlus:
					if (flagInt) value->datAsInt = value->datAsInt + VyrVal.datAsInt;
					break;
				case TMinus:
					if (flagInt) value->datAsInt = value->datAsInt - VyrVal.datAsInt;
					break;
				}
				break;
			case TypeDouble:
				*type = TypeDouble;
				switch (t){
				case TPlus:
					if (flagInt) value->datAsDouble = value->datAsInt + VyrVal.datAsDouble;
					break;
				case TMinus:
					if (flagInt) value->datAsDouble = value->datAsInt - VyrVal.datAsDouble;
					break;
				}
				break;
			}
			break;
		case TypeDouble:
			switch (VyrType){
			case TypeInt:
				*type = TypeDouble;
				switch (t){
				case TPlus:
					if (flagInt) value->datAsDouble = value->datAsDouble + VyrVal.datAsInt;
					break;
				case TMinus:
					if (flagInt) value->datAsDouble = value->datAsDouble - VyrVal.datAsInt;
					break;
				}
				break;
			case TypeDouble:
				*type = TypeDouble;
				switch (t){
				case TPlus:
					if (flagInt) value->datAsDouble = value->datAsDouble + VyrVal.datAsDouble;
					break;
				case TMinus:
					if (flagInt) value->datAsDouble = value->datAsDouble - VyrVal.datAsDouble;
					break;
				}
				break;
			}
			break;
		}

		uk1=sc->GetUK(); 
		str=sc->GetStroka();
		t=sc->Scaner(l);
	}
	sc->PutUK(uk1);
	sc->PutStroka(str);
}

void TDiagram::V2(int *type, TVal *value){
	//выражение 2
	TypeLex l; int t,uk1, str;
	//uk1=sc->GetUK(); t=sc->Scaner(l);
	int VyrType;
	TVal VyrVal;
	V3(&VyrType, &VyrVal);

	*type = VyrType;
	if (flagInt){
		if (VyrType == TypeInt){
			value->datAsInt = (VyrVal.datAsInt);
		}
		else if (VyrType == TypeDouble){
			value->datAsDouble = (VyrVal.datAsDouble);
		}
	}

	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
	while ((t<=TMod) && (t>=TMul)) 
	{
		int VyrType;
		TVal VyrVal;
		V3(&VyrType, &VyrVal);

		switch (*type){
		case TypeInt:
			switch (VyrType){
			case TypeInt:
				*type = TypeInt;
				switch (t){
				case TMul:
					if (flagInt) value->datAsInt = value->datAsInt * VyrVal.datAsInt;
					break;
				case TDiv:
					if (flagInt) value->datAsInt = value->datAsInt / VyrVal.datAsInt;
					break;
				case TMod:
					if (flagInt) value->datAsInt = value->datAsInt % VyrVal.datAsInt;
					break;
				}
				break;
			case TypeDouble:
				*type = TypeDouble;
				switch (t){
				case TMul:
					if (flagInt) value->datAsDouble = value->datAsInt * VyrVal.datAsDouble;
					break;
				case TDiv:
					if (flagInt) value->datAsDouble = value->datAsInt / VyrVal.datAsDouble;
					break;
				case TMod:
					if (flagInt) sc->PrintError("Невозможно взять остаток от деления в строке ", l);//std::cout << "невозможно взять остаток от деления в строке " << (sc->lines[sc->GetUK()]) << std::endl; throw 0;
					break;
				}
				break;
			}
			break;
		case TypeDouble:
			switch (VyrType){
			case TypeInt:
				*type = TypeDouble;
				switch (t){
				case TMul:
					if (flagInt) value->datAsDouble = value->datAsDouble * VyrVal.datAsInt;
					break;
				case TDiv:
					if (flagInt) value->datAsDouble = value->datAsDouble / VyrVal.datAsInt;
					break;
				case TMod:
					if (flagInt) sc->PrintError("Невозможно взять остаток от деления в строке ", l); //std::cout << "невозможно взять остаток от деления в строке " << (sc->lines[sc->GetUK()]) << std::endl; throw 0;
					break;
				}
				break;
			case TypeDouble:
				*type = TypeDouble;
				switch (t){
				case TMul:
					if (flagInt) value->datAsDouble = value->datAsDouble * VyrVal.datAsDouble;
					break;
				case TDiv:
					if (flagInt) value->datAsDouble = value->datAsDouble / VyrVal.datAsDouble;
					break;
				case TMod:
					//тут не было if flag
					if (flagInt) sc->PrintError("Невозможно взять остаток от деления в строке ", l);//std::cout << "невозможно взять остаток от деления в строке " << (sc->lines[sc->GetUK()]) << std::endl; throw 0;
					break;
				}
				break;
			}
			break;
		}
		uk1=sc->GetUK(); 
		str=sc->GetStroka();
		t=sc->Scaner(l);
	}
	sc->PutUK(uk1);
	sc->PutStroka(str);
}

void TDiagram::V3(int *type, TVal *value){
	//выражение 3
	TypeLex l; int t,uk1, str;
	uk1=sc->GetUK(); 
	str=sc->GetStroka();
	t=sc->Scaner(l);
	if (t == TConstInt10) 
	{
		*type = TypeInt;
		int x;
		sscanf(l, "%d", &x);
		if (flagInt) value->datAsInt = x;
		return;
		}
	if (t==TLSkob){
		int VyrType;
		TVal VyrVal;
		V(&VyrType, &VyrVal);

		*type = VyrType;
		if (flagInt){
			if (VyrType == TypeInt){
				value->datAsInt = VyrVal.datAsInt;
			}
			else{
				value->datAsDouble = VyrVal.datAsDouble;
			}
		}

		t=sc->Scaner(l);
		if (t!=TRSkob) sc->PrintError("Ожидался символ )",l); return;
	}

	char varname[MAX_LEX];
	varname[0] = '\0';

	if (t==TIdent) 
	{
		strcpy(varname, l);
		if (flagInt) pt->sem_var_declared(l, str = sc->GetStroka());
		///////////////// пока вставила сюда
		tree *VarTree;
		if (flagInt) VarTree = pt->find_up(varname);
		int VarHg[MAX_N];

		int rank = 0;

		uk1 = sc->GetUK();
		str = sc->GetStroka();
		t = sc->Scaner(l);

		if (t==TLKvScob) 
		{
			/*tree *VarTree;
			if (flagInt) VarTree = pt->find_up(varname);
			int VarHg[MAX_N];

			int rank = 0;*/

			do{

				//rank++;
				int VyrType;
				TVal VyrVal;
				V(&VyrType, &VyrVal);
				if (VyrType != TypeInt){
					sc->PrintError("Индекс должен быть целым ", l);
					//std::cout << "индекс должен быть целым " << (sc->lines[sc->GetUK()]) << std::endl; throw 0;
				}
				if (flagInt) VarHg[rank] = VyrVal.datAsInt;
				t=sc->Scaner(l);
				if (t!=TRKvScob) 
					sc->PrintError("Ожидался символ ]",l);
				rank++;
				uk1=sc->GetUK(); //чтобы было несколько скобок
				str=sc->GetStroka();
				t=sc->Scaner(l);
				//pt->sem_arr_rank(varname,rank,str=sc->GetStroka());
			}while (t==TLKvScob);

			//pt->sem_arr_rank(varname,rank,str=sc->GetStroka());
			if (flagInt) pt->sem_arr_rank(varname, rank, str = sc->GetStroka());// у Миши есть, а я убирала

			int dif = 0;
			if (flagInt) {
				for (int i = 0; i<rank; i++){
					if (VarHg[i] >= VarTree->n->hg[i]){
						sc->PrintError("Размер массива превышен в строке ", l);
						//std::cout << "размер массива превышен в строке " << (sc->lines[sc->GetUK()]) << std::endl; throw 0;
					}
					if (i > 0) dif *= VarTree->n->hg[i - 1];
					dif += VarHg[i];
				}
			}
			/*    // это у Миши есть, но связано с add, а это ++ и --, надо проверить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (flagInt){
				if (VarTree->n->type == TypeInt){
					(VarTree->n->value + dif)->datAsInt += add;
					if (add != 0) std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VarTree->n->value->datAsInt) << std::endl;
				}
				else if (VarTree->n->type == TypeDouble){
					(VarTree->n->value + dif)->datAsDouble += add;
					if (add != 0) std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VarTree->n->value->datAsDouble) << std::endl;
				}
			}*/

			/*if (t == TSet){
				sc->scan();
				int VyrType1;
				TVal VyrVal1;
				Vyrazhenie(&VyrType1, &VyrVal1);
				if (flagInt){
					if (VyrType1 == TypeInt){
						if (VarTree->n->type == TypeInt){
							VarTree->n->value->datAsInt = VyrVal1.datAsInt;
						}
						else if (pt->n->type == TypeDouble){
							VarTree->n->value->datAsDouble = VyrVal1.datAsInt;
						}
						std::cout << (VarTree->n->id) << " = " << (VyrVal1.datAsInt) << std::endl;
					}
					else if (VyrType1 == TypeDouble){
						if (VarTree->n->type == TypeInt){
							VarTree->n->value->datAsInt = VyrVal1.datAsDouble;
						}
						else if (VarTree->n->type == TypeDouble){
							VarTree->n->value->datAsDouble = VyrVal1.datAsDouble;
						}
						std::cout << (VarTree->n->id) << " = " << (VyrVal1.datAsDouble) << std::endl;
					}
				}
			}

			if (flagInt){
				if (VarTree->n->type == TypeInt){
					*type = TypeInt;
					if (flagInt) value->datAsInt = (VarTree->n->value + dif)->datAsInt;
				}
				else if (VarTree->n->type == TypeDouble){
					*type = TypeDouble;
					if (flagInt) value->datAsDouble = (VarTree->n->value + dif)->datAsDouble;
				}
			}

			int add2 = 0;

			do{
				uk = sc->GetUK();
				t = sc->scan();
				if (t == TPlusPlus) add2++;
				if (t == TMinusMinus) add2--;
				if (t != TPlusPlus && t != TMinusMinus){
					sc->PutUK(uk);
					break;
				}
			} while (true);

			if (flagInt){
				if (VarTree->n->type == TypeInt){
					(VarTree->n->value + dif)->datAsInt += add2;
					if (add2 != 0) std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VarTree->n->value->datAsInt) << std::endl;
				}
				else if (VarTree->n->type == TypeDouble){
					(VarTree->n->value + dif)->datAsDouble += add2;
					if (add2 != 0) std::cout << (VarTree->n->id) << "[" << dif << "] = " << (VarTree->n->value->datAsDouble) << std::endl;
				}
			}*/

		sc->PutUK(uk1);//прпр
		sc->PutStroka(str);
		//t=sc->Scaner(l);//прпр
		//return;
		}
		else {sc->PutUK(uk1);sc->PutStroka(str);
		// вставляю сюда для индефикатора разпознование типа
		if (flagInt){
			if (VarTree->n->type == TypeInt){
				(VarTree->n->value)->datAsInt;
			}
			else if (VarTree->n->type == TypeDouble){
				(VarTree->n->value)->datAsDouble;
			}
		}

		if (flagInt){
			if (VarTree->n->type == TypeInt){
				*type = TypeInt;
				if (flagInt) value->datAsInt = (VarTree->n->value)->datAsInt;
			}
			else if (VarTree->n->type == TypeDouble){
				*type = TypeDouble;
				if (flagInt) value->datAsDouble = (VarTree->n->value)->datAsDouble;
			}
		}
		////////////////////////////////////////////////////
		}
	}
	else {sc->PrintError("Неправильный синтаксис (элемент. выражение)",l);
		strcpy(varname,l);
		if (flagInt) pt->sem_var_declared(l, str = sc->GetStroka());
	}
}

void TDiagram::I(){
	//if
	TypeLex l; int t, uk1, str;
 	t=sc->Scaner(l);
	if (t!=TIf) 
		sc->PrintError("Ожидался if",l);
	t=sc->Scaner(l);
	if (t!=TLSkob) 
		sc->PrintError("Ожидался символ (",l);
	int VyrType;
	TVal VyrVal;
	V(&VyrType, &VyrVal);
	/*if (flagInt){
		if (VyrType == TypeInt){
			value->datAsInt = VyrVal.datAsInt;
		}
		else{
			value->datAsDouble = VyrVal.datAsDouble;
		}
	}*/
	t=sc->Scaner(l);
	if (t!=TRSkob) 
		sc->PrintError("Ожидался символ )",l);
	O1();
	uk1=sc->GetUK(); str=sc->GetStroka(); t=sc->Scaner(l);
	if(t==TElse){
		O1();
	}
	else {sc->PutUK(uk1);
	sc->PutStroka(str);}
	/*uk1=sc->GetUK(); 
	str=sc->GetStroka();
	t=sc->Scaner(l); 
	sc->PutUK(uk1);
	sc->PutStroka(str);*/
}