
@SuppressWarnings("serial")
public class ExActHeadOnWorking extends ExWrongLeave
{
	public ExActHeadOnWorking(String message) { super(message); }
	public ExActHeadOnWorking(String employeeName,String teamName,String period) {super("Cannot take leave.  "+employeeName
			+" is the acting head of "+teamName+" during "
			+period+"!");}
}