package lt.terzer;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;

public class Libwdi {

    static {
        System.out.print("Zadig4java 0.1 ");
        try {
            final Path libraryPath;
            if (!System.getProperty("os.arch").matches("x86")) {
                libraryPath = extractNativeBinary("/lib/x64/zadig4java.dll");
            }
            else {
                libraryPath = extractNativeBinary("/lib/x86/zadig4java.dll");
            }
            System.load(libraryPath.normalize().toString());
            System.out.println("successfully loaded");
        } catch (UnsatisfiedLinkError uleEx) {
            System.out.println("load failed: Library, (or dependencies thereof,) unavailable");
            System.out.println(uleEx.getMessage());
        } catch (SecurityException sEx) { // I've no idea what this exception entails in practice
            System.out.println("load failed: Library inaccessible");
            System.out.println(sEx.getMessage());
        }
    }

    private static Path extractNativeBinary(String location){
        final InputStream binary = Libwdi.class.getResourceAsStream(location);
        final Path destination;

        // Do not try to delete the temporary directory on the close if Windows
        // because there will be a write lock on the file which will cause an
        // AccessDeniedException. Instead, try to delete existing instances of
        // the temporary directory before extracting.
        destination = new TemporaryDirectory().deleteOldInstancesOnStart().getPath().resolve("./" + location).normalize();

        try {
            Files.createDirectories(destination.getParent());
            Files.copy(binary, destination);
            binary.close();
        } catch (final IOException ioe) {
            throw new IllegalStateException(String.format("Error writing native library to \"%s\".", destination), ioe);
        }

        return destination;
    }

    /**
     * Install driver for devices that does not have a driver. Filters devices by vendor id.
     * @param vid USB device vendor id
     * @param driverType Type of driver that will be installed for device
     * @return true if driver installation was successful, false otherwise
     */
    public static boolean installDriver(int vid, DriverType driverType){
        return installDriver(vid, driverType.getId()) == 0;
    }

    /**
     * Install driver for devices that does not have a driver. Filters devices by vendor and product ids.
     * @param vid USB device vendor id
     * @param pid USB device product id
     * @param driverType Type of driver that will be installed for device
     * @return true if driver installation was successful, false otherwise
     */
    public static boolean installDriver(int vid, int pid, DriverType driverType){
        return installDriver(vid, pid, driverType.getId()) == 0;
    }

    private static native int installDriver(int vid, int driverType);
    private static native int installDriver(int vid, int pid, int driverType);
}
