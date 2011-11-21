################## Aufgabe 5
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

################## Aufgabe 6
# x1 = (1,0)
# x2 = (2,0)
# x3 = (0,1)
# x4 = (2,2)
# x5 = (2,1)

# C = {{x1,x2,x4,x5},{x3}}

# Der Durchmesser von C ist mit D = 1,118 optimal
