//Jaky bude vystup metody main?

class StringPuzzle {
	public static void main(String[] args) {
		String s1 = "ahoj";
		String s2 = "ahoj";
		System.out.println("s1 == s2) " + (s1 == s2));
		System.out.println("s1.equals(s2) " + s1.equals(s2));

		String s3 = new String("ahoj");
		String s4 = new String("ahoj");
		System.out.println("s3 == s4 " + (s3 == s4));
		System.out.println("s3.equals(s4) " + s3.equals(s4));
	}
}
