package DreamTeam.GriberStyringV3.impl;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

import com.ur.urcap.api.contribution.InstallationNodeService;
import com.ur.urcap.api.contribution.ProgramNodeService;

/**
 * Hello world activator for the OSGi bundle URCAPS contribution
 *
 */
public class Activator implements BundleActivator {
	@Override
	public void start(BundleContext bundleContext) throws Exception {
		bundleContext.registerService(ProgramNodeService.class, new DreamTeam.GriberStyringV3.impl.ProgramNodeService(), null);
		bundleContext.registerService(ProgramNodeService.class, new OpenNodeService(), null);
		bundleContext.registerService(ProgramNodeService.class, new CloseNodeService(), null);
	}

	@Override
	public void stop(BundleContext bundleContext) throws Exception {
	}
}

