import java.util.*;
public class Q1 
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		pair p[] = new pair[n];
		
		for(int i=0;i<n;i++)
			p[i] = new pair(sc.nextInt(),sc.nextInt());
		long[] dst = new long[n];
		for(int i=0;i<n;i++)
		{
			dst[i] = Dist(p[i])*n + i;
			System.out.println(dst[i]);
		}
			
		Arrays.sort(dst);
		int a = (int)(dst[0]%n);
		int b = (int)(dst[1]%n);
		int c = (int)(dst[2]%n);
		
		for(int i=3;i<n;i++)
		{
			if(inLine(p[a],p[b],p[c]))
			{
				//System.out.println(dst[i]);
				c = (int)(dst[i]%n);
				continue;
			}
			else
			{
				
				break;
			}
				
		}
		System.out.println((a+1)+" "+(b+1)+" "+(c+1));
	}
	public static boolean inLine(pair p,pair q,pair r)
	{
		double slop1 = ((p.x - q.x)*1.0)/(1.0*(p.y - q.y));
		double slop2 = (1.0*(q.x - r.x))/(1.0*(q.y - r.y));
		if(slop1==slop2)
			return true;
		else
			return false;
		
				
	}
	public static long Dist(pair p)
	{
		return (long) Math.sqrt((p.x*p.x+p.y*p.y));
		
	}
}

class pair
{
	long x;
	long y;
	pair(long x,long y)
	{
		this.x = x;
		this.y = y;
	}
}