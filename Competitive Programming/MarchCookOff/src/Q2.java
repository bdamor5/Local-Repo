import java.util.*;
class Q2 
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		
		while(t-->0)
		{
			int h = sc.nextInt();
			int m = sc.nextInt();
			int ans = 1;
			
			int arr[][] = new int[10][7];
			for(int i=1;i<10;i++)
				for(int j=0;j<7;j++)
				{
					if(j==0)
						arr[i][j] = i;
					else
					{
						arr[i][j] = arr[i][j-1]*10 + i;
					}
			//		System.out.println(arr[i][j]);
					for(int k=1;k<Math.log10(arr[i][j]);k++)
					{
						int x = arr[i][j]%(int)Math.pow(10,k);
						int y = arr[i][j]/(int)Math.pow(10,k);
						//System.out.println(x+" "+y+" "+arr[i][j]);
						if(x<m && y<h)
							ans++;
					}
				}
			System.out.println(ans);
			
	
		}
	}
}
