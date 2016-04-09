import java.util.*;
public class Q3 
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		
		while(t-->0)
		{
			int n = sc.nextInt();
			int m = sc.nextInt();
			int l = sc.nextInt();
			int r = sc.nextInt();
			int arr[][] = new int[n][m];
			int prefix[][] = new int[n][m];
			
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
				{
					arr[i][j] = sc.nextInt();
					if(j>0)
					prefix[i][j]=prefix[i][j-1];
					
					prefix[i][j]+=arr[i][j];
				}
			for(int i=1;i<n;i++)
				for(int j=0;j<n;j++)
					prefix[i][j]+=prefix[i-1][j];
			long ans=0;
			
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<m;j++)
				{
					
					for(int k=0;k<=i;k++)
						for(int p=0;p<=j;p++)
						{
							long tmp = prefix[i][j];
							if(k>0)
								tmp-=prefix[k-1][j];
							if(p>0)
								tmp-=prefix[i][p-1];
							if(k>0 && p>0)
								tmp+=prefix[k-1][p-1];
							
							if(tmp>=l && tmp<=r)
								ans++;
						}
				}
			}
			System.out.println(ans);
			
		}
	}
}
