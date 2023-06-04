
public class CmdListTeams implements Command{

	@Override
	public void execute(String[] cmdParts) {
		Company.getInstance().listTeams();
	}


}
