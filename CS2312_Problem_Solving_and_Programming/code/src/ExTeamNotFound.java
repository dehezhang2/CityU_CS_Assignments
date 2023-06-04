
@SuppressWarnings("serial")
public class ExTeamNotFound extends Exception
{
	public ExTeamNotFound() { super("Team not found!"); }
	public ExTeamNotFound(String message) { super(message); }
}