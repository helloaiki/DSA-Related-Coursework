import java.util.*;

class UnionFind
{
    int[]parent;
    int[]size;
    int numberOfComponents;
    int[]cost;
    int[]og;
    public UnionFind(int n,int[]c)
    {
        numberOfComponents=n;
        parent=new int[n];
        size=new int[n];

        for(int i=0;i<n;i++)
        {
            parent[i]=i;
            size[i]=1;
        }
        cost=new int[c.length];
        og=new int[c.length];
        for(int i=0;i<c.length;i++)
        {
            cost[i]=c[i];
            og[i]=c[i];
        }
    }
    public int find(int u)
    {
        int p;
        int curr=u;
        while(curr!=parent[curr])
        {
            curr=parent[curr];
        }
        p=curr;
        curr=u;
        while(curr!=parent[curr])
        {
            int temp=parent[curr];
            parent[curr]=p;
            curr=temp;
        }

        return p;
    }
    public boolean union(int u,int v,int val)
    {
        int p1=find(u);
        int p2=find(v);
        if(p1==p2)
        {
            return false;
        }

        if(og[p1]<=og[p2])
        {
            cost[p1]+=(cost[p2]-og[p2]+val);
            parent[p2]=p1;
            size[p1]+=size[p2];
        }
        else
        {
            cost[p2]+=(cost[p1]-og[p1]+val);
            parent[p1]=p2;
            size[p2]+=size[p1];
        }

        numberOfComponents--;
        return true;
    }
}

class Edge implements Comparable<Edge>
{
    int a,b,costEdge,costNode;
    public Edge(int a,int b,int c,int cc)
    {
        this.a=a;
        this.b=b;
        costEdge=c;
        costNode=cc;
    }

    @Override
    public int compareTo(Edge e)
    {
        if(Integer.valueOf(costNode).compareTo(Integer.valueOf(e.costNode))!=0)
        {
            return Integer.valueOf(costNode).compareTo(Integer.valueOf(e.costNode));
        }

        return Integer.valueOf(costEdge).compareTo(Integer.valueOf(e.costEdge));
    }
}

class Point
{
    int id;
    int x,y,z;
    public Point(int id,int x,int y,int z)
    {
        this.id=id;
        this.x=x;
        this.y=y;
        this.z=z;
    }
}

public class Kruskal
{
    private static void print(String s)
    {
        System.out.println(s);
    }
    public static void main(String[]args)
    {
        Scanner scanner=new Scanner(System.in);
        int nodes;
        nodes=scanner.nextInt();

        int[]cost=new int[nodes];
        for(int i=0;i<nodes;i++)
        {
            int c=scanner.nextInt();
            cost[i]=c;
        }

        UnionFind un=new UnionFind(nodes, cost);


        PriorityQueue<Edge>pq=new PriorityQueue<>();

        int roads=scanner.nextInt();

        for(int i=0;i<roads;i++)
        {
            int a,b,c;
            a=scanner.nextInt()-1;
            b=scanner.nextInt()-1;
            c=scanner.nextInt();
            pq.offer(new Edge(a, b, c, Math.min(cost[a],cost[b])));
        }


        while(!pq.isEmpty() && un.numberOfComponents>1)
        {
            Edge e=pq.poll();
            int a=e.a;
            int b=e.b;
            int c=e.costEdge;
            int p1=un.find(a);
            int p2=un.find(b);
            if(p1!=p2)
            {
                print(a+" "+b);
                if(un.cost[p1]<c || un.cost[p2]<c)
                {
                    continue;
                }

                un.union(a,b,c);
                
            }
        }


        int costT=0;

        for(int i=0;i<nodes;i++)
        {
            if(un.find(i)==i)
            {
                costT+=un.cost[i];
            }
        }

        print(costT+"");


        

      
        


        

        scanner.close();
    }
}