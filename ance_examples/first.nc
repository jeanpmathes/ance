private const newline = "\n";

public a = "a";
private b = "--------";

print_newline() 
{
	print newline;
	return 0;
}

main() 
{
	a = "c";
	b = "12345678";

	print "WELCOME";
	print a;
	print b;

	print_newline();

	return 0;
}