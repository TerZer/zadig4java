# Zadig4Java

This is a Java library to be able to install drivers like with the program [Zadig](https://zadig.akeo.ie/). It uses JNI to access [Libwdi](https://github.com/pbatard/libwdi) library.
## Installation
**Step 1.** Add the JitPack repository to your build file , Add it in your root build.gradle at the end of repositories:
```
repositories {
    mavenCentral()
    maven { url 'https://jitpack.io' }
}
```
**Step 2.** Add the dependency
```
dependencies {
    implementation 'com.github.TerZer:zadig4java:0.3'
}
```

## Usage
Example:
```java
Libwdi.installDriver(vid, pid, DriverType.WDI_LIBUSBK);
```
## Requirements

Windows 7 and up. (Tested on Windows 10 and 11)

Java code has to run with administrator privileges.
## Contributing

Pull requests are welcome. For changes, please open an issue first
to discuss what you would like to change.