import java.util.ArrayList;
import java.util.List;
import java.util.Random;

class SimpleThread extends Thread {
	
	private Integer id;
	
	public SimpleThread(Integer id) {
		this.id = id;
	}

	public void run() {

		

		Random r = new Random();	
		try { Thread.currentThread().sleep(r.nextInt(301));}
		catch (InterruptedException ie) { ie.printStackTrace(); }
			
		System.out.println("FIM "+ id);
	}	
}

public class Exercicio2 {
	
	public static void main(String args[]) {
		
		//System.out.println(args[0]);
		List<SimpleThread> threads = new ArrayList<>();
		for (int i = 0; i < (Integer.parseInt(args[0])); i++) 
		{
			SimpleThread temp = new SimpleThread(i);
			threads.add(temp);
			temp.run();
			
		}
		//SimpleThread thr1 =  new SimpleThread("Joe");
		//SimpleThread thr2 =  new SimpleThread("Paul");
		
		//thr1.start();
		//thr2.start();
		
		try {
			for (SimpleThread targetTh : threads) {
				targetTh.join();
			}
			//thr1.join();
			//thr2.join();
		} catch (InterruptedException ie) { 
			ie.printStackTrace(); 
		}
		
		System.out.println("Main finalizando...");
	}
}