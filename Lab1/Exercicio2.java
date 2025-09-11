//Codigos feitos pro Douglas e Jorge
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
		try { Thread.sleep(r.nextInt(301));}
		catch (InterruptedException ie) { ie.printStackTrace(); }
			
		System.out.println("FIM "+ id);
	}	
}

public class Exercicio2 {
	public static void main(String args[]) {
		List<SimpleThread> threads = new ArrayList<>();
		for (int i = 0; i < (Integer.parseInt(args[0])); i++) 
		{
			SimpleThread temp = new SimpleThread(i);
			threads.add(temp);
			temp.start();	
		}

		try {
			for (SimpleThread targetTh : threads) {
				targetTh.join();
			}
		} catch (InterruptedException ie) { 
			ie.printStackTrace(); 
		}
		
		System.out.println("Main finalizando...");
	}
}