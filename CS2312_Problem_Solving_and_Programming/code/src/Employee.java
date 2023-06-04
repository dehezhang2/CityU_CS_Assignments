import java.util.ArrayList;
import java.util.Collections;
 
public class Employee implements Comparable<Employee>{
    private String name;
    private int yrLeaveEntitled;
    private ArrayList<LeaveRecord> allLeaves;
    private ArrayList<Role> allRoles;
     
    public Employee(String n,int yle) throws ExYearOutOfRange {
        this.name = n;
        if(yle>300) throw new ExYearOutOfRange();
        this.yrLeaveEntitled = yle;
        allLeaves = new ArrayList<>();
        allRoles = new ArrayList<>();
    }
     
    public LeaveRecord createLeave(String startDay,String endDay){
        LeaveRecord l = new LeaveRecord(startDay,endDay);
        return l;
    }
     
    private LeaveRecord getLeaveOverlap(LeaveRecord l) {
        for(LeaveRecord leave:allLeaves) {
            if(leave.isOverLap(l))
                return leave;
        }
        return null;
    }
     
    private int getSumOfLeave() {
        int ans = 0;
        for(LeaveRecord l:allLeaves) {
            ans+=l.getDays();
        }
        return ans;
    }
     
    public RActHead getOverlapedRole(LeaveRecord l) {
        for(Role r:allRoles) {
            if(r instanceof RActHead) {
                LeaveRecord period = ((RActHead)r).getPeriod();
                if(l.isOverLap(period)) {
                    return (RActHead)r;
                }
            }
        }
        return null;
    }
     
    public boolean isLeader() {
        for(Role r:allRoles) {
            if(r instanceof RLeader) 
                return true;
        }
        return false;
    }
     
    public boolean isActHead() {
        for(Role r:allRoles) {
            if(r instanceof RActHead)
                return true;
        }
        return false;
    }
 
    public void addLeave(LeaveRecord l) {
        allLeaves.add(l);
        Collections.sort(allLeaves);
    }
     
    public void addLeave(String[] cmdParts,LeaveRecord l,ArrayList<RActHead> allAddedHeads) 
            throws ExEmployeeNotFound, ExTeamNotFound, ExInsufficientArguments, ExWrongLeaveDate, 
            ExActHeadMissing, ExInsufficientLeaveBalance, ExActHeadOnWorking, ExLeaveOverlap 
    {
        if(l.getStartDate().compareTo(SystemDate.getInstance())<0) {
            throw new ExWrongLeaveDate();
        }
         
        LeaveRecord overlap = getLeaveOverlap(l);
         
        if(overlap!=null)
            throw new ExLeaveOverlap(overlap);
         
        int sum = getSumOfLeave();
        if(sum+l.getDays()>yrLeaveEntitled)
            throw new ExInsufficientLeaveBalance(yrLeaveEntitled-sum);
         
        if(this.isActHead()) {
            RActHead overlapRole = getOverlapedRole(l);
            if(overlapRole!=null) {
                throw new ExActHeadOnWorking(name,overlapRole.getTeam().getName(),overlapRole.getPeriod().toString());
            }
        }
         
        if(this.isLeader()) {
            if(cmdParts.length<6||cmdParts.length%2==1)
                throw new ExInsufficientArguments();
            ArrayList<Team> criticalTeams = new ArrayList<>();
            for(Role r:allRoles) {
                if(r instanceof RLeader) {
                    criticalTeams.add(r.getTeam());
                }
            }
             
            for(int i=4;i<cmdParts.length;i+=2) {
                try {
                    Team team = Company.getInstance().findTeam(cmdParts[i]);
                    Employee person = team.findMember(cmdParts[i+1]);
                    overlap = person.getLeaveOverlap(l);
                    if(overlap!=null) {
                        throw new ExLeaveOverlap(person.getName()+" is on leave during "+overlap+"!");
                    }
                    criticalTeams.remove(team);
 
                } catch (ExTeamNotFound e) {
                    throw e;
                } catch (ExEmployeeNotFound e) {
                    throw new ExEmployeeNotFound("Employee ("+cmdParts[i+1]+") not found for "+cmdParts[i]+"!");
                }
            }
            if(!criticalTeams.isEmpty()) {
                throw new ExActHeadMissing(criticalTeams.get(0));
            }
            
            for(int i=4;i<cmdParts.length;i+=2) {
              Team t = Company.getInstance().findTeam(cmdParts[i]);
              Employee e = t.findMember(cmdParts[i+1]);
              RActHead head = new RActHead(e,t,l);
                   
              e.setRole(t, head);
              allAddedHeads.add(head);
              t.addActHeader(head);       
          }
        }
         
        allLeaves.add(l);
        Collections.sort(allLeaves);
    }
     
    public void deleteLeave(LeaveRecord l) {
        allLeaves.remove(l);
    }
     
    public void listLeave() {
        if(allLeaves.isEmpty())
            System.out.println("No leave record");
        for(LeaveRecord l:allLeaves)
            System.out.println(l);
    }
     
    public void addRole(Role r) {
        allRoles.add(r);
        Collections.sort(allRoles);
    }
     
    public void deleteRole(Role r) {
        allRoles.remove(r);
    }
     
    public void deleteRole(Team t) {
        Role delRole = findRole(t);
        if(t!=null) allRoles.remove(delRole);
    }
     
    private Role findRole(Team t) {
        for(Role r:allRoles) {
            if(r.getTeam()==t)
                return r;
        }
        return null;
    }
     
    public void listRole() {
        if(allRoles.isEmpty()) {
            System.out.println("No role");
        }
        else {
            for(Role r:allRoles)
                System.out.println(r.getRole());
        }
    }
     
    public Role getRole(Team t) {
        for(Role r:allRoles) {
            if(r.getTeam()==t)
                return r;
        }
        return null;
    }
     
    public void setRole(Team t,Role r) {
        deleteRole(getRole(t));
        addRole(r);
        Collections.sort(allRoles);
    }
     
    public String getName() {return this.name;}
 
    public int compareTo(Employee o) {
        return this.name.compareTo(o.name);
    }
     
    public String toString(){
        return name + " (Entitled Annual Leaves: " + this.yrLeaveEntitled+" days)";
    }
     
    public static Employee searchEmployee(ArrayList<Employee> list, String str) throws ExEmployeeNotFound {
        for(Employee e:list) {
            if(e.getName().equals(str)) {
                return e;
            }
        }
        throw new ExEmployeeNotFound();
    }
 
}