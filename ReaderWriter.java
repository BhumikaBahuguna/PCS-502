import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReaderWriter {
    private static int sharedData = 0; // data to read/write
    private static int readers = 0;    // number of active readers
    private static boolean writerActive = false;

    private static final Lock lock = new ReentrantLock();
    private static final Condition canRead = lock.newCondition();
    private static final Condition canWrite = lock.newCondition();

    public static void main(String[] args) {
        Thread writer = new Thread(ReaderWriter::writer);
        Thread reader1 = new Thread(() -> reader("Reader 1"));
        Thread reader2 = new Thread(() -> reader("Reader 2"));

        writer.start();
        reader1.start();
        reader2.start();
    }

    private static void reader(String name) {
        while (true) {
            lock.lock();
            try {
                while (writerActive) { // wait if a writer is active
                    canRead.await();
                }
                readers++;
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }

            // reading section (outside lock to allow multiple readers)
            System.out.println(name + " reads: " + sharedData);

            lock.lock();
            try {
                readers--;
                if (readers == 0) {
                    canWrite.signal(); // signal writer if no readers
                }
            } finally {
                lock.unlock();
            }

            try {
                Thread.sleep(1000); // simulate reading time
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private static void writer() {
        while (true) {
            lock.lock();
            try {
                while (readers > 0 || writerActive) { // wait if readers/writer active
                    canWrite.await();
                }
                writerActive = true;

                // writing section
                sharedData = (int) (Math.random() * 100);
                System.out.println("Writer writes: " + sharedData);

                writerActive = false;
                canRead.signalAll(); // allow readers
                canWrite.signal();   // allow next writer
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }

            try {
                Thread.sleep(1500); // simulate writing time
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
