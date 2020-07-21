import java.util.Scanner;

public class Story {
	public static void main(String[] args) {
		final Scanner scanner = new Scanner(System.in);
		
		System.out.println(
			"I will tell you a story, but I need some information first."
		);
		
		System.out.println("What is the main character called?");
		final String name = scanner.nextLine();
		
		System.out.println("What is their job?");
		final String job = scanner.nextLine();
		
		System.out.println("Here is the story:");
		System.out.printf(
			(
				"Once upon a time there was %1$s, who was %2$s.%n" +
				"On the way to work, %1$s reflected on life.%n" +
				"Perhaps %1$s will not be %2$s forever.%n"
			),
			name, job
		);
	}
}
