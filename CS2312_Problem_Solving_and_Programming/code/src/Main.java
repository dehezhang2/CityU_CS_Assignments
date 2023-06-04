import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {

	@SuppressWarnings("resource")
	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);

		System.out.print("Please input the file pathname: ");
		String filepathname = in.nextLine();
		
		Scanner inFile = null;
		
		try {
			inFile = new Scanner(new File(filepathname));

			String cmdLine1 = inFile.nextLine();
			String[] cmdLine1Parts = cmdLine1.split("\\|");
			System.out.println("\n> "+cmdLine1);
			SystemDate.createTheInstance(cmdLine1Parts[1]);
			
			while (inFile.hasNext())		
			{
				String cmdLine = inFile.nextLine().trim();
				
				if (cmdLine.equals("")) continue;  

				System.out.println("\n> "+cmdLine);
				String[] cmdParts = cmdLine.split("\\|"); 
				
				switch(cmdParts[0]) {
				case "hire":
					(new CmdHire()).execute(cmdParts);
					break;
				case "listEmployees":
					(new CmdListEmployees()).execute(cmdParts);
					break;
				case "listTeams":
					(new CmdListTeams()).execute(cmdParts);
					break;
				case "setupTeam":
					(new CmdSetUpTeam()).execute(cmdParts);
					break;
				case "startNewDay":
					(new CmdNewDay()).execute(cmdParts);
					break;
				case "takeLeave":
					(new CmdTakeLeave()).execute(cmdParts);
					break;
				case "listLeaves":
					(new CmdListLeave()).execute(cmdParts);
					break;
				case "listRoles":
					(new CmdListRoles()).execute(cmdParts);
					break;
				case "addTeamMember":
					(new CmdAddTeamMember()).execute(cmdParts);
					break;
				case "listTeamMembers":
					(new CmdListTeamMember()).execute(cmdParts);
					break;
				case "undo":
					RecordedCommand.undoOneCommand();
					break;
				case "redo":
					RecordedCommand.redoOneCommand();
					break;
				default: throw new ExWrongCommand();
				}
			}
			
		} catch (FileNotFoundException e) {
			System.out.println("File not Found!");
		} catch (ExWrongCommand e) {
			System.out.println("Unknown command - ignored!");
		} catch (InputMismatchException e) {
			System.out.println("File content problem.  Program terminated.");
		}
		finally {
			inFile.close();
			in.close();
		}
	}
}
