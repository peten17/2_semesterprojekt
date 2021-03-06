package DreamTeam.GriberStyringV3.impl;

import java.io.InputStream;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.contribution.ProgramNodeService;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;

public class GriberProgramNodeService implements ProgramNodeService {
	
	public GriberProgramNodeService() {}

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
		return true;
	}

	@Override
	public String getTitle() {
		return "GriberStyringV3";
	}

	@Override
	public InputStream getHTML() {
		InputStream is = this.getClass().getResourceAsStream("/html/ProgramNode.html");
		return is;
	}

	@Override
	public ProgramNodeContribution createNode(URCapAPI api, DataModel model) {
		return new DreamTeam.GriberStyringV3.impl.GriberProgramNodeContribution(model, api);
	}

}
