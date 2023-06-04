
public class CmdAddTeamMember extends RecordedCommand{
	private Team team;
	private Employee person;
	private Role role;
	
	public void execute(String[] cmdParts) {
		try {
			if(cmdParts.length<3)
				throw new ExInsufficientArguments();
			team = Company.getInstance().findTeam(cmdParts[1]);
			person = Company.getInstance().findEmployee(cmdParts[2]);
			team.addMember(person); 
			role = new RMember(team);
			person.addRole(role);
			
			
			addUndoCommand(this);
			clearRedoList();
			System.out.println("Done.");
		} catch (ExInsufficientArguments e) {
			System.out.println(e.getMessage());
		} catch (ExEmployeeNotFound e) {
			System.out.println(e.getMessage());
		} catch (ExEmployeeExist e) {
			System.out.println(e.getMessage());
		} catch (ExTeamNotFound e) {
			System.out.println(e.getMessage());
		}
	}

	@Override
	public void undo() {
		team.deleteMember(person);
		person.deleteRole(role);
		addRedoCommand(this);
	}

	@Override
	public void redo() {
		try {
			person.addRole(role);
			role.getTeam().addMember(person); 
			addUndoCommand(this);
		} catch (ExEmployeeExist e) {
			System.out.println(e.getMessage());
		}
	}
}
