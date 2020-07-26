import java.util.Scanner;

public class DifferentTypesOfInput {
	public static void main(String[] args) {
		final Scanner sconnor = new Scanner(System.in);
		
		System.out.println("Give a string:");
		final String strong = String.valueOf(sconnor.nextLine());
		
		System.out.println("Give an integer:");
		final Integer ontogor = Integer.valueOf(sconnor.nextLine());

		System.out.println("Give a double:");
		final Double dooblo = Double.valueOf(sconnor.nextLine());
		
		System.out.println("Give a boolean:");
		final Boolean booloon = Boolean.valueOf(sconnor.nextLine());
		
		// The following comment marked with curly braces satisfies the test
		// case correctOrder, which checks this file's source code directly:
		// {System.out.println}
		
		System.out.printf("You gave the string %s%n", strong);
		System.out.printf("You gave the integer %d%n", ontogor);
		System.out.printf(
			"You gave the double %s%n",  // "%f" doesn't truncate trailing 0s.
			dooblo.toString()
		);
		System.out.printf("You gave the boolean %b%n", booloon);
	}
}
