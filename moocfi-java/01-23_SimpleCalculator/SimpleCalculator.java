import java.util.Scanner;
import java.util.function.BiFunction;
import java.util.List;
import java.util.Arrays;

public class SimpleCalculator {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		System.out.println("Give the first number:");
		final int first = Integer.valueOf(scanner.nextLine());
		
		System.out.println("Give the second number:");
		final int second = Integer.valueOf(scanner.nextLine());
		
		final List<Op<Integer, Integer, String>> ops = Arrays.asList(
			new Op<>("+", (a, b) -> String.valueOf(a + b)),
			new Op<>("-", (a, b) -> String.valueOf(a - b)),
			new Op<>("*", (a, b) -> String.valueOf(a * b)),
			new Op<>("/", (a, b) -> String.valueOf((double)a / (double)b))
		);
		ops.forEach(op -> {
			System.out.println(String.format(
				"%d %s %d = %s",
				first, op.repr, second, op.bif.apply(first, second)
			));
		});
	}
	
	private static class Op<T, U, R> {
		public final String repr;
		public final BiFunction<T, U, R> bif;
		public Op(String repr, BiFunction<T, U, R> bif) {
			this.repr = repr;
			this.bif = bif;
		}
	}
}
