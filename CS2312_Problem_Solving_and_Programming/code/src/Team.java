import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
 
public class Team implements Comparable<Team>{
    private String name;
    private Day datesetup;
    private ArrayList<Employee> allMembers;
    private ArrayList<RActHead> allActHeaders;
     
    public Team(String str) {
        name = str;
        allMembers = new ArrayList<>();
        allActHeaders = new ArrayList<>();
        datesetup = SystemDate.getInstance().clone();
    }
     
    public Employee findMember(String name) throws ExEmployeeNotFound {
        return Employee.searchEmployee(allMembers, name);
    }
     
    public void addMember(Employee e) throws ExEmployeeExist {
        for(Employee m:allMembers) {
            if(m==e)
                throw new ExEmployeeExist("Employee has already joined the team!");
        }
        allMembers.add(e);
        Collections.sort(allMembers);
    }
     
    public void deleteMember(Employee e) {
        allMembers.remove(e);
    }
     
    public void dismiss() {
        for(Employee e:allMembers) {
            e.deleteRole(this);
        }
    }
     
    public void listMember() {
        System.out.println(name+":");
        for(Employee e:allMembers) {
            System.out.println(e.getRole(this).getNameAndRole(e));
        }
        if(!allActHeaders.isEmpty()) {
            System.out.println("Acting heads:");
            for(RActHead head:allActHeaders) {
                System.out.println(head);
            }
        }
    }
     
    public void addActHeader(RActHead head) {
        allActHeaders.add(head);
        Collections.sort(allActHeaders,new Comparator<RActHead>() {
 
            @Override
            public int compare(RActHead head1, RActHead head2) {
                return head1.getPeriod().compareTo(head2.getPeriod());
            }
             
        });
    }
     
     
    public void deleteActHeader(RActHead head) {
        allActHeaders.remove(head);
    }
     
    public String getName() {return this.name;}
     
    private Employee getLeader() {
        for(Employee e:allMembers) {
            if(e.getRole(this) instanceof RLeader) {
                return e;
            }
        }
        return null;
    } 
     
    @Override
    public int compareTo(Team o) {
        return this.name.compareTo(o.name);
    }
 
    public static void list(ArrayList<Team> list) {
        System.out.printf("%-30s%-10s%-13s\n","Team Name","Leader","Setup Date");
        for(Team t:list) {
            System.out.printf("%-30s%-10s%-13s\n",t.name,t.getLeader().getName(),t.datesetup.toString());
        }
    }
 
    public static Team searchTeam(ArrayList<Team> list,String name) throws ExTeamNotFound {
        for(Team t:list) {
            if(t.getName().equals(name)) {
                return t;
            }
        }
        throw new ExTeamNotFound();
    }
     
}