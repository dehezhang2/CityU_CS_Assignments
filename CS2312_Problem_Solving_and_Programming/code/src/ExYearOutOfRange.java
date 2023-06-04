
@SuppressWarnings("serial")
public class ExYearOutOfRange extends Exception
{
	public ExYearOutOfRange() { super("Annual leaves out of range (0-300)!"); }
	public ExYearOutOfRange(String message) { super(message); }
}