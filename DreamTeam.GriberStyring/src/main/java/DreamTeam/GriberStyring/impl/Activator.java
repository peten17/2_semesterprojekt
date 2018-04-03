package DreamTeam.GriberStyring.impl;

import com.ur.urcap.api.contribution.InstallationNodeService;
import com.ur.urcap.api.contribution.ProgramNodeService;
import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

/**
 *
 *
 */
public class Activator implements BundleActivator {
	@Override
	public void start(final BundleContext context) throws Exception {
		GripperControlInstallationService gripperControlInstallationservice = new GripperControlInstallationService();
                
                context.registerService(InstallationNodeService.class, gripperControlInstallationservice, null);
                //context.registerService(ProgramNodeService.class, new GripperControlInstallationService(), null);
                
                /*bundleContext.registerService(type, this, dctnr);*/
	}

	@Override
	public void stop(BundleContext bundleContext) throws Exception {
		System.out.println("Activator says Goodbye World!");
	}
        
}

