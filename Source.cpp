#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
int randomizer(int min, int max) {
	time_t sec;
	sec = time(NULL);
	int r = (rand() * sec) % (max - min) + min;
	return r;
}
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
		void what_was_created() {printf("был создан объект класса Desc(%d,%d)\n", num1, num2);
		}
		~Desc() { printf("~вызван деструктор ~Desc()\n"); }
	};
}
namespace overriden_methods {
	class IBase {
	protected:
		virtual void what_was_created() = NULL;
	public:
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
		void v_second_meth() { printf("Вызван 2-ой метод класса Desc\n"); }
		void nv_second_meth() { printf("Вызван 2-ой метод класса Desc\n"); }
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
namespace dynamic_cast_examples {
	class Object {
	private:
		virtual void do_nothing() {
			//nothing...
		}
		int id;
	public:
		void set_id(int id) { this->id = id; }
		int get_id() { return this->id; }
		Object() { id = 0; }
	};
	class Point :public Object{
	private:
		int x, y;
	public:
		friend bool operator==(Point p1, Point p2) {
			bool eq; (p1.get_x() == p2.get_x() && p1.get_y() == p2.get_y()) ? eq = true : eq = false;
			return eq;
		}
		friend bool operator!=(Point p1, Point p2) {
			return !(p1 == p2);
		}
		int get_x() { return x; }
		int get_y() { return y; }
		void set(int x, int y) { this->x = x; this->y = y; }
		Point() { x = 0; y = 0; }
		Point(int x, int y) { this->x = x; this->y = y; }
		Point(Point* p) { this->x = p->get_x(); this->y = p->get_y(); }
	};
	class Circle : public Point {
	private:
		int r;
	public:
		int get_radius() { return r; }
		void set_radius(int r) { if (r > 0) { this->r = r; } }
		Circle() : Point() { r = 1; }
		Circle(int x, int y, int r) :Point(x, y) { r > 0 ? this->r = r : this->r = 1; }
	};
	class Triangle : public Object {
	private:
		Point p1, p2, p3;
	public:
		Triangle() { p1.set(0, 0); p2.set(1, 0);p1.set(0, 1);}
		Triangle(Point p1, Point p2, Point p3) { if (p1 != p2 && p2 != p3) { this->p1 = p1; this->p2 = p2; this->p3 = p3; } else { p1.set(0, 0); p2.set(1, 0); p1.set(0, 1); } }
	};
	Object* create_rand_obj() {
		int r = randomizer(0, 3);
		Point p1, p2, p3;
		switch (r)
		{
		case 0:
			return new Point(randomizer(-10, 10), randomizer(-10, 10));
			break;
		case 1:
			return new Circle(randomizer(-10, 10), randomizer(-10, 10), randomizer(3, 15));
			break;
		case 2:
			p1.set(randomizer(-10, 10), randomizer(-10, 10));
			p2.set(randomizer(-10, 10), randomizer(-10, 10));
			p3.set(randomizer(-10, 10), randomizer(-10, 10));
			return new Triangle(p1, p2, p3);
			break;
		default:
			printf("error:imposible case\n");
			return NULL;
			break;
		}
	}
}
namespace objects_like_p {
	class Base {
	private:
		int x, y;
	public:
		void set(int x, int y) { this->x = x; this->y = y; }
		int get_x() { return x; }
		int get_y() { return y; }
		Base() { x = 0; y = 0; printf("Base()\n"); };
		Base(Base* obj) { this->x = obj->get_x(); this->y = obj->get_y(); printf("Base(Base* obj)\n"); };
		Base(Base& obj) { this->x = obj.get_x(); this->y = obj.get_y(); printf("Base(Base& obj)\n"); };
		~Base() { printf("~Base()\n"); };
	};
	class Desc :public Base {
	private:
		int color;
	public:
		void set_color(int color) { 0x0 <= color && color <= 0xFFFFFF ? this->color = color : this->color = 0x0; }
		int get_color() { return color; }
		Desc() { color = 0x0; printf("Desc()\n"); };
		Desc(Desc* obj) :Base(obj) { int color = obj->get_color(); 0x0 <= color && color <= 0xFFFFFF ? this->color = color : this->color = 0x0; printf("Desc(Desc* obj)\n"); };
		Desc(Desc& obj) { int color = obj.get_color(); 0x0 <= color && color <= 0xFFFFFF ? this->color = color : this->color = 0x0; printf("Desc(Desc& obj)\n"); };
		~Desc() { printf("~Desc()\n"); };
	};
	void func1(Base  obj) { printf("func1:\n в функцию была передана копия объекта.\n%d\nx:%d y:%d\n", &obj, obj.get_x(), obj.get_y()); };
	void func2(Base* obj) { printf("func1:\n в функцию был передан указатель на объект.\n%d\nx:%d y:%d\n", &obj, obj->get_x(), obj->get_y()); };
	void func3(Base& obj) { printf("func1:\n в функцию был передан объект.\n%d\nx:%d y:%d\n", &obj, obj.get_x(), obj.get_y()); };

