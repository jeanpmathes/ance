private const [ui8 : 1] newline := "\n";

public [ui8 : 1] a <- "a";
private [ui8 : 8] b <- "--------";

private i42 TEST <- +11:42;
private i64 INTEGER <- -187;

private ui64 hex <- 0xCAFEBABE;
private ui64 bin <- 0b010101010101;
private ui64 oct <- 0o1234567;

public ui32 main()
{
	a <- "c";
	b <- "12345678";

	print "WELCOME";
	print a;
	print b;

	print_newline();

	INTEGER <- -234;

	print_and_pass_trough_newline();

	ui64 i <- 11;
	ui64 j;

	i <- j;
	j <- get_answer();
	i <- get_answer();
	j <- get_answer();
	j <- INTEGER;

	print_arrow("a", "b");

	print_ln("--------");
	print_ln("POGGERS ");
	print_ln("HELLO   ");

	return SUCCESS;
}

private ui64 get_answer() {
	return 42;
}

private void print_newline()
{
	print newline;
	return;
}

private void print_ln([ui8 : 8] word) 
{
	print word;
	print newline;

	return;
}

private void print_arrow([ui8 : 1] start, [ui8 : 1] tip) 
{
	print start;
	print " ----> ";
	print tip;

	return;
}

public [ui8 : 1] get_newline()
{
	return newline;
}

private [ui8 : 1] print_and_pass_trough_newline() 
{
	print get_newline();
	return get_newline();
}

private const ui32 SUCCESS := 0:32;
private const ui32 FAILURE := 1:32;