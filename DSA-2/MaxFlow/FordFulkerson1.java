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

public class FordFulkerson1
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

    private static double calculateDist(int x1,int y1,int x2,int y2)
    {
        return Math.sqrt(Math.pow(x1-x2, 2)+Math.pow(y1-y2,2));
    }

    

    public static void main(String[]args)
    {
        Scanner scanner=new Scanner(System.in);
        int nodes;
        double maxDistance;
        nodes=scanner.nextInt();
        maxDistance=scanner.nextDouble();
        List<int[]>edgeList=new ArrayList<>();
        int[]numberPenguins=new int[nodes];
        List<int[]>coordinates=new ArrayList<>();
        int totalPenguins=0;


        for(int i=0;i<nodes;i++)
        {
            int x,y,n,m;
            x=scanner.nextInt();
            y=scanner.nextInt();
            n=scanner.nextInt();
            m=scanner.nextInt();
            numberPenguins[i]=n;
            totalPenguins+=n;
            coordinates.add(new int[]{x,y,m});
        }

        for(int i=0;i<nodes;i++)
        {
            for(int j=i+1;j<nodes;j++)
            {
                int x1,y1,x2,y2;
                x1=coordinates.get(i)[0];
                y1=coordinates.get(i)[1];
                x2=coordinates.get(j)[0];
                y2=coordinates.get(j)[1];
                if(calculateDist(x1,y1,x2,y2)<=maxDistance)
                {
                    edgeList.add(new int[]{i,j,coordinates.get(i)[2]});
                    edgeList.add(new int[]{j,i,coordinates.get(j)[2]});
                }

            }
        }
        
        

        List<Integer>answer=new ArrayList<>();
        for(int k=0;k<nodes;k++)
        {
            Element[]graph=new Element[nodes+1];
        
            for(int i=0;i<nodes+1;i++)
            {
                graph[i]=new Element(i);
            }


            int extraNodes=0;
            

            for(int i=0;i<edgeList.size();i++)
            {
                int u=edgeList.get(i)[0];
                int v=edgeList.get(i)[1];
                int c=edgeList.get(i)[2];
                if(graph[v].getCost(u)!=-1)
                {
                    extraNodes++;
                }
                if(graph[u].getCost(v)!=-1)
                {
                    c+=graph[u].getCost(v);
                    edgeList.get(i)[2]=c;
                }
                graph[u].addEdge(v, c);
            }

            for(int i=0;i<numberPenguins.length;i++)
            {
               if(numberPenguins[i]>0)
               {
                  graph[nodes].addEdge(i, numberPenguins[i]);
               }
            }


            

            int src,des;

            src=nodes;
            des=k;

            int[]total={0};
            int[]flowInc={0};


        


            Element[]residualGraph=new Element[nodes+extraNodes+1];
            for(int i=0;i<residualGraph.length;i++)
            {
                residualGraph[i]=new Element(i);
            }

            int extraNodeTracker=nodes;

            for(int i=0;i<edgeList.size();i++)
            {
                int u=edgeList.get(i)[0];
                int v=edgeList.get(i)[1];
                int c=edgeList.get(i)[2];
                if(graph[v].getCost(u)!=-1 && residualGraph[u].getCost(v)==0)
                {
                    residualGraph[u].addEdge(extraNodeTracker, c);
                    residualGraph[extraNodeTracker].addEdge(u, 0);
                    residualGraph[extraNodeTracker].addEdge(v, c);
                    residualGraph[v].addEdge(extraNodeTracker, 0);
                    extraNodeTracker++;
                }
                else
                {
                    residualGraph[u].addEdge(v, c);
                    residualGraph[v].addEdge(u, 0);
                }
            }

            for(int i=0;i<numberPenguins.length;i++)
            {
               if(numberPenguins[i]>0)
               {
                  residualGraph[nodes].addEdge(i, numberPenguins[i]);
                  residualGraph[i].addEdge(nodes, 0);
               }
            }
            while(hasAugmentingPath(residualGraph,flowInc,src,des))
            {
                total[0]+=flowInc[0];
            }
            if(total[0]==totalPenguins)
            {
                answer.add(k);
            }
        }



        for(int i=0;i<answer.size();i++)
        {
            print(answer.get(i)+"");
        }
       

         






        scanner.close();
    }
}