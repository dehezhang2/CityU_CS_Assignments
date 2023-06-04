
public class RLeader extends Role{
	public RLeader(Team t) {
		super(t); 
	}
	
	@Override
	public String getNameAndRole(Employee e) {
		return e.getName()+" (Head of Team)";
	}

	@Override
	public String getRole() {
		return super.getTeam().getName() + " (Head of Team)";
	}
	
}
