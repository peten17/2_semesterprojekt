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
    
    private static final String IP_KEY = "ip";
    private static final String PORT_KEY = "port";
    private static final String DEFAULT_IP = "000.000.000.000";
    private static final String DEFAULT_PORT = "1";
    private DataModel model;

    public GripperControlInstallationNodeContribution(DataModel model) {
        this.model = model;
        
    }
    
    private InputTextField ipAddress;
    private InputTextField portNum;
    
    public void setIP(String ip){
        if("".equals(ip)){
            resetIP();
        }else {
            model.set(IP_KEY, ip);
        }
    }
    
    public void resetIP(){
        ipAddress.setText(DEFAULT_IP);
        model.set(IP_KEY, DEFAULT_IP);
    }

    @Override
    public void openView() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void closeView() {
    }

    @Override
    public void generateScript(ScriptWriter writer) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    

}
