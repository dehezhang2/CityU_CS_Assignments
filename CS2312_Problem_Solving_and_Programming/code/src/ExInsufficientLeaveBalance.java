
@SuppressWarnings("serial")
public class ExInsufficientLeaveBalance extends ExWrongLeave
{
	public ExInsufficientLeaveBalance(int balance){super("Insufficient balance. "+ balance +" days left only!");}
	public ExInsufficientLeaveBalance(String message) { super(message); }
}