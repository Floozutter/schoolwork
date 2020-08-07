import java.util.Scanner;

public class SecondsInADay {
	public static final int SECONDS_PER_DAY = 86400;
	public static void main(String[] args) {
		System.out.println(
			"How many days would you like to convert to seconds?"
		);
		Integer days = Integer.valueOf((new Scanner(System.in)).nextLine());
		System.out.println(SECONDS_PER_DAY * days);
	}
}
