package DreamTeam.GriberStyring.impl;

import com.ur.urcap.api.contribution.InstallationNodeContribution;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;
import com.ur.urcap.api.ui.annotation.Input;
import com.ur.urcap.api.ui.component.InputEvent;
import com.ur.urcap.api.ui.component.InputTextField;

/**
 *
 * @author Kasper_Melddgaard
 */
public class GripperControlInstallationNodeContribution implements InstallationNodeContribution {
    
    private static final String IP_KEY = "setIP";
    private static final String PORT_KEY = "setPort";
    private static final String DEFAULT_IP = "000.000.000.000";
    private static final String DEFAULT_PORT = "1";
    private DataModel model;

    public GripperControlInstallationNodeContribution(DataModel model) {
        this.model = model;
        
    }
    
    @Input(id = IP_KEY)
    private InputTextField ipAddress;
    
    @Input(id = PORT_KEY)
    private InputTextField portNum;
    
//    @Input(id = IP_KEY)
//    public void onIPChange(InputEvent event) {
//		if (event.getEventType() == InputEvent.EventType.ON_CHANGE) {
//			setIP(ipAddress.getText());
//		}
//	}
//    
//        @Input(id = PORT_KEY)
//    public void onPortChange(InputEvent event) {
//		if (event.getEventType() == InputEvent.EventType.ON_CHANGE) {
//			setIP(portNum.getText());
//		}
//	}
        
    public void setIP(String ip){
        if("".equals(ip)){
            resetIP();
        }else {
            model.set(IP_KEY, ip);
        }
    }
    
    public String getIP(){
        if (!model.isSet(IP_KEY)){
            this.resetIP();
        }
        return model.get(IP_KEY, DEFAULT_IP);
    }
    
    public void resetIP(){
<<<<<<< HEAD
        ipAddress.setText(null);
=======
        ipAddress.setText(DEFAULT_IP);
>>>>>>> 5d7886b56f87afd1aa37fc8329345edf9a7350a7
        model.set(IP_KEY, DEFAULT_IP);
    }
    
    public void setPort(String port){
        if ("".equals(port)){
            resetPort();
        } else{
            model.set(PORT_KEY, port);
        }
    }
    
    public void resetPort(){
        portNum.setText(DEFAULT_PORT);
        model.set(PORT_KEY, DEFAULT_PORT);
    }
    
    public String getPort(){
        if (!model.isSet(PORT_KEY)){
            this.resetPort();
        }
        return model.get(PORT_KEY, DEFAULT_PORT);
    }

    @Override
    public void openView() {
        ipAddress.setText(getIP());
        portNum.setText(getPort());
    }

    @Override
    public void closeView() {
    }

    @Override
    public void generateScript(ScriptWriter writer) {
        writer.assign("Grip_Controller_IP", "\"" +  this.getIP() + "\"");
        writer.assign("Grip_Controller_Port", "\"" + this.getPort() + "\"" );
    }
    

}
