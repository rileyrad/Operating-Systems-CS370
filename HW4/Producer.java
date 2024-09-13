import java.util.Random;

public class Producer implements Runnable {
    
    private Buffer buffer;
    private Double total = 0.0;

    public Producer(Buffer buffer) {
        this.buffer = buffer;
    }


    public void run(){
        synchronized(this.buffer) {
            for (int i = 1; i <= 1000000; i++) {
                Random random = new Random();
                Double bufferElement = random.nextDouble() * 100.0;
                total += bufferElement;
                if((i % 100000 == 0) && (i != 0)){
                    System.out.printf("Producer: Generated %d items, Cumulative value of generated items=%.3f\n", i, total);
                }
                try {
                    buffer.write(bufferElement);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }


}