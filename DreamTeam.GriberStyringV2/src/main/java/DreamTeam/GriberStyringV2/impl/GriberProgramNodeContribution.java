package DreamTeam.GriberStyringV2.impl;

import java.io.InputStream;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;

public class GriberProgramNodeContribution implements ProgramNodeContribution {
	
	private final DataModel model;
	private final URCapAPI api;
	private final String popupTitle = "Popup: ";
	private final String message = "Im being executed";
	private final String IPAdd = "10.125.45.176";
	private final int port = 8080;
	private final String socketName = "my_socket";
	
	public GriberProgramNodeContribution(DataModel model, URCapAPI api){
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
		
		return "Griber";
	}

	@Override
	public boolean isDefined() {
		
		return true;
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		// Create a URscript that connects to IP+Socket of RPI
		writer.assign("message","\"" + message + "\"");
		writer.assign("Title", "\"" + popupTitle + "\"");
		writer.assign("IP", "\"" + IPAdd + "\"");
		writer.assign("port", Integer.toString(port));
		writer.assign("socketName", "\"" + socketName + "\"");
		//writer.assign("command", "\"" + message + "\"");
		writer.assign("command", "\"" + message + "\"");
		writer.appendLine("textmsg(Title, IP)");
		writer.appendLine("socket_open(IP, port, socketName)");
		writer.appendLine("socket_send_string(command, socketName)");
		writer.appendLine("socket_close(socketName)");
		//writer.appendLine("popup(\"" + message + "\", Title, False, False, blocking=True)");
	}
	
}
