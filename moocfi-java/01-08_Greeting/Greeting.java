import java.util.Scanner;

public class Greeting {
	public static void main(String[] args) {
		System.out.println("What's your name?");
		System.out.printf(
			"Hi %s%n",
			(new Scanner(System.in)).nextLine()
		);
	}
}
