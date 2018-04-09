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
	private final String popupTitle = "Popup: ";
	private final String message = "It's a popup";
	
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
		
		return "Griber";
	}

	@Override
	public boolean isDefined() {
		
		return true;
	}

	@Override
	public void generateScript(ScriptWriter writer) {
		// Create a URscript that connects to IP+Socket of RPI
		writer.assign("message","\"" + message + "\"");
		writer.assign("Title", "\"" + popupTitle + "\"");
		writer.appendLine("textmsg(Title, message)");
		writer.appendLine("");
		//writer.appendLine("popup(\"" + message + "\", Title, False, False, blocking=True)");
	}
	
}
