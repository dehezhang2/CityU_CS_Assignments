public class CmdSetUpTeam extends RecordedCommand{
    private Team team;
    private Role theRole;
    private Employee leader;
     
    @Override
    public void execute(String[] cmdParts) {
        try {
            if (cmdParts.length!=3)
                throw new ExInsufficientArguments();
            // must do this at first
            team = Company.getInstance().createTeam(cmdParts[1]);
            leader =Company.getInstance().findEmployee(cmdParts[2]);
            Company.getInstance().addTeam(team);
             
            theRole = new RLeader(team);
            leader.addRole(theRole);
             
            team.addMember(leader);
             
            addUndoCommand(this);
            clearRedoList();
            System.out.println("Done.");
        } catch (ExEmployeeNotFound e) {
            System.out.println(e.getMessage());
        } catch (ExInsufficientArguments e) {
            System.out.println(e.getMessage());
        } catch (ExTeamExist e) {
            System.out.println(e.getMessage());
        } catch (ExEmployeeExist e) {
            System.out.println(e.getMessage());
        }
    }
 
    @Override
    public void undo() {
        Company.getInstance().deleteTeam(team);
        addRedoCommand(this);
    }
 
    @Override
    public void redo() {
        try {
            Company.getInstance().addTeam(team);
            leader.addRole(theRole);
        } catch (ExTeamExist e) {
            System.out.println(e.getMessage());
        }
        addUndoCommand(this);   
    }
 
}