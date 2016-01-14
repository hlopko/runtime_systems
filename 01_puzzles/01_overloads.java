class Overloads2 {

	public static void foo(String string) { System.out.println("I have string: "+string.toString());	}
	public static void foo(Object o) { System.out.println("I have object: " + o.toString());	}

	public static void main(String[] args) {
        Object o = "hello";
        foo(o);
	}
}
