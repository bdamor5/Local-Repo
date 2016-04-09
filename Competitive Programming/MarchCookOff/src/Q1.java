import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
class Q1 
{
	public static void main(String[] args)
	{
		MyScanner sc = new MyScanner();
		int t = sc.nextInt();
		while(t-->0)
		{
			int n = sc.nextInt();
			int arr[] = new int[n];
			
			for(int i=0;i<n;i++)
				arr[i] = sc.nextInt();
			
			int ans = arr[0];
			for(int i=1;i<n;i++)
				ans=ans^arr[i];
			
			if(ans==0)
				System.out.println("First");
			else if(n%2==0)
				System.out.println("First");
			else
				System.out.println("Second");
		}
	}
}
class MyScanner {
	   BufferedReader br;
	   StringTokenizer st;
	  
	   public MyScanner() {
	      br = new BufferedReader(new InputStreamReader(System.in));
	   }
	  
	   String next() {
	      while (st == null || !st.hasMoreElements()) {
	         try {
	            st = new StringTokenizer(br.readLine());
	         } catch (IOException e) {
	            e.printStackTrace();
	         }
	      }
	      return st.nextToken();
	   }
	  
	   int nextInt() {
	      return Integer.parseInt(next());
	   }
	  
	   long nextLong() {
	      return Long.parseLong(next());
	   }
	  
	   double nextDouble() {
	      return Double.parseDouble(next());
	   }
	  
	   String nextLine(){
	      String str = "";
	      try {
	         str = br.readLine();
	      } catch (IOException e) {
	         e.printStackTrace();
	      }
	      return str;
	   }
	 
	}
