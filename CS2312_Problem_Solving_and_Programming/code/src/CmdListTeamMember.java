
public class CmdListTeamMember implements Command{
	public void execute(String[] cmdParts) {
		Company.getInstance().listTeamMembers();
	}
}
