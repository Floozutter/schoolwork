if __name__ == "__main__":
	print(
		"You wrote:\n" +
		"\n".join(map(input, (
			"Write the first string:\n",
			"Write the second string:\n",
			"Write the third string:\n"
		)))
	)