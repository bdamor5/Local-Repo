import java.io.*;
import java.util.*;

public class Q2 
{
	static int time=0;
	public static void main(String[] args) 
	{
		MyScanner sc = new MyScanner();
		PrintWriter ps =new PrintWriter(System.out);
		int n = sc.nextInt();
		Ver v[] = new Ver[n+1];
		
		for(int i=1;i<=n;i++)
			v[i] = new Ver();
		for(int i=1;i<n;i++)
			v[sc.nextInt()].nb.add(sc.nextInt());
		
		DFS(v,1);
		BFS(v,1);
		int q = sc.nextInt();
		/*for(int i=1;i<=n;i++)
		{
			System.out.println(v[i].st+" "+v[i].et);
		}*/
		for(int i=0;i<q;i++)
		{
			int wh = sc.nextInt();
			int a = sc.nextInt();
			int b = sc.nextInt();
			
			if(wh==0)
			{
				if(v[a].st<v[b].st && v[a].et>v[b].et)
				{
					int c = Math.abs(v[a].dst-v[b].dst)+1;
					ps.println("YES "+c);
				}
				else
					ps.println("NO");
			}
			else
			{
				if(v[b].st<v[a].st && v[b].et>v[a].et)
				{
					int c = Math.abs(v[a].dst-v[b].dst)+1;
					ps.println("YES "+c);
				}
				else
					ps.println("NO");
			}
		}
		ps.close();
	}
	public static void DFS(Ver[] v,int i)
	{
		v[i].st = ++time;
		for(int j=0;j<v[i].nb.size();j++)
		{
				DFS(v,v[i].nb.get(j));
		}
		v[i].et = ++time;
	}
	public static void BFS(Ver[] v,int i)
	{
		for(int j=0;j<v[i].nb.size();j++)
			v[v[i].nb.get(j)].dst = v[i].dst+1;
		for(int j=0;j<v[i].nb.size();j++)
			BFS(v,v[i].nb.get(j));
	}
}
class Ver
{
	int st,et;
	int clr=0;
	int dst=0;
	ArrayList<Integer> nb = new ArrayList<Integer>(); 
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