	Base func1() { Base obj; return obj; };
	Base* func2() { return new Base(); };
	Base& func3() { Base obj; return obj; };

}
namespace smart_pointers {
	class Object {
	public:
		std::string name;

		Object() { name = "задайте имя"; std::cout<<"Создан объект класса Object \"" + name + "\"\n"; }
		Object(std::string name) { this->name = name; std::cout << "Создан объект класса Object \"" + name + "\"\n";}
		~Object() { printf("Объект класса Object удален.\n"); }
	};
}
void next() {
	_getch();
	system("cls");
	printf("\n");
}
int main() {
	setlocale(LC_ALL, "Russian");

	{
		using namespace virtual_destructor;
		Base* desc = new Desc(5, 3);
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
		desc.nv_first_meth();//этот метод не виртуальный
		printf("В этом случае вызывается функция second_meth базового класса Base\n");
		desc.v_first_meth(); //этот метод виртуальный
		printf("В этом случае вызывается функция second_meth базового класса Desc\n");
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
				printf("проверка isA(\"second\") == true\nscm[%d]=fcm[%d] (fcm[%d]-> ", i, i, i); std::cout << fcm[i]->classname() << ")\n";
				scm[i] = (second_c*)fcm[i];
			}
			else {
				printf("проверка isA(\"second\")== false\n");
				printf("fcm[% d] -> ", i);
				std::cout << fcm[i]->classname() << "\n";
			}
		}
		printf("\nТеперь массив scm выглядит так:\n");
		for (int i = 0; i < 3; i++) {
			if (scm[i] != NULL) {
				std::cout << i << "-й" << " объект: " << scm[i]->classname() << "\n";
			}
			else {
				printf("%d-й объект: NULL\n", i);
			}
		}
		delete fc;
		delete sc;
		delete tc;
	}
	next();
	{
		int n = -1;
		using namespace dynamic_cast_examples;
		while (n < 2 || n>100) {
			system("cls");
			printf("Введите размер хранилища: ");
			std::cin >> n;
		}
		Point p;
		Object** storage = new Object * [n];
		printf("Применим метод set_radius к объектам Circle с помощью dynamic_cast:\n");
		printf(",--]storage-info[--,\n");
		for (int i = 0; i < n; i++) {
			storage[i] = create_rand_obj();
			storage[i]->set_id(i);
			Circle* c_ptr = dynamic_cast<Circle*>(storage[i]);
			Point* p_ptr = dynamic_cast<Point*>(storage[i]);
			Triangle* t_ptr = dynamic_cast<Triangle*>(storage[i]);
			if (c_ptr != NULL) {
				printf("|%d| Circle - (%d,%d,%d)", i, c_ptr->get_x(), c_ptr->get_y(), c_ptr->get_radius());
				printf(" -- > set_radius -->");
				c_ptr->set_radius(randomizer(4, 14));
				printf("(%d,%d,%d)\n", c_ptr->get_x(), c_ptr->get_y(), c_ptr->get_radius());
			}
			else if (p_ptr != NULL) {
				printf("|%d| Point\n", i);
			}
			else if (t_ptr != NULL) {
				printf("|%d| Triangle\n", i);
			}
		}
		printf("`------------------`");

		printf("Попробуем применить метод set_radius");
		for (int i = 0; i < n; i++) {
			delete storage[i];
		}
		delete[] storage;
	}
	next();
	{
		using namespace objects_like_p;
		Base bobj;
		Desc dobj;
		bobj.set(randomizer(-10, 10), randomizer(-10, 10));
		dobj.set(randomizer(-10, 10), randomizer(-10, 10));
		func1(bobj);
		func2(&bobj);
		func3(bobj);
		printf("\n");

		func1(dobj);
		func2(&dobj);
		func3(dobj);
		printf("\n");

		printf("Base func1()\n");
		Base obj1;
		obj1 = func1();
		printf("Base* func2()\n");
		Base* obj2 = func2();
		printf("Base& func3()\n");
		Base obj3 = func3();
	}
	next();
	{
		//умные указатели
		using namespace smart_pointers;
		std::string name = "Объект";
		{
			printf("unique ptr:\n");
			std::unique_ptr<Object> first_ptr = std::make_unique<Object>(name);
			std::unique_ptr<Object> second_ptr;
			std::cout << "Первый указатель: " << (static_cast<bool>(first_ptr) ? "не null\n" : "null\n");
			std::cout << "Второй указатель: " << (static_cast<bool>(second_ptr) ? "не null\n" : "null\n");
			second_ptr = move(first_ptr);
			std::cout << "Первый указатель: " << (static_cast<bool>(first_ptr) ? "не null\n" : "null\n");
			std::cout << "Второй указатель: " << (static_cast<bool>(second_ptr) ? "не null\n" : "null\n");
		}
		{

			printf("\n\nshared ptr:\n");
			std::shared_ptr<Object> first_ptr = std::make_shared<Object>(name);
			printf("shared ptr первый указатель: %p\n", &first_ptr);
			std::shared_ptr<Object> second_ptr = first_ptr;
			printf("shared ptr второй указатель: %p\n", &second_ptr);
		}
	}
	return 0;
}