import java.util.ArrayList;
 
public class CmdTakeLeave extends RecordedCommand{
    private LeaveRecord theLeave;
    private Employee person;
    private ArrayList<RActHead> allAddedHead = new ArrayList<>();
     
    public void execute(String[] cmdParts) {
        try {
            if(cmdParts.length<4)
                throw new ExInsufficientArguments();
             
            person = Company.getInstance().findEmployee(cmdParts[1]);
            theLeave = person.createLeave(cmdParts[2], cmdParts[3]);
            person.addLeave(cmdParts, theLeave,allAddedHead);
       
            addUndoCommand(this);
            clearRedoList();
            System.out.println("Done.");
             
        } catch (ExInsufficientArguments e) {
            System.out.println(e.getMessage());
        } catch (ExEmployeeNotFound e) {
            System.out.println(e.getMessage());
        } catch (ExWrongLeave e) {
            System.out.println(e.getMessage());
        } catch (ExTeamNotFound e) {
            System.out.println(e.getMessage());
        }
    }
 
    @Override
    public void undo() {
        person.deleteLeave(theLeave);
        if(person.isLeader()) {
            for(RActHead head:allAddedHead) {
                head.getPerson().setRole(head.getTeam(), new RMember(head.getTeam()));
                head.getTeam().deleteActHeader(head);
            }
        }
         
        addRedoCommand(this);
    }
 
    @Override
    public void redo() {
        person.addLeave(theLeave);
 
        if(person.isLeader()) {
            for(RActHead head:allAddedHead) {
                head.getPerson().setRole(head.getTeam(), head);
                head.getTeam().addActHeader(head);
            }
        }
             
        addUndoCommand(this);
    }
     
}