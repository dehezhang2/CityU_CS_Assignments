
@SuppressWarnings("serial")
public class ExEmployeeNotFound extends Exception
{
	public ExEmployeeNotFound() { super("Employee not found!"); }
	public ExEmployeeNotFound(String message) { super(message); }
}