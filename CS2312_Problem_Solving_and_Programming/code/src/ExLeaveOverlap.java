
@SuppressWarnings("serial")
public class ExLeaveOverlap extends ExWrongLeave
{
	public ExLeaveOverlap(LeaveRecord overlap) {super("Overlap with leave from "+overlap+"!");}
	public ExLeaveOverlap(String message) { super(message); }
}