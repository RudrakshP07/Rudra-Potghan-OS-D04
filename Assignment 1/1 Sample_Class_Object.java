import java.util.concurrent.Semaphore;

class SharedResource {
    private Semaphore semaphore;

    public SharedResource(int permits) {
        semaphore = new Semaphore(permits);
    }

    public void useResource() {
        try {
            semaphore.acquire();
            System.out.println(Thread.currentThread().getName() + " is using the shared resource.");
            Thread.sleep(1000); // Simulate some work being done
            System.out.println(Thread.currentThread().getName() + " has finished using the shared resource.");
            semaphore.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class MyThread extends Thread {
    private SharedResource sharedResource;

    public MyThread(SharedResource sharedResource) {
        this.sharedResource = sharedResource;
    }

    public void run() {
        sharedResource.useResource();
    }
}

public class SemaphoreExample {
    public static void main(String[] args) {
        SharedResource sharedResource = new SharedResource(2); // Permitting 2 threads at a time

        // Create multiple threads
        Thread t1 = new MyThread(sharedResource);
        Thread t2 = new MyThread(sharedResource);
        Thread t3 = new MyThread(sharedResource);
        Thread t4 = new MyThread(sharedResource);

        // Start the threads
        t1.start();
        t2.start();
        t3.start();
        t4.start();
    }
}
