package DreamTeam.GriberStyringV2.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;

public class OpenNodeContribution implements ProgramNodeContribution {
	
	/*--------- Send to server variables ---------*/
	private final String popupTitle = "From Open Node: ";
	private final String message = "Open script executing";
	private final String command = "Open";
	private final String STATIC_IP_ADD = "10.125.45.176";
	private final int STATIC_Port = 8080;
	private final String socketName = "my_socket";
	/*--------------------------------------------*/
	
	private final DataModel model;
	private final URCapAPI api;
	
	OpenNodeContribution(DataModel model, URCapAPI api){
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
		return "Open external gripper";
	}

	@Override
	public boolean isDefined() {
		return true;
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		writer.assign("message","\"" + message + "\"");
		writer.assign("Title", "\"" + popupTitle + "\"");
		writer.assign("socketName", "\"" + socketName + "\"");
		writer.assign("command", "\"" + message + "\"");
		
		//log
		writer.appendLine("textmsg(Title, message)");
		
		//attempt connection + send command to server
		writer.appendLine("socket_open(IP, port, socketName)");
		writer.appendLine("socket_send_string(command, socketName)");
		writer.appendLine("socket_close(socketName)");
		
	}

}
