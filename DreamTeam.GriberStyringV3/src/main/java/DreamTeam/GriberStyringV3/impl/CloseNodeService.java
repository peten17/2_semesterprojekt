package DreamTeam.GriberStyringV3.impl;

import java.io.InputStream;

import com.ur.urcap.api.contribution.NonUserInsertable;
import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.contribution.ProgramNodeService;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;

public class CloseNodeService implements ProgramNodeService, NonUserInsertable{
	
	public CloseNodeService() {
	}

	@Override
	public String getId() {
		return "Close Node";
	}

	@Override
	public boolean isDeprecated() {
		return false;
	}

	@Override
	public boolean isChildrenAllowed() {
		return false;
	}

	@Override
	public String getTitle() {
		return "Close Node";
	}

	@Override
	public InputStream getHTML() {
		InputStream is = this.getClass().getResourceAsStream("/html/CloseNode.html");
		return is;
	}

	@Override
	public ProgramNodeContribution createNode(URCapAPI api, DataModel model) {
		return new CloseNodeContribution(model, api);
	}

}
