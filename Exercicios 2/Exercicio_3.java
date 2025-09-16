import java.util.Random;



class PingPong {
	
	private int data = 1;
	private int turn = 0;
    
	public void update(int id) throws InterruptedException {
		
        synchronized(this)
        {
			if(id == 0)
			{
				doPing(id);

			}
			else
			{
				doPong(id);
			}

			Thread.sleep(new Random().nextInt(1000));
        }
	}

	public synchronized void doPing(int id) // Thread A
	{
		
		while(turn != id)
		{
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
			
    	System.out.println("Ping - id:"+ id+ "- Data: "+data);
		data++;
		turn = 1;
		notifyAll();
	}

	public synchronized void doPong(int id) // Thread B
	{
		
		while(turn != id)
		{
			try {
				wait();
			} catch (InterruptedException e) {

				e.printStackTrace();
			}
		}
			
   	System.out.println("Pong - id:"+ id+ "- Data: "+data);
    	data++;
		turn = 0;
		notifyAll();
	}

	public synchronized int getData() {
		return data;
	}
}

//class PingPong 
//{


//}

class MyThread extends Thread {
	
	static final int n = 4; //constante final
	int id;
	PingPong myMonitor;
	
	public MyThread(int id, PingPong myMonitor) {
		this.id = id;
		this.myMonitor = myMonitor;
	}
	
	public void run() {
		while (myMonitor.getData() < n*2) {
			try {

                //System.out.println("Ping ID=" + id);
				myMonitor.update(id);// -> é o controle de quem ta executando
				//Thread.currentThread().sleep(new Random().nextInt(3000));
               // System.out.println("Pong ID=" + id);
                //print pong
			}
			catch (InterruptedException ie) { 
				ie.printStackTrace(); 
			}
		} 
	}
}




public class Exercicio_3 {
	
	public static void main(String args[]) {
		
		PingPong myMonitor = new PingPong();
		
		MyThread t1 = new MyThread(0, myMonitor);
		MyThread t2 = new MyThread(1, myMonitor);
		
		t1.start();
		t2.start();
		
		try {
			t1.join();
			t2.join();
		} catch (Exception e) {
			// TODO: handle exception
		}

	}
}
