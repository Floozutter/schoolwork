import java.util.Scanner;

public class BooleanInput {
	public static void main(String[] args) {
		System.out.println("Write something:");
		Boolean bool = Boolean.valueOf((new Scanner(System.in)).nextLine());
		System.out.println("True or false? " + bool.toString());
	}
}
