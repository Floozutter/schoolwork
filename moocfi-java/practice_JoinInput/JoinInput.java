import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class JoinInput {
	public static void main(String[] args) {
		final Scanner scanner = new Scanner(System.in);
		System.out.printf(
			"You wrote:%n%s%n",
			Stream.of(
				"Write the first string:",
				"Write the second string:",
				"Write the third string:"
			).map(s -> {
				System.out.println(s);
				return scanner.nextLine();
			}).collect(Collectors.joining(System.lineSeparator()))
		);
	}
}
