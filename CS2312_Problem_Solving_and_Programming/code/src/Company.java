import java.util.Collections;
import java.util.ArrayList;
 
public class Company {
    private ArrayList<Employee> allEmployee;
    private ArrayList<Team> allTeams;
     
    private static Company instance = new Company();
     
    private Company() {
        allEmployee = new ArrayList<>();
        allTeams = new ArrayList<>();
    }
     
    public static Company getInstance() {return instance;}
     
    public Employee createEmployee(String n,int yle) throws ExYearOutOfRange {
        Employee e = new Employee(n,yle);
        return e;
    }
     
    public Employee findEmployee(String name) throws ExEmployeeNotFound {
        return Employee.searchEmployee(allEmployee, name);
    }
     
    public void listEmployees() {
        for(Employee e:allEmployee) {
            System.out.println(e);
        }
    }
     
    public void deleteEmployee(Employee e) {
        allEmployee.remove(e);
    }
     
    public void addEmployee(Employee e) throws ExEmployeeExist {
        for(Employee person:allEmployee) {
            if(person.getName().equals(e.getName()))
                throw new ExEmployeeExist();
        }
        allEmployee.add(e);
        Collections.sort(allEmployee);
    }
     
    public Team createTeam(String str) throws ExEmployeeNotFound{
        Team t = null;
        t = new Team(str);
        return t;
         
    }
     
    public Team findTeam(String name) throws ExTeamNotFound {
        return Team.searchTeam(allTeams, name);
    }
     
    public void deleteTeam(Team t) {
        allTeams.remove(t);
        t.dismiss();
    }
     
    public void addTeam(Team t) throws ExTeamExist {
        for(Team team : allTeams) {
            if(team.getName().equals(t.getName()))
                throw new ExTeamExist();
        }
        allTeams.add(t);
        Collections.sort(allTeams);
    }
     
    public void listTeams() {Team.list(allTeams);}
     
    public void listTeamMembers() {
        for(int i=0;i<allTeams.size();i++) {
            if(i>0) System.out.println();
            allTeams.get(i).listMember();
        }
    }
     
    public void listLeaves() {
        for(Employee e:allEmployee) {
            System.out.println(e.getName()+":");
            e.listLeave();
        }
    }
     
}