public class Consumer implements Runnable {
    
    private Buffer buffer;
    private Double total = 0.0;

    public Consumer(Buffer buffer) {
        this.buffer = buffer;
    }


    public void run(){
        synchronized(this.buffer) {
            for (int i = 1; i <= 1000000; i++) {
                try {
                    Double bufferElement = buffer.read();
                    total += bufferElement;
                    if((i % 100000 == 0)  && (i != 0)){
                        System.out.printf("Consumer: Consumed %d items, Cumulative value of consumed items=%.3f\n", i, total);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }

}