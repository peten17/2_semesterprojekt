package DreamTeam.GriberStyringV2.impl;

import java.io.InputStream;

import com.ur.urcap.api.contribution.InstallationNodeContribution;
import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;

public class GriberProgramNodeContribution implements ProgramNodeContribution {
	
	private final DataModel model;
	private final URCapAPI api;
	
	public GriberProgramNodeContribution(DataModel model, URCapAPI api){
		this.model = model;
		this.api = api;
	}

	@Override
	public void openView() {
	}

	@Override
	public void closeView() {
		
		
	}

	@Override
	public String getTitle() {
		
		return "Griber2";
	}

	@Override
	public boolean isDefined() {
		
		return true;
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		
	}
	
}
