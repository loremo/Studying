import java.util.ArrayList;

public class LabyrinthState implements State {
	
	private Kachel kachel;
	private State parent;	
	
	public LabyrinthState(Kachel k){
		kachel = k;
	}
	
	public Kachel getKachel(){
		return kachel;
	}	
	
	public String toString(){
		return kachel.getName() + " ";
	}

	@Override
	public boolean equals(Object o) {
		return this.kachel == ((LabyrinthState)o).getKachel();
	}

	@Override
	public ArrayList<State> getFollowingStates() {
		ArrayList<State> retList = new ArrayList<State>();
		if (kachel.getNachbar(Kachel.Richtung.OBEN) != null)
			if(!kachel.getNachbar(Kachel.Richtung.OBEN).getFlag())
				retList.add(new LabyrinthState(kachel.getNachbar(Kachel.Richtung.OBEN)));
		if (kachel.getNachbar(Kachel.Richtung.UNTEN) != null)
			if(!kachel.getNachbar(Kachel.Richtung.UNTEN).getFlag())
				retList.add(new LabyrinthState(kachel.getNachbar(Kachel.Richtung.UNTEN)));
		if (kachel.getNachbar(Kachel.Richtung.RECHTSOBEN) != null)
			if(!kachel.getNachbar(Kachel.Richtung.RECHTSOBEN).getFlag())
				retList.add(new LabyrinthState(kachel.getNachbar(Kachel.Richtung.RECHTSOBEN)));
		if (kachel.getNachbar(Kachel.Richtung.RECHTSUNTEN) != null)
			if(!kachel.getNachbar(Kachel.Richtung.RECHTSUNTEN).getFlag())
				retList.add(new LabyrinthState(kachel.getNachbar(Kachel.Richtung.RECHTSUNTEN)));
		if (kachel.getNachbar(Kachel.Richtung.LINKSOBEN) != null)
			if(!kachel.getNachbar(Kachel.Richtung.LINKSOBEN).getFlag())
				retList.add(new LabyrinthState(kachel.getNachbar(Kachel.Richtung.LINKSOBEN)));
		if (kachel.getNachbar(Kachel.Richtung.LINKSUNTEN) != null)
			if(!kachel.getNachbar(Kachel.Richtung.LINKSUNTEN).getFlag())
				retList.add(new LabyrinthState(kachel.getNachbar(Kachel.Richtung.LINKSUNTEN)));
		return retList;
	}

	@Override
	public void setVisited() {
		kachel.setFlag();
		
	}

	@Override
	public boolean visited() {
		return kachel.getFlag();
	}

	@Override
	public void setParent(State s) {
		parent = s;
		
	}

	@Override
	public State getParent() {
		return parent;
	}
}
