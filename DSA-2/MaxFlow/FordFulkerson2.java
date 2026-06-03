import java.util.*;

class Element
{
    int id;
    HashMap<Integer,Integer>edge;

    public Element(int id)
    {
        this.id=id;
        edge=new HashMap<>();
    }
    public void addEdge(int v,int c)
    {
        edge.put(v, c);
    }
    public void changeEdge(int v,int f)
    {
        edge.replace(v,f);
    }
    public int getCost(int v)
    {
        return edge.getOrDefault(v,-1);
    }
}

public class FordFulkerson2
{
    private static boolean hasAugmentingPath(Element[]residualGraph,int[]flowInc,int source,int destination)
    {
        flowInc[0]=0;

        Queue<Element>queue=new ArrayDeque<>();
        
        boolean foundDes=false;
        boolean[]visited=new boolean[residualGraph.length];
        queue.offer(residualGraph[source]);
        visited[source]=true;
        int min=0;
        int[]parent=new int[residualGraph.length];
        Arrays.fill(parent, -1);
        while(!queue.isEmpty())
        {
            Element e=queue.poll();
            
            Iterator<Map.Entry<Integer,Integer>>it1=residualGraph[e.id].edge.entrySet().iterator();
            while(it1.hasNext())
            {
                Map.Entry<Integer,Integer>entry=it1.next();
                if(visited[entry.getKey()])
                {
                    continue;
                }
                if(entry.getValue()>0)
                {
                    parent[entry.getKey()]=e.id;
                    visited[entry.getKey()]=true;
                    queue.offer(residualGraph[entry.getKey()]);
                    if(entry.getKey()==destination)
                    {
                        foundDes=true;
                        break;
                    }
                }
                
            }

            if(foundDes)
            {
                break;
            }
            
        }


        if(!foundDes)
        {
            return false;
        }
         
        int curr=destination;
        while(parent[curr]!=-1)
        {
            int start=parent[curr];
            int end=curr;
            min=min==0?residualGraph[start].getCost(end):Math.min(min,residualGraph[start].getCost(end));
            curr=parent[curr];
        }
        curr=destination;
        while(parent[curr]!=-1)
        {
            int start=parent[curr];
            int end=curr;
            int residue=residualGraph[start].getCost(end);
            int shrinkage=residualGraph[end].getCost(start);
            residualGraph[start].changeEdge(end, residue-min);
            residualGraph[end].changeEdge(start, shrinkage+min);
            curr=parent[curr];
        }
        flowInc[0]=min;
        return true;
    }

    private static void print(String s)
    {
        System.out.println(s);
    }

    

    public static void main(String[]args)
    {
        Scanner scanner=new Scanner(System.in);
        int people,officer,edges;
        people=scanner.nextInt();
        officer=scanner.nextInt();
        edges=scanner.nextInt();
        List<int[]>edgeList=new ArrayList<>();


        for(int i=0;i<edges;i++)
        {
            int u,v;
            u=scanner.nextInt();
            v=scanner.nextInt();
            if(u==v)
            {
                continue;
            }
            edgeList.add(new int[]{u,v,1});
        }
        
        Element[]graph=new Element[people];
        for(int i=0;i<people;i++)
        {
            graph[i]=new Element(i);
        }


        

        for(int i=0;i<edges;i++)
        {
            int u=edgeList.get(i)[0];
            int v=edgeList.get(i)[1];
            int c=edgeList.get(i)[2];
            graph[u].addEdge(v, c);
        }




        Element[]residualGraph=new Element[people+2];
        for(int i=0;i<residualGraph.length;i++)
        {
            residualGraph[i]=new Element(i);
        }

    

        for(int i=0;i<edges;i++)
        {
            int u=edgeList.get(i)[0];
            int v=edgeList.get(i)[1];
            int c=edgeList.get(i)[2];
            
            residualGraph[u].addEdge(v, c);
            residualGraph[v].addEdge(u, 0);
            
        }




        int src=people,des=people+1;

        for(int i=0;i<officer;i++)
        {
            residualGraph[src].addEdge(i, 1);
            residualGraph[i].addEdge(src, 0);
        }

        for(int i=officer;i<people;i++)
        {
            residualGraph[i].addEdge(des,1);
            residualGraph[des].addEdge(i, 0);
        }


        int[]total={0};
        int[]flowInc={0};

        while(hasAugmentingPath(residualGraph,flowInc,src,des))
        {
            total[0]+=flowInc[0];
        }


        print(total[0]+"");

        for(int i=0;i<edgeList.size();i++)
        {
            int a,b;
            a=edgeList.get(i)[0];
            b=edgeList.get(i)[1];
            if(residualGraph[b].getCost(a)==1)
            {
                print(a+" "+b);
            }
        }




         






        scanner.close();
    }
}