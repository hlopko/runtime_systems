class A { public String myGetClass() { return "A"; }}

class B extends A {
  public boolean foo() {
		return (this.getClass() == super.getClass());
	}

	public boolean bar() {
		return (this.myGetClass().equals(super.myGetClass()));
	}
}

class C extends B {	public String myGetClass() { return "C"; }}

class SuperSendPuzzle {
	public static void main(String[] args) {
		B b = new B();
		System.out.println("b.foo(): " + b.foo());
		System.out.println("b.bar(): " + b.bar());

		B cAsB = new C();
		System.out.println("cAsB.foo(): " + cAsB.foo());
		System.out.println("cAsB.bar(): " + cAsB.bar());
	}
}
