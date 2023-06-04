
@SuppressWarnings("serial")
public class ExWrongLeaveDate extends ExWrongLeave
{
	public ExWrongLeaveDate() {super("Wrong Date.  System date is already "+SystemDate.getInstance()+"!");}
	public ExWrongLeaveDate(String message) { super(message); }
}