import java.util.concurrent.Semaphore; // concurrent حزمة داخل المكتبة





class Buffer {
    private final int Asize = 5;
    private final String[] bufferArray = new String[Asize]; 
    private int front = 0;  // مؤشر البداية
    private int last = 0;   // مؤشر النهاية
    private int size = 0;   // عدد العناصر الحالية في المصفوفة

    
    Semaphore empty = new Semaphore(Asize); // عدد الخانات الفاضية
    Semaphore full = new Semaphore(0);  // عدد الخانات المليانة
    Semaphore mutex = new Semaphore(1); // لحماية المنطقة الحرجة واحد فقط من يدخل

    
    public void produce(String process) throws InterruptedException { // المنتج يضيف مهمة
        empty.acquire();     //  يحجز للعملية مكان أو ينتظر إذا ما فيه مكان 
        mutex.acquire();     // يدخل المنطقة الحرجة

        
        bufferArray[last] = process; // إضافة المهمة في المصفوفة
        last = (last + 1) % Asize;  // التكرار عندما تصل النهاية
        size++;
        System.out.println("Produced: " + process);

        mutex.release();     // يطلع من المنطقة الحرجة
        full.release();      // تعلم المستهلك ان فيه بيانات جاهزة للاستهلاك
    }

    
    public void consume() throws InterruptedException { // المستهلك يسحب مهمة
        full.acquire();      // ينتظر إذا ما فيه مهام
        mutex.acquire();     // يدخل المنطقة الحرجة

        
        String process = bufferArray[front]; // سحب المهمة من المصفوفة
        front = (front + 1) % Asize;  // التكرار عندما تصل البداية
        size--;
        System.out.println("Consumed: " + process);

        mutex.release();     // يطلع من المنطقة الحرجة
        empty.release();     // تعلم المنتج ان فيه خانات فاضية
    }
}


class Producer extends Thread {
    private final Buffer buffer;
    private final int ID;

    public Producer(Buffer b, int id) {
        buffer = b;
        ID = id;
    }

    public void run() {
        try {
            for (int i = 1; i <= 5; i++) {
                String process = "process-P" + ID + "-" + i;
                buffer.produce(process);
                Thread.sleep(500); // تأخير نصف ثانية
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}


class Consumer extends Thread {
    private final Buffer buffer;
    private final int ID;

    public Consumer(Buffer b, int id) {
        buffer = b;
        ID = id;
    }

    public void run() {
        try {
            for (int i = 1; i <= 5; i++) {
                buffer.consume();
                Thread.sleep(1000); // تأخير ثانية
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}


public class Main {
    public static void main(String[] args) {
        Buffer b1 = new Buffer();

        // إنشاء المنتجين
        Producer p1 = new Producer(b1, 1);
        Producer p2 = new Producer(b1, 2);

        // إنشاء المستهلكين
        Consumer c1 = new Consumer(b1, 1);
        Consumer c2 = new Consumer(b1, 2);

        // تشغيل الخيوط
        p1.start();
        p2.start();
        c1.start();
        c2.start();
    }
}