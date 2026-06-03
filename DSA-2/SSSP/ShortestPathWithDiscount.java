import java.util.*;
//this keeps track of the nodes neighbours and respective edge weights
class Node
{
    private int id;
    public HashMap<Integer,Integer>neighbours;
    public Node(int id)
    {
        this.id=id;
        neighbours=new HashMap<>();
    }
    public int getId()
    {
        return id;
    }
    
    public void addNeighbour(int node,int weight)
    {
        neighbours.put(node,weight);
    }

    public void showNeighbours()
    {
        Iterator<Map.Entry<Integer, Integer>> it = neighbours.entrySet().iterator();
            while (it.hasNext()) 
            {
               Map.Entry<Integer, Integer> entry = it.next();
               System.out.println("Edge "+entry.getKey()+" Val "+entry.getValue());
            }
    }
}
//for priority queue

class NodeVal implements Comparable<NodeVal>
{
    private int id;
    private int distance;
    boolean halved;
    public NodeVal(int id,int d,boolean response)
    {
        this.id=id;
        distance=d;
        halved=response;
    }

    public int getDistance()
    {
        return distance;
    }

    public int getId()
    {
        return id;
    }

    public boolean hasBeenHalved()
    {
        return halved;
    }

    @Override

    public int compareTo(NodeVal nv)
    {
        return Integer.valueOf(distance).compareTo(Integer.valueOf(nv.distance));
    }


}




public class ShortestPathWithDiscount
{
    public static void main(String[]args)
    {
        Scanner scanner=new Scanner(System.in);

        int numberOfNodes,numberOfEdges;
        //number of nodes and edges input
        numberOfNodes=scanner.nextInt();
        numberOfEdges=scanner.nextInt();
        boolean[]visited=new boolean[numberOfNodes+1]; //visited-popped from priority queue 
        boolean[]visitedButNotDequeued=new boolean[numberOfNodes+1]; //for infinity check- IS NOT THE SAME AS VISITED
        

        PriorityQueue<NodeVal>pq=new PriorityQueue<>();//priority queue
        Node[]nodes=new Node[numberOfNodes];//basically neighbour tracker. Gives neighbours when needed. Node 1 corresponds to array 0 index

        for(int i=0;i<numberOfNodes;i++)
        {
            nodes[i]=new Node(i+1);
        }
         
        //entering all neighbours to respective edges
        for(int i=0;i<numberOfEdges;i++)
        {
            int from,to,weight;
            from=scanner.nextInt();
            to=scanner.nextInt();
            weight=scanner.nextInt();
            nodes[from-1].addNeighbour(to, weight);
        }




        int[]distanceFromSource=new int[numberOfNodes+1];//actual distance from source. One to one correspondence

        NodeVal start=new NodeVal(1, 0, false);//starting node
        visitedButNotDequeued[1]=true;
        pq.add(start);
        

        while(!pq.isEmpty())
        {
            NodeVal poppedNode=pq.poll();
            int index=poppedNode.getId()-1;
            int parentIndex=poppedNode.getId();
            
            visited[parentIndex]=true;
            HashMap<Integer,Integer>neighbours=nodes[index].neighbours;
            Iterator<Map.Entry<Integer, Integer>> it = neighbours.entrySet().iterator();
            while (it.hasNext()) 
            {
               Map.Entry<Integer, Integer> entry = it.next();
               int to=entry.getKey();
               int weight=entry.getValue();
               if(!visited[to])
               {
                   if(visitedButNotDequeued[to])
                   {
                        
                        if(poppedNode.hasBeenHalved())
                        {
                            int distanceFromThisParent=poppedNode.getDistance()+weight;
                            
                            NodeVal newNode=new NodeVal(to, distanceFromThisParent, true);
                            pq.add(newNode);
                            if(distanceFromSource[to]>distanceFromThisParent)
                            {
                                distanceFromSource[to]=distanceFromThisParent;
                            }
                        }
                        else
                        {
                            
                            
                            int distanceFromThisParent=Math.min(poppedNode.getDistance()+weight,poppedNode.getDistance()+(int)Math.floor(weight/2));
                            
                            NodeVal newNode1=new NodeVal(to, poppedNode.getDistance()+weight, false);
                            NodeVal newNode2=new NodeVal(to, poppedNode.getDistance()+(int)Math.floor(weight/2), true);
                            
                            pq.add(newNode1);
                            pq.add(newNode2);
                            if(distanceFromThisParent<distanceFromSource[to])
                            {
                                distanceFromSource[to]=Math.min(newNode1.getDistance(),newNode2.getDistance());
                            }
                        }
                        
                   }
                   else
                   {
                      if(poppedNode.hasBeenHalved())
                        {
                                
                                int distanceFromThisParent=poppedNode.getDistance()+weight;
                                distanceFromSource[to]=distanceFromThisParent;
                                NodeVal newNode=new NodeVal(to, distanceFromThisParent, true);
                                pq.add(newNode);
                        }
                        else
                        {
                                NodeVal newNode1=new NodeVal(to, poppedNode.getDistance()+weight, false);
                                NodeVal newNode2=new NodeVal(to, poppedNode.getDistance()+(int)Math.floor(weight/2), true);
                                distanceFromSource[to]=Math.min(newNode1.getDistance(),newNode2.getDistance());
                                pq.add(newNode1);
                                pq.add(newNode2);
                        }  

                        visitedButNotDequeued[to]=true;
                      
                   }
               }
            }
        }


        System.out.println(distanceFromSource[numberOfNodes]);


        scanner.close();
    }
}