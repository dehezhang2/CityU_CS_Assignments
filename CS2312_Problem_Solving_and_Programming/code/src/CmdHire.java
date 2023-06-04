
public class CmdHire extends RecordedCommand{
	private Employee person;
	
	public void execute(String[] cmdParts) {
		try {
			if (cmdParts.length<3)
			    throw new ExInsufficientArguments();
			person = Company.getInstance().createEmployee(cmdParts[1],Integer.parseInt(cmdParts[2]));
			Company.getInstance().addEmployee(person);
			
			addUndoCommand(this);
			clearRedoList();
			System.out.println("Done.");
		} catch (NumberFormatException e) {
			System.out.println("Wrong number format!");
		} catch (ExEmployeeExist e) {
			System.out.println(e.getMessage());
		} catch (ExInsufficientArguments e) {
			System.out.println(e.getMessage());
		} catch (ExYearOutOfRange e) {
			System.out.println(e.getMessage());
		} 
	}

	@Override
	public void undo() {
		Company.getInstance().deleteEmployee(person);
		addRedoCommand(this);
	}

	@Override
	public void redo() {
		try {
			Company.getInstance().addEmployee(person);
		} catch (ExEmployeeExist e) {
			System.out.println(e.getMessage());
		}
		addUndoCommand(this);
	}
}
