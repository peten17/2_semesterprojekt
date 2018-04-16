package DreamTeam.GriberStyringV2.impl;

import java.io.InputStream;

import com.ur.urcap.api.contribution.NonUserInsertable;
import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.contribution.ProgramNodeService;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;

public class OpenNodeService implements ProgramNodeService, NonUserInsertable {
	
	public OpenNodeService(){
	}

	@Override
	public String getId() {
		return "Open Node";
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
		return "OpenNode";
	}

	@Override
	public InputStream getHTML() {
		InputStream is = this.getClass().getResourceAsStream("/html/OpenNode.html");
		return is;
	}

	@Override
	public ProgramNodeContribution createNode(URCapAPI api, DataModel model) {
		return new OpenNodeContribution(model, api);
	}

}
