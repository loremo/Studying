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
		UP,RIGHT,DOWN,LEFT
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
		
	// Hero's movement logic
	public Cell[][] move(int x, int y){
		Cell[][] g = null; // doesn't change the state of the current game, but returns a new game!
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

	public Cell[][] getGame(){
		Cell[][] g = new Cell[game.length][game[0].length];
		for(int i = 0; i < game.length; ++i){
			for(int j = 0; j < game[0].length; ++j){
				g[i][j] = game[i][j];			
			}			
		}
		return g;	// return by value
	}
	
	public String toString(){
		return "X: " + (hero.x+1) + " Y: " + (hero.y+1) + "\n";
	}

	@Override
	public void setParent(State s) {
		this.parent = s;		
	}

	@Override
	public State getParent() {
		return parent;
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

	@Override
	public void setVisited() {
		if (!visited.contains(this))
			visited.add(this);
	}

	@Override
	public boolean visited() {
		if (visited.contains(this))
			return true;
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
		Cell[][] start = {	{Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.HERO,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.BOX,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.GOAL,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL},};
		
		Cell[][] finish = {	{Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.WALL,Cell.SPACE,Cell.HERO,Cell.WALL},
							// if you place the hero left to the goal, BreadthSearch need more time than DepthSearch!
							{Cell.WALL,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.SPACE,Cell.BOX_GOAL,Cell.WALL},
							{Cell.WALL,Cell.SPACE,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL,Cell.WALL},};
		
		System.out.println("DepthSearch:");
		DepthSearch ds = new DepthSearch();
		long time = System.currentTimeMillis();
		try{
			ds.solve(new SokobanState(start), new SokobanState(finish));
		} catch(Exception e){
		}
		System.out.println("Execution time: " + (System.currentTimeMillis() - time));
		
		// flush the list of visited states (because its static)
		SokobanState.visited = new ArrayList<SokobanState>();

		System.out.println("BreadthSearch:");
		BreadthSearch bs = new BreadthSearch();
		time = System.currentTimeMillis();
		try{
			bs.solve(new SokobanState(start), new SokobanState(finish));
		} catch(Exception e){
		}
		System.out.println("Execution time: " + (System.currentTimeMillis() - time));
	}
}
