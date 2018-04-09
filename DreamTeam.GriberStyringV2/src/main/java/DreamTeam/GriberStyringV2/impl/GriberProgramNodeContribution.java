package DreamTeam.GriberStyringV2.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;
import com.ur.urcap.api.ui.annotation.Input;
import com.ur.urcap.api.ui.component.InputButton;

public class GriberProgramNodeContribution implements ProgramNodeContribution {
	
	private final DataModel model;
	private final URCapAPI api;
	
	/*------Button/HTML handling variables--------*/
//	private final String BUTTON_OPEN_ID = "Open";
//	private final String BUTTON_CLOSE_ID = "Close";
//	
//	@Input(id = BUTTON_OPEN_ID)
//	public InputButton buttonOpen;
//
//	@Input(id = BUTTON_CLOSE_ID)
//	public InputButton buttonClose;
	/*--------------------------------------------*/
	
	
	/*--------- Send to server variables ---------*/
	private final String popupTitle = "From Parent Node: ";
	private final String message = "I will hopefully ask is you want to open or close the gripper";
	private final String IPAdd = "10.125.45.176";
	private final int port = 8080;
	private final String socketName = "my_socket";
	/*--------------------------------------------*/
	
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
		writer.assign("command", "\"" + message + "\"");
		writer.appendLine("textmsg(Title, message)");
		writer.appendLine("socket_open(IP, port, socketName)");
		writer.appendLine("socket_send_string(command, socketName)");
		writer.appendLine("socket_close(socketName)");
		//writer.appendLine("popup(\"" + message + "\", Title, False, False, blocking=True)");
	}
	
}
