package DreamTeam.GriberStyring.impl;

import com.ur.urcap.api.contribution.InstallationNodeContribution;
import com.ur.urcap.api.contribution.InstallationNodeService;
import com.ur.urcap.api.domain.URCapAPI;

import java.io.InputStream;

import com.ur.urcap.api.domain.data.DataModel;

/**
 *
 * @author Kasper_Melddgaard
 */
public class GripperControlInstallationService implements InstallationNodeService {

	public GripperControlInstallationService() {}
	
    @Override
    public String getTitle() {
        return "Gripper Control"; 
    }

    @Override
    public InputStream getHTML() {
        InputStream is = this.getClass().getResourceAsStream("/HTML/impl/installation.html");
        return is;
    }

    @Override
    public InstallationNodeContribution createInstallationNode(URCapAPI urcapi, DataModel model) {
        return new GripperControlInstallationNodeContribution(model);
    }

}
