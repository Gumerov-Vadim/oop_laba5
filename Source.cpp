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
		virtual ~Base() { printf("~вызван деструктор ~Base()\n"); }
		int take_away() { printf("вызван метод базового класса take_away()\n"); return res = num1 - num2; }
		int result() { printf("вызван метод базового класса result()\n"); return res; }
		virtual void what_was_created() {
				printf("был создан объект класса Base(%d,%d)\n", num1, num2);		
		}
	};
	class Desc : public Base{
	public:
		int take_away() { printf("вызван переопределённый метод класса наследника take_away()\n"); return res = num2 - num1; }
		Desc() :Base() {cname = 'c'; what_was_created();}
		Desc(int num1, int num2) : Base(num1, num2) {cname = 'c'; what_was_created();}
		void what_was_created() {printf("был создан объект класса Base(%d,%d)\n", num1, num2);
		}
		~Desc() { printf("~вызван деструктор ~Desc()\n"); }
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
		void what_was_created() {printf("Создан объект Base()\n");}
		virtual ~Base() { printf("~вызван деструктор ~Base()\n"); }
		void v_first_meth() { printf("Вызван 1-ый метод класса base, "); v_second_meth(); }
		void nv_first_meth() { printf("Вызван 1-ый метод класса base, "); nv_second_meth(); }
		virtual void v_second_meth(){ printf("Вызван 2-ой метод класса base\n"); }
		void nv_second_meth() { printf("Вызван 2-ой метод класса base\n"); }
	};
	class Desc : public Base {
	public:
		Desc() { cname = 'c'; what_was_created(); }
		void what_was_created() {printf("Создан объект Desc()\n");}
		void second_meth() { printf("Вызван 2-ой метод класса Desc\n"); }
		~Desc() { printf("~вызван деструктор ~Desc()\n"); }
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
		void what_was_created() { printf("Создан объект Base()\n"); }
		virtual ~Base() { printf("~вызван деструктор ~Base()\n"); }
		virtual void v_meth() { printf("Вызван виртуальный метод класса base\n");}
		void nv_meth() { printf("Вызван невиртуальный метод класса base\n");}
	};
	class Desc : public Base {
	public:
		Desc() { cname = 'c'; what_was_created(); }
		void what_was_created() { printf("Создан объект Desc()\n"); }
		void v_meth() { printf("Вызван виртуальный метод класса Desc\n"); }
		void nv_meth() { printf("Вызван невиртуальный метод класса Desc\n"); }
		~Desc() { printf("~вызван деструктор ~Desc()\n"); }
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
		void was_deleted(){ std::cout << "объект класса " << name << " удален\n"; }
		void what_was_created() { printf("Был создан объект класса "); std::cout << name<<"\n"; }
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
		printf("рельзутат работы метода: %d\n", desc->result());
		delete desc;
		printf("Виртуальный деструктор нужен, чтобы при удалении объекта класса наследника из переменной базового класса вызывался правильный деструктор\n");

	}
	next();
	{
		//•	в методе1 базового класса вызывается метод2, который определен в этом же классе как невиртуальный, у класса - потомка метод2 переопределен
		//что происходит при вызове метода1 у класса - потомка ?
		using namespace overriden_methods;
		Desc desc;
		desc.v_first_meth(); //этот метод виртуальный
		printf("В этом случае вызывается функция second_meth базового класса Base\n");
		desc.nv_first_meth();//этот метод не виртуальный
		printf("В этом случае вызывается функция second_meth базового класса Base\n");
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
		printf("\nСозданы два массива указателей fcm[3] = { fc1,fc2,fc3 }\n(Массив указателей на объекты класса first_c или его потомков)\n и scm[3] = { sc2,sc3,tc3 }\n(Массив указателей на объекты класса second_c или его потомков)\n");
		printf("\n проверим с помощью методов classname(\"name\") и isA(\"name\") к какому классу относятся объекты внутри массива:\n");
		printf("массив fcm, метод classname()\n");
		for (int i = 0; i < 3; i++) {
			printf("элемент №%d :\n", i);
			std::cout << fcm[i]->classname() << "\n";
		}
		printf("\nмассив fcm, метод isA\n");
		for (int i = 0; i < 3; i++) {
			printf("элемент №%d: \n", i);
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

		printf("\nмассив scm, метод classname()\n");
		for (int i = 0; i < 3; i++) {
			printf("элемент №%d :\n", i);
			std::cout << fcm[i]->classname() << "\n";
		}
		printf("\nмассив scm, метод isA\n");
		for (int i = 0; i < 3; i++) {
			printf("элемент №%d: \n", i);
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
		printf("\nОтличие между методами classname() и isA() в том, что classname возвращает название созданного объекта,\n а метод isA() возвращает true, если объект принадлежит данному классу или является его наследником\n");
		delete fc1;
		delete fc2;
		delete fc3;
		delete sc2;
		delete sc3;
		delete tc3;

		//Приведение типов
		next();
		printf("Пример опасного приведения типов:\n");

		first_c* fc = new first_c();
		first_c* sc = new second_c();
		first_c* tc = new third_c();
		fcm[0] = fc;
		fcm[1] = sc;
		fcm[2] = tc;

		for (int i = 0; i < 3; i++) {
			scm[i] = NULL;
		}
		printf("создадим два массива с указателями класса first fcm[3] и класса second scm[3].\nЗаполним первый массив указателями на объекты классов first,second,third\nи с помощью опасного приведения типов запишем указатели из первого массива во второй.\n");
		for (int i = 0; i < 3; i++) {
			if (fcm[i]->isA("second")) {
				printf("проверка isA(\"second\") == true\nscm[%d]=fcm[%d] (fcm[%d]-> ",i,i,i); std::cout << fcm[i]->classname()<<")\n";
				scm[i] = (second_c*)fcm[i];
			}
			else {
				printf("проверка isA(\"second\")== false\n");
				printf("fcm[% d] -> ", i);
				std::cout<<fcm[i]->classname()<<"\n";
			}
		}
		printf("\nТеперь массив scm выглядит так:\n");
		for (int i = 0; i < 3; i++) {
			if (scm[i] != NULL) {
				std::cout <<i<<"-й" << " объект: " << scm[i]->classname() << "\n";
			}
			else {
				printf("%d-й объект: NULL\n", i);
			}
		}
		delete fc;
		delete sc;
		delete tc;
	}
	return 0;
}