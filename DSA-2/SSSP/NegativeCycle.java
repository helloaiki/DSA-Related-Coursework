import java.util.*;

import javax.management.RuntimeErrorException;

class Edge
{
    private int to,from,weight;
    public Edge(int f,int t,int w)
    {
        to=t;
        from=f;
        weight=w;
    }

    public int getFrom()
    {
        return from;
    }

    public int getTo()
    {
        return to;

    }

    public int getWeight()
    {
        return weight;
    }
}

public class NegativeCycle
{
    public static void main(String[]args)
    {
        int numberOfNodes,numberOfEdges;
        Scanner scanner=new Scanner(System.in);
        numberOfNodes=scanner.nextInt();
        numberOfEdges=scanner.nextInt();
        Edge[]edges=new Edge[numberOfEdges];
        for(int i=0;i<numberOfEdges;i++)
        {
            int to,from,weight;
            from=scanner.nextInt();
            to=scanner.nextInt();
            weight=scanner.nextInt();
            Edge edge=new Edge(from,to,weight);
            edges[i]=edge;
        }

        int[]distanceFromSource=new int[numberOfNodes+1];
        boolean[]visited=new boolean[numberOfNodes+1];
        int[]parents=new int[numberOfNodes+1];
        int visitedNodes=0;
        List<Integer>queue=new ArrayList<>(); 
        for(int i=1;i<=numberOfNodes;i++)
        {
            queue.add(i);
        }

        
        while(visitedNodes!=numberOfNodes)
        {
            if(queue.isEmpty())
            {
                throw new RuntimeErrorException(null);
            }
            int node=queue.get(0);
            queue.remove(Integer.valueOf(node));
            visited[node]=true;
            visitedNodes++;
            parents[node]=node;
            distanceFromSource[node]=0;
            for(int i=0;i<numberOfNodes-1;i++)
            {
                for(int j=0;j<edges.length;j++)
                {
                    int from=edges[j].getFrom();
                    int to=edges[j].getTo();
                    int weight=edges[j].getWeight();
                    if(visited[from])
                    {
                        if(visited[to])
                        {
                            if(distanceFromSource[to]>distanceFromSource[from]+weight)
                            {
                                parents[to]=from;
                                distanceFromSource[to]=distanceFromSource[from]+weight;
                            }

                        }
                        else
                        {
                            distanceFromSource[to]=distanceFromSource[from]+weight;
                            parents[to]=from;
                            visitedNodes++;
                            queue.remove(Integer.valueOf(to));
                            visited[to]=true;
                        }
                    }
                }
            }
        }


        List<Integer>nodesWhoseValueChanged=new ArrayList<>();

        
       for(int j=0;j<edges.length;j++)
            {
                int from=edges[j].getFrom();
                int to=edges[j].getTo();
                int weight=edges[j].getWeight();
                if(visited[from])
                {
                    
                    if(distanceFromSource[to]>distanceFromSource[from]+weight)
                    {
                        parents[to]=from;
                        distanceFromSource[to]=distanceFromSource[from]+weight;
                        nodesWhoseValueChanged.add(to);
                    }

                }
            }

        if(nodesWhoseValueChanged.isEmpty())
        {
            System.out.println(-1);
        }
        else
        {
            int tracer=0;
            boolean found=false;
            for(int i=0;i<nodesWhoseValueChanged.size();i++)
            {
                for(int j=0;j<nodesWhoseValueChanged.size();j++)
                {
                    if(nodesWhoseValueChanged.get(i)==parents[nodesWhoseValueChanged.get(j)])
                    {
                        tracer=nodesWhoseValueChanged.get(i);
                        found=true;
                        break;
                    }
                }

                if(found)
                {
                    break;
                }
            }
            int curr=tracer;
            List<Integer>cycle=new ArrayList<>();
            
            while(parents[curr]!=tracer )
            {
                 cycle.add(curr);
                curr=parents[curr];
            }

            cycle.add(curr);

            Collections.reverse(cycle);
           
            for(int i=0;i<cycle.size();i++)
            {
                System.out.print(cycle.get(i)+" ");
            }
            

       }


    }
    
}