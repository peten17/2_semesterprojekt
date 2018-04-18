/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package DreamTeam.GriberStyring.impl;

import com.ur.urcap.api.contribution.ProgramNodeContribution;
import com.ur.urcap.api.domain.URCapAPI;
import com.ur.urcap.api.domain.data.DataModel;
import com.ur.urcap.api.domain.script.ScriptWriter;

public class GripperControlProgramContribution implements ProgramNodeContribution{

    private final URCapAPI api;
    private final DataModel model;
    
    public GripperControlProgramContribution(URCapAPI api, DataModel model) {
        this.api = api;
        this.model = model;
    }

    @Override
    public void openView() {
        return;
    }

    @Override
    public void closeView() {
    }

    @Override
    public String getTitle() {
        return "GripControl";
    }

    @Override
    public boolean isDefined() {
        return true; //prototype
    }

    @Override
    public void generateScript(ScriptWriter writer) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

}
