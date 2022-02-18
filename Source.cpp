#include <iostream>
#include <string>
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
	};
	class first_c :public Ic {
	public:
		std::string classname() {
			return "first";
		}
		first_c() {
			name = "first";
		}
		virtual ~first_c(){}
		bool isA(std::string name) { return (name == this->classname()); }
	};
	class second_c :public first_c {
	public:
		std::string classname() {
			return "second";
		}
		bool isA(std::string name) { return (name == this->classname() || this->first_c::isA(name)); }
		second_c() {
			name = "second";
		}
		~second_c() {}
	};
	class third_c :public second_c {
	public:
		std::string classname() {
			return "third";
		}
		bool isA(std::string name) { return (name == this->classname() || this->second_c::isA(name)); }
		third_c() {
			name = "third";
		}
		~third_c() {}
	};
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
	printf("\n\n");
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
	printf("\n\n");
	{
		using namespace virtual_methods;
		Base* desc = new Desc();
		desc->nv_meth();
		desc->v_meth();
		delete desc;
	}
	return 0;
}