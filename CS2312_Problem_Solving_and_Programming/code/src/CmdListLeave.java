
public class CmdListLeave implements Command{

	@Override
	public void execute(String[] cmdParts) {
		try {
			if(cmdParts.length==1)
				Company.getInstance().listLeaves();
			else {
				Company.getInstance().findEmployee(cmdParts[1]).listLeave();
			}
		} catch (ExEmployeeNotFound e) {
			System.out.println(e.getMessage());
		}
	}

}
