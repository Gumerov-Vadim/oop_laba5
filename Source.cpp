#include <iostream>
#include <string>
#include <conio.h>
namespace virtual_destructor {
	class IBase {
	protected:
		virtual void what_was_created() = NULL;
	public :
		virtual int take_away() = NULL;
		virtual int result() = NULL;
	};
	class Base : public IBase{
	protected:
			char cname;
			int num1, num2,res;
	public:
		Base() { num1 = 0; num2 = 0; res; cname = 'b'; what_was_created(); }
		Base(int num1, int num2) { this->num1 = num1; this->num2 = num2; cname = 'b'; what_was_created();}
		virtual ~Base() { printf("~������ ���������� ~Base()\n"); }
		int take_away() { printf("������ ����� �������� ������ take_away()\n"); return res = num1 - num2; }
		int result() { printf("������ ����� �������� ������ result()\n"); return res; }
		virtual void what_was_created() {
				printf("��� ������ ������ ������ Base(%d,%d)\n", num1, num2);		
		}
	};
	class Desc : public Base{
	public:
		int take_away() { printf("������ ��������������� ����� ������ ���������� take_away()\n"); return res = num2 - num1; }
		Desc() :Base() {cname = 'c'; what_was_created();}
		Desc(int num1, int num2) : Base(num1, num2) {cname = 'c'; what_was_created();}
		void what_was_created() {printf("��� ������ ������ ������ Base(%d,%d)\n", num1, num2);
		}
		~Desc() { printf("~������ ���������� ~Desc()\n"); }
	};
}
namespace overriden_methods {
	class IBase {
	protected:
		virtual void what_was_created() = NULL;
	public:
		//virtual void v_first_meth() = NULL;
		//virtual void second_meth() = NULL;
	};
	class Base : public IBase {
	protected:
		char cname;
	public:
		Base() { cname = 'b'; what_was_created();}
		void what_was_created() {printf("������ ������ Base()\n");}
		virtual ~Base() { printf("~������ ���������� ~Base()\n"); }
		void v_first_meth() { printf("������ 1-�� ����� ������ base, "); v_second_meth(); }
		void nv_first_meth() { printf("������ 1-�� ����� ������ base, "); nv_second_meth(); }
		virtual void v_second_meth(){ printf("������ 2-�� ����� ������ base\n"); }
		void nv_second_meth() { printf("������ 2-�� ����� ������ base\n"); }
	};
	class Desc : public Base {
	public:
		Desc() { cname = 'c'; what_was_created(); }
		void what_was_created() {printf("������ ������ Desc()\n");}
		void second_meth() { printf("������ 2-�� ����� ������ Desc\n"); }
		~Desc() { printf("~������ ���������� ~Desc()\n"); }
	};
}
namespace virtual_methods{
	class IBase {
	protected:
		virtual void what_was_created() = NULL;
	public:
		//virtual void v_first_meth() = NULL;
		//virtual void second_meth() = NULL;
	};
	class Base : public IBase {
	protected:
		char cname;
	public:
		Base() { cname = 'b'; what_was_created(); }
		void what_was_created() { printf("������ ������ Base()\n"); }
		virtual ~Base() { printf("~������ ���������� ~Base()\n"); }
		virtual void v_meth() { printf("������ ����������� ����� ������ base\n");}
		void nv_meth() { printf("������ ������������� ����� ������ base\n");}
	};
	class Desc : public Base {
	public:
		Desc() { cname = 'c'; what_was_created(); }
		void what_was_created() { printf("������ ������ Desc()\n"); }
		void v_meth() { printf("������ ����������� ����� ������ Desc\n"); }
		void nv_meth() { printf("������ ������������� ����� ������ Desc\n"); }
		~Desc() { printf("~������ ���������� ~Desc()\n"); }
	};
}
namespace check_classes {
	class Ic {
	protected:
		std::string name;
	public:
		virtual std::string classname() = NULL;
		virtual bool isA(std::string name) = NULL;
		virtual void what_was_created() = NULL;
		virtual void was_deleted() = NULL;
	};
	class first_c :public Ic {
	protected:
		void was_deleted(){ std::cout << "������ ������ " << name << " ������\n"; }
		void what_was_created() { printf("��� ������ ������ ������ "); std::cout << name<<"\n"; }
	public:
		std::string classname() {
			return "first";
		}
		first_c() { name = "first"; what_was_created(); }
		virtual ~first_c() { was_deleted(); }
		bool isA(std::string name) { return (name == "first"); }
	};
	class second_c :public first_c {
	public:
		std::string classname() {
			return "second";
		}
		bool isA(std::string name) { return (name == "second" || this->first_c::isA(name)); }
		second_c() {name = "second"; what_was_created();}
		~second_c() { was_deleted(); }
	};
	class third_c :public second_c {
	public:
		std::string classname() {
			return "third";
		}
		bool isA(std::string name) { return (name == "third" || this->second_c::isA(name)); }
		third_c() {	name = "third"; what_was_created();	}
		~third_c() { was_deleted(); }
	};
}
void next() {
	switch (_getch())
	{
	default:
		system("cls");
		printf("\n");
		break;
	}
}
int main() {
	setlocale(LC_ALL, "Russian"); 
	
	{
		using namespace virtual_destructor;
		Base* desc = new Desc(5,3);
		desc->take_away();
		printf("��������� ������ ������: %d\n", desc->result());
		delete desc;
		printf("����������� ���������� �����, ����� ��� �������� ������� ������ ���������� �� ���������� �������� ������ ��������� ���������� ����������\n");

	}
	next();
	{
		//�	� ������1 �������� ������ ���������� �����2, ������� ��������� � ���� �� ������ ��� �������������, � ������ - ������� �����2 �������������
		//��� ���������� ��� ������ ������1 � ������ - ������� ?
		using namespace overriden_methods;
		Desc desc;
		desc.v_first_meth(); //���� ����� �����������
		printf("� ���� ������ ���������� ������� second_meth �������� ������ Base\n");
		desc.nv_first_meth();//���� ����� �� �����������
		printf("� ���� ������ ���������� ������� second_meth �������� ������ Base\n");
	}
	next();
	{
		using namespace virtual_methods;
		Base* desc = new Desc();
		desc->nv_meth();
		desc->v_meth();
		delete desc;
	}
	next(); 
	{
		using namespace check_classes;
		first_c* fc1 = new first_c();
		first_c* fc2 = new second_c();
		first_c* fc3 = new third_c();
		second_c* sc2 = new second_c();
		second_c* sc3 = new third_c();
		third_c* tc3 = new third_c();

		first_c* fcm[3] = { fc1,fc2,fc3 };
		second_c* scm[3] = { sc2,sc3,tc3 };
		printf("\n������� ��� ������� ���������� fcm[3] = { fc1,fc2,fc3 }\n(������ ���������� �� ������� ������ first_c ��� ��� ��������)\n � scm[3] = { sc2,sc3,tc3 }\n(������ ���������� �� ������� ������ second_c ��� ��� ��������)\n");
		printf("\n �������� � ������� ������� classname(\"name\") � isA(\"name\") � ������ ������ ��������� ������� ������ �������:\n");
		printf("������ fcm, ����� classname()\n");
		for (int i = 0; i < 3; i++) {
			printf("������� �%d :\n", i);
			std::cout << fcm[i]->classname() << "\n";
		}
		printf("\n������ fcm, ����� isA\n");
		for (int i = 0; i < 3; i++) {
			printf("������� �%d: \n", i);
			if (fcm[i]->isA("first")) {
				printf("first\n");
			}
			if (fcm[i]->isA("second")) {
				printf("second\n");
			}
			if (fcm[i]->isA("third")) {
				printf("third\n");
			}
		}

		printf("\n������ scm, ����� classname()\n");
		for (int i = 0; i < 3; i++) {
			printf("������� �%d :\n", i);
			std::cout << fcm[i]->classname() << "\n";
		}
		printf("\n������ scm, ����� isA\n");
		for (int i = 0; i < 3; i++) {
			printf("������� �%d: \n", i);
			if (scm[i]->isA("first")) {
				printf("first\n");
			}
			if (scm[i]->isA("second")) {
				printf("second\n");
			}
			if (scm[i]->isA("third")) {
				printf("third\n");
			}
		}
		printf("\n������� ����� �������� classname() � isA() � ���, ��� classname ���������� �������� ���������� �������,\n � ����� isA() ���������� true, ���� ������ ����������� ������� ������ ��� �������� ��� �����������\n");
		delete fc1;
		delete fc2;
		delete fc3;
		delete sc2;
		delete sc3;
		delete tc3;

		//���������� �����
		next();
		printf("������ �������� ���������� �����:\n");

		first_c* fc = new first_c();
		first_c* sc = new second_c();
		first_c* tc = new third_c();
		fcm[0] = fc;
		fcm[1] = sc;
		fcm[2] = tc;

		for (int i = 0; i < 3; i++) {
			scm[i] = NULL;
		}
		printf("�������� ��� ������� � ����������� ������ first fcm[3] � ������ second scm[3].\n�������� ������ ������ ����������� �� ������� ������� first,second,third\n� � ������� �������� ���������� ����� ������� ��������� �� ������� ������� �� ������.\n");
		for (int i = 0; i < 3; i++) {
			if (fcm[i]->isA("second")) {
				printf("�������� isA(\"second\") == true\nscm[%d]=fcm[%d] (fcm[%d]-> ",i,i,i); std::cout << fcm[i]->classname()<<")\n";
				scm[i] = (second_c*)fcm[i];
			}
			else {
				printf("�������� isA(\"second\")== false\n");
				printf("fcm[% d] -> ", i);
				std::cout<<fcm[i]->classname()<<"\n";
			}
		}
		printf("\n������ ������ scm �������� ���:\n");
		for (int i = 0; i < 3; i++) {
			if (scm[i] != NULL) {
				std::cout <<i<<"-�" << " ������: " << scm[i]->classname() << "\n";
			}
			else {
				printf("%d-� ������: NULL\n", i);
			}
		}
		delete fc;
		delete sc;
		delete tc;
	}
	return 0;
}