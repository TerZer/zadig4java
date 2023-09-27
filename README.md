# Zadig4Java

This is a Java library to be able to install drivers like with the program [Zadig](https://zadig.akeo.ie/). It uses JNI to access [Libwdi](https://github.com/pbatard/libwdi) library.

## Requirements

Windows 7 and up. (Tested on Windows 10 and 11)

Java code has to run with administrator privileges.
## Usage
Example:
```java
Libwdi.installDriver(vid, pid, DriverType.WDI_LIBUSBK);
```

## Contributing

Pull requests are welcome. For changes, please open an issue first
to discuss what you would like to change.