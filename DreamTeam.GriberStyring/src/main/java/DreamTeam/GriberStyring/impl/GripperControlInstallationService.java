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

    @Override
    public String getTitle() {
        return "Gripper Control"; 
    }

    @Override
    public InputStream getHTML() {
        InputStream is = this.getClass().getResourceAsStream("/src/main/resources/HTML/impl/installation.html");
        return is;
    }

    @Override
    public InstallationNodeContribution createInstallationNode(URCapAPI urcapi, DataModel dm) {
        return new GripperControlInstallationNodeContribution(dm);
    }

}
