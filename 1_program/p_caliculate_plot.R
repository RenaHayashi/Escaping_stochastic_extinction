###############################
# 1. Load package
###############################
library( ggplot2 )

###############################
# 2. differential
###############################
differential <- read.csv("p_caliculate_differential.csv", header = F)
differential <- as.data.frame(differential)
names(differential) <- c("t", "pd")
differential <- differential[49001:50001, 1:2] 

line_size = 1.5
g1 <- ggplot(differential, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=pd),color="#13AA99", size=line_size)+
  ylim(0,1)

ggsave(file = "p_caliculate_differential.png", plot = g1)

###############################
# 3. integral
###############################
integral <- read.csv("p_caliculate_integral.csv", header = F)
integral <- as.data.frame(integral)
names(integral) <- c("t", "pi")

g2 <- ggplot(integral, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=pi), size=line_size)+
  ylim(0,1)

ggsave(file = "p_caliculate_integral.png", plot = g2)

###############################
# 4. integral_10
###############################
integral_10 <- read.csv("p_caliculate_integral_10.csv", header = F)
integral_10 <- as.data.frame(integral_10)
names(integral_10) <- c("t", "pi10")
integral_10 <- integral_10[1:1001,]

g3 <- ggplot(integral_10, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=pi10), size=line_size)+
  ylim(0,1)

ggsave(file = "p_caliculate_integral_10.png", plot = g3)

###############################
# 4. integral_20
###############################
integral_20 <- read.csv("p_caliculate_integral_20.csv", header = F)
integral_20 <- as.data.frame(integral_20)
names(integral_20) <- c("t", "pi20")
integral_20 <- integral_20[1:1001,]

g3 <- ggplot(integral_20, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=pi20), size=line_size)+
  ylim(0,1)

ggsave(file = "p_caliculate_integral_20.png", plot = g3)

###############################
# 5. all
###############################
differential <- differential[order(differential$t),]
both <- as.data.frame(cbind(differential, integral[,2]))
both <- as.data.frame(cbind(both, integral_10[,2]))
# both <- as.data.frame(cbind(both, integral_20[,2]))
names(both) <- c("t", "pd", "pi", "pi10")

g3 <- ggplot(both, aes(x=t))+
  theme_bw()+
  labs(x = "t",y = "p(t)") +
  geom_line(aes(y=pd),color="#008970", size=line_size)+
  geom_line(aes(y=pi),color="#003d41", size=line_size)+
  # geom_line(aes(y=pi10),color="#003a41", size=line_size)+
  # geom_line(aes(y=pi20),color="#003a41", size=line_size)+
  ylim(0,1)

ggsave(file = "p_integral_differential.png", plot = g3)
