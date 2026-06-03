import java.util.*;

class Vertex
{
    int id;
    List<Integer>neighbour;

    public Vertex(int id)
    {
        this.id=id;
        neighbour=new ArrayList<>();
    }
    public void addNeighbour(int v,int w)
    {
        neighbour.add(v);
        neighbour.add(w);
    }
}

class Edge implements Comparable<Edge>
{
    int a,b,c;
    public Edge(int a,int b,int c)
    {
        this.a=a;
        this.b=b;
        this.c=c;
    }
    @Override

    public int compareTo(Edge e)
    {
        return Integer.valueOf(c).compareTo(Integer.valueOf(e.c));
    }

}

public class Prim
{
    private static void print(String s)
    {
        System.out.println(s);
    }
    public static void main(String[]args)
    {
        Scanner scanner=new Scanner(System.in);
        int island,road;
        island=scanner.nextInt();
        road=scanner.nextInt();
        Vertex[]vertice=new Vertex[island];

        for(int i=0;i<island;i++)
        {
            vertice[i]=new Vertex(i);
        }

        for(int i=0;i<road;i++)
        {
            int a,b,c;
            a=scanner.nextInt();
            b=scanner.nextInt();
            c=scanner.nextInt();
            vertice[a].addNeighbour(b, c);
            vertice[b].addNeighbour(a, c);
        }

        int root;
        root=scanner.nextInt();

        boolean[]isIncluded=new boolean[island];
        List<int[]>edges=new ArrayList<>();

        PriorityQueue<Edge>pq=new PriorityQueue<>();
        int min=-1;//if negativ edge allowed change this value. do smth like a boolean
        int start=root,end=-1;
        for(int i=0;i<vertice[root].neighbour.size();i+=2)
        {
            int v=vertice[root].neighbour.get(i);
            int cost=vertice[root].neighbour.get(i+1);
            if(min==-1)
            {
                min=cost;
                end=v;
            }
            else
            {
                if(min>cost)
                {
                    min=cost;
                    end=v;
                }
            }
        }

        if(end!=-1)
        {
            edges.add(new int[]{start,end});
            int totalCost=min;
            isIncluded[start]=true;
            isIncluded[end]=true;
            int includedVertice=2;
            for(int i=0;i<vertice[start].neighbour.size();i+=2)
            {
                int v=vertice[start].neighbour.get(i);
                int cost=vertice[start].neighbour.get(i+1);
                if(!isIncluded[v])
                {
                    pq.offer(new Edge(start, v, cost));
                }
            }

            for(int i=0;i<vertice[end].neighbour.size();i+=2)
            {
                int v=vertice[end].neighbour.get(i);
                int cost=vertice[end].neighbour.get(i+1);
                if(!isIncluded[v])
                {
                    pq.offer(new Edge(end, v, cost));
                }
            }

            while(!pq.isEmpty() && includedVertice<island)
            {
                Edge e=pq.poll();
                int a,b,c;
                a=e.a;
                b=e.b;
                c=e.c;
                if(isIncluded[b])
                {
                    continue;
                }
                totalCost+=c;
                isIncluded[b]=true;
                includedVertice+=1;
                edges.add(new int[]{a,b});
                for(int i=0;i<vertice[b].neighbour.size();i+=2)
                {
                    int v=vertice[b].neighbour.get(i);
                    int cost=vertice[b].neighbour.get(i+1);
                    if(!isIncluded[v])
                    {
                        pq.offer(new Edge(b, v, cost));
                    }

                }
            }

             
            print("Total weight: "+totalCost);
            print("Root node "+root);
            for(int i=0;i<edges.size();i++)
            {
                print(edges.get(i)[0]+" "+edges.get(i)[1]);
            }
      
            

        }




        scanner.close();
    }
}