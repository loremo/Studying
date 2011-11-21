################## Aufgabe 1
v <- read.csv("data1.csv", header=TRUE)
d <- dist(v)
d <- d*d
d

single <- hclust(d, method="single")
png(filename="singleLinkage.png")
plot(single)

complete <- hclust(d, method="complete")
png(filename="completeLinkage.png")
plot(complete)

average <- hclust(d, method="aver")
png(filename="groupAverage.png")
plot(average)

centroid <- hclust(d, method="centroid")
png(filename="centroid.png")
plot(centroid)

ward <- hclust(d, method="ward")
png(filename="ward.png")
plot(ward)
