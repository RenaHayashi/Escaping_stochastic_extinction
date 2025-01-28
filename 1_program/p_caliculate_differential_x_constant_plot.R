###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. Load data
###############################
p_caliculate <- read.csv("p_caliculate_differential_x_constant.csv", header = F)
p_caliculate <- as.data.frame(p_caliculate)
t <- as.data.frame(p_caliculate[1:1001,1])
x5 <- as.data.frame(p_caliculate[1:1001,2])
x5_5 <- as.data.frame(p_caliculate[1002:2002,2])
x6 <- as.data.frame(p_caliculate[2003:3003,2])
x6_5 <- as.data.frame(p_caliculate[3004:4004,2])
x7 <- as.data.frame(p_caliculate[4005:5005,2])

data <- cbind(t, x5)
data <- cbind(data, x5_5)
data <- cbind(data, x6)
data <- cbind(data, x6_5)
data <- cbind(data, x7)

names(data) <- c("t", "x5", "x5_5", "x6", "x6_5", "x7")


g <- ggplot(data, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=x5),color="#58B8FA")+
  # geom_line(aes(y=x5_5),color="#4E7DDE")+
  geom_line(aes(y=x6),color="#626DF5")+
  geom_line(aes(y=x6_5),color="#6B4EDE")+
  geom_line(aes(y=x7),color="#A558FA")+
  ylim(0,1)

ggsave(file = "p_caliculate_differential_x_constant.png", plot = g)
