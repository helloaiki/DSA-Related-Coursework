import java.io.IOException;
import java.io.InputStream;
import java.util.*;


    class Element
    {
        int id;
        List<Integer>neighbour;
        List<Integer>weight;
        public Element(int id)
        {
            this.id=id;
            neighbour=new ArrayList<>();
            weight=new ArrayList<>();
        }
        public void addNeighbour(int v,int w)
        {
            neighbour.add(v);
            weight.add(w);
        }
    }

    class Node implements Comparable<Node>
    {
        int id;
        int dist;
        int times;
        public Node(int id,int d,int times)
        {
            this.id=id;
            dist=d;
            this.times=times;
        }
        public int compareTo(Node n)
        {
            return Integer.valueOf(dist).compareTo(Integer.valueOf(n.dist));
        }
    }

public class ShortestPathBetweenCity
{
    static class FS 
    {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private final InputStream in = System.in;

        int read() throws IOException 
        {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException 
        {
            int c, sign = 1, val = 0;
            do {
                c = read();
            } while (c <= ' ');

            if (c == '-') {
                sign = -1;
                c = read();
            }

            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
        String next() throws IOException 
        {
            int c;
            StringBuilder sb = new StringBuilder();
            do {
                c = read();
            } while (c <= ' ');

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }
            return sb.toString();
       }
    }

    

    public static void main(String[]args)throws Exception
    {
       
        FS fs=new FS();
        int city,road,queryCount;
        city=fs.nextInt();
        road=fs.nextInt();
        int[][]edges=new int[city][city];
        int[][]time=new int[city][city];

        Element[]elements=new Element[city];
        int[][]dist=new int[city][city];
        boolean[][]canVisit=new boolean[city][city];
        

        for(int i=0;i<city;i++)
        {
            elements[i]=new Element(i);
        }

        for(int i=0;i<road;i++)
        {
            int from,to,cost;
            from=fs.nextInt();
            to=fs.nextInt();
            cost=fs.nextInt();
            elements[from].addNeighbour(to, cost);
            elements[to].addNeighbour(from, cost);
            dist[from][to]=dist[to][from]=cost;
            canVisit[from][to]=canVisit[to][from]=true;
            edges[from][to]=1;
            time[from][to]=1;
        }

        for(int i=0;i<city;i++)
        {
            dist[i][i]=0;
            canVisit[i][i]=true;
            edges[i][i]=0;
        }


       int v=fs.nextInt();
       int limit=fs.nextInt();



        queryCount=fs.nextInt();

        List<int[]>queries=new ArrayList<>();

        for(int i=0;i<queryCount;i++)
        {
            int a,b;
            a=fs.nextInt();
            b=fs.nextInt();
            queries.add(new int[]{a,b});
        }
        
        for(int inner=0;inner<city-1;inner++)
        {
            for(int i=0;i<city;i++)
            {
                for(int j=0;j<city;j++)
                {
                    if(canVisit[i][inner] && canVisit[inner][j])
                    {
                        if(!canVisit[i][j])
                        {
                            dist[i][j]=dist[i][inner]+dist[inner][j];
                            canVisit[i][j]=true;
                            time[i][j]=time[i][inner]+time[inner][j];
                        }
                        else
                        {
                            
                            if(dist[i][j]>dist[i][inner]+dist[inner][j])
                            {
                                dist[i][j]=dist[i][inner]+dist[inner][j];
                                time[i][j]=time[i][inner]+time[inner][j];
                            }
                        }
                    }
                }
            }
        }
        
        for(int i=0;i<city;i++)
        {
            for(int j=0;j<city;j++)
            {
                if(!canVisit[i][j])
                {
                    dist[i][j]=-1;
                }
            }
        }


        for(int i=0;i<city;i++)
        {
            for(int j=0;j<city;j++)
            {
                if(dist[i][j]!=-1 && dist[i][v]!=-1 && dist[v][j]!=-1 && time[i][v]<=limit)
                {
                    if(j!=v)
                    {
                        if(dist[i][j]>dist[i][v]+dist[v][j]-edges[i][v]-edges[v][j])
                        {
                            dist[i][j]=dist[i][v]+dist[v][j]-edges[i][v]-edges[v][j];
                            time[i][j]=time[i][v]+time[v][j];
                        }
                    }
                    else
                    {
                        if(dist[i][j]>dist[i][v]+dist[v][j]-edges[i][v]-edges[v][j]+1)
                        {
                            dist[i][j]=dist[i][v]+dist[v][j]-edges[i][v]-edges[v][j]+1;
                            time[i][j]=time[i][v]+time[v][j];
                        }
                    }
                }
            }
        }

       

        
      
        for(int i=0;i<queries.size();i++)
        {
           
            int a=queries.get(i)[0];
            int b=queries.get(i)[1];
            System.out.println(dist[a][b]);
            
        }

    }
} 