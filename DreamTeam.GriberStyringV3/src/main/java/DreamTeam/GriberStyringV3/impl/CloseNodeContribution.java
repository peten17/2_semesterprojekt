package DreamTeam.GriberStyringV3.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;
import com.ur.urcap.api.ui.annotation.Input;
import com.ur.urcap.api.ui.component.InputEvent;
import com.ur.urcap.api.ui.component.InputRadioButton;
import com.ur.urcap.api.ui.component.LabelComponent;

public class CloseNodeContribution implements ProgramNodeContribution {
	/*----------HTML ID/KEYS----------------------*/
	private final String RADIO50_ID = "radio1";
	private final String RADIO75_ID = "radio2";
	private final String RADIO100_ID = "radio3";
	private final String LABEL_ID = "labelpromt";
	
	//Radio buttons
	@Input(id = RADIO50_ID)
	public InputRadioButton radio50;
	
	@Input(id = RADIO75_ID)
	public InputRadioButton radio75;
	
	@Input(id = RADIO100_ID)
	public InputRadioButton radio100;
	
	@Input(id = LABEL_ID)
	public LabelComponent label;
	
	/*--------- Send to server variables ---------*/
	private final String popupTitle = "From Close Node: ";
	private final String message = "I will ask to close gripper";
	private final String command = "Close";
	private String force = "";
	private final String STATIC_IP_ADD = "10.125.45.176";
	private final int STATIC_Port = 8080;
	private final String socketName = "my_socket";
	/*--------------------------------------------*/
	
	/*--------------HTML implementation-----------*/
	@Input(id = RADIO50_ID)
	public void radio50Select(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_CHANGE){
			//label.setVisible(false);
			force = "50";
		}
	}
	
	@Input(id = RADIO75_ID)
	public void radio75Select(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_CHANGE){
			//label.setVisible(false);
			force = "75";
		}
	}
	
	@Input(id = RADIO100_ID)
	public void radio100Select(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_CHANGE){
			//label.setVisible(true);
			force = "100";
		}
	}
	/*--------------------------------------------*/
	
	private final DataModel model;
	private final URCapAPI api;	
	
	public CloseNodeContribution(DataModel model, URCapAPI api){
		this.model = model;
		this.force = "50";
		this.api = api;
	}

	@Override
	public void openView() {
		//on first openView
		if (!radio50.isSelected() && !radio75.isSelected() && !radio100.isSelected()){
			radio50.setSelected();
		}
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
		writer.assign("socketName", "\"" + socketName + "\"");
		writer.assign("command", "\"" + command + ";" + force + "\"");
//		writer.assign("force", "\"" + force + "\"");
		writer.appendLine("textmsg(Title, message)");
		writer.appendLine("textmsg(\"Command \", command)");
		writer.appendLine("socket_open(IP, port, socketName)");
		writer.appendLine("socket_send_string(command, socketName)");
		writer.appendLine("socket_close(socketName)");
		
		//insert wait on script level
		writer.appendLine("sleep(0.5)");
	}

}
