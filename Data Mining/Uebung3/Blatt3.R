################## Aufgabe 8

# liefert den schwerpunkt(vektor) einer matrix zurück
schwerpunkt <- function(x) {
  ret <- numeric()
  for( i in 1:length(x[1,]) ) {
    ret <- append(ret, sum(x[,i]) / length(x[,i]))
  }
  return(ret)
}

# liefert die summe der quadrate der differenzen zum schwerpunkt zurück
varianzsumme <- function(list){
  ret <- 0
  for( name in 1:length(list) ) {
    c <- schwerpunkt(list[[name]])
    for(i in 1:length(list[[name]][,1])){
      for(j in 1:length(list[[name]][1,])){
	ret = ret + (list[[name]][i,j] - c[j]) * (list[[name]][i,j] - c[j])
      }
    }
  }
  return(ret)
}

# führt einen vertauschungsschritt aus und liefert eine liste mit den 
# vertauschten clustern zurück (falls vertauschung stattgefunden hat.
# anderenfalls wird die gleiche liste zurückgegeben)
vertauschen <- function(list){
  VarianzSummenKMinimum <- varianzsumme(list)
  ret <- list
  for( nameAussen in 1:length(list) ) {
    for(i in 1:length(list[[nameAussen]][,1])){
      Vektor_nach_Abspaltung <- list[[nameAussen]][-i,]
      N_MIN <- 0
      if (length(Vektor_nach_Abspaltung[,1]) >= N_MIN) {
	wanderndes_Element <- list[[nameAussen]][i,]
	for( nameInnen in 1:length(list) ) {
	  if (nameInnen != nameAussen){
	    Vektor_nach_Vereinigung <- rbind(list[[nameInnen]], wanderndes_Element)
	    tmp <- list
	    tmp[[nameAussen]] <- Vektor_nach_Abspaltung
	    tmp[[nameInnen]] <- Vektor_nach_Vereinigung
	    if (varianzsumme(tmp) < VarianzSummenKMinimum){
	      VarianzSummenKMinimum <- varianzsumme(tmp)
	      ret <- tmp
	    }
	  }
	}
      }
    }
  }
  return(ret)
}



v <- read.csv("80X.csv", header=FALSE)
indezes <- 1:length(v[,1])
indezes <- sample(indezes) # random permutation
data <- numeric()

for (i in 1:length(v[,1])){
  data <- rbind(data, v[indezes[i],])
}

liste <- split(data, 1:3)

varianzLetzterSchritt <- varianzsumme(liste)
aktuelleVarianz <- -1
varianzvektor <- numeric()
print("Anfangsvarianz:")
while (aktuelleVarianz < varianzLetzterSchritt){
  varianzvektor <- rbind(varianzvektor, varianzLetzterSchritt)
  varianzLetzterSchritt <- varianzsumme(liste)
  print(varianzLetzterSchritt)
  liste <- vertauschen(liste)
  aktuelleVarianz <- varianzsumme(liste)
}

liste

plot(varianzvektor)
