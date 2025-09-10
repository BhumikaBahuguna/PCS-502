import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {
    private static final int BUFFER_SIZE = 5;
    private static final int[] buffer = new int[BUFFER_SIZE];
    private static int in = 0, out = 0, count = 0;
    private static final Lock lock = new ReentrantLock();
    private static final Condition notFull = lock.newCondition();
    private static final Condition notEmpty = lock.newCondition();

    public static void main(String[] args) {
        Thread producer = new Thread(ProducerConsumer::producer);
        Thread consumer = new Thread(ProducerConsumer::consumer);

        producer.start();
        consumer.start();
    }

    private static void producer() {
        while (true) {
            int item = (int) (Math.random() * 100); // produce an item

            lock.lock();
            try {
                while (count == BUFFER_SIZE) // buffer full
                    notFull.await();

                buffer[in] = item;
                System.out.println("Produced: " + item + " at " + in);
                in = (in + 1) % BUFFER_SIZE;
                count++;

                notEmpty.signal(); // signal buffer has item
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }

            try {
                Thread.sleep(1000); // simulate production time
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private static void consumer() {
        while (true) {
            lock.lock();
            try {
                while (count == 0) // buffer empty
                    notEmpty.await();

                int item = buffer[out];
                System.out.println("Consumed: " + item + " at " + out);
                out = (out + 1) % BUFFER_SIZE;
                count--;

                notFull.signal(); // signal buffer has space
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }

            try {
                Thread.sleep(1000); // simulate consumption time
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}