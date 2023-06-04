
@SuppressWarnings("serial")
public class ExInsufficientArguments extends Exception
{
	public ExInsufficientArguments() { super("Insufficient command arguments!"); }
	public ExInsufficientArguments(String message) { super(message); }
}