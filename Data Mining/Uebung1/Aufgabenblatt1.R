################## Aufgabe 1
v <- read.csv("data1.csv", header=TRUE)
Haeuf <- table(v)

png(filename="piechart.png")
pie(Haeuf)

png(filename="frequencydiagramm.png")
plot(Haeuf, main="Frequency Diagramm", xlab="Value", ylab="Frequency")

png(filename="barchart.png")
barplot(Haeuf, horiz=TRUE)

################## Aufgabe 2
# Modalwert
names(which.max(Haeuf))

# Median
if((length(v[,1]) %% 2) == 0) {
  median <-(v[floor(length(v[,1])/2),1]+v[(floor(length(v[,1])/2))+1,1]) * 0.5
} else {
  median <- v[length(v[,1])/2,1]
}
median

# 1/5-Quantil
quantile(v[,1], probs = 0.2)

# Arithmetisches Mittel
mean(v[,1])

# Spannweite
max(v[,1]) - min(v[,1])

# Interquartilbereich
quantile(v[,1], probs = 0.75) - quantile(v[,1], probs = 0.25)

# Varianz
var(v[,1])

# Standardabweichung
sqrt(var(v[,1]))

# Box-Plot
png(filename="boxplot.png")
boxplot(v[,1])

################## Aufgabe 3
v <- read.csv("data2.csv", header=TRUE)
cor(v[,1], v[,2])
