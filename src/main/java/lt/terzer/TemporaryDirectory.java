package lt.terzer;

import java.io.File;
import java.io.IOException;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;

class TemporaryDirectory {
    static final String LIBWDI_PREFIX = "libwdi_tmp";
    final Path path;

    public TemporaryDirectory() {
        try {
            path = Files.createTempDirectory(LIBWDI_PREFIX);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public Path getPath() {
        return path;
    }

    public TemporaryDirectory deleteOldInstancesOnStart() {
        Path tempDirectory = path.getParent();

        for (File file : tempDirectory.toFile().listFiles()) {
            if (file.isDirectory() && file.getName().startsWith(LIBWDI_PREFIX)) {
                try {
                    delete(file.toPath());
                } catch (RuntimeException e) {

                }
            }
        }

        return this;
    }

    public TemporaryDirectory markDeleteOnExit() {
        Runtime.getRuntime().addShutdownHook(new Thread() {
            @Override
            public void run() {
                delete();
            }
        });

        return this;
    }

    private void delete(Path path) {
        if (!Files.exists(path)) {
            return;
        }

        try {
            Files.walkFileTree(path, new SimpleFileVisitor<Path>() {
                @Override
                public FileVisitResult postVisitDirectory(final Path dir, final IOException e) throws IOException {
                    Files.deleteIfExists(dir);
                    return super.postVisitDirectory(dir, e);
                }

                @Override
                public FileVisitResult visitFile(final Path file, final BasicFileAttributes attrs)
                        throws IOException {
                    Files.deleteIfExists(file);
                    return super.visitFile(file, attrs);
                }
            });
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void delete() {
        delete(path);
    }
}