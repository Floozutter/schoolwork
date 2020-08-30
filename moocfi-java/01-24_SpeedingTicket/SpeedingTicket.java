import java.util.Scanner;

public class SpeedingTicket {
	public static void main(String[] args) {
		System.out.println("Give speed:");
		if (Integer.valueOf((new Scanner(System.in)).nextLine()) > 120) {
			System.out.println("Speeding ticket!");
		}
	}
}
