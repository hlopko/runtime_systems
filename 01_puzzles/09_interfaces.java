interface I1                    { String FIELD = "I1";}
interface I2 extends I1         { String FIELD = "I2";}
class A                         { public static String FIELD = "A";}
class B extends A               { public String FIELD = "B";}
class C implements I1           {}
class D extends C implements I2 { String FIELD = "D";}
class E extends C implements I2 {}
class AWithI1 implements I1     { String FIELD = "AWithI1";}

class InterfacePuzzle {
	public static void main(String[] args) {
		A a = new A();
		B b = new B();
		A bAsA = new B();
		System.out.println("a.FIELD: " + a.FIELD);
		System.out.println("b.FIELD: " + b.FIELD);
		System.out.println("bAsA.FIELD: " + bAsA.FIELD);
		AWithI1 aWithI1 = new AWithI1();
		System.out.println("aWithI1.FIELD: " + aWithI1.FIELD);

		C c = new C();
		D d = new D();
		C dAsC = new D();
		E e = new E();
		System.out.println("c.FIELD: " + c.FIELD);
		System.out.println("d.FIELD: " + d.FIELD);
		System.out.println("dAsC.FIELD: " + dAsC.FIELD);
        System.out.println("e.FIELD: " + e.FIELD);
	}
}
