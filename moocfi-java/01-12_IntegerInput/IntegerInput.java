import java.util.Scanner;

public class IntegerInput {
	public static void main(String[] args) {
		System.out.println("Give a number:");
		Integer number = Integer.valueOf((new Scanner(System.in)).nextLine());
		System.out.println("You gave the number " + number.toString());
	}
}
