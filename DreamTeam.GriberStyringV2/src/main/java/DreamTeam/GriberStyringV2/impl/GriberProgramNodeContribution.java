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
	private final String popupTitle = "Popup";
	private final String message = "PopPop";
	
	public GriberProgramNodeContribution(DataModel model, URCapAPI api){
		this.model = model;
		this.api = api;
	}

	@Override
	public void openView() {
	}

	@Override
	public void closeView() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public String getTitle() {
		// TODO Auto-generated method stub
		return "Griber";
	}

	@Override
	public boolean isDefined() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		// Create a URscript that connects to IP+Socket of RPI
		writer.appendLine();
		writer.appendLine();
	}
	
}
