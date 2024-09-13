public class Driver {
    
    public static void main(String[] args){
        Buffer buffer = new Buffer();

        Thread producer = new Thread(new Producer(buffer));
        Thread consumer = new Thread(new Consumer(buffer));

        producer.start();
        consumer.start();

        try {

            producer.join();
            System.out.println("Producer: Finished generating 1,000,000 items");

            consumer.join();
            System.out.println("Consumer: Finished consuming 1,000,000 items");

        } catch (InterruptedException e) {

            System.out.println(e.toString());

        }

        System.out.println("Exiting!");
    }
}
