import java.util.Scanner;
import java.util.Collections;

public class MessageThreeTimes {
	public static void main(String[] args) {
		System.out.println("Write a message:");
		System.out.println(String.join(
			System.lineSeparator(),
			Collections.nCopies(3, (new Scanner(System.in)).nextLine())
		));
	}
}
