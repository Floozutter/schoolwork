import java.util.Scanner;

public class Orwell {
	public static void main(String[] args) {
		System.out.println("Give a number:");
		if (Integer.valueOf((new Scanner(System.in)).nextLine()) == 1984) {
			System.out.println("Orwell");
		}
	}
}
