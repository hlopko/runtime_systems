//Jaky bude vystup metody main? Pujde kod kompilovat?

//--------------------------------------------------------------------------------

class A extends RuntimeException {}

class B extends A {}

class Exceptions
{
	public static void main(String[] argv) {
		try {
			B ex = (B) new A();
			System.out.println("Throwing...");
			throw ex;
		} catch (B ex_b) {
			System.out.println("Caught B!");
		}
	}
}
