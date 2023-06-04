public abstract class Role implements Comparable<Role>
{
	private Team team;
	
	public Role(Team t) {
		this.team = t;
	}
	
	public Team getTeam() {
		return team;
	}
	
	@Override
	public int compareTo(Role other) {
		return team.compareTo(other.team);
	}
	
	public abstract String getNameAndRole(Employee e);
	public abstract String getRole();

}