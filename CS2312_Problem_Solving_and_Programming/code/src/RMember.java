
public class RMember extends Role{
	public RMember(Team t) {
		super(t);
	}
	
	@Override
	public String getNameAndRole(Employee e) {
		return e.getName();
	}

	@Override
	public String getRole() {
		return super.getTeam().getName();
	}
}
