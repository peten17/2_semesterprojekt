package DreamTeam.GriberStyringV2.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;

public class CloseNodeContribution implements ProgramNodeContribution {
	
	/*--------- Send to server variables ---------*/
	private final String popupTitle = "From Close Node: ";
	private final String message = "I will ask to close gripper";
	private final String command = "Close";
	private final String IPAdd = "10.125.45.176";
	private final int port = 8080;
	private final String socketName = "my_socket";
	/*--------------------------------------------*/
	
	private final DataModel model;
	private final URCapAPI api;
	
	
	public CloseNodeContribution(DataModel model, URCapAPI api){
		this.model = model;
		this.api = api;
	}

	@Override
	public void openView() {
	}

	@Override
	public void closeView() {
	}

	@Override
	public String getTitle() {
		return "Close external gripper";
	}

	@Override
	public boolean isDefined() {
		return true;
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		writer.assign("message","\"" + message + "\"");
		writer.assign("Title", "\"" + popupTitle + "\"");
		writer.assign("IP", "\"" + IPAdd + "\"");
		writer.assign("port", Integer.toString(port));
		writer.assign("socketName", "\"" + socketName + "\"");
		writer.assign("command", "\"" + message + "\"");
		writer.appendLine("textmsg(Title, message)");
		writer.appendLine("socket_open(IP, port, socketName)");
		writer.appendLine("socket_send_string(command, socketName)");
		writer.appendLine("socket_close(socketName)");
	}

}
