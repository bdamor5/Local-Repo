import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;
class Question1 
{
	static int max = 1000000007;
	public static void main(String args[]) throws IOException
	{
		sc.init(System.in);
		int t = sc.nextInt();
		while(t-->0)
		{
			int n = sc.nextInt();
			int arr[] = new int[n];
			for(int i=0;i<n;i++)
			{
				arr[i] = sc.nextInt();
			}
			Arrays.sort(arr);
			int gp[] = new int[n];
			int c = 0;
			int x = arr[0];
			for(int i=0;i<n;i++)
			{
				if(arr[i]==x)
					gp[c]++;
				else
				{
					x = arr[i];
					c++;
					gp[c]++;
				}
			}
			c++;
		
			int ans = 0;
			
			PriorityQueue<Integer> p= new PriorityQueue<Integer>();
			for(int i=0;i<c;i++)
				p.add(max-gp[i]);
		
			for(int i=0;i<n;i++)
			{
				if(p.isEmpty())
					break;
				int a = max-p.poll();
				if(p.isEmpty())
				{
					ans+=a;
					break;
				}
				int b = max-p.poll();
			//	System.out.println(a+" "+b);
				if(a==0 || b==0)
					break;
				a--;
				b--;
				ans++;
				if(a!=0)
				p.add(max-a);
				if(b!=0)
				p.add(max-b);
			
			}
			if(!p.isEmpty())
			ans+=p.poll();
			System.out.println(ans);
			
		}
	}
}
class sc {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
                     new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                   reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }
	
    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}
