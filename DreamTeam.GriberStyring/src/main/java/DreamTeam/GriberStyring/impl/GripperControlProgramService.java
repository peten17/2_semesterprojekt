package DreamTeam.GriberStyring.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.contribution.ProgramNodeService;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import java.io.InputStream;

/**
 *
 * @author Kasper_Melddgaard
 */
public class GripperControlProgramService implements ProgramNodeService {

    public GripperControlProgramService() {
    }
    
    

    @Override
    public String getId() {
        return "GripperControlNode";
    }

    @Override
    public boolean isDeprecated() {
        return true;
    }

    @Override
    public boolean isChildrenAllowed() {
        return false;
    }

    @Override
    public String getTitle() {
        return "GripperControl";
    }

    @Override
    public InputStream getHTML() {
        InputStream is = this.getClass().getResourceAsStream("/src/main/resources/HTML/impl/programnode.html");
            
        return is;
    }

    @Override
    public ProgramNodeContribution createNode(URCapAPI api, DataModel model) {
        return new GripperControlProgramContribution(api, model);
    }

}
