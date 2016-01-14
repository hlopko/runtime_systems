//Jaky bude vystup metody main? Pujde kod kompilovat?
class X           { void print() { System.out.println("I'm X");  }}
class Y           { void print() { System.out.println("I'm Y");  }}
class Z extends Y { void print() { System.out.println("I'm Z");  }}
class A           { void foo(X x, Y y)  { 
                        System.out.println("In A::foo(X,Y)");
                        x.print();
                        y.print();
                  }}
class B extends A { void foo(X x,Z y)   {
                        System.out.println("In B::foo(X,Z)");
                        x.print();
                        y.print();
                  }}
class Overloads { public static void main(String[] args) {
	A a;	B b;	X x;	Y y;	Z z;
	
	a = new A(); x = new X(); y = new Y();
	a.foo(x, y);
	
	a = new B(); x = new X(); y = new Z();
	a.foo(x, y);

	b = new B(); x = new X(); y = new Z();
	b.foo(x, y);

	b = new B(); x = new X(); z = new Z();
	b.foo(x, z);
  }
}
