
public class CmdListEmployees implements Command{
	public void execute(String[] cmdParts) {
		Company.getInstance().listEmployees();
	}
}
