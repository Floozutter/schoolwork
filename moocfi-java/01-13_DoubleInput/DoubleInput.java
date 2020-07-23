import java.util.Scanner;

public class DoubleInput {
	public static void main(String[] args) {
		System.out.println("Give a number:");
		Double number = Double.valueOf((new Scanner(System.in)).nextLine());
		System.out.println("You gave the number " + number.toString());
	}
}
