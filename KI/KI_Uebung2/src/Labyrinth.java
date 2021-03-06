public class Labyrinth {
	private Kachel[][] lab;
	
	public Labyrinth(int hoehe, int laenge){
		lab = new Kachel[hoehe][laenge];
		for (int i = 0; i < hoehe; i++) {
			for (int j = 0; j < laenge; j++) {
				lab[i][j] = new Kachel(""+i+"."+j);
			}
		}
	}
	
	public void createPass(int x, int y, Kachel.Richtung r){
		switch (r) {
		case OBEN:
			lab[y][x].setNachbar(r, lab[y-1][x]);
			lab[y-1][x].setNachbar(Kachel.Richtung.UNTEN, lab[y][x]);
			break;
		case UNTEN:
			lab[y][x].setNachbar(r, lab[y+1][x]);
			lab[y+1][x].setNachbar(Kachel.Richtung.OBEN, lab[y][x]);
			break;
		case RECHTSOBEN:
			if ((x % 2) == 0){
				lab[y][x].setNachbar(r, lab[y-1][x+1]);
				lab[y-1][x+1].setNachbar(Kachel.Richtung.LINKSUNTEN, lab[y][x]);
			} else {
				lab[y][x].setNachbar(r, lab[y][x+1]);
				lab[y][x+1].setNachbar(Kachel.Richtung.LINKSUNTEN, lab[y][x]);
			}
			break;
		case RECHTSUNTEN:
			if ((x % 2) == 0){
				lab[y][x].setNachbar(r, lab[y][x+1]);
				lab[y][x+1].setNachbar(Kachel.Richtung.LINKSOBEN, lab[y][x]);
			} else {
				lab[y][x].setNachbar(r, lab[y+1][x+1]);
				lab[y+1][x+1].setNachbar(Kachel.Richtung.LINKSOBEN, lab[y][x]);
			}
			break;
		case LINKSOBEN:
			if ((x % 2) == 0){
				lab[y][x].setNachbar(r, lab[y-1][x-1]);
				lab[y-1][x-1].setNachbar(Kachel.Richtung.RECHTSUNTEN, lab[y][x]);
			} else {
				lab[y][x].setNachbar(r, lab[y][x-1]);
				lab[y][x-1].setNachbar(Kachel.Richtung.RECHTSUNTEN, lab[y][x]);
			}
			break;
		case LINKSUNTEN:
			if ((x % 2) == 0){
				lab[y][x].setNachbar(r, lab[y][x-1]);
				lab[y][x-1].setNachbar(Kachel.Richtung.RECHTSOBEN, lab[y][x]);
			} else {
				lab[y][x].setNachbar(r, lab[y+1][x-1]);
				lab[y+1][x-1].setNachbar(Kachel.Richtung.RECHTSOBEN, lab[y][x]);
			}
			break;
		default:
			break;
		}
		return;
	}
	
	public Kachel getKachel(int x, int y){
		return lab[y][x];
	}
	
	public static void unittest(){
		Labyrinth l = new Labyrinth(14, 17);
		l.createPass(2, 2, Kachel.Richtung.OBEN);
		l.createPass(2, 2, Kachel.Richtung.RECHTSOBEN);
		l.createPass(2, 2, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(2, 2, Kachel.Richtung.UNTEN);
		l.createPass(2, 2, Kachel.Richtung.LINKSUNTEN);
		l.createPass(2, 2, Kachel.Richtung.LINKSOBEN);
		
		l.createPass(5, 1, Kachel.Richtung.OBEN);
		l.createPass(5, 1, Kachel.Richtung.RECHTSOBEN);
		l.createPass(5, 1, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(5, 1, Kachel.Richtung.UNTEN);
		l.createPass(5, 1, Kachel.Richtung.LINKSUNTEN);
		l.createPass(5, 1, Kachel.Richtung.LINKSOBEN);
		
		System.out.println(l.getKachel(2, 1).getNachbar(Kachel.Richtung.UNTEN)==l.getKachel(2, 2));
		System.out.println(l.getKachel(3, 1).getNachbar(Kachel.Richtung.LINKSUNTEN)==l.getKachel(2, 2));
		System.out.println(l.getKachel(3, 2).getNachbar(Kachel.Richtung.LINKSOBEN)==l.getKachel(2, 2));
		System.out.println(l.getKachel(2, 3).getNachbar(Kachel.Richtung.OBEN)==l.getKachel(2, 2));
		System.out.println(l.getKachel(1, 2).getNachbar(Kachel.Richtung.RECHTSOBEN)==l.getKachel(2, 2));
		System.out.println(l.getKachel(1, 1).getNachbar(Kachel.Richtung.RECHTSUNTEN)==l.getKachel(2, 2));
		
		System.out.println(l.getKachel(5, 0).getNachbar(Kachel.Richtung.UNTEN)==l.getKachel(5, 1));
		System.out.println(l.getKachel(6, 1).getNachbar(Kachel.Richtung.LINKSUNTEN)==l.getKachel(5, 1));
		System.out.println(l.getKachel(6, 2).getNachbar(Kachel.Richtung.LINKSOBEN)==l.getKachel(5, 1));
		System.out.println(l.getKachel(5, 2).getNachbar(Kachel.Richtung.OBEN)==l.getKachel(5, 1));
		System.out.println(l.getKachel(4, 2).getNachbar(Kachel.Richtung.RECHTSOBEN)==l.getKachel(5, 1));
		System.out.println(l.getKachel(4, 1).getNachbar(Kachel.Richtung.RECHTSUNTEN)==l.getKachel(5, 1));
	}
	
	public static Labyrinth createLabyrinth() {
		Labyrinth l = new Labyrinth(4, 7);
		
		l.createPass(0, 0, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(1, 0, Kachel.Richtung.LINKSUNTEN);
		l.createPass(0, 1, Kachel.Richtung.UNTEN);
		l.createPass(0, 2, Kachel.Richtung.UNTEN);
		l.createPass(0, 3, Kachel.Richtung.RECHTSOBEN);
		l.createPass(1, 2, Kachel.Richtung.RECHTSOBEN);
		l.createPass(2, 2, Kachel.Richtung.UNTEN);
		l.createPass(2, 2, Kachel.Richtung.OBEN);
		l.createPass(2, 3, Kachel.Richtung.RECHTSOBEN);
		l.createPass(3, 2, Kachel.Richtung.RECHTSOBEN);
		l.createPass(4, 2, Kachel.Richtung.UNTEN);
		l.createPass(4, 3, Kachel.Richtung.RECHTSOBEN);
		l.createPass(5, 2, Kachel.Richtung.RECHTSUNTEN);

		l.createPass(1, 0, Kachel.Richtung.RECHTSOBEN);
		l.createPass(2, 0, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(3, 0, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(4, 1, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(4, 1, Kachel.Richtung.OBEN); // bla
		l.createPass(4, 1, Kachel.Richtung.UNTEN); // circle!
		l.createPass(5, 1, Kachel.Richtung.RECHTSUNTEN);
		l.createPass(6, 2, Kachel.Richtung.OBEN); // bla
		l.createPass(6, 2, Kachel.Richtung.UNTEN);
		
		return l;
	}
	
	public static void main(String[] args) {
		//unittest();
		Labyrinth l = createLabyrinth();		
		System.out.println("DepthSearch:");
		DepthSearch ds = new DepthSearch();
		try{
			ds.solve(new LabyrinthState(l.getKachel(0, 0)), new LabyrinthState(l.getKachel(6, 3)));
		} catch(Exception e) {
			
		}
				
		l = createLabyrinth(); // resetting visited-values
		System.out.println("BreadthSearch:");
		BreadthSearch bs = new BreadthSearch();
		try{
		bs.solve(new LabyrinthState(l.getKachel(0, 0)), new LabyrinthState(l.getKachel(6, 3)));
		} catch(Exception e) {
			
		}
	}

}
