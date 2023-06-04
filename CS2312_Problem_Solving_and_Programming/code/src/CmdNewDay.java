
public class CmdNewDay extends RecordedCommand{
	private String oldDay;
	@Override
	public void execute(String[] cmdParts) {
		try {
			if (cmdParts.length<2)
			    throw new ExInsufficientArguments();
			oldDay = SystemDate.getInstance().toString();
			SystemDate.getInstance().set(cmdParts[1]);
			
			addUndoCommand(this);
			clearRedoList();
			System.out.println("Done.");
		} catch (ExInsufficientArguments e) {
			System.out.println(e.getMessage());
		}
	}

	@Override
	public void undo() {
		String tmp = oldDay;
		oldDay = SystemDate.getInstance().toString();
		SystemDate.getInstance().set(tmp);
		addRedoCommand(this);
	}

	@Override
	public void redo() {
		String tmp = oldDay;
		oldDay = SystemDate.getInstance().toString();
		SystemDate.getInstance().set(tmp);
		addUndoCommand(this);
	}

}
