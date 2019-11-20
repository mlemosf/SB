/*
 * Compile assim: javac hello.java -target 1.2 -source 1.2
 * Hello!

-1
3.000000
-5.000000
-1
1
0
-2

 */
public class hello{
	public static void main(String args[]){
		int d = -1;
		double e = 3.0;
		double f = -5.0;
		long x = -1;
		long y = 1;
		
		
		System.out.println("Hello!\n");	
		System.out.println(d);	
		System.out.println(e);
		System.out.println(f);		
		System.out.println(x);
		System.out.println(y);
		System.out.println(x+y);
		System.out.println(x-y);
	}	
}
