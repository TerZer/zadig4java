package lt.terzer;

public enum DriverType {
    WDI_WINUSB(0),
    WDI_LIBUSB0(1),
    WDI_LIBUSBK(2),
    WDI_CDC(3),
    WDI_USER(4),
    WDI_NB_DRIVERS(5);

    private final int id;

    DriverType(int id){
        this.id = id;
    }

    public int getId() {
        return id;
    }
}
