###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. Read data
###############################
x_caliculation <- read.csv("x_caliculate_drug.csv", header = F)
p_caliculation <- read.csv("p_caliculate_differential_drug_bm.csv", header = F)

x_caliculation <- as.data.frame(x_caliculation)
names(x_caliculation) <- c("t", "x", "y")
x_caliculation <- x_caliculation[1:1001,]

p_caliculation <- as.data.frame(p_caliculation)
names(p_caliculation) <- c("t", "p")
p_caliculation <- p_caliculation[order(p_caliculation$t,decreasing = FALSE),]

p_caliculation <- p_caliculation[1:1001,]

data <- cbind(x_caliculation, p_caliculation[1:1001,2])
names(data) <- c("t", "x", "y", "p")
###############################
###############################
length_data <- nrow(data)
for (i in 1:length_data) {
  
  if(data[i,1]>6){
    b = 0
  }else{
    b = 2.5*10^-4
  }
  
  x <- data[i,2]
  y <- data[i,3]
  p <- data[i,4]
  bxyp = b*x*y*p
  data[i,5] <- bxyp
}

max <- which.max(data$bxyp)
names(data) <- c("t", "x", "y", "p", "bxyp")

###############################
# 4. Plot
###############################

g0 <- ggplot(data, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "b'xyp") +
  geom_line(aes(y=bxyp), size=line_size)+
  ylim(0,20000)

ggsave(file = "bxyp_drug_bm.png", plot = g0)

