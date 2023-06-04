
@SuppressWarnings("serial")
public class ExWrongCommand extends Exception
{
	public ExWrongCommand() { super("Wrong Command"); }   
	public ExWrongCommand(String message) { super(message); } 
}