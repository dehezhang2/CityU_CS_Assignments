
@SuppressWarnings("serial")
public class ExEmployeeExist extends Exception
{
	public ExEmployeeExist() { super("Employee already exists!"); }
	public ExEmployeeExist(String message) { super(message); }
}