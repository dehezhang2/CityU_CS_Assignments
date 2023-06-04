
public class CmdListRoles implements Command{
	public void execute(String[] cmdParts) {
		try {
			if(cmdParts.length<2)
				throw new ExInsufficientArguments();
			Company.getInstance().findEmployee(cmdParts[1]).listRole();
		} catch (ExEmployeeNotFound e) {
			System.out.println(e.getMessage());
		} catch (ExInsufficientArguments e) {
			System.out.println(e.getMessage());
		}
	}
}
