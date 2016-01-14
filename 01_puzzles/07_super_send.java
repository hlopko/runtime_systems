class A {
    void foo() {
        System.out.println("foo");    bar();
    }
    void bar() {
        System.out.println("bar");
    }}

class B extends A {
    void foo() {
        System.out.println("foo2");   bar();
    }
    void bar() {
        System.out.println("bar2");
    }
    void print() {
        super.foo();
    }
}

class SuperSend2 {
    public static void main(String[] args) {
        new B().print();
    }
}
