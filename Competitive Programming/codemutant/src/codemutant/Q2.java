package codemutant;

import java.util.*;

public class Q2 {

	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		int t= sc.nextInt();
		
		while(t-->0)
		{
			int n = sc.nextInt();
			int k = sc.nextInt();
			
			int sx = sc.nextInt();
			int sy = sc.nextInt();
			int ex = sc.nextInt();
			int ey = sc.nextInt();
			
			int x = Math.abs((ex - sx));
			int y = Math.abs((ey - sy));
			if(x%2==1 || y%2==1 || k<x/2 || k<y/2)
			{
				System.out.println(0);
			}
			else
			{
				int ansx = 0,ansy=0;
				x/=2;
				y/=2;
				//System.out.println(nCr(10,0));
				for(int i=x;i<=k;i++)
				{
					ansx += nCr(k,i)*nCr(k-i,i-x);
					if((k-2*i+x)%2==0 && k-2*i+x>0)
						ansx*=(int) Math.pow(2, k-2*i-x-1);
				}
				
				for(int i=y;i<=k;i++)
				{
					ansy += nCr(k,i);
					if((k-i)%2==0 && k-i!=0)
						ansy*=(int) Math.pow(2, k-i-1);
				}
					System.out.println(ansx*ansy);
			}
			
			
		}

	}
	public static int nCr(int n,int r)
	{
		if(r==0 || r==n)
			return 1;
		int ans=n;
		if(r<n/2)
			r = n-r;
		for(int i=n-1;i>r;i--)
		{
			ans*=i;
			
		}
		for(int i=n-r;i>=1;i--)
			ans/=i;
		return ans;
	}

}
