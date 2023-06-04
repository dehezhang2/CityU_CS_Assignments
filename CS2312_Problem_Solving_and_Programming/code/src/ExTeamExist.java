
@SuppressWarnings("serial")
public class ExTeamExist extends Exception
{
	public ExTeamExist() { super("Team already exists!"); }
	public ExTeamExist(String message) { super(message); }
}