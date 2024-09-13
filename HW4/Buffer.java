public class Buffer {

    private Double[] buffer;
    private int readIndex;
    private int writeIndex;
    private int size;

    public Buffer() {
        this.buffer = new Double[1000];
        this.readIndex = 0;
        this.writeIndex = 0;
        this.size = 0;
    }

    public void write(Double element) throws InterruptedException{
        while (size == 1000) {
            wait();
        }
        buffer[writeIndex % 1000] = element;
        writeIndex++;
        size++;
        notifyAll();
    }

    public Double read() throws InterruptedException {
        while (size == 0) {
            wait();
        }
        Double item = buffer[readIndex % 1000];
        readIndex++;
        size--;
        notifyAll();
        return item;
    }

}