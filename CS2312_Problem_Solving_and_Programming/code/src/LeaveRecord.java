
public class LeaveRecord implements Comparable<LeaveRecord>{
	private Day startDate;
	private Day endDate;
	private int days;
	
	public LeaveRecord(String str1, String str2) {
		startDate = new Day(str1);
		endDate = new Day(str2);
		days = Day.elapse(startDate, endDate);
	}
	
	public String toString() {
		return startDate+" to "+endDate;
	}
	
	public Day getStartDate() {return startDate;}
	
	public int getDays() {return days;}
	
	@Override
	public int compareTo(LeaveRecord otherLeave) {
		return startDate.compareTo(otherLeave.startDate);
	}

	public boolean isOverLap(LeaveRecord otherLeave) {
		return !(startDate.compareTo(otherLeave.endDate)>0)&&!(endDate.compareTo(otherLeave.startDate)<0);
	}
	
	
}