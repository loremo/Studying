import java.util.ArrayList;


public class SokobanState implements State {
		
	private State parent; // parent state from which this state was derived
	private Cell[][] game;
	public static ArrayList<SokobanState> visited = new ArrayList<SokobanState>();
	private Cords hero = new Cords();
	
	class Cords {
		public int x,y;
	};
	
	enum Cell{
		HERO,BOX,SPACE,WALL,GOAL,HERO_GOAL,BOX_GOAL
	}
	
	enum Direction{
		DOWN,LEFT,UP,RIGHT
	}
	
	public SokobanState(Cell[][] g){
		game = g;
		for(int i = 0; i < game.length; ++i){
			for(int j = 0; j < game[0].length; ++j){
				if (game[i][j] == Cell.HERO || game[i][j] == Cell.HERO_GOAL){
					hero.x = j;
					hero.y = i;
				}				
			}			
		}
	}
		
	public Cell[][] move(int x, int y){
		Cell[][] g = null;
		Cell after; 
			try {
				after = game[hero.y][hero.x]==Cell.HERO_GOAL?Cell.GOAL:Cell.SPACE; // What remains in the cell the hero used to be after he has moved?
				if(game[hero.y+y][hero.x+x] == Cell.SPACE){
					g = getGame();
					g[hero.y+y][hero.x+x] = Cell.HERO;
					g[hero.y][hero.x] = after;
				}
				else if(game[hero.y+y][hero.x+x] == Cell.GOAL){
					g = getGame();
					g[hero.y+y][hero.x+x] = Cell.HERO_GOAL;
					g[hero.y][hero.x] = after;
				}
				else if(game[hero.y+y][hero.x+x] == Cell.BOX){
					if(game[hero.y+(2*y)][hero.x+(2*x)] == Cell.SPACE){
						g = getGame();
						g[hero.y+(2*y)][hero.x+(2*x)] = Cell.BOX;
						g[hero.y+y][hero.x+x] = Cell.HERO;
						g[hero.y][hero.x] = after;
					}
					else if(game[hero.y+(2*y)][hero.x+(2*x)] == Cell.GOAL){
						g = getGame();
						g[hero.y+(2*y)][hero.x+(2*x)] = Cell.BOX_GOAL;
						g[hero.y+y][hero.x+x] = Cell.HERO;
						g[hero.y][hero.x] = after;
					}
				}
				else if (game[hero.y+y][hero.x+x] == Cell.BOX_GOAL){
					if(game[hero.y+(2*y)][hero.x+(2*x)] == Cell.SPACE){
						g = getGame();
						g[hero.y+(2*y)][hero.x+(2*x)] = Cell.BOX;
						g[hero.y+y][hero.x+x] = Cell.HERO_GOAL;
						g[hero.y][hero.x] = after;
					}
					else if(game[hero.y+(2*y)][hero.x+(2*x)] == Cell.GOAL){
						g = getGame();
						g[hero.y+(2*y)][hero.x+(2*x)] = Cell.BOX_GOAL;
						g[hero.y+y][hero.x+x] = Cell.HERO_GOAL;
						g[hero.y][hero.x] = after;
					}
				}
			} catch(Exception e) {
			}
			return g;
	}

	@Override
	public void setParent(State s) {
		this.parent = s;
		
	}

	@Override
	public State getParent() {
		return parent;
	}

	public Cell[][] getGame(){
		Cell[][] g = new Cell[game.length][game[0].length];
		for(int i = 0; i < game.length; ++i){
			for(int j = 0; j < game[0].length; ++j){
				g[i][j] = game[i][j];			
			}			
		}
		return g;
	}
	
	public String toString(){
		return "X: " + (hero.x+1) + " Y: " + (hero.y+1) + "\n";
	}

	@Override
	public ArrayList<State> getFollowingStates() {
		ArrayList<State> stateList = new ArrayList<State>();
		for (Direction direction : Direction.values()){
			Cell[][] tmp;
			switch (direction) {
			case UP:
				tmp = move(0, -1); 
				if(tmp != null){
					State nextState = new SokobanState(tmp);
					if(!nextState.visited())
						stateList.add(new SokobanState(tmp));
				}
				break;
			case RIGHT:
				tmp = move(1, 0); 
				if(tmp != null){
					State nextState = new SokobanState(tmp);
					if(!nextState.visited())
						stateList.add(new SokobanState(tmp));
				}
				break;
			case DOWN:
				tmp = move(0, 1); 
				if(tmp != null){
					State nextState = new SokobanState(tmp);
					if(!nextState.visited())
						stateList.add(new SokobanState(tmp));
				}
				break;
			case LEFT:
				tmp = move(-1, 0); 
				if(tmp != null){
					State nextState = new SokobanState(tmp);
					if(!nextState.visited())
						stateList.add(new SokobanState(tmp));
				}
				break;
			default:
				break;
			}
		}
		return stateList;
	}

	static boolean  first = true;
	@Override
	public void setVisited(boolean b) {
		if (first){
			visited.add(this);
			first = false;
		}
		if (!visited.contains(this))
			visited.add(this);
	}

	@Override
	public boolean visited() {
		for (State s : visited){
			if (s.equals(this))
				return true;
		}
		return false;
	}
	
	@Override
	public boolean equals(Object o) {
		for(int i = 0; i < game.length; ++i){
			for(int j = 0; j < game[0].length; ++j){
				if(game[i][j] != ((SokobanState)o).getGame()[i][j]){
					return false;
				}
			}			
		}
		return true;
	}

	public static void main(String[] args) {
		Cell[][] start = {	{Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.HERO,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.BOX,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.WALL,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.GOAL,Cell.WALL},
							{Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL}};
		
		Cell[][] finish = {	{Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.WALL,Cell.HERO,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.BOX_GOAL,Cell.WALL},
							{Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL}};
		
		DepthSearch ds = new DepthSearch();
		new SokobanState(start).setVisited(true);
		ds.solve(new SokobanState(start), new SokobanState(finish));
		
		SokobanState.visited = new ArrayList<SokobanState>();
		
		BreadthSearch bs = new BreadthSearch();
		bs.solve(new SokobanState(start), new SokobanState(finish));
		
		//SokobanState.visited = new ArrayList<SokobanState>();		
		//bs.getSolution();
	}
}
