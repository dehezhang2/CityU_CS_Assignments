
@SuppressWarnings("serial")
public class ExActHeadMissing extends ExWrongLeave
{
	public ExActHeadMissing(Team criticalTeam) {super("Please name a member to be the acting head of "+criticalTeam.getName());}
	public ExActHeadMissing(String message) { super(message); }
}