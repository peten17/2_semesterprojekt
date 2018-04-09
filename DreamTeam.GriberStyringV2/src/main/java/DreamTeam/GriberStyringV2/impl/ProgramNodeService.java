package DreamTeam.GriberStyringV2.impl;

import java.io.InputStream;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;

public class ProgramNodeService implements com.ur.urcap.api.contribution.ProgramNodeService {
	
	public ProgramNodeService() {}

	@Override
	public String getId() {
		return "ǴriberStyringNode";
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
		return "GriberStyring";
	}

	@Override
	public InputStream getHTML() {
		InputStream is = this.getClass().getResourceAsStream("/html/ProgramNode.html");
		return is;
	}

	@Override
	public ProgramNodeContribution createNode(URCapAPI api, DataModel model) {
		return new DreamTeam.GriberStyringV2.impl.GriberProgramNodeContribution(model, api);
	}

}
