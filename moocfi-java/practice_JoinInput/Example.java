import java.util.Scanner;

public class Example {
	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);

		System.out.println("Write the first string:");
		String first = reader.nextLine();
		System.out.println("Write the second string:");
		String second = reader.nextLine();
		System.out.println("Write the third string:");
		String third = reader.nextLine();

		System.out.println("You wrote:");
		System.out.println(first);
		System.out.println(second);
		System.out.println(third);
	}
}
