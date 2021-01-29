private const [ui8 : 1] newline = "\n";

public [ui8 : 1] a = "a";
private [ui8 : 8] b = "--------";

private ui32 SUCCESS = 0:32;
private ui32 FAILURE = 420:32;

private i42 TEST = +11:42;
private i64 INTEGER = -187;

private ui64 hex = 0xCAFEBABE;
private ui64 bin = 0b010101010101;
private ui64 oct = 0o1234567;

print_newline()
{
	print newline;
	return 0:32;
}

main() 
{
	a = "c";
	b = "12345678";

	print "WELCOME";
	print a;
	print b;

	print_newline();

	FAILURE = 1:32;
	INTEGER = -234;

	return FAILURE;
}