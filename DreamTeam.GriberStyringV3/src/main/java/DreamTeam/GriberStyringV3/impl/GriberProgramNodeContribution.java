package DreamTeam.GriberStyringV3.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.contribution.ProgramNodeService;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.program.ProgramModel;
import com.ur.urcap.api.domain.program.nodes.ProgramNodeFactory;
import com.ur.urcap.api.domain.program.structure.TreeNode;
import com.ur.urcap.api.domain.program.structure.TreeStructureException;
import com.ur.urcap.api.domain.script.ScriptWriter;
import com.ur.urcap.api.ui.annotation.Input;
import com.ur.urcap.api.ui.component.InputButton;
import com.ur.urcap.api.ui.component.InputEvent;
import com.ur.urcap.api.ui.component.InputTextField;

public class GriberProgramNodeContribution implements ProgramNodeContribution {
	
	private final DataModel model;
	private final URCapAPI api;
	
	/*------Button/HTML handling variables--------*/
	private final String OPEN_TEMPLATE = "Open socket gripper";
	private final String CLOSE_TEMPLATE = "Close socket gripper";
	private final String BUTTON_OPEN_ID = "buttonOpen";
	private final String BUTTON_CLOSE_ID = "buttonClose";
	private final String BUTTON_RESET_ID = "buttonReset";
	private final String IP_FIELD_ID = "ipInput";
	private final String PORT_FIELD_ID = "portInput";
	
	//Node id holder for model
	private final String NODE_NAME = "NodeType";
	private final String DEFAULT_NAME = "Socket Gripper";
	
	//IP/port DataModel holders
	private final String IP_KEY = "IP";
	private final String PORT_KEY = "PORT";
	
	
	//Buttons
	@Input(id = BUTTON_OPEN_ID)
	public InputButton buttonOpen;

	@Input(id = BUTTON_CLOSE_ID)
	public InputButton buttonClose;
	
	@Input(id = BUTTON_RESET_ID)
	public InputButton buttonReset;
	
	//Input fields
	@Input(id = IP_FIELD_ID)
	private InputTextField ipIn;
	
	@Input(id = PORT_FIELD_ID)
	private InputTextField portIn;

	/*------------------------------------*/
	//On press events:
	@Input (id = BUTTON_OPEN_ID)
	public void buttonOpenClick(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_PRESSED){
			model.set(NODE_NAME, OPEN_TEMPLATE);
			createTree(OPEN_TEMPLATE);
			updateView();
//			setButtons(false, false, true);
		}
	}
	
	@Input (id = BUTTON_CLOSE_ID)
	public void buttonCloseClick(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_PRESSED){
			model.set(NODE_NAME, CLOSE_TEMPLATE);
			createTree(CLOSE_TEMPLATE);
			updateView();
//			setButtons(false, false, true);
		}
	}
	
	@Input (id = BUTTON_RESET_ID)
	public void buttonResetClick(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_PRESSED){
			model.set(NODE_NAME, DEFAULT_NAME);
			clearTree();
			updateView();
//			setButtons(true, true, false);
		}
	}
	
	public void setButtons(boolean open, boolean close, boolean reset){
		buttonClose.setEnabled(close);
		buttonOpen.setEnabled(open);
		buttonReset.setEnabled(reset);
	}
	
	public void updateView(){
		int childCnt =
				api.getProgramModel().getRootTreeNode(this).getChildren().size();
		boolean emptyTree = (childCnt==0);
		setButtons(emptyTree, emptyTree, !emptyTree);
		
		ipIn.setText(getIPIn());
		portIn.setText(Integer.toString(getPortIn()));
	}
	
	public void clearTree() {
		TreeNode tree = api.getProgramModel().getRootTreeNode(this);
		int size = tree.getChildren().size();
		try {
			for (int i = 0; i < size; i++) {
				tree.removeChild(tree.getChildren().get(0));
			}
		} catch (TreeStructureException e){
			
		}
	}
	
	public void createTree(String template){
		ProgramModel programModel = api.getProgramModel();
		ProgramNodeFactory nf = programModel.getProgramNodeFactory();
		TreeNode root = programModel.getRootTreeNode(this);
		root.setChildSequenceLocked(true);
		
		try {
			addCommand(template, root, nf);
		} catch (TreeStructureException e){
			
		}
	}
	
	public void addCommand(String template, TreeNode root, ProgramNodeFactory nf)
			throws TreeStructureException {
		Class<? extends ProgramNodeService> clazz =
				template.equals(CLOSE_TEMPLATE)
						? CloseNodeService.class
						: OpenNodeService.class;
		root.addChild(nf.createURCapProgramNode(clazz));
	}
	
	/*------------Input field methods-------------*/
	public String getIPIn(){
		if (!model.isSet(IP_KEY)){
			model.set(IP_KEY, "input IP");
		}
		return model.get(IP_KEY, "000.000.000.000");
	}
	
	public int getPortIn(){
		if (!model.isSet(PORT_KEY)){
			model.set(PORT_KEY, 0);
		}
//		if (portIn.getText() == ""){
//			portIn.setText("0");
//		}
		return model.get(PORT_KEY, Integer.parseInt(portIn.getText()));
	}
	
	@Input(id = IP_FIELD_ID)
	public void ipChange(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_CHANGE){
			if ("".equals(getIPIn())){
				ipIn.setText("Input IP");
				model.set(IP_KEY, "000.000.000.000");
			} else {
				model.set(IP_KEY, ipIn.getText());
			}
		}
	}
	
	@Input(id = PORT_FIELD_ID)
	public void portChange(InputEvent event){
		if (event.getEventType() == InputEvent.EventType.ON_CHANGE){
			if ("".equals(getPortIn())){
				ipIn.setText("0");
				model.set(PORT_KEY, 0);
			} else {
				model.set(PORT_KEY, Integer.parseInt(portIn.getText()));
			}
		}
	}
	
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
		//port input workaround
//		portIn.setText("0");
		
		updateView();
	}

	@Override
	public void closeView() {		
		
	}

	@Override
	public String getTitle() {
		//return "Socket Gripper";
		return model.get(NODE_NAME, DEFAULT_NAME);
	}

	@Override
	public boolean isDefined() {
		
		return !(getPortIn() == 0);
	}
	
	private String getErrorMessege(){
		return "Connecting to IP " + getIPIn() + " failed!";
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		// Create a URscript that connects to IP+Socket of RPI
		writer.assign("message","\"" + message + "\"");
		writer.assign("Title", "\"" + popupTitle + "\"");
		writer.assign("IP", "\"" + getIPIn() + "\"");
		writer.assign("port", Integer.toString(getPortIn()));
		writer.assign("portString", "\" " + Integer.toString(getPortIn()) + "\"");
		writer.assign("socketName", "\"" + socketName + "\"");
		writer.assign("command", "\"" + message + "\"");
		writer.assign("error", "\"" + getErrorMessege() + "\"");
//		writer.assign("controllerTemp", "0");
		
		//writer.appendLine("controllerTemp = get_controller_temp()");
		//log
		writer.appendLine("textmsg(Title, message)");
		writer.appendLine("textmsg(Title, IP)");
		writer.appendLine("textmsg(Title, port)");
//		writer.appendLine("textmsg(Title, controllerTemp)");
		
		//allow children access to variables
		writer.writeChildren();
	}
	
}
