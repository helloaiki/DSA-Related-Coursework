import java.io.IOException;
import java.io.InputStream;
import java.util.*;

class Element
    {
        int id;
        List<Integer>neighbour;
        List<Double>weight;
        public Element(int id)
        {
            this.id=id;
            neighbour=new ArrayList<>();
            weight=new ArrayList<>();
        }
        public void addNeighbour(int v,double w)
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

public class Arbitrage
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
       double nextDouble() throws IOException
        {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            double val = 0.0;
            while (c >= '0' && c <= '9') {
                val = val * 10 + (c - '0');
                c = read();
            }

            if (c == '.') {
                double div = 1.0;
                c = read();
                while (c >= '0' && c <= '9') {
                    div *= 10;
                    val += (c - '0') / div;
                    c = read();
                }
            }

            return val * sign;
        }

    }
    public static void main(String[]args)throws Exception
    {
        FS fs=new FS();
        int currencies;
        currencies=fs.nextInt();

        HashMap<String,Integer>mapping=new HashMap<>();
        Element[]elements=new Element[currencies];
        double[][]a=new double[currencies][currencies];
        boolean[][]canVisit=new boolean[currencies][currencies];

        for(int i=0;i<currencies;i++)
        {
            String currency=fs.next();
            mapping.put(currency,i);
            elements[i]=new Element(i);
        }

        
        int transfers=fs.nextInt();

        for(int i=0;i<transfers;i++)
        {
            String from,to;
            double amount;
            from=fs.next();
            amount=fs.nextDouble();
            to=fs.next();
            if(amount!=0)
            {
                amount=-Math.log(amount);
                elements[mapping.get(from)].addNeighbour(mapping.get(to), amount);  
                a[mapping.get(from)][mapping.get(to)]=amount;
                canVisit[mapping.get(from)][mapping.get(to)]=true;
            }
        }

        for(int inner=0;inner<currencies;inner++)
        {
            for(int i=0;i<currencies;i++)
            {
                for(int j=0;j<currencies;j++)
                {
                    if(canVisit[i][inner] && canVisit[inner][j])
                    {
                        if(!canVisit[i][j])
                        {
                            a[i][j]=a[i][inner]+a[inner][j];
                            canVisit[i][j]=true;
                        }
                        else
                        {
                            a[i][j]=Math.min(a[i][j],a[i][inner]+a[inner][j]);
                        }
                    }
                }
            }
        }

        for(int i=0;i<currencies;i++)
        {
            if((-a[i][i])>0)
            {
                System.out.println("Yes");
                return;

            }
        }

        System.out.println("No");




    }
}