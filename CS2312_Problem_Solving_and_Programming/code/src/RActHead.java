
public class RActHead extends RMember{
	private Employee person;
	private LeaveRecord period;
	
	public RActHead(Employee e, Team t,LeaveRecord p) {
		super(t);
		this.person = e;
		this.period = p;
	}
	
	public LeaveRecord getPeriod() {
		return period;
	}
	
	public Employee getPerson() {
		return person;
	}
	
	public String toString() {
		return period+": "+person.getName();
	}
	
}
