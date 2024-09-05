//530
import java.awt.Frame;
import java.awt.Point;
import java.util.ArrayList;
import java.awt.Graphics;
import java.awt.MenuBar;
import java.awt.Menu;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.util.Iterator;

public class Test20 extends Frame{
	private final static int POINT=0;
	private final static int LINE=1;
	private final static int RECTANGLE=2;
	private final static int OVAL=3;
	
	private int type;
	Point p1;
	Point p2;
	ArrayList<Point> points = new ArrayList<Point>();
	
	ArrayList<DrawPoint> area = new ArrayList<DrawPoint>();
	
	public Test20(String s){
		super(s);
	}
	
	public void mainFrame(){
		MenuBar menuBar = new MenuBar();
		Menu menu = new Menu("菜单");
		MenuItem fmi4 = new MenuItem("Exit");
		fmi4.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.exit(0);
			}
		});
		menu.addSeparator();
		menu.add(fmi4);
		Menu mtype = new Menu("画笔种类");
		MenuItem menuItem = new MenuItem("点状");
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				type = Test20.POINT;
			}
		});
		MenuItem menuItem2 =new MenuItem("线状");
		menuItem2.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				type = Test20.LINE;
			}
		});
		MenuItem dmi3 = new MenuItem("矩形");
		dmi3.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				type = Test20.RECTANGLE;
			}
		});
		MenuItem dmi4 = new MenuItem("圆形");
		dmi4.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				type = Test20.OVAL;
			}
		});
		mtype.add(menuItem);
		mtype.add(menuItem2);
		mtype.add(dmi3);
		mtype.add(dmi4);
		menuBar.add(menu);
		menuBar.add(mtype);
		setMenuBar(menuBar);
		addWindowListener(new WindowAdapter(){
			public void mousePressed(WindowAdapter e){
				System.exit(0);
			}
		});
		addMouseListener(new MouseAdapter(){
			public void mousePressed(MouseEvent e){
				p1=new Point(e.getX(),e.getY());
				if(type==Test20.POINT){
					points.add(p1);
					repaint();
				}
			}
			public void mouseReleased(MouseEvent e){
				if(type != Test20.POINT){
					p2=new Point(e.getX(),e.getY());
					area.add(new DrawPoint(p1,p2,type));
					repaint();
				}
			}
		});
		setBounds(50,50,640,480);
		setBackground(Color.WHITE);
		setVisible(true);
	}
	public void paint(Graphics g){
		Iterator<Point> ip =points.iterator();
		g.setColor(Color.black);
		while(ip.hasNext()){
			Point p =ip.next();
			g.fillOval(p.x,p.y,10,10);
		}
		int x1,x2,y1,y2;
		for(Iterator<DrawPoint> ipp =area.iterator();ipp.hasNext();){
			DrawPoint pp =ipp.next();
			x1=(int)pp.startPoint.getX();
			y1=(int)pp.startPoint.getY();
			x2=(int)pp.startPoint.getX();
			y2=(int)pp.startPoint.getY();
			switch(pp.type){
				case LINE:
				g.setColor(Color.green);
				g.drawLine(x1,y1,x2,y2);
				break;
				case RECTANGLE:
				g.setColor(Color.red);
				g.drawRect(x1,y1,x2-x1,y2-y1);
				break;
				case OVAL:
				g.setColor(Color.blue);
				g.drawOval(x1,y1,x2-x1,y2-y1);
				break;
				default:
				break;
			}
		}
	}
	public static void main(String[] args){
		Test20 drawApp = new Test20("多功能彩色画笔");
		drawApp.mainFrame();
	}
}
class DrawPoint{
	public Point startPoint;
	public Point endPoint;
	public int type;
	public DrawPoint(Point sPoint,Point ePoint,int drawType){
		startPoint = sPoint;
		endPoint = ePoint;
		type = drawType;
	}
}