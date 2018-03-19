package DreamTeam.GriberStyring.impl;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;
import dk.sdu.mmmi.rd1.robotcomm.RobotClient;

/**
 * Hello world activator for the OSGi bundle URCAPS contribution
 *
 */
public class Activator implements BundleActivator {
	@Override
	public void start(final BundleContext context) throws Exception {
		GripperControlInstallationService gripperControlInstallationservice = new GripperControlInstallationService();
                
                /*bundleContext.registerService(type, this, dctnr);*/
	}

	@Override
	public void stop(BundleContext bundleContext) throws Exception {
		System.out.println("Activator says Goodbye World!");
	}
        
}

